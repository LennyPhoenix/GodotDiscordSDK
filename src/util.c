#include "util.h"

godot_object *instantiate_custom_class(const char *p_class_name, const char *p_base,
                                       Library *p_lib)
{
    godot_string class_name;

    p_lib->api->godot_string_new(&class_name);
    p_lib->api->godot_string_parse_utf8(&class_name, p_class_name);

    godot_object *script;
    // Get the script object
    {
        godot_string script_path_string;

        // Get the .gdns path
        {
            godot_string path_string;
            { // Get the .gdnlib path
                godot_method_bind *mb_get_path = p_lib->api->godot_method_bind_get_method("Resource", "get_path");

                godot_variant_call_error error;
                godot_variant ret = p_lib->api->godot_method_bind_call(mb_get_path, (godot_object *)p_lib->gdnlib, NULL, 0, &error);

                path_string = p_lib->api->godot_variant_as_string(&ret);
            }
            godot_char_string path_char_string = p_lib->api->godot_string_utf8(&path_string);

            const char *path = p_lib->api->godot_char_string_get_data(&path_char_string);
            int path_size = p_lib->api->godot_char_string_length(&path_char_string);

            // Get script name
            godot_string script_name_string = p_lib->api->godot_string_camelcase_to_underscore_lowercased(&class_name);
            godot_char_string script_name_char_string = p_lib->api->godot_string_utf8(&script_name_string);
            const char *script_name = p_lib->api->godot_char_string_get_data(&script_name_char_string);
            int script_name_size = p_lib->api->godot_char_string_length(&script_name_char_string);

            // Get folder of script
            int last_slash_char;
            for (int i = 0; i < path_size; i++)
            {
                if (path[i] == '/')
                {
                    last_slash_char = i + 1;
                }
            }

            // Join the strings together
            char *script_path = calloc(last_slash_char + script_name_size + 6, sizeof(char));
            memcpy(script_path, path, sizeof(char) * last_slash_char);
            memcpy(script_path + last_slash_char, script_name, sizeof(char) * script_name_size);
            memcpy(script_path + last_slash_char + script_name_size, ".gdns", sizeof(char) * 5);

            script_path_string = p_lib->api->godot_string_chars_to_utf8(script_path);

            free(script_path);
        }

        // Load the script
        godot_object *resource_loader = p_lib->api->godot_global_get_singleton("ResourceLoader");

        godot_variant resource_loader_variant;
        p_lib->api->godot_variant_new_object(&resource_loader_variant, resource_loader);

        godot_string method_name = p_lib->api->godot_string_chars_to_utf8("load");

        godot_variant path_variant;
        p_lib->api->godot_variant_new_string(&path_variant, &script_path_string);

        godot_variant *args[] = {&path_variant};

        godot_variant_call_error error;
        godot_variant script_variant = p_lib->api->godot_variant_call(&resource_loader_variant,
                                                                      &method_name,
                                                                      args, 1,
                                                                      &error);

        script = p_lib->api->godot_variant_as_object(&script_variant);
    }

    // Construct the base object
    godot_class_constructor base_constructor = p_lib->api->godot_get_class_constructor(p_base);
    godot_method_bind *mb_set_script = p_lib->api->godot_method_bind_get_method("Object", "set_script");
    godot_object *base_obj = base_constructor();
    // Add the script
    {
        const void *args[] = {script};
        p_lib->api->godot_method_bind_ptrcall(mb_set_script, base_obj, args, NULL);
    }

    // p_lib->api->godot_object_destroy(script);
    p_lib->api->godot_string_destroy(&class_name);

    return base_obj;
}

godot_variant_call_error object_emit_signal(godot_object *p_object,
                                            const char *p_signal_name,
                                            int p_num_args, godot_variant *p_args,
                                            Library *p_lib)
{
    godot_variant variant;
    p_lib->api->godot_variant_new_object(&variant, p_object);

    godot_string method_name;
    p_lib->api->godot_string_new(&method_name);
    p_lib->api->godot_string_parse_utf8(&method_name, "emit_signal");

    godot_variant **args = calloc(p_num_args + 1, sizeof(godot_variant *));

    godot_string signal_name;
    p_lib->api->godot_string_new(&signal_name);
    p_lib->api->godot_string_parse_utf8(&signal_name, p_signal_name);

    godot_variant variant_signal_name;
    p_lib->api->godot_variant_new_string(&variant_signal_name, &signal_name);
    p_lib->api->godot_string_destroy(&signal_name);

    args[0] = &variant_signal_name;

    for (int i = 0; i < p_num_args; i++)
    {
        args[i + 1] = &p_args[i];
    }

    godot_variant_call_error error;
    p_lib->api->godot_variant_call(&variant, &method_name, args, p_num_args + 1, &error);

    p_lib->api->godot_variant_destroy(&variant);
    p_lib->api->godot_string_destroy(&method_name);
    p_lib->api->godot_variant_destroy(&variant_signal_name);

    return error;
}
