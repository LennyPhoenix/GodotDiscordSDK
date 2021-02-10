#include "core.h"

GDCALLINGCONV void *core_constructor(godot_object *p_instance, Library *p_lib)
{
    Core *core = p_lib->api->godot_alloc(sizeof(Core));
    memset(core, 0, sizeof(Core));

    core->object = p_instance;
    core->lib = p_lib;

    return core;
}

GDCALLINGCONV void core_destructor(godot_object *p_instance, Library *p_lib,
                                   Core *p_core)
{
    if (p_core->users)
        godot_unreference(p_core->users, p_lib);
    if (p_core->images)
        godot_unreference(p_core->images, p_lib);
    if (p_core->activities)
        godot_unreference(p_core->activities, p_lib);

    if (p_core->hook_data)
        p_lib->api->godot_free(p_core->hook_data);

    if (p_core->internal)
    {
        p_core->internal->destroy(p_core->internal);
        p_lib->api->godot_free(p_core->user_events);
    }

    p_lib->api->godot_free(p_core);
}

godot_variant core_create(godot_object *p_instance, Library *p_lib,
                          Core *p_core,
                          int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 2 || p_num_args == 3)
    {
        uint64_t id = p_lib->api->godot_variant_as_uint(p_args[0]);
        uint64_t create_flags = p_lib->api->godot_variant_as_uint(p_args[1]);
        if (p_num_args == 3)
        {
            uint64_t instance_id = p_lib->api->godot_variant_as_uint(p_args[2]);
            char instance[128];
            memset(instance, 0, sizeof(char) * 128);
            sprintf(instance, "%Iu", instance_id);
#ifdef _WIN32
            _putenv_s("DISCORD_INSTANCE_ID", instance);
#else
            setenv("DISCORD_INSTANCE_ID", instance, true);
#endif
        }

        struct DiscordCreateParams params;
        memset(&params, 0, sizeof(struct DiscordCreateParams));
        DiscordCreateParamsSetDefault(&params);
        params.client_id = id;
        params.event_data = p_core;
        params.flags = create_flags;

        p_core->user_events = p_lib->api->godot_alloc(sizeof(struct IDiscordUserEvents));
        p_core->user_events->on_current_user_update = on_current_user_update;
        params.user_events = p_core->user_events;

        p_core->activity_events = p_lib->api->godot_alloc(sizeof(struct IDiscordActivityEvents));
        p_core->activity_events->on_activity_join = on_activity_join;
        p_core->activity_events->on_activity_spectate = on_activity_spectate;
        p_core->activity_events->on_activity_join_request = on_activity_join_request;
        p_core->activity_events->on_activity_invite = on_activity_invite;
        params.activity_events = p_core->activity_events;

        enum EDiscordResult result = DiscordCreate(DISCORD_VERSION, &params, &p_core->internal);

        if (result != DiscordResult_Ok)
        {
            p_core->internal = NULL;
        }

        p_lib->api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

void log_hook(CallbackData *p_data,
              enum EDiscordLogLevel p_level, const char *p_message)
{
    Library *lib = p_data->lib;

    godot_variant level_variant;
    godot_variant message_variant;

    lib->api->godot_variant_new_int(&level_variant, p_level);

    godot_string message_string = p_data->lib->api->godot_string_chars_to_utf8(p_message);
    lib->api->godot_variant_new_string(&message_variant, &message_string);

    godot_variant *args[] = {&level_variant, &message_variant};

    object_call(p_data->callback_object, &p_data->callback_name, 2, args, p_data->lib);
}

godot_variant core_set_log_hook(godot_object *p_instance, Library *p_lib,
                                Core *p_core,
                                int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_core->internal && p_num_args == 3) // Min Level, Hook Object, Hook Method
    {
        int64_t min_level = p_lib->api->godot_variant_as_int(p_args[0]);
        godot_object *hook_object = p_lib->api->godot_variant_as_object(p_args[1]);
        godot_string hook_method = p_lib->api->godot_variant_as_string(p_args[2]);

        if (!p_core->hook_data)
        {
            p_core->hook_data = p_lib->api->godot_alloc(sizeof(CallbackData));
        }

        memset(p_core->hook_data, 0, sizeof(CallbackData));
        p_core->hook_data->callback_name = hook_method;
        p_core->hook_data->callback_object = hook_object;
        p_core->hook_data->core = p_core;
        p_core->hook_data->lib = p_lib;

        p_core->internal->set_log_hook(p_core->internal, min_level, p_core->hook_data, log_hook);

        p_lib->api->godot_variant_new_nil(&result_variant);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

godot_variant core_run_callbacks(godot_object *p_instance, Library *p_lib,
                                 Core *p_core,
                                 int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_core->internal)
    {
        enum EDiscordResult result = p_core->internal->run_callbacks(p_core->internal);

        p_lib->api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

godot_variant core_get_user_manager(godot_object *p_instance, Library *p_lib,
                                    Core *p_core,
                                    int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_core->internal)
    {
        godot_object *manager;
        if (!p_core->users)
        {
            manager = instantiate_custom_class("UserManager", "Reference", p_lib);
            UserManager *data = p_lib->nativescript_api->godot_nativescript_get_userdata(manager);
            data->core = p_core;
            data->internal = p_core->internal->get_user_manager(p_core->internal);
            p_core->users = data;

            godot_reference(manager, p_lib);
        }
        else
        {
            manager = p_core->users;
        }

        p_lib->api->godot_variant_new_object(&result_variant, manager);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

godot_variant core_get_image_manager(godot_object *p_instance, Library *p_lib,
                                     Core *p_core,
                                     int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_core->internal)
    {
        godot_object *manager;
        if (!p_core->images)
        {
            manager = instantiate_custom_class("ImageManager", "Reference", p_lib);
            ImageManager *data = p_lib->nativescript_api->godot_nativescript_get_userdata(manager);
            data->core = p_core;
            data->internal = p_core->internal->get_image_manager(p_core->internal);
            p_core->images = data;

            godot_reference(manager, p_lib);
        }
        else
        {
            manager = p_core->images;
        }

        p_lib->api->godot_variant_new_object(&result_variant, manager);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

godot_variant core_get_activity_manager(godot_object *p_instance, Library *p_lib,
                                        Core *p_core,
                                        int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_core->internal)
    {
        godot_object *manager;
        if (!p_core->activities)
        {
            manager = instantiate_custom_class("ActivityManager", "Reference", p_lib);
            ActivityManager *data = p_lib->nativescript_api->godot_nativescript_get_userdata(manager);
            data->core = p_core;
            data->internal = p_core->internal->get_activity_manager(p_core->internal);
            p_core->activities = data;

            godot_reference(manager, p_lib);
        }
        else
        {
            manager = p_core->activities;
        }

        p_lib->api->godot_variant_new_object(&result_variant, manager);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

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
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "Core", "Reference",
                                                               constructor, destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Create
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = core_create;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "Core", "create",
                                                                        attributes, method);
        }
        // Set Log Hook
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = core_set_log_hook;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "Core", "set_log_hook",
                                                                        attributes, method);
        }
        // Run Callbacks
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = core_run_callbacks;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "Core", "run_callbacks",
                                                                        attributes, method);
        }
        // Get User Manager
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = core_get_user_manager;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "Core", "get_user_manager",
                                                                        attributes, method);
        }
        // Get Image Manager
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = core_get_image_manager;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "Core", "get_image_manager",
                                                                        attributes, method);
        }
        // Get Activity Manager
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = core_get_activity_manager;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "Core", "get_activity_manager",
                                                                        attributes, method);
        }
    }
}
