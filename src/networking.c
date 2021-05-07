#include "networking.h"

#include "core.h"
#include "util.h"

GDCALLINGCONV void *network_manager_constructor(godot_object *p_instance, void *p_method_data)
{
    Library *lib = p_method_data;

    NetworkManager *network_manager = lib->core_api->godot_alloc(sizeof(NetworkManager));
    memset(network_manager, 0, sizeof(NetworkManager));

    network_manager->object = p_instance;
    network_manager->lib    = lib;

    return network_manager;
}

GDCALLINGCONV void network_manager_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    lib->core_api->godot_free(network_manager);
}

godot_variant network_manager_get_peer_id(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                          int p_num_args, godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 0)
    {
        uint64_t peer_id;
        network_manager->internal->get_peer_id(network_manager->internal, &peer_id);

        lib->core_api->godot_variant_new_uint(&result_variant, peer_id);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_peer_id()\" call. Expected 0.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

godot_variant network_manager_flush(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                                    godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 0)
    {
        enum EDiscordResult result = network_manager->internal->flush(network_manager->internal);
        lib->core_api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"flush()\" call. Expected 0.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

void register_network_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = network_manager_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = network_manager_destructor;
    destructor.method_data  = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle, "NetworkManager", "Object", constructor,
                                                               destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Get Peer ID
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_get_peer_id;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "get_peer_id",
                                                                        attributes, method);
        }
        // Flush
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_flush;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "flush", attributes,
                                                                        method);
        }
    }
}
