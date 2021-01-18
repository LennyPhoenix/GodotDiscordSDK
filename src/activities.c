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
