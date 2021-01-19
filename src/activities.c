#include "activities.h"

GDCALLINGCONV void *activity_timestamps_constructor(godot_object *p_instance, Library *p_lib)
{
    struct DiscordActivityTimestamps *timestamps = p_lib->api->godot_alloc(sizeof(struct DiscordActivityTimestamps));
    memset(timestamps, 0, sizeof(timestamps));

    return timestamps;
}

GDCALLINGCONV void activity_timestamps_destructor(godot_object *p_instance, Library *p_lib,
                                                  struct DiscordActivityTimestamps *p_timestamps)
{
    p_lib->api->godot_free(p_timestamps);
}

godot_variant activity_timestamps_get_start(godot_object *p_instance, Library *p_lib,
                                            struct DiscordActivityTimestamps *p_timestamps)
{
    godot_variant start;

    p_lib->api->godot_variant_new_int(&start, p_timestamps->start);

    return start;
}

GDCALLINGCONV void activity_timestamps_set_start(godot_object *p_instance, Library *p_lib,
                                                 struct DiscordActivityTimestamps *p_timestamps,
                                                 godot_variant *p_start)
{
    p_timestamps->start = p_lib->api->godot_variant_as_int(p_start);
}

godot_variant activity_timestamps_get_end(godot_object *p_instance, Library *p_lib,
                                          struct DiscordActivityTimestamps *p_timestamps)
{
    godot_variant end;

    p_lib->api->godot_variant_new_int(&end, p_timestamps->end);

    return end;
}

GDCALLINGCONV void activity_timestamps_set_end(godot_object *p_instance, Library *p_lib,
                                               struct DiscordActivityTimestamps *p_timestamps,
                                               godot_variant *p_end)
{
    p_timestamps->end = p_lib->api->godot_variant_as_int(p_end);
}

void register_activity_timestamps(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(constructor));
    constructor.create_func = activity_timestamps_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(destructor));
    destructor.destroy_func = activity_timestamps_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ActivityTimestamps", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // Start
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_int(&default_value, 0);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = activity_timestamps_get_start;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = activity_timestamps_set_start;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityTimestamps", "start",
                                                                          &attributes,
                                                                          set, get);
        }
        // End
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_int(&default_value, 0);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = activity_timestamps_get_end;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = activity_timestamps_set_end;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityTimestamps", "end",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}

GDCALLINGCONV void *activity_assets_constructor(godot_object *p_instance, Library *p_lib)
{
    struct DiscordActivityAssets *assets = p_lib->api->godot_alloc(sizeof(struct DiscordActivityAssets));
    memset(assets, 0, sizeof(assets));

    return assets;
}

GDCALLINGCONV void activity_assets_destructor(godot_object *p_instance, Library *p_lib,
                                              struct DiscordActivityAssets *p_assets)
{
    p_lib->api->godot_free(p_assets);
}

godot_variant activity_assets_get_large_image(godot_object *p_instance, Library *p_lib,
                                              struct DiscordActivityAssets *p_timestamps)
{
    godot_variant large_image;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_timestamps->large_image);
    p_lib->api->godot_variant_new_string(&large_image, &string);
    p_lib->api->godot_string_destroy(&string);

    return large_image;
}

GDCALLINGCONV void activity_assets_set_large_image(godot_object *p_instance, Library *p_lib,
                                                   struct DiscordActivityAssets *p_timestamps,
                                                   godot_variant *p_large_image)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_large_image);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *large_image = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_timestamps->large_image, 0, sizeof(char) * 128);
    memcpy(p_timestamps->large_image, large_image, sizeof(char) * MIN(size, 127));
}

godot_variant activity_assets_get_large_text(godot_object *p_instance, Library *p_lib,
                                             struct DiscordActivityAssets *p_timestamps)
{
    godot_variant large_text;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_timestamps->large_text);
    p_lib->api->godot_variant_new_string(&large_text, &string);
    p_lib->api->godot_string_destroy(&string);

    return large_text;
}

GDCALLINGCONV void activity_assets_set_large_text(godot_object *p_instance, Library *p_lib,
                                                  struct DiscordActivityAssets *p_timestamps,
                                                  godot_variant *p_large_text)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_large_text);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *large_text = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_timestamps->large_text, 0, sizeof(char) * 128);
    memcpy(p_timestamps->large_text, large_text, sizeof(char) * MIN(size, 127));
}

godot_variant activity_assets_get_small_image(godot_object *p_instance, Library *p_lib,
                                              struct DiscordActivityAssets *p_timestamps)
{
    godot_variant small_image;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_timestamps->small_image);
    p_lib->api->godot_variant_new_string(&small_image, &string);
    p_lib->api->godot_string_destroy(&string);

    return small_image;
}

GDCALLINGCONV void activity_assets_set_small_image(godot_object *p_instance, Library *p_lib,
                                                   struct DiscordActivityAssets *p_timestamps,
                                                   godot_variant *p_small_image)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_small_image);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *small_image = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_timestamps->small_image, 0, sizeof(char) * 128);
    memcpy(p_timestamps->small_image, small_image, sizeof(char) * MIN(size, 127));
}

godot_variant activity_assets_get_small_text(godot_object *p_instance, Library *p_lib,
                                             struct DiscordActivityAssets *p_timestamps)
{
    godot_variant small_text;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_timestamps->small_text);
    p_lib->api->godot_variant_new_string(&small_text, &string);
    p_lib->api->godot_string_destroy(&string);

    return small_text;
}

GDCALLINGCONV void activity_assets_set_small_text(godot_object *p_instance, Library *p_lib,
                                                  struct DiscordActivityAssets *p_timestamps,
                                                  godot_variant *p_small_text)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_small_text);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *small_text = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_timestamps->small_text, 0, sizeof(char) * 128);
    memcpy(p_timestamps->small_text, small_text, sizeof(char) * MIN(size, 127));
}

void register_activity_assets(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(constructor));
    constructor.create_func = activity_assets_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(destructor));
    destructor.destroy_func = activity_assets_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ActivityAssets", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // Large Image
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = activity_assets_get_large_image;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = activity_assets_set_large_image;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "large_image",
                                                                          &attributes,
                                                                          set, get);
        }
        // Large Text
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = activity_assets_get_large_text;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = activity_assets_set_large_text;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "large_text",
                                                                          &attributes,
                                                                          set, get);
        }
        // Small Image
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = activity_assets_get_small_image;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = activity_assets_set_small_image;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "small_image",
                                                                          &attributes,
                                                                          set, get);
        }
        // Small Text
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = activity_assets_get_small_text;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = activity_assets_set_small_text;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "small_text",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}
