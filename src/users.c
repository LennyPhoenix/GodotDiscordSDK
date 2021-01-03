#include "users.h"

void *user_constructor(godot_object *p_instance, Library *p_lib)
{
    struct DiscordUser *user = p_lib->api->godot_alloc(sizeof(struct DiscordUser));
    memset(user, 0, sizeof(user));

    return user;
}

void user_destructor(godot_object *p_instance, Library *p_lib,
                     struct DiscordUser *p_user)
{
    p_lib->api->godot_free(p_user);
}

godot_variant user_get_id(godot_object *p_instance, Library *p_lib,
                          struct DiscordUser *p_user)
{
    godot_variant id;

    p_lib->api->godot_variant_new_int(&id, p_user->id);

    return id;
}

void user_set_id(godot_object *p_instance, Library *p_lib,
                 struct DiscordUser *p_user,
                 godot_variant *p_id)
{
    p_user->id = p_lib->api->godot_variant_as_int(p_id);
}

godot_variant user_get_username(godot_object *p_instance, struct Library *p_lib,
                                struct DiscordUser *p_user)
{
    godot_variant username;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_user->username);
    p_lib->api->godot_variant_new_string(&username, &string);
    p_lib->api->godot_string_destroy(&string);

    return username;
}

void user_set_username(godot_object *p_instance, struct Library *p_lib,
                       struct DiscordUser *p_user,
                       godot_variant *p_username)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_username);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *username = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_user->username, 0, sizeof(char) * 256);
    memcpy(p_user->username, username, sizeof(char) * min(size, 255));
}

godot_variant user_get_discriminator(godot_object *p_instance, struct Library *p_lib,
                                     struct DiscordUser *p_user)
{
    godot_variant discriminator;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_user->discriminator);
    p_lib->api->godot_variant_new_string(&discriminator, &string);
    p_lib->api->godot_string_destroy(&string);

    return discriminator;
}

void user_set_discriminator(godot_object *p_instance, struct Library *p_lib,
                            struct DiscordUser *p_user,
                            godot_variant *p_discriminator)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_discriminator);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *discriminator = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_user->discriminator, 0, sizeof(char) * 8);
    memcpy(p_user->discriminator, discriminator, sizeof(char) * min(size, 7));
}

godot_variant user_get_avatar(godot_object *p_instance, struct Library *p_lib,
                              struct DiscordUser *p_user)
{
    godot_variant avatar;

    godot_string string = p_lib->api->godot_string_chars_to_utf8(p_user->avatar);
    p_lib->api->godot_variant_new_string(&avatar, &string);
    p_lib->api->godot_string_destroy(&string);

    return avatar;
}

void user_set_avatar(godot_object *p_instance, struct Library *p_lib,
                     struct DiscordUser *p_user,
                     godot_variant *p_avatar)
{
    godot_string string = p_lib->api->godot_variant_as_string(p_avatar);
    godot_char_string char_string = p_lib->api->godot_string_utf8(&string);
    const char *avatar = p_lib->api->godot_char_string_get_data(&char_string);

    int size = p_lib->api->godot_char_string_length(&char_string);

    memset(p_user->avatar, 0, sizeof(char) * 128);
    memcpy(p_user->avatar, avatar, sizeof(char) * min(size, 127));
}

godot_variant user_get_bot(godot_object *p_instance, struct Library *p_lib,
                           struct DiscordUser *p_user)
{
    godot_variant bot;

    p_lib->api->godot_variant_new_bool(&bot, p_user->bot);

    return bot;
}

void user_set_bot(godot_object *p_instance, struct Library *p_lib,
                  struct DiscordUser *p_user,
                  godot_variant *p_bot)
{
    p_user->bot = p_lib->api->godot_variant_as_bool(p_bot);
}

void register_user(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(constructor));
    constructor.create_func = user_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(destructor));
    destructor.destroy_func = user_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "User", "Resource",
                                                               constructor, destructor);

    // Attributes
    {
        godot_property_attributes attributes;
        godot_variant default_value;
        godot_property_get_func get;
        godot_property_set_func set;

        // ID
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
            get.get_func = user_get_id;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = user_set_id;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "id",
                                                                          &attributes,
                                                                          set, get);
        }
        // Username
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = user_get_username;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = user_set_username;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "username",
                                                                          &attributes,
                                                                          set, get);
        }
        // Discriminator
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = user_get_discriminator;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = user_set_discriminator;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "discriminator",
                                                                          &attributes,
                                                                          set, get);
        }
        // Avatar
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_STRING;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            godot_string string = p_lib->api->godot_string_chars_to_utf8("");
            p_lib->api->godot_variant_new_string(&default_value, &string);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = user_get_avatar;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = user_set_avatar;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "avatar",
                                                                          &attributes,
                                                                          set, get);
        }
        // Bot
        {
            memset(&attributes, 0, sizeof(attributes));
            attributes.type = GODOT_VARIANT_TYPE_BOOL;
            attributes.usage = GODOT_PROPERTY_USAGE_DEFAULT;
            attributes.rset_type = GODOT_METHOD_RPC_MODE_DISABLED;

            attributes.hint = GODOT_PROPERTY_HINT_NONE;
            attributes.hint_string = p_lib->api->godot_string_chars_to_utf8("");

            p_lib->api->godot_variant_new_bool(&default_value, 0);
            attributes.default_value = default_value;

            memset(&get, 0, sizeof(get));
            get.get_func = user_get_bot;
            get.method_data = p_lib;

            memset(&set, 0, sizeof(set));
            set.set_func = user_set_bot;
            set.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_property(p_handle,
                                                                          "User", "bot",
                                                                          &attributes,
                                                                          set, get);
        }

        p_lib->api->godot_variant_destroy(&default_value);
    }
}

void *user_manager_constructor(godot_object *p_instance, Library *p_lib)
{
    UserManager *user_manager = p_lib->api->godot_alloc(sizeof(UserManager));

    user_manager->object = p_instance;
    user_manager->lib = p_lib;

    return user_manager;
}

void user_manager_destructor(godot_object *p_instance, Library *p_lib,
                             UserManager *p_user_manager)
{
    p_lib->api->godot_free(p_user_manager);
}

godot_variant user_manager_get_current_user(godot_object *p_instance, Library *p_lib,
                                            UserManager *p_user_manager,
                                            int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 2) // Callback Object, Callback Name
    {
        godot_object *callback_object = p_lib->api->godot_variant_as_object(p_args[0]);
        godot_string callback_name = p_lib->api->godot_variant_as_string(p_args[1]);

        godot_object *user = instantiate_custom_class("User", "Resource", p_lib);
        struct DiscordUser *user_internal = p_lib->nativescript_api->godot_nativescript_get_userdata(user);
        enum EDiscordResult result = p_user_manager->internal->get_current_user(p_user_manager->internal, user_internal);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant user_variant;

            p_lib->api->godot_variant_new_int(&result_variant, result);
            p_lib->api->godot_variant_new_object(&user_variant, user);

            godot_variant *args[] = {&result_variant, &user_variant};

            object_call(callback_object, &callback_name, 2, args, p_lib);
        }

        p_lib->api->godot_variant_new_nil(&result_variant);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

void DISCORD_API get_user_callback(CallbackData *p_data,
                                   enum EDiscordResult p_result, struct DiscordUser *p_user)
{
    Library *lib = p_data->lib;

    godot_variant result_variant;
    godot_variant user_variant;

    godot_object *user = instantiate_custom_class("User", "Resource", lib);
    struct DiscordUser *data = lib->nativescript_api->godot_nativescript_get_userdata(user);

    memcpy(data, p_user, sizeof(struct DiscordUser));

    lib->api->godot_variant_new_int(&result_variant, p_result);
    lib->api->godot_variant_new_object(&user_variant, user);

    godot_variant *args[] = {&result_variant, &user_variant};

    object_call(p_data->callback_object, &p_data->callback_name, 2, args, p_data->lib);

    free(p_data);
}

godot_variant user_manager_get_user(godot_object *p_instance, Library *p_lib,
                                    UserManager *p_user_manager,
                                    int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 3) // ID, Callback Object, Callback Name
    {
        int64_t id = p_lib->api->godot_variant_as_int(p_args[0]);
        godot_object *callback_object = p_lib->api->godot_variant_as_object(p_args[1]);
        godot_string callback_name = p_lib->api->godot_variant_as_string(p_args[2]);

        godot_object *user = instantiate_custom_class("User", "Resource", p_lib);

        CallbackData *callback_data = calloc(1, sizeof(CallbackData));
        callback_data->callback_object = callback_object;
        callback_data->callback_name = callback_name;
        callback_data->core = p_user_manager->core;
        callback_data->lib = p_lib;

        p_user_manager->internal->get_user(p_user_manager->internal,
                                           id,
                                           callback_data, &get_user_callback);

        p_lib->api->godot_variant_new_nil(&result_variant);
    }
    else
    {
        p_lib->api->godot_variant_new_int(&result_variant, DiscordResult_InvalidCommand);
    }

    return result_variant;
}

void register_user_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(constructor));
    constructor.create_func = user_manager_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(destructor));
    destructor.destroy_func = user_manager_destructor;
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "UserManager", "Reference",
                                                               constructor, destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Get Current User
        {
            memset(&method, 0, sizeof(method));
            method.method = user_manager_get_current_user;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "UserManager", "get_current_user",
                                                                        attributes, method);
        }
        // Get User
        {
            memset(&method, 0, sizeof(method));
            method.method = user_manager_get_user;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "UserManager", "get_user",
                                                                        attributes, method);
        }
    }

    // Signals
    {
        godot_signal signal;

        // Current User Update
        {
            memset(&signal, 0, sizeof(signal));
            signal.name = p_lib->api->godot_string_chars_to_utf8("current_user_update");

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "UserManager", &signal);
        }
    }
}

void DISCORD_API on_current_user_update(Core *p_core)
{
    godot_string signal = p_core->lib->api->godot_string_chars_to_utf8("current_user_update");
    object_emit_signal(p_core->users->object, &signal, 0, NULL, p_core->lib);
}
