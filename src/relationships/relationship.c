#include "relationship.h"
#include "relationships/presence.h"

#include "users/user.h"
#include "util.h"

GDCALLINGCONV void *relationship_constructor(godot_object *p_instance, void *p_method_data)
{
    Library *lib = p_method_data;

    INIT_OBJECT(relationship, Relationship, struct DiscordRelationship, lib, p_instance);

    relationship->user = instantiate_custom_class("User", "Resource", lib);
    godot_reference(relationship->user, lib);

    relationship->presence = instantiate_custom_class("Presence", "Resource", lib);
    godot_reference(relationship->presence, lib);

    return relationship;
}

GDCALLINGCONV void relationship_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib               = p_method_data;
    Relationship *relationship = p_user_data;

    if (relationship->user)
        godot_unreference(relationship->user, lib);
    if (relationship->presence)
        godot_unreference(relationship->presence, lib);

    lib->core_api->godot_free(relationship->internal);
    lib->core_api->godot_free(relationship);
}

godot_variant relationship_get_type(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib               = p_method_data;
    Relationship *relationship = p_user_data;

    godot_variant type;

    lib->core_api->godot_variant_new_int(&type, relationship->internal->type);

    return type;
}

GDCALLINGCONV void relationship_set_type(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                         godot_variant *p_type)
{
    Library *lib               = p_method_data;
    Relationship *relationship = p_user_data;

    relationship->internal->type = lib->core_api->godot_variant_as_int(p_type);
}

godot_variant relationship_get_user(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib               = p_method_data;
    Relationship *relationship = p_user_data;

    godot_variant user;

    lib->core_api->godot_variant_new_object(&user, relationship->user);

    return user;
}

GDCALLINGCONV void relationship_set_user(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                         godot_variant *p_user)
{
    Library *lib               = p_method_data;
    Relationship *relationship = p_user_data;

    if (relationship->user)
        godot_unreference(relationship->user, lib);

    relationship->user = lib->core_api->godot_variant_as_object(p_user);

    if (relationship->user)
        godot_reference(relationship->user, lib);
}

godot_variant relationship_get_presence(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib               = p_method_data;
    Relationship *relationship = p_user_data;

    godot_variant presence;

    lib->core_api->godot_variant_new_object(&presence, relationship->presence);

    return presence;
}

GDCALLINGCONV void relationship_set_presence(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                             godot_variant *p_presence)
{
    Library *lib               = p_method_data;
    Relationship *relationship = p_user_data;

    if (relationship->presence)
        godot_unreference(relationship->presence, lib);

    relationship->presence = lib->core_api->godot_variant_as_object(p_presence);

    if (relationship->presence)
        godot_reference(relationship->presence, lib);
}

struct DiscordRelationship *relationship_collapse(godot_object *p_instance, Library *p_lib)
{
    Relationship *relationship = p_lib->nativescript_api->godot_nativescript_get_userdata(p_instance);

    User *user                   = p_lib->nativescript_api->godot_nativescript_get_userdata(relationship->user);
    relationship->internal->user = *user->internal;

    relationship->internal->presence = *presence_collapse(relationship->presence, p_lib);

    return relationship->internal;
}

void relationship_reconstruct(godot_object *p_instance, struct DiscordRelationship *p_relationship, Library *p_lib)
{
    Relationship *relationship = p_lib->nativescript_api->godot_nativescript_get_userdata(p_instance);
    *relationship->internal    = *p_relationship;

    User *user      = p_lib->nativescript_api->godot_nativescript_get_userdata(relationship->user);
    *user->internal = p_relationship->user;

    presence_reconstruct(relationship->presence, &p_relationship->presence, p_lib);
}

void register_relationship(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = relationship_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = relationship_destructor;
    destructor.method_data  = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle, "Relationship", "Resource", constructor,
                                                               destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // Type
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type  = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            attributes.hint        = GODOT_PROPERTY_HINT_ENUM;
            attributes.hint_string = p_lib->core_api->godot_string_chars_to_utf8(
                "None,Friend,Blocked,Pending Incoming,Pending Outgoing,Implicit");

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func    = relationship_get_type;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func    = relationship_set_type;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle, "Relationship", "type", &attributes,
                                                                          set, get);

            p_lib->core_api->godot_string_destroy(&attributes.hint_string);
        }
        // User
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type  = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func    = relationship_get_user;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func    = relationship_set_user;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle, "Relationship", "user", &attributes,
                                                                          set, get);
        }
        // Presence
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type  = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func    = relationship_get_presence;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func    = relationship_set_presence;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle, "Relationship", "presence",
                                                                          &attributes, set, get);
        }
    }
}
