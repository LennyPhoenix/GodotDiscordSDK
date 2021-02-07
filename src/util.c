#include "util.h"

godot_string get_script_path(godot_string *p_class_name,
                             Library *p_lib)
{
    // Get the .gdnlib path
    char *gdnlib_path;
    int gdnlib_path_size;
    {
        godot_method_bind *mb_get_path = p_lib->api->godot_method_bind_get_method("Resource", "get_path");

        godot_variant_call_error error;
        godot_variant ret = p_lib->api->godot_method_bind_call(mb_get_path, (godot_object *)p_lib->gdnlib, NULL, 0, &error);

        godot_string gdnlib_path_string = p_lib->api->godot_variant_as_string(&ret);
        godot_char_string gdnlib_path_char_string = p_lib->api->godot_string_utf8(&gdnlib_path_string);

        gdnlib_path = (char *)p_lib->api->godot_char_string_get_data(&gdnlib_path_char_string);
        gdnlib_path_size = p_lib->api->godot_char_string_length(&gdnlib_path_char_string);
    }

    // Get script name
    char *script_name;
    int script_name_size;
    {
        godot_string script_name_string = p_lib->api->godot_string_camelcase_to_underscore_lowercased(p_class_name);
        godot_char_string script_name_char_string = p_lib->api->godot_string_utf8(&script_name_string);

        script_name = (char *)p_lib->api->godot_char_string_get_data(&script_name_char_string);
        script_name_size = p_lib->api->godot_char_string_length(&script_name_char_string);
    }

    // Get folder of script
    int last_slash_char;
    for (int i = 0; i < gdnlib_path_size; i++)
    {
        if (gdnlib_path[i] == '/')
        {
            last_slash_char = i + 1;
        }
    }

    // Join the strings together
    char *script_path = p_lib->api->godot_alloc(sizeof(char) * (last_slash_char + script_name_size + 6));
    memset(script_path, 0, sizeof(char) * (last_slash_char + script_name_size + 6));
    memcpy(script_path, gdnlib_path, last_slash_char * sizeof(char));
    memcpy(script_path + last_slash_char, script_name, script_name_size * sizeof(char));
    memcpy(script_path + last_slash_char + script_name_size, ".gdns", 5 * sizeof(char));

    godot_string script_path_string = p_lib->api->godot_string_chars_to_utf8(script_path);

    p_lib->api->godot_free(script_path);

    return script_path_string;
}

godot_object *instantiate_custom_class(const char *p_class_name, const char *p_base,
                                       Library *p_lib)
{
    godot_string class_name = p_lib->api->godot_string_chars_to_utf8(p_class_name);

    // Get the script object
    godot_object *script;
    {
        godot_string script_path_string = get_script_path(&class_name, p_lib);

        // Load the script
        godot_object *resource_loader = p_lib->api->godot_global_get_singleton("ResourceLoader");

        godot_variant resource_loader_variant;
        p_lib->api->godot_variant_new_object(&resource_loader_variant, resource_loader);

        godot_variant path_variant;
        p_lib->api->godot_variant_new_string(&path_variant, &script_path_string);

        godot_variant script_variant;
        {
            godot_variant *args[] = {&path_variant};

            godot_string method_name = p_lib->api->godot_string_chars_to_utf8("load");

            godot_variant_call_error error;
            script_variant = p_lib->api->godot_variant_call(&resource_loader_variant,
                                                            &method_name,
                                                            args, 1,
                                                            &error);
        }

        script = p_lib->api->godot_variant_as_object(&script_variant);
    }

    // Construct the base object
    godot_class_constructor base_constructor = p_lib->api->godot_get_class_constructor(p_base);
    godot_object *object = base_constructor();

    // Add the script
    {
        static godot_method_bind *bind = NULL;
        if (!bind)
            bind = p_lib->api->godot_method_bind_get_method("Object", "set_script");

        const void *args[] = {script};

        p_lib->api->godot_method_bind_ptrcall(bind, object, args, NULL);
    }

    return object;
}

godot_variant_call_error object_emit_signal(godot_object *p_object,
                                            godot_string *p_signal_name,
                                            int p_num_args, godot_variant **p_args,
                                            Library *p_lib)
{
    godot_variant variant;
    p_lib->api->godot_variant_new_object(&variant, p_object);

    godot_string method_name = p_lib->api->godot_string_chars_to_utf8("emit_signal");

    godot_variant **args = p_lib->api->godot_alloc(sizeof(godot_variant *) * (p_num_args + 1));

    godot_variant variant_signal_name;
    p_lib->api->godot_variant_new_string(&variant_signal_name, p_signal_name);

    args[0] = &variant_signal_name;

    for (int i = 0; i < p_num_args; i++)
    {
        args[i + 1] = p_args[i];
    }

    godot_variant_call_error error;
    p_lib->api->godot_variant_call(&variant, &method_name, args, p_num_args + 1, &error);

    p_lib->api->godot_free(args);

    return error;
}

godot_variant_call_error object_call(godot_object *p_object,
                                     godot_string *p_method_name,
                                     int p_num_args, godot_variant **p_args,
                                     Library *p_lib)
{
    godot_variant variant;
    p_lib->api->godot_variant_new_object(&variant, p_object);

    godot_variant **args = p_lib->api->godot_alloc(sizeof(godot_variant *) * (p_num_args + 1));

    godot_variant variant_method_name;
    p_lib->api->godot_variant_new_string(&variant_method_name, p_method_name);
    args[0] = &variant_method_name;

    for (int i = 0; i < p_num_args; i++)
    {
        args[i + 1] = p_args[i];
    }

    godot_string method_name = p_lib->api->godot_string_chars_to_utf8("call");

    godot_variant_call_error error;
    p_lib->api->godot_variant_call(&variant, &method_name, args, p_num_args + 1, &error);

    p_lib->api->godot_free(args);

    return error;
}

void godot_reference(godot_object *p_object, Library *p_lib)
{
    static godot_method_bind *bind = NULL;
    if (!bind)
        bind = p_lib->api->godot_method_bind_get_method("Reference", "reference");
    godot_bool ret;
    p_lib->api->godot_method_bind_ptrcall(bind, p_object, NULL, &ret);
}

void godot_unreference(godot_object *p_object, Library *p_lib)
{
    static godot_method_bind *bind = NULL;
    if (!bind)
        bind = p_lib->api->godot_method_bind_get_method("Reference", "unreference");
    godot_bool ret;
    p_lib->api->godot_method_bind_ptrcall(bind, p_object, NULL, &ret); // this returns `true` if the reference count is now at zero...
    if (ret)
        p_lib->api->godot_object_destroy(p_object); // ...in which case, delete the object
}
