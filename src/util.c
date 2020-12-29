#include "util.h"

godot_object *instantiate_custom_class(const char *p_class_name, const char *p_base,
                                       Library *p_lib)
{
    godot_string class_name;

    p_lib->api->godot_string_new(&class_name);
    p_lib->api->godot_string_parse_utf8(&class_name, p_class_name);

    godot_class_constructor script_constructor = p_lib->api->godot_get_class_constructor("NativeScript");
    godot_method_bind *mb_set_library = p_lib->api->godot_method_bind_get_method("NativeScript", "set_library");
    godot_method_bind *mb_set_class_name = p_lib->api->godot_method_bind_get_method("NativeScript", "set_class_name");
    godot_object *script = script_constructor();
    {
        const void *args[] = {p_lib->gdnlib};
        p_lib->api->godot_method_bind_ptrcall(mb_set_library, script, args, NULL);
    }
    {
        const void *args[] = {&class_name};
        p_lib->api->godot_method_bind_ptrcall(mb_set_class_name, script, args, NULL);
    }

    godot_class_constructor base_constructor = p_lib->api->godot_get_class_constructor(p_base);
    godot_method_bind *mb_set_script = p_lib->api->godot_method_bind_get_method("Object", "set_script");
    godot_object *base_obj = base_constructor();
    {
        const void *args[] = {script};
        p_lib->api->godot_method_bind_ptrcall(mb_set_script, base_obj, args, NULL);
    }

    p_lib->api->godot_string_destroy(&class_name);

    return base_obj;
}