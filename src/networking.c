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
}
