#include "images.h"

GDCALLINGCONV void *image_dimensions_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(dimensions, ImageDimensions, struct DiscordImageDimensions, p_lib, p_instance)

    return dimensions;
}

GDCALLINGCONV void image_dimensions_destructor(godot_object *p_instance, Library *p_lib,
                                               ImageDimensions *p_dimensions)
{
    p_lib->api->godot_free(p_dimensions->internal);
    p_lib->api->godot_free(p_dimensions);
}

godot_variant image_dimensions_get_width(godot_object *p_instance, Library *p_lib,
                                         ImageDimensions *p_dimensions)
{
    godot_variant width;

    p_lib->api->godot_variant_new_uint(&width, p_dimensions->internal->width);

    return width;
}

GDCALLINGCONV void image_dimensions_set_width(godot_object *p_instance, Library *p_lib,
                                              ImageDimensions *p_dimensions,
                                              godot_variant *p_width)
{
    p_dimensions->internal->width = (uint32_t)p_lib->api->godot_variant_as_uint(p_width);
}

godot_variant image_dimensions_get_height(godot_object *p_instance, Library *p_lib,
                                          ImageDimensions *p_dimensions)
{
    godot_variant height;

    p_lib->api->godot_variant_new_uint(&height, p_dimensions->internal->height);

    return height;
}

GDCALLINGCONV void image_dimensions_set_height(godot_object *p_instance, Library *p_lib,
                                               ImageDimensions *p_dimensions,
                                               godot_variant *p_height)
{
    p_dimensions->internal->height = (uint32_t)p_lib->api->godot_variant_as_uint(p_height);
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
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // Width
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_uint(&default_value, 0);
            attributes.default_value = default_value;

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
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_uint(&default_value, 0);
            attributes.default_value = default_value;

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

GDCALLINGCONV void *image_handle_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(handle, ImageHandle, struct DiscordImageHandle, p_lib, p_instance);

    return handle;
}

GDCALLINGCONV void image_handle_destructor(godot_object *p_instance, Library *p_lib,
                                           ImageHandle *p_handle)
{
    p_lib->api->godot_free(p_handle->internal);
    p_lib->api->godot_free(p_handle);
}

godot_variant image_handle_get_type(godot_object *p_instance, Library *p_lib,
                                    ImageHandle *p_handle)
{
    godot_variant type;

    p_lib->api->godot_variant_new_int(&type, p_handle->internal->type);

    return type;
}

GDCALLINGCONV void image_handle_set_type(godot_object *p_instance, Library *p_lib,
                                         ImageHandle *p_handle,
                                         godot_variant *p_type)
{
    p_handle->internal->type = p_lib->api->godot_variant_as_int(p_type);
}

godot_variant image_handle_get_id(godot_object *p_instance, Library *p_lib,
                                  ImageHandle *p_handle)
{
    godot_variant id;

    p_lib->api->godot_variant_new_int(&id, p_handle->internal->id);

    return id;
}

GDCALLINGCONV void image_handle_set_id(godot_object *p_instance, Library *p_lib,
                                       ImageHandle *p_handle,
                                       godot_variant *p_id)
{
    p_handle->internal->id = p_lib->api->godot_variant_as_int(p_id);
}

godot_variant image_handle_get_size(godot_object *p_instance, Library *p_lib,
                                    ImageHandle *p_handle)
{
    godot_variant size;

    p_lib->api->godot_variant_new_uint(&size, p_handle->internal->size);

    return size;
}

GDCALLINGCONV void image_handle_set_size(godot_object *p_instance, Library *p_lib,
                                         ImageHandle *p_handle,
                                         godot_variant *p_size)
{
    p_handle->internal->size = (uint32_t)p_lib->api->godot_variant_as_uint(p_size);
}

void register_image_handle(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = image_handle_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = image_handle_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ImageHandle", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // Type
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_ENUM;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("User");

            p_lib->api->godot_variant_new_int(&default_value, DiscordImageType_User);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = image_handle_get_type;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = image_handle_set_type;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ImageHandle", "type",
                                                                          &attributes,
                                                                          set, get);
        }
        // ID
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_int(&default_value, 0);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = image_handle_get_id;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = image_handle_set_id;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ImageHandle", "id",
                                                                          &attributes,
                                                                          set, get);
        }
        // Size
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_uint(&default_value, 0);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = image_handle_get_size;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = image_handle_set_size;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ImageHandle", "size",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}

GDCALLINGCONV void *image_manager_constructor(godot_object *p_instance, Library *p_lib)
{
    ImageManager *image_manager = p_lib->api->godot_alloc(sizeof(ImageManager));

    image_manager->object = p_instance;
    image_manager->lib = p_lib;

    return image_manager;
}

GDCALLINGCONV void image_manager_destructor(godot_object *p_instance, Library *p_lib,
                                            ImageManager *p_image_manager)
{
    p_lib->api->godot_free(p_image_manager);
}

void DISCORD_API fetch_callback(CallbackData *p_data,
                                enum EDiscordResult p_result, struct DiscordImageHandle p_handle)
{
    Library *lib = p_data->lib;

    godot_variant result_variant;
    godot_variant handle_variant;

    godot_object *handle_object = instantiate_custom_class("ImageHandle", "Resource", lib);
    ImageHandle *handle = lib->nativescript_api->godot_nativescript_get_userdata(handle_object);

    memcpy(handle->internal, &p_handle, sizeof(struct DiscordImageHandle));

    lib->api->godot_variant_new_int(&result_variant, p_result);
    lib->api->godot_variant_new_object(&handle_variant, handle_object);

    godot_variant *args[] = {&result_variant, &handle_variant};

    object_call(p_data->callback_object, &p_data->callback_name, 2, args, p_data->lib);

    lib->api->godot_free(p_data);
}

godot_variant image_manager_fetch(godot_object *p_instance, Library *p_lib,
                                  ImageManager *p_image_manager,
                                  int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 4) // Handle, Refresh, Callback Object, Callback Name
    {
        godot_object *handle_object = p_lib->api->godot_variant_as_object(p_args[0]);
        bool refresh = p_lib->api->godot_variant_as_bool(p_args[1]);
        godot_object *callback_object = p_lib->api->godot_variant_as_object(p_args[2]);
        godot_string callback_name = p_lib->api->godot_variant_as_string(p_args[3]);

        ImageHandle *handle = p_lib->nativescript_api->godot_nativescript_get_userdata(handle_object);

        CallbackData *callback_data = p_lib->api->godot_alloc(sizeof(CallbackData));
        callback_data->callback_object = callback_object;
        callback_data->callback_name = callback_name;
        callback_data->core = p_image_manager->core;
        callback_data->lib = p_lib;

        p_image_manager->internal->fetch(p_image_manager->internal,
                                         *handle->internal, refresh,
                                         callback_data, fetch_callback);

        p_lib->api->godot_variant_new_nil(&result_variant);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

godot_variant image_manager_get_dimensions(godot_object *p_instance, Library *p_lib,
                                           ImageManager *p_image_manager,
                                           int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1) // Handle
    {
        godot_object *handle_object = p_lib->api->godot_variant_as_object(p_args[0]);
        ImageHandle *handle = p_lib->nativescript_api->godot_nativescript_get_userdata(handle_object);

        godot_object *dimensions_object = instantiate_custom_class("ImageDimensions", "Resource", p_lib);
        ImageDimensions *dimensions = p_lib->nativescript_api->godot_nativescript_get_userdata(dimensions_object);

        enum EDiscordResult result = p_image_manager->internal->get_dimensions(p_image_manager->internal,
                                                                               *handle->internal, dimensions->internal);

        if (result == DiscordResult_Ok)
        {
            p_lib->api->godot_variant_new_object(&result_variant, dimensions_object);
        }
        else
        {
            p_lib->api->godot_variant_new_int(&result_variant, result);
        }
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

godot_variant image_manager_get_data(godot_object *p_instance, Library *p_lib,
                                     ImageManager *p_image_manager,
                                     int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1) // Handle
    {
        godot_object *handle_object = p_lib->api->godot_variant_as_object(p_args[0]);
        ImageHandle *handle = p_lib->nativescript_api->godot_nativescript_get_userdata(handle_object);

        struct DiscordImageDimensions dimensions;
        {
            enum EDiscordResult result = p_image_manager->internal->get_dimensions(p_image_manager->internal,
                                                                                   *handle->internal, &dimensions);
            if (result != DiscordResult_Ok)
            {
                p_lib->api->godot_variant_new_int(&result_variant, result);
                return result_variant;
            }
        }

        uint32_t size = dimensions.width * dimensions.height * 4;
        uint8_t *bytes = p_lib->api->godot_alloc(sizeof(uint8_t) * size);

        enum EDiscordResult result = p_image_manager->internal->get_data(p_image_manager->internal,
                                                                         *handle->internal,
                                                                         bytes, size);

        if (result == DiscordResult_Ok)
        {
            godot_pool_byte_array array;
            p_lib->api->godot_pool_byte_array_new(&array);

            for (unsigned int i = 0; i < size; i++)
            {
                p_lib->api->godot_pool_byte_array_append(&array, bytes[i]);
            }

            p_lib->api->godot_variant_new_pool_byte_array(&result_variant, &array);
        }
        else
        {
            p_lib->api->godot_variant_new_int(&result_variant, result);
        }

        p_lib->api->godot_free(bytes);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

void register_image_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = image_manager_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = image_manager_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ImageManager", "Reference",
                                                               constructor, destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Fetch
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = image_manager_fetch;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "ImageManager", "fetch",
                                                                        attributes, method);
        }
        // Get Dimensions
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = image_manager_get_dimensions;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "ImageManager", "get_dimensions",
                                                                        attributes, method);
        }
        // Get Data
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = image_manager_get_data;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "ImageManager", "get_data",
                                                                        attributes, method);
        }
    }
}
