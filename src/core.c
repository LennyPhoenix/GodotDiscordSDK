#include "core.h"

void *core_constructor(godot_object *p_instance, Library *p_lib)
{
    Discord *discord = p_lib->api->godot_alloc(sizeof(Discord));

    return discord;
}

void core_destructor(godot_object *p_instance, Library *p_lib,
                     Discord *p_discord)
{
    if (p_discord->core)
    {
        p_discord->core->destroy(p_discord->core);
    }
    p_lib->api->godot_free(p_discord);
}

godot_variant core_create(godot_object *p_instance, Library *p_lib,
                          Discord *p_discord,
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
        params.event_data = p_discord;
        params.flags = create_flags;

        enum EDiscordResult result = DiscordCreate(DISCORD_VERSION, &params, &p_discord->core);

        if (result != DiscordResult_Ok)
        {
            p_discord->core = NULL;
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
                                 Discord *p_discord,
                                 int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 0 && p_discord->core)
    {
        enum EDiscordResult result = p_discord->core->run_callbacks(p_discord->core);

        p_lib->api->godot_variant_new_int(&result_variant, result);
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
}