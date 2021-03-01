#include "relationships.h"

GDCALLINGCONV void *relationship_manager_constructor(godot_object *p_instance, Library *p_lib)
{
    RelationshipManager *relationship_manager = p_lib->core_api->godot_alloc(sizeof(RelationshipManager));

    relationship_manager->object = p_instance;
    relationship_manager->lib = p_lib;

    return relationship_manager;
}

GDCALLINGCONV void relationship_manager_destructor(godot_object *p_instance, Library *p_lib,
                                                   RelationshipManager *p_relationship_manager)
{
    p_lib->core_api->godot_free(p_relationship_manager);
}

void register_relationship_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = relationship_manager_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = relationship_manager_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "RelationshipManager", "Reference",
                                                               constructor, destructor);
}
