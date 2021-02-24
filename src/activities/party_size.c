#include "party_size.h"

#include "util.h"

GDCALLINGCONV void *party_size_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(party_size,
                PartySize, struct DiscordPartySize,
                p_lib, p_instance);

    return party_size;
}

GDCALLINGCONV void party_size_destructor(godot_object *p_instance, Library *p_lib,
                                         PartySize *p_party_size)
{
    p_lib->core_api->godot_free(p_party_size->internal);
    p_lib->core_api->godot_free(p_party_size);
}

godot_variant party_size_get_current_size(godot_object *p_instance, Library *p_lib,
                                          PartySize *p_party_size)
{
    godot_variant current_size;

    p_lib->core_api->godot_variant_new_int(&current_size, p_party_size->internal->current_size);

    return current_size;
}

GDCALLINGCONV void party_size_set_current_size(godot_object *p_instance, Library *p_lib,
                                               PartySize *p_party_size,
                                               godot_variant *p_current_size)
{
    p_party_size->internal->current_size = (int32_t)p_lib->core_api->godot_variant_as_int(p_current_size);
}

godot_variant party_size_get_max_size(godot_object *p_instance, Library *p_lib,
                                      PartySize *p_party_size)
{
    godot_variant max_size;

    p_lib->core_api->godot_variant_new_int(&max_size, p_party_size->internal->max_size);

    return max_size;
}

GDCALLINGCONV void party_size_set_max_size(godot_object *p_instance, Library *p_lib,
                                           PartySize *p_party_size,
                                           godot_variant *p_max_size)
{
    p_party_size->internal->max_size = (int32_t)p_lib->core_api->godot_variant_as_int(p_max_size);
}

void register_party_size(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = party_size_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = party_size_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "PartySize", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // Current Size
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = party_size_get_current_size;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = party_size_set_current_size;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "PartySize", "current_size",
                                                                          &attributes,
                                                                          set, get);
        }
        // Max Size
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = party_size_get_max_size;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = party_size_set_max_size;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "PartySize", "max_size",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}
