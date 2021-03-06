#include "relationships.h"

#include "util.h"
#include "relationships/relationship.h"

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

    // Signals
    {
        godot_signal signal;

        // Refresh
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("refresh");

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "RelationshipManager", &signal);

            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Relationship Update
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("relationship_update");

            godot_signal_argument relationship;
            {
                memset(&relationship, 0, sizeof(godot_signal_argument));
                relationship.name = p_lib->core_api->godot_string_chars_to_utf8("relationship");

                relationship.type = GODOT_VARIANT_TYPE_OBJECT;
            }

            godot_signal_argument args[] = {relationship};
            signal.args = args;
            signal.num_args = 1;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "RelationshipManager", &signal);

            p_lib->core_api->godot_string_destroy(&relationship.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
    }
}

void on_refresh(Core *p_core)
{
    Library *lib = p_core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("refresh");

    object_emit_signal(p_core->relationships->object, &signal, 0, NULL, lib);

    lib->core_api->godot_string_destroy(&signal);
}

void on_relationship_update(Core *p_core, struct DiscordRelationship *p_relationship)
{
    Library *lib = p_core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("relationship_update");

    godot_variant relationship_variant;

    godot_object *relationship_object = instantiate_custom_class("Relationship", "Resource", lib);
    relationship_reconstruct(relationship_object, p_relationship, p_core->lib);

    lib->core_api->godot_variant_new_object(&relationship_variant, relationship_object);

    godot_variant *args[] = {&relationship_variant};

    object_emit_signal(p_core->relationships->object, &signal, 1, args, lib);

    lib->core_api->godot_variant_destroy(&relationship_variant);
    lib->core_api->godot_string_destroy(&signal);
}
