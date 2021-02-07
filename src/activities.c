#include "activities.h"

GDCALLINGCONV void *activity_timestamps_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(timestamps,
                ActivityTimestamps, struct DiscordActivityTimestamps,
                p_lib, p_instance);

    return timestamps;
}

GDCALLINGCONV void activity_timestamps_destructor(godot_object *p_instance, Library *p_lib,
                                                  ActivityTimestamps *p_timestamps)
{
    p_lib->api->godot_free(p_timestamps->internal);
    p_lib->api->godot_free(p_timestamps);
}

godot_variant activity_timestamps_get_start(godot_object *p_instance, Library *p_lib,
                                            ActivityTimestamps *p_timestamps)
{
    godot_variant start;

    p_lib->api->godot_variant_new_int(&start, p_timestamps->internal->start);

    return start;
}

GDCALLINGCONV void activity_timestamps_set_start(godot_object *p_instance, Library *p_lib,
                                                 ActivityTimestamps *p_timestamps,
                                                 godot_variant *p_start)
{
    p_timestamps->internal->start = p_lib->api->godot_variant_as_int(p_start);
}

godot_variant activity_timestamps_get_end(godot_object *p_instance, Library *p_lib,
                                          ActivityTimestamps *p_timestamps)
{
    godot_variant end;

    p_lib->api->godot_variant_new_int(&end, p_timestamps->internal->end);

    return end;
}

GDCALLINGCONV void activity_timestamps_set_end(godot_object *p_instance, Library *p_lib,
                                               ActivityTimestamps *p_timestamps,
                                               godot_variant *p_end)
{
    p_timestamps->internal->end = p_lib->api->godot_variant_as_int(p_end);
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
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_int(&default_value, 0);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_timestamps_get_start;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_timestamps_set_start;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityTimestamps", "start",
                                                                          &attributes,
                                                                          set, get);
        }
        // End
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
            get.get_func = activity_timestamps_get_end;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_timestamps_set_end;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityTimestamps", "end",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}

GDCALLINGCONV void *activity_assets_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(assets,
                ActivityAssets, struct DiscordActivityAssets,
                p_lib, p_instance);

    return assets;
}

GDCALLINGCONV void activity_assets_destructor(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_assets)
{
    p_lib->api->godot_free(p_assets->internal);
    p_lib->api->godot_free(p_assets);
}

godot_variant activity_assets_get_large_image(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_assets)
{
    godot_variant large_image;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_assets->internal->large_image);
    p_lib->api->godot_variant_new_string(&large_image, &string);
    p_lib->api->godot_string_destroy(&string);

    return large_image;
}

GDCALLINGCONV void activity_assets_set_large_image(godot_object *p_instance, Library *p_lib,
                                                   ActivityAssets *p_assets,
                                                   godot_variant *p_large_image)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_large_image);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *large_image = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_assets->internal->large_image, 0, sizeof(char) * 128);
    memcpy(p_assets->internal->large_image, large_image, sizeof(char) * MIN(size, 127));
}

godot_variant activity_assets_get_large_text(godot_object *p_instance, Library *p_lib,
                                             ActivityAssets *p_assets)
{
    godot_variant large_text;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_assets->internal->large_text);
    p_lib->api->godot_variant_new_string(&large_text, &string);
    p_lib->api->godot_string_destroy(&string);

    return large_text;
}

GDCALLINGCONV void activity_assets_set_large_text(godot_object *p_instance, Library *p_lib,
                                                  ActivityAssets *p_assets,
                                                  godot_variant *p_large_text)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_large_text);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *large_text = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_assets->internal->large_text, 0, sizeof(char) * 128);
    memcpy(p_assets->internal->large_text, large_text, sizeof(char) * MIN(size, 127));
}

godot_variant activity_assets_get_small_image(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_assets)
{
    godot_variant small_image;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_assets->internal->small_image);
    p_lib->api->godot_variant_new_string(&small_image, &string);
    p_lib->api->godot_string_destroy(&string);

    return small_image;
}

GDCALLINGCONV void activity_assets_set_small_image(godot_object *p_instance, Library *p_lib,
                                                   ActivityAssets *p_assets,
                                                   godot_variant *p_small_image)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_small_image);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *small_image = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_assets->internal->small_image, 0, sizeof(char) * 128);
    memcpy(p_assets->internal->small_image, small_image, sizeof(char) * MIN(size, 127));
}

godot_variant activity_assets_get_small_text(godot_object *p_instance, Library *p_lib,
                                             ActivityAssets *p_assets)
{
    godot_variant small_text;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_assets->internal->small_text);
    p_lib->api->godot_variant_new_string(&small_text, &string);
    p_lib->api->godot_string_destroy(&string);

    return small_text;
}

GDCALLINGCONV void activity_assets_set_small_text(godot_object *p_instance, Library *p_lib,
                                                  ActivityAssets *p_assets,
                                                  godot_variant *p_small_text)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_small_text);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *small_text = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_assets->internal->small_text, 0, sizeof(char) * 128);
    memcpy(p_assets->internal->small_text, small_text, sizeof(char) * MIN(size, 127));
}

void register_activity_assets(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = activity_assets_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = activity_assets_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ActivityAssets", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // Large Image
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_assets_get_large_image;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_assets_set_large_image;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "large_image",
                                                                          &attributes,
                                                                          set, get);
        }
        // Large Text
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_assets_get_large_text;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_assets_set_large_text;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "large_text",
                                                                          &attributes,
                                                                          set, get);
        }
        // Small Image
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_assets_get_small_image;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_assets_set_small_image;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "small_image",
                                                                          &attributes,
                                                                          set, get);
        }
        // Small Text
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_assets_get_small_text;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_assets_set_small_text;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityAssets", "small_text",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}

GDCALLINGCONV void *party_size_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(party_size,
                PartySize, struct DiscordPartySize,
                p_lib, p_instance);

    return party_size;
}

GDCALLINGCONV void party_size_destructor(godot_object *p_instance, Library *p_lib,
                                         PartySize *p_party_size)
{
    p_lib->api->godot_free(p_party_size->internal);
    p_lib->api->godot_free(p_party_size);
}

godot_variant party_size_get_current_size(godot_object *p_instance, Library *p_lib,
                                          PartySize *p_party_size)
{
    godot_variant current_size;

    p_lib->api->godot_variant_new_int(&current_size, p_party_size->internal->current_size);

    return current_size;
}

GDCALLINGCONV void party_size_set_current_size(godot_object *p_instance, Library *p_lib,
                                               PartySize *p_party_size,
                                               godot_variant *p_current_size)
{
    p_party_size->internal->current_size = (int32_t)p_lib->api->godot_variant_as_int(p_current_size);
}

godot_variant party_size_get_max_size(godot_object *p_instance, Library *p_lib,
                                      PartySize *p_party_size)
{
    godot_variant max_size;

    p_lib->api->godot_variant_new_int(&max_size, p_party_size->internal->max_size);

    return max_size;
}

GDCALLINGCONV void party_size_set_max_size(godot_object *p_instance, Library *p_lib,
                                           PartySize *p_party_size,
                                           godot_variant *p_max_size)
{
    p_party_size->internal->max_size = (int32_t)p_lib->api->godot_variant_as_int(p_max_size);
}

void register_party_size(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = party_size_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = party_size_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "PartySize", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // Current Size
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
            get.get_func = party_size_get_current_size;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = party_size_set_current_size;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "PartySize", "current_size",
                                                                          &attributes,
                                                                          set, get);
        }
        // Max Size
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
            get.get_func = party_size_get_max_size;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = party_size_set_max_size;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "PartySize", "max_size",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}

GDCALLINGCONV void *activity_party_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(party,
                ActivityParty, struct DiscordActivityParty,
                p_lib, p_instance);

    party->size = instantiate_custom_class("PartySize", "Resource", p_lib);
    godot_reference(party->size, p_lib);

    return party;
}

GDCALLINGCONV void activity_party_destructor(godot_object *p_instance, Library *p_lib,
                                             ActivityParty *p_party)
{
    if (p_party->size)
        godot_unreference(p_party->size, p_lib);

    p_lib->api->godot_free(p_party->internal);
    p_lib->api->godot_free(p_party);
}

godot_variant activity_party_get_id(godot_object *p_instance, Library *p_lib,
                                    ActivityParty *p_party)
{
    godot_variant id;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_party->internal->id);
    p_lib->api->godot_variant_new_string(&id, &string);
    p_lib->api->godot_string_destroy(&string);

    return id;
}

GDCALLINGCONV void activity_party_set_id(godot_object *p_instance, Library *p_lib,
                                         ActivityParty *p_party,
                                         godot_variant *p_id)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_id);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *id = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_party->internal->id, 0, sizeof(char) * 128);
    memcpy(p_party->internal->id, id, sizeof(char) * MIN(size, 127));
}

godot_variant activity_party_get_privacy(godot_object *p_instance, Library *p_lib,
                                         ActivityParty *p_party)
{
    godot_variant privacy;

    p_lib->api->godot_variant_new_int(&privacy, p_party->internal->privacy);

    return privacy;
}

GDCALLINGCONV void activity_party_set_privacy(godot_object *p_instance, Library *p_lib,
                                              ActivityParty *p_party,
                                              godot_variant *p_privacy)
{
    p_party->internal->privacy = p_lib->api->godot_variant_as_int(p_privacy);
}

godot_variant activity_party_get_size(godot_object *p_instance, Library *p_lib,
                                      ActivityParty *p_activity_party)
{
    godot_variant size;

    p_lib->api->godot_variant_new_object(&size, p_activity_party->size);

    return size;
}

GDCALLINGCONV void activity_party_set_size(godot_object *p_instance, Library *p_lib,
                                           ActivityParty *p_party,
                                           godot_variant *p_size)
{
    if (p_party->size)
        godot_unreference(p_party->size, p_lib);

    p_party->size = p_lib->api->godot_variant_as_object(p_size);

    if (p_party->size)
        godot_reference(p_party->size, p_lib);
}

void activity_party_collapse(godot_object *p_instance, Library *p_lib)
{
    ActivityParty *party = p_lib->nativescript_api->godot_nativescript_get_userdata(p_instance);
    PartySize *size = p_lib->nativescript_api->godot_nativescript_get_userdata(party->size);

    memcpy(&party->internal->size, size->internal, sizeof(struct DiscordPartySize));
}

void register_activity_party(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = activity_party_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = activity_party_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ActivityParty", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // ID
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_party_get_id;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_party_set_id;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityParty", "id",
                                                                          &attributes,
                                                                          set, get);
        }
        // Privacy
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_ENUM;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("Private,Public");

            p_lib->api->godot_variant_new_int(&default_value, DiscordActivityPartyPrivacy_Private);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_party_get_privacy;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_party_set_privacy;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityParty", "privacy",
                                                                          &attributes,
                                                                          set, get);
        }
        // Size
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_nil(&default_value);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_party_get_size;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_party_set_size;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivityParty", "size",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}

GDCALLINGCONV void *activity_secrets_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(secrets,
                ActivitySecrets, struct DiscordActivitySecrets,
                p_lib, p_instance);

    return secrets;
}

GDCALLINGCONV void activity_secrets_destructor(godot_object *p_instance, Library *p_lib,
                                               ActivitySecrets *p_secrets)
{
    p_lib->api->godot_free(p_secrets->internal);
    p_lib->api->godot_free(p_secrets);
}

godot_variant activity_secrets_get_match(godot_object *p_instance, Library *p_lib,
                                         ActivitySecrets *p_secrets)
{
    godot_variant match;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_secrets->internal->match);
    p_lib->api->godot_variant_new_string(&match, &string);
    p_lib->api->godot_string_destroy(&string);

    return match;
}

GDCALLINGCONV void activity_secrets_set_match(godot_object *p_instance, Library *p_lib,
                                              ActivitySecrets *p_secrets,
                                              godot_variant *p_match)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_match);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *match = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_secrets->internal->match, 0, sizeof(char) * 128);
    memcpy(p_secrets->internal->match, match, sizeof(char) * MIN(size, 127));
}

godot_variant activity_secrets_get_join(godot_object *p_instance, Library *p_lib,
                                        ActivitySecrets *p_secrets)
{
    godot_variant join;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_secrets->internal->join);
    p_lib->api->godot_variant_new_string(&join, &string);
    p_lib->api->godot_string_destroy(&string);

    return join;
}

GDCALLINGCONV void activity_secrets_set_join(godot_object *p_instance, Library *p_lib,
                                             ActivitySecrets *p_secrets,
                                             godot_variant *p_join)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_join);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *join = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_secrets->internal->join, 0, sizeof(char) * 128);
    memcpy(p_secrets->internal->join, join, sizeof(char) * MIN(size, 127));
}

godot_variant activity_secrets_get_spectate(godot_object *p_instance, Library *p_lib,
                                            ActivitySecrets *p_secrets)
{
    godot_variant spectate;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_secrets->internal->spectate);
    p_lib->api->godot_variant_new_string(&spectate, &string);
    p_lib->api->godot_string_destroy(&string);

    return spectate;
}

GDCALLINGCONV void activity_secrets_set_spectate(godot_object *p_instance, Library *p_lib,
                                                 ActivitySecrets *p_secrets,
                                                 godot_variant *p_spectate)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_spectate);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *spectate = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_secrets->internal->spectate, 0, sizeof(char) * 128);
    memcpy(p_secrets->internal->spectate, spectate, sizeof(char) * MIN(size, 127));
}

void register_activity_secrets(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = activity_secrets_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = activity_secrets_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ActivitySecrets", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // Match
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_secrets_get_match;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_secrets_set_match;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivitySecrets", "match",
                                                                          &attributes,
                                                                          set, get);
        }
        // Join
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_secrets_get_join;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_secrets_set_join;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivitySecrets", "join",
                                                                          &attributes,
                                                                          set, get);
        }
        // Spectate
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_secrets_get_spectate;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_secrets_set_spectate;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "ActivitySecrets", "spectate",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}

GDCALLINGCONV void *activity_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(activity,
                Activity, struct DiscordActivity,
                p_lib, p_instance);

    activity->internal->supported_platforms = DiscordActivitySupportedPlatformFlags_Desktop |
                                              DiscordActivitySupportedPlatformFlags_Android |
                                              DiscordActivitySupportedPlatformFlags_iOS;

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

    p_lib->api->godot_free(p_activity->internal);
    p_lib->api->godot_free(p_activity);
}

godot_variant activity_get_application_id(godot_object *p_instance, Library *p_lib,
                                          Activity *p_activity)
{
    godot_variant application_id;

    p_lib->api->godot_variant_new_int(&application_id, p_activity->internal->application_id);

    return application_id;
}

GDCALLINGCONV void activity_set_application_id(godot_object *p_instance, Library *p_lib,
                                               Activity *p_activity,
                                               godot_variant *p_application_id) {} // Read-Only

godot_variant activity_get_name(godot_object *p_instance, Library *p_lib,
                                Activity *p_activity)
{
    godot_variant name;

    godot_string name_string = p_lib->api->godot_string_chars_to_utf8(p_activity->internal->name);
    p_lib->api->godot_variant_new_string(&name, &name_string);

    return name;
}

GDCALLINGCONV void activity_set_name(godot_object *p_instance, Library *p_lib,
                                     Activity *p_activity,
                                     godot_variant *p_name) {} // Read-Only

godot_variant activity_get_state(godot_object *p_instance, Library *p_lib,
                                 Activity *p_activity)
{
    godot_variant state;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_activity->internal->state);
    p_lib->api->godot_variant_new_string(&state, &string);
    p_lib->api->godot_string_destroy(&string);

    return state;
}

GDCALLINGCONV void activity_set_state(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity,
                                      godot_variant *p_state)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_state);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *state = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_activity->internal->state, 0, sizeof(char) * 128);
    memcpy(p_activity->internal->state, state, sizeof(char) * MIN(size, 127));
}

godot_variant activity_get_details(godot_object *p_instance, Library *p_lib,
                                   Activity *p_activity)
{
    godot_variant details;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_activity->internal->details);
    p_lib->api->godot_variant_new_string(&details, &string);
    p_lib->api->godot_string_destroy(&string);

    return details;
}

GDCALLINGCONV void activity_set_details(godot_object *p_instance, Library *p_lib,
                                        Activity *p_activity,
                                        godot_variant *p_details)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_details);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *details = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_activity->internal->details, 0, sizeof(char) * 128);
    memcpy(p_activity->internal->details, details, sizeof(char) * MIN(size, 127));
}

godot_variant activity_get_timestamps(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity)
{
    godot_variant timestamps;

    p_lib->api->godot_variant_new_object(&timestamps, p_activity->timestamps);

    return timestamps;
}

GDCALLINGCONV void activity_set_timestamps(godot_object *p_instance, Library *p_lib,
                                           Activity *p_activity,
                                           godot_variant *p_timestamps)
{
    if (p_activity->timestamps)
        godot_unreference(p_activity->timestamps, p_lib);

    p_activity->timestamps = p_lib->api->godot_variant_as_object(p_timestamps);

    if (p_activity->timestamps)
        godot_reference(p_activity->timestamps, p_lib);
}

godot_variant activity_get_assets(godot_object *p_instance, Library *p_lib,
                                  Activity *p_activity)
{
    godot_variant assets;

    p_lib->api->godot_variant_new_object(&assets, p_activity->assets);

    return assets;
}

GDCALLINGCONV void activity_set_assets(godot_object *p_instance, Library *p_lib,
                                       Activity *p_activity,
                                       godot_variant *p_assets)
{
    if (p_activity->assets)
        godot_unreference(p_activity->assets, p_lib);

    p_activity->assets = p_lib->api->godot_variant_as_object(p_assets);

    if (p_activity->assets)
        godot_reference(p_activity->assets, p_lib);
}

godot_variant activity_get_party(godot_object *p_instance, Library *p_lib,
                                 Activity *p_activity)
{
    godot_variant party;

    p_lib->api->godot_variant_new_object(&party, p_activity->party);

    return party;
}

GDCALLINGCONV void activity_set_party(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity,
                                      godot_variant *p_party)
{
    if (p_activity->party)
        godot_unreference(p_activity->party, p_lib);

    p_activity->party = p_lib->api->godot_variant_as_object(p_party);

    if (p_activity->party)
        godot_reference(p_activity->party, p_lib);
}

godot_variant activity_get_secrets(godot_object *p_instance, Library *p_lib,
                                   Activity *p_activity)
{
    godot_variant secrets;

    p_lib->api->godot_variant_new_object(&secrets, p_activity->secrets);

    return secrets;
}

GDCALLINGCONV void activity_set_secrets(godot_object *p_instance, Library *p_lib,
                                        Activity *p_activity,
                                        godot_variant *p_secrets)
{
    if (p_activity->secrets)
        godot_unreference(p_activity->secrets, p_lib);

    p_activity->secrets = p_lib->api->godot_variant_as_object(p_secrets);

    if (p_activity->secrets)
        godot_reference(p_activity->secrets, p_lib);
}

godot_variant activity_get_instance(godot_object *p_instance, Library *p_lib,
                                    Activity *p_activity)
{
    godot_variant instance;

    p_lib->api->godot_variant_new_bool(&instance, p_activity->internal->instance);

    return instance;
}

GDCALLINGCONV void activity_set_instance(godot_object *p_instance, Library *p_lib,
                                         Activity *p_activity,
                                         godot_variant *p_is_instance)
{
    p_activity->internal->instance = p_lib->api->godot_variant_as_bool(p_is_instance);
}

godot_variant activity_get_supported_platforms(godot_object *p_instance, Library *p_lib,
                                               Activity *p_activity)
{
    godot_variant supported_platforms;

    p_lib->api->godot_variant_new_uint(&supported_platforms, p_activity->internal->supported_platforms);

    return supported_platforms;
}

GDCALLINGCONV void activity_set_supported_platforms(godot_object *p_instance, Library *p_lib,
                                                    Activity *p_activity,
                                                    godot_variant *p_supported_platforms)
{
    p_activity->internal->supported_platforms = (uint32_t)p_lib->api->godot_variant_as_uint(p_supported_platforms);
}

void activity_collapse(godot_object *p_instance, Library *p_lib)
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
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // Application ID
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_STORAGE | GODOT_PROPERTY_USAGE_NETWORK;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_int(&default_value, 0);
            attributes.default_value = default_value;

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
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

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
        }
        // State
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

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
        }
        // Details
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

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
        }
        // Timestamps
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_OBJECT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_nil(&default_value);
            attributes.default_value = default_value;

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
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_nil(&default_value);
            attributes.default_value = default_value;

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
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_nil(&default_value);
            attributes.default_value = default_value;

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
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_nil(&default_value);
            attributes.default_value = default_value;

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
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_bool(&default_value, false);
            attributes.default_value = default_value;

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
        // Supported Platforms
        {
            memset(&get, 0, sizeof(godot_property_get_func));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_int(&default_value,
                                              DiscordActivitySupportedPlatformFlags_Desktop |
                                                  DiscordActivitySupportedPlatformFlags_Android |
                                                  DiscordActivitySupportedPlatformFlags_iOS);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = activity_get_supported_platforms;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = activity_set_supported_platforms;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "Activity", "supported_platforms",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}

GDCALLINGCONV void *activity_manager_constructor(godot_object *p_instance, Library *p_lib)
{
    ActivityManager *activity_manager = p_lib->api->godot_alloc(sizeof(ActivityManager));

    activity_manager->object = p_instance;
    activity_manager->lib = p_lib;

    return activity_manager;
}

GDCALLINGCONV void activity_manager_destructor(godot_object *p_instance, Library *p_lib,
                                               ActivityManager *p_activity_manager)
{
    p_lib->api->godot_free(p_activity_manager);
}

godot_variant activity_manager_register_command(godot_object *p_instance, Library *p_lib,
                                                ActivityManager *p_activity_manager,
                                                int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1) // Command
    {
        godot_string command_string = p_lib->api->godot_variant_as_string(p_args[0]);
        godot_char_string command_char_string = p_lib->api->godot_string_utf8(&command_string);

        const char *command = p_lib->api->godot_char_string_get_data(&command_char_string);

        enum EDiscordResult result = p_activity_manager->internal->register_command(p_activity_manager->internal, command);

        p_lib->api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}
godot_variant activity_manager_register_steam(godot_object *p_instance, Library *p_lib,
                                              ActivityManager *p_activity_manager,
                                              int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1) // Steam ID
    {
        uint32_t steam_id = (uint32_t)p_lib->api->godot_variant_as_uint(p_args[0]);

        enum EDiscordResult result = p_activity_manager->internal->register_steam(p_activity_manager->internal, steam_id);

        p_lib->api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}
void DISCORD_API update_activity_callback(CallbackData *p_data,
                                          enum EDiscordResult p_result)
{
    Library *lib = p_data->lib;

    godot_variant result_variant;

    lib->api->godot_variant_new_int(&result_variant, p_result);

    godot_variant *args[] = {&result_variant};

    object_call(p_data->callback_object, &p_data->callback_name, 1, args, p_data->lib);

    lib->api->godot_free(p_data);
}

godot_variant activity_manager_update_activity(godot_object *p_instance, Library *p_lib,
                                               ActivityManager *p_activity_manager,
                                               int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 3) // Activity, Callback Object, Callback Name
    {
        godot_object *activity_object = p_lib->api->godot_variant_as_object(p_args[0]);
        Activity *activity = p_lib->nativescript_api->godot_nativescript_get_userdata(activity_object);
        godot_object *callback_object = p_lib->api->godot_variant_as_object(p_args[1]);
        godot_string callback_name = p_lib->api->godot_variant_as_string(p_args[2]);

        activity_collapse(activity_object, p_lib);

        CallbackData *callback_data = p_lib->api->godot_alloc(sizeof(CallbackData));
        callback_data->callback_object = callback_object;
        callback_data->callback_name = callback_name;
        callback_data->core = p_activity_manager->core;
        callback_data->lib = p_lib;

        p_activity_manager->internal->update_activity(p_activity_manager->internal,
                                                      activity->internal,
                                                      callback_data, update_activity_callback);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

void register_activity_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = activity_manager_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = activity_manager_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "ActivityManager", "Reference",
                                                               constructor, destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Register Command
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = activity_manager_register_command;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "ActivityManager", "register_command",
                                                                        attributes, method);
        }
        // Register Steam
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = activity_manager_register_steam;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "ActivityManager", "register_steam",
                                                                        attributes, method);
        }
        // Update Activity
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = activity_manager_update_activity;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "ActivityManager", "update_activity",
                                                                        attributes, method);
        }
    }
}
