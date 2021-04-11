#include "core.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>

GDCALLINGCONV void *core_constructor(godot_object *p_instance, void *p_method_data)
{
    Library *lib = p_method_data;

    Core *core = lib->core_api->godot_alloc(sizeof(Core));
    memset(core, 0, sizeof(Core));

    core->object = p_instance;
    core->lib    = lib;

    return core;
}

GDCALLINGCONV void core_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib = p_method_data;
    Core *core   = p_user_data;

    if (core->users)
        lib->core_api->godot_object_destroy(core->users->object);
    if (core->images)
        lib->core_api->godot_object_destroy(core->images->object);
    if (core->activities)
        lib->core_api->godot_object_destroy(core->activities->object);
    if (core->relationships)
        lib->core_api->godot_object_destroy(core->relationships->object);

    if (core->hook_data)
    {
        if (core->hook_data->callback_object)
            lib->core_api->godot_string_destroy(&core->hook_data->callback_name);
        lib->core_api->godot_free(core->hook_data);
    }

    if (core->internal)
    {
        core->internal->destroy(core->internal);
        lib->core_api->godot_free(core->user_events);
        lib->core_api->godot_free(core->activity_events);
        lib->core_api->godot_free(core->relationship_events);
    }

    lib->core_api->godot_free(core);
}

godot_variant core_create(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                          godot_variant **p_args)
{
    Library *lib = p_method_data;
    Core *core   = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 2 || p_num_args == 3)
    {
        uint64_t id           = lib->core_api->godot_variant_as_uint(p_args[0]);
        uint64_t create_flags = lib->core_api->godot_variant_as_uint(p_args[1]);
        if (p_num_args == 3)
        {
            uint64_t instance_id = lib->core_api->godot_variant_as_uint(p_args[2]);
            char instance[128];
            memset(instance, 0, sizeof(char) * 128);
            sprintf(instance, "%lu", instance_id);
#ifdef _WIN32
            _putenv_s("DISCORD_INSTANCE_ID", instance);
#else
            setenv("DISCORD_INSTANCE_ID", instance, true);
#endif
        }

        struct DiscordCreateParams params;
        memset(&params, 0, sizeof(struct DiscordCreateParams));
        DiscordCreateParamsSetDefault(&params);
        params.client_id  = id;
        params.event_data = core;
        params.flags      = create_flags;

        core->user_events                         = lib->core_api->godot_alloc(sizeof(struct IDiscordUserEvents));
        core->user_events->on_current_user_update = on_current_user_update;
        params.user_events                        = core->user_events;

        core->activity_events                       = lib->core_api->godot_alloc(sizeof(struct IDiscordActivityEvents));
        core->activity_events->on_activity_join     = on_activity_join;
        core->activity_events->on_activity_spectate = on_activity_spectate;
        core->activity_events->on_activity_join_request = on_activity_join_request;
        core->activity_events->on_activity_invite       = on_activity_invite;
        params.activity_events                          = core->activity_events;

        core->relationship_events             = lib->core_api->godot_alloc(sizeof(struct IDiscordRelationshipEvents));
        core->relationship_events->on_refresh = on_refresh;
        core->relationship_events->on_relationship_update = on_relationship_update;
        params.relationship_events                        = core->relationship_events;

        enum EDiscordResult result = DiscordCreate(DISCORD_VERSION, &params, &core->internal);

        if (result != DiscordResult_Ok)
            core->internal = NULL;

        lib->core_api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"create()\" call. Expected 2 or 3.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

void log_hook(void *p_callback_data, enum EDiscordLogLevel p_level, const char *p_message)
{
    CallbackData *data = p_callback_data;
    Library *lib       = data->lib;
    Core *core         = data->data;

    godot_variant level_variant;
    godot_variant message_variant;

    lib->core_api->godot_variant_new_int(&level_variant, p_level);

    godot_string message_string = lib->core_api->godot_string_chars_to_utf8(p_message);
    lib->core_api->godot_variant_new_string(&message_variant, &message_string);

    const godot_variant *args[] = {&level_variant, &message_variant};

    if (data->callback_object)
    {
        if (lib->core_1_1_api->godot_is_instance_valid(data->callback_object))
            object_call(data->callback_object, &data->callback_name, 2, args, NULL, lib);
        else
            PRINT_ERROR("Callback object is no longer a valid instance.", lib);
    }

    godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("log_hook");
    object_emit_signal(core->object, &signal_name, 2, args, lib);

    lib->core_api->godot_string_destroy(&signal_name);
    lib->core_api->godot_string_destroy(&message_string);
    lib->core_api->godot_variant_destroy(&message_variant);
    lib->core_api->godot_variant_destroy(&level_variant);
}

godot_variant core_set_log_hook(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                                godot_variant **p_args)
{
    Library *lib = p_method_data;
    Core *core   = p_user_data;

    godot_variant result_variant;

    if (!core->internal)
    {
        PRINT_ERROR("Attempted to run method on unitialised Core, make sure you have run \"create\" first.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
        return result_variant;
    }

    if (p_num_args == 1 || p_num_args == 3) // Min Level, [Hook Object, Hook Method]
    {
        int64_t min_level = lib->core_api->godot_variant_as_int(p_args[0]);

        if (!core->hook_data)
            core->hook_data = lib->core_api->godot_alloc(sizeof(CallbackData));
        else if (core->hook_data->callback_object)
            lib->core_api->godot_string_destroy(&core->hook_data->callback_name);

        memset(core->hook_data, 0, sizeof(CallbackData));
        core->hook_data->lib  = lib;
        core->hook_data->data = core;

        if (p_num_args == 3)
        {
            godot_object *hook_object        = lib->core_api->godot_variant_as_object(p_args[1]);
            godot_string hook_method         = lib->core_api->godot_variant_as_string(p_args[2]);
            core->hook_data->callback_name   = hook_method;
            core->hook_data->callback_object = hook_object;
        }

        core->internal->set_log_hook(core->internal, min_level, core->hook_data, log_hook);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"set_log_hook()\" call. Expected 1 or 3.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant core_run_callbacks(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                                 godot_variant **p_args)
{
    Library *lib = p_method_data;
    Core *core   = p_user_data;

    godot_variant result_variant;

    if (!core->internal)
    {
        PRINT_ERROR("Attempted to run method on unitialised Core, make sure you have run \"create\" first.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
        return result_variant;
    }

    enum EDiscordResult result = core->internal->run_callbacks(core->internal);

    lib->core_api->godot_variant_new_int(&result_variant, result);

    return result_variant;
}

godot_variant core_get_user_manager(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                                    godot_variant **p_args)
{
    Library *lib = p_method_data;
    Core *core   = p_user_data;

    godot_variant result_variant;

    if (!core->internal)
    {
        PRINT_ERROR("Attempted to run method on unitialised Core, make sure you have run \"create\" first.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
        return result_variant;
    }

    godot_object *manager;
    if (!core->users)
    {
        manager           = instantiate_custom_class("UserManager", "Reference", lib);
        UserManager *data = lib->nativescript_api->godot_nativescript_get_userdata(manager);

        data->internal = core->internal->get_user_manager(core->internal);
        core->users    = data;
    }
    else
    {
        manager = core->users;
    }

    lib->core_api->godot_variant_new_object(&result_variant, manager);

    return result_variant;
}

godot_variant core_get_image_manager(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                                     godot_variant **p_args)
{
    Library *lib = p_method_data;
    Core *core   = p_user_data;

    godot_variant result_variant;

    if (!core->internal)
    {
        PRINT_ERROR("Attempted to run method on unitialised Core, make sure you have run \"create\" first.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
        return result_variant;
    }

    godot_object *manager;
    if (!core->images)
    {
        manager            = instantiate_custom_class("ImageManager", "Reference", lib);
        ImageManager *data = lib->nativescript_api->godot_nativescript_get_userdata(manager);
        data->internal     = core->internal->get_image_manager(core->internal);
        core->images       = data;
    }
    else
    {
        manager = core->images;
    }

    lib->core_api->godot_variant_new_object(&result_variant, manager);

    return result_variant;
}

godot_variant core_get_activity_manager(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                        int p_num_args, godot_variant **p_args)
{
    Library *lib = p_method_data;
    Core *core   = p_user_data;

    godot_variant result_variant;

    if (!core->internal)
    {
        PRINT_ERROR("Attempted to run method on unitialised Core, make sure you have run \"create\" first.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
        return result_variant;
    }

    godot_object *manager;
    if (!core->activities)
    {
        manager               = instantiate_custom_class("ActivityManager", "Reference", lib);
        ActivityManager *data = lib->nativescript_api->godot_nativescript_get_userdata(manager);
        data->internal        = core->internal->get_activity_manager(core->internal);
        core->activities      = data;
    }
    else
    {
        manager = core->activities;
    }

    lib->core_api->godot_variant_new_object(&result_variant, manager);

    return result_variant;
}

godot_variant core_get_relationship_manager(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                            int p_num_args, godot_variant **p_args)
{
    Library *lib = p_method_data;
    Core *core   = p_user_data;

    godot_variant result_variant;

    if (!core->internal)
    {
        PRINT_ERROR("Attempted to run method on unitialised Core, make sure you have run \"create\" first.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
        return result_variant;
    }

    godot_object *manager;
    if (!core->relationships)
    {
        manager                   = instantiate_custom_class("RelationshipManager", "Reference", lib);
        RelationshipManager *data = lib->nativescript_api->godot_nativescript_get_userdata(manager);
        data->internal            = core->internal->get_relationship_manager(core->internal);
        core->relationships       = data;
    }
    else
    {
        manager = core->relationships;
    }

    lib->core_api->godot_variant_new_object(&result_variant, manager);

    return result_variant;
}

void register_core(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = core_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = core_destructor;
    destructor.method_data  = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle, "Core", "Reference", constructor, destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Create
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = core_create;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "Core", "create", attributes, method);
        }
        // Set Log Hook
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = core_set_log_hook;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "Core", "set_log_hook", attributes,
                                                                        method);
        }
        // Run Callbacks
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = core_run_callbacks;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "Core", "run_callbacks", attributes,
                                                                        method);
        }
        // Get User Manager
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = core_get_user_manager;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "Core", "get_user_manager",
                                                                        attributes, method);
        }
        // Get Image Manager
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = core_get_image_manager;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "Core", "get_image_manager",
                                                                        attributes, method);
        }
        // Get Activity Manager
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = core_get_activity_manager;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "Core", "get_activity_manager",
                                                                        attributes, method);
        }
        // Get Relationship Manager
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = core_get_relationship_manager;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "Core", "get_relationship_manager",
                                                                        attributes, method);
        }
    }

    // Signals
    {
        godot_signal signal;

        // Log Hook
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("log_hook");

            godot_signal_argument level;
            {
                memset(&level, 0, sizeof(godot_signal_argument));
                level.name = p_lib->core_api->godot_string_chars_to_utf8("level");

                level.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument message;
            {
                memset(&message, 0, sizeof(godot_signal_argument));
                message.name = p_lib->core_api->godot_string_chars_to_utf8("message");

                message.type = GODOT_VARIANT_TYPE_STRING;
            }

            godot_signal_argument args[] = {level, message};
            signal.args                  = args;
            signal.num_args              = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "Core", &signal);

            p_lib->core_api->godot_string_destroy(&message.name);
            p_lib->core_api->godot_string_destroy(&level.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
    }
}
