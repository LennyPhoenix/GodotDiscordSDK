#include "activity.h"

#include "util.h"

#include "activities/activity_timestamps.h"
#include "activities/activity_assets.h"
#include "activities/party_size.h"
#include "activities/activity_party.h"
#include "activities/activity_secrets.h"

GDCALLINGCONV void *activity_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(activity,
                Activity, struct DiscordActivity,
                p_lib, p_instance);

    activity->timestamps = instantiate_custom_class("ActivityTimestamps", "Resource", p_lib);
    godot_reference(activity->timestamps, p_lib);

    activity->assets = instantiate_custom_class("ActivityAssets", "Resource", p_lib);
    godot_reference(activity->assets, p_lib);

    activity->party = instantiate_custom_class("ActivityParty", "Resource", p_lib);
    godot_reference(activity->party, p_lib);

    activity->secrets = instantiate_custom_class("ActivitySecrets", "Resource", p_lib);
    godot_reference(activity->secrets, p_lib);

    return activity;
}

GDCALLINGCONV void activity_destructor(godot_object *p_instance, Library *p_lib,
                                       Activity *p_activity)
{
    if (p_activity->timestamps)
        godot_unreference(p_activity->timestamps, p_lib);

    if (p_activity->assets)
        godot_unreference(p_activity->assets, p_lib);

    if (p_activity->party)
        godot_unreference(p_activity->party, p_lib);

    if (p_activity->secrets)
        godot_unreference(p_activity->secrets, p_lib);

    p_lib->core_api->godot_free(p_activity->internal);
    p_lib->core_api->godot_free(p_activity);
}

godot_variant activity_get_application_id(godot_object *p_instance, Library *p_lib,
                                          Activity *p_activity)
{
    godot_variant application_id;

    p_lib->core_api->godot_variant_new_int(&application_id, p_activity->internal->application_id);

    return application_id;
}

GDCALLINGCONV void activity_set_application_id(godot_object *p_instance, Library *p_lib,
                                               Activity *p_activity,
                                               godot_variant *p_application_id)
{
    PRINT_ERROR("Attempted to write to readonly property \"application_id\".", p_lib);
}

godot_variant activity_get_name(godot_object *p_instance, Library *p_lib,
                                Activity *p_activity)
{
    godot_variant name;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_activity->internal->name);
    p_lib->core_api->godot_variant_new_string(&name, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return name;
}

GDCALLINGCONV void activity_set_name(godot_object *p_instance, Library *p_lib,
                                     Activity *p_activity,
                                     godot_variant *p_name)
{
    PRINT_ERROR("Attempted to write to readonly property \"name\".", p_lib);
}

godot_variant activity_get_state(godot_object *p_instance, Library *p_lib,
                                 Activity *p_activity)
{
    godot_variant state;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_activity->internal->state);
    p_lib->core_api->godot_variant_new_string(&state, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return state;
}

GDCALLINGCONV void activity_set_state(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity,
                                      godot_variant *p_state)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_state);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *state = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_activity->internal->state, 0, sizeof(char) * 128);
    memcpy(p_activity->internal->state, state, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant activity_get_details(godot_object *p_instance, Library *p_lib,
                                   Activity *p_activity)
{
    godot_variant details;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_activity->internal->details);
    p_lib->core_api->godot_variant_new_string(&details, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return details;
}

GDCALLINGCONV void activity_set_details(godot_object *p_instance, Library *p_lib,
                                        Activity *p_activity,
                                        godot_variant *p_details)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_details);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *details = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_activity->internal->details, 0, sizeof(char) * 128);
    memcpy(p_activity->internal->details, details, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant activity_get_timestamps(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity)
{
    godot_variant timestamps;

    p_lib->core_api->godot_variant_new_object(&timestamps, p_activity->timestamps);

    return timestamps;
}

GDCALLINGCONV void activity_set_timestamps(godot_object *p_instance, Library *p_lib,
                                           Activity *p_activity,
                                           godot_variant *p_timestamps)
{
    if (p_activity->timestamps)
        godot_unreference(p_activity->timestamps, p_lib);

    p_activity->timestamps = p_lib->core_api->godot_variant_as_object(p_timestamps);

    if (p_activity->timestamps)
        godot_reference(p_activity->timestamps, p_lib);
}

godot_variant activity_get_assets(godot_object *p_instance, Library *p_lib,
                                  Activity *p_activity)
{
    godot_variant assets;

    p_lib->core_api->godot_variant_new_object(&assets, p_activity->assets);

    return assets;
}

GDCALLINGCONV void activity_set_assets(godot_object *p_instance, Library *p_lib,
                                       Activity *p_activity,
                                       godot_variant *p_assets)
{
    if (p_activity->assets)
        godot_unreference(p_activity->assets, p_lib);

    p_activity->assets = p_lib->core_api->godot_variant_as_object(p_assets);

    if (p_activity->assets)
        godot_reference(p_activity->assets, p_lib);
}

godot_variant activity_get_party(godot_object *p_instance, Library *p_lib,
                                 Activity *p_activity)
{
    godot_variant party;

    p_lib->core_api->godot_variant_new_object(&party, p_activity->party);

    return party;
}

GDCALLINGCONV void activity_set_party(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity,
                                      godot_variant *p_party)
{
    if (p_activity->party)
        godot_unreference(p_activity->party, p_lib);

    p_activity->party = p_lib->core_api->godot_variant_as_object(p_party);

    if (p_activity->party)
        godot_reference(p_activity->party, p_lib);
}

godot_variant activity_get_secrets(godot_object *p_instance, Library *p_lib,
                                   Activity *p_activity)
{
    godot_variant secrets;

    p_lib->core_api->godot_variant_new_object(&secrets, p_activity->secrets);

    return secrets;
}

GDCALLINGCONV void activity_set_secrets(godot_object *p_instance, Library *p_lib,
                                        Activity *p_activity,
                                        godot_variant *p_secrets)
{
    if (p_activity->secrets)
        godot_unreference(p_activity->secrets, p_lib);

    p_activity->secrets = p_lib->core_api->godot_variant_as_object(p_secrets);

    if (p_activity->secrets)
        godot_reference(p_activity->secrets, p_lib);
}

godot_variant activity_get_instance(godot_object *p_instance, Library *p_lib,
                                    Activity *p_activity)
{
    godot_variant instance;

    p_lib->core_api->godot_variant_new_bool(&instance, p_activity->internal->instance);

    return instance;
}

GDCALLINGCONV void activity_set_instance(godot_object *p_instance, Library *p_lib,
                                         Activity *p_activity,
                                         godot_variant *p_is_instance)
{
    p_activity->internal->instance = p_lib->core_api->godot_variant_as_bool(p_is_instance);
}

struct DiscordActivity *activity_collapse(godot_object *p_instance, Library *p_lib)
{
    Activity *activity = p_lib->nativescript_api->godot_nativescript_get_userdata(p_instance);

    ActivityTimestamps *timestamps = p_lib->nativescript_api->godot_nativescript_get_userdata(activity->timestamps);
    ActivityAssets *assets = p_lib->nativescript_api->godot_nativescript_get_userdata(activity->assets);
    ActivityParty *party = p_lib->nativescript_api->godot_nativescript_get_userdata(activity->party);
    ActivitySecrets *secrets = p_lib->nativescript_api->godot_nativescript_get_userdata(activity->secrets);

    activity_party_collapse(activity->party, p_lib);

    memcpy(&activity->internal->timestamps, timestamps->internal, sizeof(struct DiscordActivityTimestamps));
    memcpy(&activity->internal->assets, assets->internal, sizeof(struct DiscordActivityAssets));
    memcpy(&activity->internal->party, party->internal, sizeof(struct DiscordActivityParty));
    memcpy(&activity->internal->secrets, secrets->internal, sizeof(struct DiscordActivitySecrets));

    return activity->internal;
}

void activity_reconstruct(godot_object *p_instance, struct DiscordActivity *p_activity, Library *p_lib)
{
    Activity *activity = p_lib->nativescript_api->godot_nativescript_get_userdata(p_instance);
    memcpy(activity->internal, p_activity, sizeof(struct DiscordActivity));
    ActivityTimestamps *activity_timestamps = p_lib->nativescript_api->godot_nativescript_get_userdata(activity->timestamps);
    memcpy(activity_timestamps->internal, &p_activity->timestamps, sizeof(struct DiscordActivityTimestamps));
    ActivityAssets *activity_assets = p_lib->nativescript_api->godot_nativescript_get_userdata(activity->assets);
    memcpy(activity_assets->internal, &p_activity->assets, sizeof(struct DiscordActivityAssets));
    activity_party_reconstruct(activity->party, &p_activity->party, p_lib);
    ActivitySecrets *activity_secrets = p_lib->nativescript_api->godot_nativescript_get_userdata(activity->secrets);
    memcpy(activity_secrets->internal, &p_activity->secrets, sizeof(struct DiscordActivitySecrets));
}

void register_activity(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = activity_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = activity_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "Activity", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // Application ID
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_STORAGE | GODOT_PROPERTY_USAGE_NETWORK;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_application_id;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_application_id;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "application_id",
                                                                          &attributes,
                                                                          set, get);
        }
        // Name
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_STORAGE | GODOT_PROPERTY_USAGE_NETWORK;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_name;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_name;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "name",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // State
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_state;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_state;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "state",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Details
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_details;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_details;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "details",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Timestamps
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_timestamps;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_timestamps;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "timestamps",
                                                                          &attributes,
                                                                          set, get);
        }
        // Assets
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_assets;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_assets;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "assets",
                                                                          &attributes,
                                                                          set, get);
        }
        // Party
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_party;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_party;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "party",
                                                                          &attributes,
                                                                          set, get);
        }
        // Secrets
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_secrets;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_secrets;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "secrets",
                                                                          &attributes,
                                                                          set, get);
        }
        // Instance
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_BOOL;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_instance;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_instance;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "instance",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}
