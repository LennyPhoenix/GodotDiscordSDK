#include "core.h"

void *core_constructor(godot_object *p_instance, Library *p_lib)
{
    Core *core = p_lib->api->godot_alloc(sizeof(Core));
    memset(core, 0, sizeof(Core));

    core->object = p_instance;
    core->lib = p_lib;

    return core;
}

void core_destructor(godot_object *p_instance, Library *p_lib,
                     Core *p_core)
{
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

    if (p_num_args == 2)
    {
        uint64_t id = p_lib->api->godot_variant_as_uint(p_args[0]);
        uint64_t create_flags = p_lib->api->godot_variant_as_uint(p_args[1]);

        struct DiscordCreateParams params;
        memset(&params, 0, sizeof(params));
        DiscordCreateParamsSetDefault(&params);
        params.client_id = id;
        params.event_data = p_core;
        params.flags = create_flags;

        p_core->user_events = p_lib->api->godot_alloc(sizeof(p_core->user_events));
        p_core->user_events->on_current_user_update = on_current_user_update;
        params.user_events = p_core->user_events;

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

void register_core(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(constructor));
    constructor.create_func = &core_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(destructor));
    destructor.destroy_func = &core_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "Core", "Reference",
                                                               constructor, destructor);

    godot_method_attributes default_method_attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

    godot_instance_method create;
    memset(&create, 0, sizeof(create));
    create.method = &core_create;
    create.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                "Core", "create",
                                                                default_method_attributes, create);

    godot_instance_method run_callbacks;
    memset(&run_callbacks, 0, sizeof(run_callbacks));
    run_callbacks.method = &core_run_callbacks;
    run_callbacks.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                "Core", "run_callbacks",
                                                                default_method_attributes, run_callbacks);

    godot_instance_method get_user_manager;
    memset(&get_user_manager, 0, sizeof(get_user_manager));
    get_user_manager.method = &core_get_user_manager;
    get_user_manager.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                "Core", "get_user_manager",
                                                                default_method_attributes, get_user_manager);
}
