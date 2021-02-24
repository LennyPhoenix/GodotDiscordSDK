#include "image_dimensions.h"

#include "util.h"

GDCALLINGCONV void *image_dimensions_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(dimensions, ImageDimensions, struct DiscordImageDimensions, p_lib, p_instance)

    return dimensions;
}

GDCALLINGCONV void image_dimensions_destructor(godot_object *p_instance, Library *p_lib,
                                               ImageDimensions *p_dimensions)
{
    p_lib->core_api->godot_free(p_dimensions->internal);
    p_lib->core_api->godot_free(p_dimensions);
}

godot_variant image_dimensions_get_width(godot_object *p_instance, Library *p_lib,
                                         ImageDimensions *p_dimensions)
{
    godot_variant width;

    p_lib->core_api->godot_variant_new_uint(&width, p_dimensions->internal->width);

    return width;
}

GDCALLINGCONV void image_dimensions_set_width(godot_object *p_instance, Library *p_lib,
                                              ImageDimensions *p_dimensions,
                                              godot_variant *p_width)
{
    p_dimensions->internal->width = (uint32_t)p_lib->core_api->godot_variant_as_uint(p_width);
}

godot_variant image_dimensions_get_height(godot_object *p_instance, Library *p_lib,
                                          ImageDimensions *p_dimensions)
{
    godot_variant height;

    p_lib->core_api->godot_variant_new_uint(&height, p_dimensions->internal->height);

    return height;
}

GDCALLINGCONV void image_dimensions_set_height(godot_object *p_instance, Library *p_lib,
                                               ImageDimensions *p_dimensions,
                                               godot_variant *p_height)
{
    p_dimensions->internal->height = (uint32_t)p_lib->core_api->godot_variant_as_uint(p_height);
}

void register_image_dimensions(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = image_dimensions_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = image_dimensions_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ImageDimensions", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // Width
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = image_dimensions_get_width;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = image_dimensions_set_width;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ImageDimensions", "width",
                                                                          &attributes,
                                                                          set, get);
        }
        // Height
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = image_dimensions_get_height;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = image_dimensions_set_height;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ImageDimensions", "height",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}
