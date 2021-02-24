#include "user.h"

#include "util.h"

GDCALLINGCONV void *user_constructor(godot_object *p_instance, Library *p_lib)
{
    INIT_OBJECT(user, User, struct DiscordUser, p_lib, p_instance);

    return user;
}

GDCALLINGCONV void user_destructor(godot_object *p_instance, Library *p_lib,
                                   User *p_user)
{
    p_lib->core_api->godot_free(p_user->internal);
    p_lib->core_api->godot_free(p_user);
}

godot_variant user_get_id(godot_object *p_instance, Library *p_lib,
                          User *p_user)
{
    godot_variant id;

    p_lib->core_api->godot_variant_new_int(&id, p_user->internal->id);

    return id;
}

GDCALLINGCONV void user_set_id(godot_object *p_instance, Library *p_lib,
                               User *p_user,
                               godot_variant *p_id)
{
    p_user->internal->id = p_lib->core_api->godot_variant_as_int(p_id);
}

godot_variant user_get_username(godot_object *p_instance, struct Library *p_lib,
                                User *p_user)
{
    godot_variant username;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_user->internal->username);
    p_lib->core_api->godot_variant_new_string(&username, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return username;
}

GDCALLINGCONV void user_set_username(godot_object *p_instance, struct Library *p_lib,
                                     User *p_user,
                                     godot_variant *p_username)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_username);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *username = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_user->internal->username, 0, sizeof(char) * 256);
    memcpy(p_user->internal->username, username, sizeof(char) * MIN(size, 255));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant user_get_discriminator(godot_object *p_instance, struct Library *p_lib,
                                     User *p_user)
{
    godot_variant discriminator;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_user->internal->discriminator);
    p_lib->core_api->godot_variant_new_string(&discriminator, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return discriminator;
}

GDCALLINGCONV void user_set_discriminator(godot_object *p_instance, struct Library *p_lib,
                                          User *p_user,
                                          godot_variant *p_discriminator)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_discriminator);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *discriminator = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_user->internal->discriminator, 0, sizeof(char) * 8);
    memcpy(p_user->internal->discriminator, discriminator, sizeof(char) * MIN(size, 7));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant user_get_avatar(godot_object *p_instance, struct Library *p_lib,
                              User *p_user)
{
    godot_variant avatar;

    godot_string string = p_lib->core_api->godot_string_chars_to_utf8(p_user->internal->avatar);
    p_lib->core_api->godot_variant_new_string(&avatar, &string);

    p_lib->core_api->godot_string_destroy(&string);

    return avatar;
}

GDCALLINGCONV void user_set_avatar(godot_object *p_instance, struct Library *p_lib,
                                   User *p_user,
                                   godot_variant *p_avatar)
{
    godot_string string = p_lib->core_api->godot_variant_as_string(p_avatar);
    godot_char_string char_string = p_lib->core_api->godot_string_utf8(&string);

    const char *avatar = p_lib->core_api->godot_char_string_get_data(&char_string);

    int size = p_lib->core_api->godot_char_string_length(&char_string);

    memset(p_user->internal->avatar, 0, sizeof(char) * 128);
    memcpy(p_user->internal->avatar, avatar, sizeof(char) * MIN(size, 127));

    p_lib->core_api->godot_char_string_destroy(&char_string);
    p_lib->core_api->godot_string_destroy(&string);
}

godot_variant user_get_bot(godot_object *p_instance, struct Library *p_lib,
                           User *p_user)
{
    godot_variant bot;

    p_lib->core_api->godot_variant_new_bool(&bot, p_user->internal->bot);

    return bot;
}

GDCALLINGCONV void user_set_bot(godot_object *p_instance, struct Library *p_lib,
                                User *p_user,
                                godot_variant *p_bot)
{
    p_user->internal->bot = p_lib->core_api->godot_variant_as_bool(p_bot);
}

void register_user(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = user_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = user_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "User", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_property_get_func get;
        godot_property_set_func set;

        // ID
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_INT;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = user_get_id;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = user_set_id;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "id",
                                                                          &attributes,
                                                                          set, get);
        }
        // Username
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = user_get_username;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = user_set_username;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "username",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Discriminator
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = user_get_discriminator;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = user_set_discriminator;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "discriminator",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Avatar
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            godot_string string = p_lib->core_api->godot_string_chars_to_utf8("");
            p_lib->core_api->godot_variant_new_string(&attributes.default_value, &string);

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = user_get_avatar;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = user_set_avatar;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "avatar",
                                                                          &attributes,
                                                                          set, get);

            p_lib->core_api->godot_variant_destroy(&attributes.default_value);
            p_lib->core_api->godot_string_destroy(&string);
        }
        // Bot
        {
            memset(&attributes, 0, sizeof(godot_property_attributes));
            attributes.type = GODOT_VARIANT_TYPE_BOOL;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;

            memset(&get, 0, sizeof(godot_property_get_func));
            get.get_func = user_get_bot;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(godot_property_set_func));
            set.set_func = user_set_bot;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "bot",
                                                                          &attributes,
                                                                          set, get);
        }
    }
}
