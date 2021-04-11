#include "presence.h"

#include "activities/activity.h"
#include "util.h"

GDCALLINGCONV void *presence_constructor(godot_object *p_instance, void *p_method_data)
{
    Library *lib = p_method_data;

    INIT_OBJECT(presence, Presence, struct DiscordPresence, lib, p_instance);

    presence->activity = instantiate_custom_class("Activity", "Resource", lib);
    godot_reference(presence->activity, lib);

    return presence;
}

GDCALLINGCONV void presence_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib       = p_method_data;
    Presence *presence = p_user_data;

    if (presence->activity)
        godot_unreference(presence->activity, lib);

    lib->core_api->godot_free(presence->internal);
    lib->core_api->godot_free(presence);
}

godot_variant presence_get_status(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib       = p_method_data;
    Presence *presence = p_user_data;

    godot_variant status;

    lib->core_api->godot_variant_new_int(&status, presence->internal->status);

    return status;
}

GDCALLINGCONV void presence_set_status(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                       godot_variant *p_status)
{
    Library *lib       = p_method_data;
    Presence *presence = p_user_data;

    presence->internal->status = lib->core_api->godot_variant_as_int(p_status);
}

godot_variant presence_get_activity(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib       = p_method_data;
    Presence *presence = p_user_data;

    godot_variant activity;

    lib->core_api->godot_variant_new_object(&activity, presence->activity);

    return activity;
}

GDCALLINGCONV void presence_set_activity(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                         godot_variant *p_activity)
{
    Library *lib       = p_method_data;
    Presence *presence = p_user_data;

    if (presence->activity)
        godot_unreference(presence->activity, lib);

    presence->activity = lib->core_api->godot_variant_as_object(p_activity);

    if (presence->activity)
        godot_reference(presence->activity, lib);
}

struct DiscordPresence *presence_collapse(godot_object *p_instance, Library *p_lib)
{
    Presence *presence = p_lib->nativescript_api->godot_nativescript_get_userdata(p_instance);

    presence->internal->activity = *activity_collapse(presence->activity, p_lib);

    return presence->internal;
}

void presence_reconstruct(godot_object *p_instance, struct DiscordPresence *p_presence, Library *p_lib)
{
    Presence *presence  = p_lib->nativescript_api->godot_nativescript_get_userdata(p_instance);
    *presence->internal = *p_presence;

    Activity *activity  = p_lib->nativescript_api->godot_nativescript_get_userdata(presence->activity);
    *activity->internal = p_presence->activity;
    activity_reconstruct(presence->activity, &p_presence->activity, p_lib);
}

void register_presence(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = presence_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = presence_destructor;
    destructor.method_data  = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle, "Presence", "Resource", constructor,
                                                               destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // Status
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type  = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            attributes.hint        = GODOT_PROPERTY_HINT_ENUM;
            attributes.hint_string = p_lib->core_api->godot_string_chars_to_utf8("Offline,Online,Idle,Do Not Disturb");

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func    = presence_get_status;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func    = presence_set_status;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle, "Presence", "status", &attributes,
                                                                          set, get);

            p_lib->core_api->godot_string_destroy(&attributes.hint_string);
        }
        // Activity
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type  = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func    = presence_get_activity;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func    = presence_set_activity;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle, "Presence", "activity", &attributes,
                                                                          set, get);
        }
    }
}
