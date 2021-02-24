#include "activity_assets.h"

#include "util.h"

GDCALLINGCONV void *activity_assets_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(assets,
                ActivityAssets, struct DiscordActivityAssets,
                p_lib, p_instance);

    return assets;
}

GDCALLINGCONV void activity_assets_destructor(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_assets)
{
    p_lib->core_api->godot_free(p_assets->internal);
    p_lib->core_api->godot_free(p_assets);
}

godot_variant activity_assets_get_large_image(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_assets)
{
    godot_variant large_image;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_assets->internal->large_image);
    p_lib->core_api->godot_variant_new_string(&large_image, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return large_image;
}

GDCALLINGCONV void activity_assets_set_large_image(godot_object *p_instance, Library *p_lib,
                                                   ActivityAssets *p_assets,
                                                   godot_variant *p_large_image)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_large_image);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *large_image = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_assets->internal->large_image, 0, sizeof(char) * 128);
    memcpy(p_assets->internal->large_image, large_image, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant activity_assets_get_large_text(godot_object *p_instance, Library *p_lib,
                                             ActivityAssets *p_assets)
{
    godot_variant large_text;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_assets->internal->large_text);
    p_lib->core_api->godot_variant_new_string(&large_text, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return large_text;
}

GDCALLINGCONV void activity_assets_set_large_text(godot_object *p_instance, Library *p_lib,
                                                  ActivityAssets *p_assets,
                                                  godot_variant *p_large_text)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_large_text);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *large_text = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_assets->internal->large_text, 0, sizeof(char) * 128);
    memcpy(p_assets->internal->large_text, large_text, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant activity_assets_get_small_image(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_assets)
{
    godot_variant small_image;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_assets->internal->small_image);
    p_lib->core_api->godot_variant_new_string(&small_image, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return small_image;
}

GDCALLINGCONV void activity_assets_set_small_image(godot_object *p_instance, Library *p_lib,
                                                   ActivityAssets *p_assets,
                                                   godot_variant *p_small_image)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_small_image);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *small_image = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_assets->internal->small_image, 0, sizeof(char) * 128);
    memcpy(p_assets->internal->small_image, small_image, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant activity_assets_get_small_text(godot_object *p_instance, Library *p_lib,
                                             ActivityAssets *p_assets)
{
    godot_variant small_text;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_assets->internal->small_text);
    p_lib->core_api->godot_variant_new_string(&small_text, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return small_text;
}

GDCALLINGCONV void activity_assets_set_small_text(godot_object *p_instance, Library *p_lib,
                                                  ActivityAssets *p_assets,
                                                  godot_variant *p_small_text)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_small_text);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *small_text = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_assets->internal->small_text, 0, sizeof(char) * 128);
    memcpy(p_assets->internal->small_text, small_text, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

void register_activity_assets(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = activity_assets_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = activity_assets_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ActivityAssets", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // Large Image
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_assets_get_large_image;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_assets_set_large_image;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "large_image",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Large Text
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_assets_get_large_text;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_assets_set_large_text;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "large_text",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Small Image
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_assets_get_small_image;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_assets_set_small_image;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "small_image",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Small Text
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_assets_get_small_text;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_assets_set_small_text;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "small_text",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
    }
}
