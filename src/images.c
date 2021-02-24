#include "images.h"

#include "util.h"

GDCALLINGCONV void *image_manager_constructor(godot_object *p_instance, Library *p_lib)
{
    ImageManager *image_manager = p_lib->core_api->godot_alloc(sizeof(ImageManager));

    image_manager->object = p_instance;
    image_manager->lib = p_lib;

    return image_manager;
}

GDCALLINGCONV void image_manager_destructor(godot_object *p_instance, Library *p_lib,
                                            ImageManager *p_image_manager)
{
    p_lib->core_api->godot_free(p_image_manager);
}

void fetch_callback(CallbackData *p_data,
                    enum EDiscordResult p_result, struct DiscordImageHandle p_handle)
{
    Library *lib = p_data->lib;

    godot_variant result_variant;
    godot_variant handle_variant;

    godot_object *handle_object = instantiate_custom_class("ImageHandle", "Resource", lib);
    ImageHandle *handle = lib->nativescript_api->godot_nativescript_get_userdata(handle_object);

    memcpy(handle->internal, &p_handle, sizeof(struct DiscordImageHandle));

    lib->core_api->godot_variant_new_int(&result_variant, p_result);
    lib->core_api->godot_variant_new_object(&handle_variant, handle_object);

    godot_variant *args[] = {&result_variant, &handle_variant};

    if (p_data->callback_object)
    {
        if (lib->core_1_1_api->godot_is_instance_valid(p_data->callback_object))
            object_call(p_data->callback_object, &p_data->callback_name, 2, args, lib);
        else
            PRINT_ERROR("Callback object is no longer a valid instance.", lib);

        lib->core_api->godot_string_destroy(&p_data->callback_name);
    }

    godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("fetch_callback");
    object_emit_signal(p_data->core->images->object, &signal_name, 2, args, lib);

    lib->core_api->godot_string_destroy(&signal_name);
    lib->core_api->godot_variant_destroy(&handle_variant);
    lib->core_api->godot_variant_destroy(&result_variant);
    lib->core_api->godot_free(p_data);
}

godot_variant image_manager_fetch(godot_object *p_instance, Library *p_lib,
                                  ImageManager *p_image_manager,
                                  int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 2 || p_num_args == 4) // Handle, Refresh, [Callback Object, Callback Name]
    {
        godot_object *handle_object = p_lib->core_api->godot_variant_as_object(p_args[0]);
        bool refresh = p_lib->core_api->godot_variant_as_bool(p_args[1]);

        ImageHandle *handle = p_lib->nativescript_api->godot_nativescript_get_userdata(handle_object);

        CallbackData *callback_data = p_lib->core_api->godot_alloc(sizeof(CallbackData));
        memset(callback_data, 0, sizeof(CallbackData));
        callback_data->core = p_image_manager->core;
        callback_data->lib = p_lib;

        if (p_num_args == 4)
        {
            godot_object *callback_object = p_lib->core_api->godot_variant_as_object(p_args[2]);
            godot_string callback_name = p_lib->core_api->godot_variant_as_string(p_args[3]);
            callback_data->callback_object = callback_object;
            callback_data->callback_name = callback_name;
        }

        p_image_manager->internal->fetch(p_image_manager->internal,
                                         *handle->internal, refresh,
                                         callback_data, fetch_callback);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"fetch()\" call. Expected 2 or 4.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant image_manager_get_dimensions(godot_object *p_instance, Library *p_lib,
                                           ImageManager *p_image_manager,
                                           int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // Handle, [Callback Object, Callback Name]
    {
        godot_object *handle_object = p_lib->core_api->godot_variant_as_object(p_args[0]);
        ImageHandle *handle = p_lib->nativescript_api->godot_nativescript_get_userdata(handle_object);

        godot_object *dimensions_object = instantiate_custom_class("ImageDimensions", "Resource", p_lib);
        ImageDimensions *dimensions = p_lib->nativescript_api->godot_nativescript_get_userdata(dimensions_object);

        enum EDiscordResult result = p_image_manager->internal->get_dimensions(p_image_manager->internal,
                                                                               *handle->internal, dimensions->internal);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant dimensions_variant;

            p_lib->core_api->godot_variant_new_int(&result_variant, result);
            p_lib->core_api->godot_variant_new_object(&dimensions_variant, dimensions_object);

            godot_variant *args[] = {&result_variant, &dimensions_variant};

            if (p_num_args == 3)
            {
                godot_object *callback_object = p_lib->core_api->godot_variant_as_object(p_args[1]);
                godot_string callback_name = p_lib->core_api->godot_variant_as_string(p_args[2]);

                if (p_lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, p_lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", p_lib);

                p_lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = p_lib->core_api->godot_string_chars_to_utf8("get_dimensions_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, p_lib);

            p_lib->core_api->godot_string_destroy(&signal_name);
            p_lib->core_api->godot_variant_destroy(&dimensions_variant);
            p_lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_dimensions()\" call. Expected 1 or 3.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant image_manager_get_data(godot_object *p_instance, Library *p_lib,
                                     ImageManager *p_image_manager,
                                     int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // Handle, [Callback Object, Callback Name]
    {
        godot_object *handle_object = p_lib->core_api->godot_variant_as_object(p_args[0]);
        ImageHandle *handle = p_lib->nativescript_api->godot_nativescript_get_userdata(handle_object);

        enum EDiscordResult result;
        godot_pool_byte_array data;
        p_lib->core_api->godot_pool_byte_array_new(&data);

        // Get Data
        {
            struct DiscordImageDimensions dimensions;
            result = p_image_manager->internal->get_dimensions(p_image_manager->internal,
                                                               *handle->internal, &dimensions);

            if (result == DiscordResult_Ok)
            {
                uint32_t size = dimensions.width * dimensions.height * 4;
                uint8_t *bytes = p_lib->core_api->godot_alloc(sizeof(uint8_t) * size);

                result = p_image_manager->internal->get_data(p_image_manager->internal,
                                                             *handle->internal,
                                                             bytes, size);

                if (result == DiscordResult_Ok)
                    for (unsigned int i = 0; i < size; i++)
                        p_lib->core_api->godot_pool_byte_array_append(&data, bytes[i]);

                p_lib->core_api->godot_free(bytes);
            }
        }

        // Run Callbacks
        {
            godot_variant result_variant;
            godot_variant data_variant;

            p_lib->core_api->godot_variant_new_int(&result_variant, result);
            p_lib->core_api->godot_variant_new_pool_byte_array(&data_variant, &data);

            godot_variant *args[] = {&result_variant, &data_variant};

            if (p_num_args == 3)
            {
                godot_object *callback_object = p_lib->core_api->godot_variant_as_object(p_args[1]);
                godot_string callback_name = p_lib->core_api->godot_variant_as_string(p_args[2]);

                if (p_lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, p_lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", p_lib);

                p_lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = p_lib->core_api->godot_string_chars_to_utf8("get_data_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, p_lib);

            p_lib->core_api->godot_string_destroy(&signal_name);
            p_lib->core_api->godot_variant_destroy(&data_variant);
            p_lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_data()\" call. Expected 1 or 3.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

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

    // Signals
    {
        godot_signal signal;

        // Fetch Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("fetch_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument handle;
            {
                memset(&handle, 0, sizeof(godot_signal_argument));
                handle.name = p_lib->core_api->godot_string_chars_to_utf8("handle");

                handle.type = GODOT_VARIANT_TYPE_OBJECT;
            }

            godot_signal_argument args[] = {result, handle};
            signal.args = args;
            signal.num_args = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "ImageManager", &signal);

            p_lib->core_api->godot_string_destroy(&handle.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Get Dimensions Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("get_dimensions_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument dimensions;
            {
                memset(&dimensions, 0, sizeof(godot_signal_argument));
                dimensions.name = p_lib->core_api->godot_string_chars_to_utf8("dimensions");

                dimensions.type = GODOT_VARIANT_TYPE_OBJECT;
            }

            godot_signal_argument args[] = {result, dimensions};
            signal.args = args;
            signal.num_args = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "ImageManager", &signal);

            p_lib->core_api->godot_string_destroy(&dimensions.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Get Data Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("get_data_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument data;
            {
                memset(&data, 0, sizeof(godot_signal_argument));
                data.name = p_lib->core_api->godot_string_chars_to_utf8("data");

                data.type = GODOT_VARIANT_TYPE_POOL_BYTE_ARRAY;
            }

            godot_signal_argument args[] = {result, data};
            signal.args = args;
            signal.num_args = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "ImageManager", &signal);

            p_lib->core_api->godot_string_destroy(&data.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
    }
}
