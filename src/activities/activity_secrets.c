#include "activity_secrets.h"

#include "util.h"

GDCALLINGCONV void *activity_secrets_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(secrets,
                ActivitySecrets, struct DiscordActivitySecrets,
                p_lib, p_instance);

    return secrets;
}

GDCALLINGCONV void activity_secrets_destructor(godot_object *p_instance, Library *p_lib,
                                               ActivitySecrets *p_secrets)
{
    p_lib->core_api->godot_free(p_secrets->internal);
    p_lib->core_api->godot_free(p_secrets);
}

godot_variant activity_secrets_get_match(godot_object *p_instance, Library *p_lib,
                                         ActivitySecrets *p_secrets)
{
    godot_variant match;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_secrets->internal->match);
    p_lib->core_api->godot_variant_new_string(&match, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return match;
}

GDCALLINGCONV void activity_secrets_set_match(godot_object *p_instance, Library *p_lib,
                                              ActivitySecrets *p_secrets,
                                              godot_variant *p_match)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_match);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *match = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_secrets->internal->match, 0, sizeof(char) * 128);
    memcpy(p_secrets->internal->match, match, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant activity_secrets_get_join(godot_object *p_instance, Library *p_lib,
                                        ActivitySecrets *p_secrets)
{
    godot_variant join;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_secrets->internal->join);
    p_lib->core_api->godot_variant_new_string(&join, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return join;
}

GDCALLINGCONV void activity_secrets_set_join(godot_object *p_instance, Library *p_lib,
                                             ActivitySecrets *p_secrets,
                                             godot_variant *p_join)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_join);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *join = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_secrets->internal->join, 0, sizeof(char) * 128);
    memcpy(p_secrets->internal->join, join, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant activity_secrets_get_spectate(godot_object *p_instance, Library *p_lib,
                                            ActivitySecrets *p_secrets)
{
    godot_variant spectate;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_secrets->internal->spectate);
    p_lib->core_api->godot_variant_new_string(&spectate, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return spectate;
}

GDCALLINGCONV void activity_secrets_set_spectate(godot_object *p_instance, Library *p_lib,
                                                 ActivitySecrets *p_secrets,
                                                 godot_variant *p_spectate)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_spectate);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *spectate = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_secrets->internal->spectate, 0, sizeof(char) * 128);
    memcpy(p_secrets->internal->spectate, spectate, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

void register_activity_secrets(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = activity_secrets_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = activity_secrets_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ActivitySecrets", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // Match
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_secrets_get_match;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_secrets_set_match;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivitySecrets", "match",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Join
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_secrets_get_join;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_secrets_set_join;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivitySecrets", "join",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Spectate
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_secrets_get_spectate;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_secrets_set_spectate;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivitySecrets", "spectate",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
    }
}
