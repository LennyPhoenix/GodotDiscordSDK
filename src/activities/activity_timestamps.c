#include "activity_timestamps.h"

#include "util.h"

GDCALLINGCONV void *activity_timestamps_constructor(godot_object *p_instance, void *p_method_data)
{
    Library *lib = p_method_data;

    INIT_OBJECT(timestamps, ActivityTimestamps, struct DiscordActivityTimestamps, lib, p_instance);

    return timestamps;
}

GDCALLINGCONV void activity_timestamps_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib                   = p_method_data;
    ActivityTimestamps *timestamps = p_user_data;

    lib->core_api->godot_free(timestamps->internal);
    lib->core_api->godot_free(timestamps);
}

godot_variant activity_timestamps_get_start(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib                   = p_method_data;
    ActivityTimestamps *timestamps = p_user_data;

    godot_variant start;

    lib->core_api->godot_variant_new_int(&start, timestamps->internal->start);

    return start;
}

GDCALLINGCONV void activity_timestamps_set_start(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                                 godot_variant *p_start)
{
    Library *lib                   = p_method_data;
    ActivityTimestamps *timestamps = p_user_data;

    timestamps->internal->start = lib->core_api->godot_variant_as_int(p_start);
}

godot_variant activity_timestamps_get_end(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib                   = p_method_data;
    ActivityTimestamps *timestamps = p_user_data;

    godot_variant end;

    lib->core_api->godot_variant_new_int(&end, timestamps->internal->end);

    return end;
}

GDCALLINGCONV void activity_timestamps_set_end(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                               godot_variant *p_end)
{
    Library *lib                   = p_method_data;
    ActivityTimestamps *timestamps = p_user_data;

    timestamps->internal->end = lib->core_api->godot_variant_as_int(p_end);
}

void register_activity_timestamps(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = activity_timestamps_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = activity_timestamps_destructor;
    destructor.method_data  = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle, "ActivityTimestamps", "Resource", constructor,
                                                               destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // Start
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type  = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func    = activity_timestamps_get_start;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func    = activity_timestamps_set_start;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle, "ActivityTimestamps", "start",
                                                                          &attributes, set, get);
        }
        // End
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type  = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func    = activity_timestamps_get_end;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func    = activity_timestamps_set_end;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle, "ActivityTimestamps", "end",
                                                                          &attributes, set, get);
        }
    }
}
