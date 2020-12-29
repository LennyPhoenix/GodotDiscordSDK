#include "users.h"

void on_current_user_update(struct Core *p_core)
{
    object_emit_signal(p_core->users->object, "current_user_update", 0, NULL, p_core->lib);
}

void *user_manager_constructor(godot_object *p_instance, Library *p_lib)
{
    UserManager *user_manager = p_lib->api->godot_alloc(sizeof(UserManager));

    user_manager->object = p_instance;
    user_manager->lib = p_lib;

    return user_manager;
}

void user_manager_destructor(godot_object *p_instance, Library *p_lib,
                             UserManager *p_user_manager)
{
    p_lib->api->godot_free(p_user_manager);
}

void register_user_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func manager_constructor;
    memset(&manager_constructor, 0, sizeof(manager_constructor));
    manager_constructor.create_func = &user_manager_constructor;
    manager_constructor.method_data = p_lib;

    godot_instance_destroy_func manager_destructor;
    memset(&manager_destructor, 0, sizeof(manager_destructor));
    manager_destructor.destroy_func = &user_manager_destructor;
    manager_destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "UserManager", "Reference",
                                                               manager_constructor, manager_destructor);

    godot_string signal_name;
    p_lib->api->godot_string_new(&signal_name);

    godot_signal current_user_update;
    memset(&current_user_update, 0, sizeof(current_user_update));
    p_lib->api->godot_string_parse_utf8(&signal_name, "current_user_update");
    current_user_update.name = signal_name;

    p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                "UserManager", &current_user_update);

    p_lib->api->godot_string_destroy(&signal_name);
}
