#include "users.h"
#include "users/user.h"

#include "core.h"
#include "util.h"

GDCALLINGCONV void *user_manager_constructor(godot_object *p_instance, void *p_method_data)
{
    Library *lib = p_method_data;

    UserManager *user_manager = lib->core_api->godot_alloc(sizeof(UserManager));
    memset(user_manager, 0, sizeof(UserManager));

    user_manager->object = p_instance;
    user_manager->lib    = lib;

    return user_manager;
}

GDCALLINGCONV void user_manager_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib              = p_method_data;
    UserManager *user_manager = p_user_data;

    lib->core_api->godot_free(user_manager);
}

godot_variant user_manager_get_current_user(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                            int p_num_args, godot_variant **p_args)
{
    Library *lib              = p_method_data;
    UserManager *user_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 0 || p_num_args == 2) // [Callback Object, Callback Name]
    {
        godot_object *user_object  = instantiate_custom_class("User", "Resource", lib);
        User *user                 = lib->nativescript_api->godot_nativescript_get_userdata(user_object);
        enum EDiscordResult result = user_manager->internal->get_current_user(user_manager->internal, user->internal);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant user_variant;

            lib->core_api->godot_variant_new_int(&result_variant, result);
            lib->core_api->godot_variant_new_object(&user_variant, user_object);

            const godot_variant *args[] = {&result_variant, &user_variant};

            if (p_num_args == 2)
            {
                godot_object *callback_object = lib->core_api->godot_variant_as_object(p_args[0]);
                godot_string callback_name    = lib->core_api->godot_variant_as_string(p_args[1]);

                if (lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, NULL, lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", lib);

                lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("get_current_user_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, lib);

            lib->core_api->godot_string_destroy(&signal_name);
            lib->core_api->godot_variant_destroy(&user_variant);
            lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_current_user()\" call. Expected 0 or 2.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

void get_user_callback(void *p_callback_data, enum EDiscordResult p_result, struct DiscordUser *p_user)
{
    CallbackData *data        = p_callback_data;
    Library *lib              = data->lib;
    UserManager *user_manager = data->data;

    godot_variant result_variant;
    godot_variant user_variant;

    godot_object *user_object = instantiate_custom_class("User", "Resource", lib);
    User *user                = lib->nativescript_api->godot_nativescript_get_userdata(user_object);

    memcpy(user->internal, p_user, sizeof(struct DiscordUser));

    lib->core_api->godot_variant_new_int(&result_variant, p_result);
    lib->core_api->godot_variant_new_object(&user_variant, user_object);

    const godot_variant *args[] = {&result_variant, &user_variant};

    if (data->callback_object)
    {
        if (lib->core_1_1_api->godot_is_instance_valid(data->callback_object))
            object_call(data->callback_object, &data->callback_name, 2, args, NULL, lib);
        else
            PRINT_ERROR("Callback object is no longer a valid instance.", lib);

        lib->core_api->godot_string_destroy(&data->callback_name);
    }

    godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("get_user_callback");
    object_emit_signal(user_manager->object, &signal_name, 2, args, lib);

    lib->core_api->godot_string_destroy(&signal_name);
    lib->core_api->godot_variant_destroy(&user_variant);
    lib->core_api->godot_variant_destroy(&result_variant);
    lib->core_api->godot_free(p_callback_data);
}

godot_variant user_manager_get_user(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                                    godot_variant **p_args)
{
    Library *lib              = p_method_data;
    UserManager *user_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // ID, [Callback Object, Callback Name]
    {
        int64_t id = lib->core_api->godot_variant_as_int(p_args[0]);

        godot_object *user_object = instantiate_custom_class("User", "Resource", lib);

        CallbackData *callback_data = lib->core_api->godot_alloc(sizeof(CallbackData));
        memset(callback_data, 0, sizeof(CallbackData));
        callback_data->lib  = lib;
        callback_data->data = user_manager;

        if (p_num_args == 3)
        {
            godot_object *callback_object  = lib->core_api->godot_variant_as_object(p_args[1]);
            godot_string callback_name     = lib->core_api->godot_variant_as_string(p_args[2]);
            callback_data->callback_object = callback_object;
            callback_data->callback_name   = callback_name;
        }

        user_manager->internal->get_user(user_manager->internal, id, callback_data, get_user_callback);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_user()\" call. Expected 1 or 3.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant user_manager_get_current_user_premium_type(godot_object *p_instance, void *p_method_data,
                                                         void *p_user_data, int p_num_args, godot_variant **p_args)
{
    Library *lib              = p_method_data;
    UserManager *user_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 0 || p_num_args == 2) // [Callback Object, Callback Name]
    {
        enum EDiscordPremiumType premium_type;
        enum EDiscordResult result =
            user_manager->internal->get_current_user_premium_type(user_manager->internal, &premium_type);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant premium_type_variant;

            lib->core_api->godot_variant_new_int(&result_variant, result);
            lib->core_api->godot_variant_new_int(&premium_type_variant, premium_type);

            const godot_variant *args[] = {&result_variant, &premium_type_variant};

            if (p_num_args == 2)
            {
                godot_object *callback_object = lib->core_api->godot_variant_as_object(p_args[0]);
                godot_string callback_name    = lib->core_api->godot_variant_as_string(p_args[1]);

                if (lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, NULL, lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", lib);

                lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name =
                lib->core_api->godot_string_chars_to_utf8("get_current_user_premium_type_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, lib);

            lib->core_api->godot_string_destroy(&signal_name);
            lib->core_api->godot_variant_destroy(&premium_type_variant);
            lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_current_user_premium_type()\" call. Expected 0 or 2.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant user_manager_current_user_has_flag(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                                 int p_num_args, godot_variant **p_args)
{
    Library *lib              = p_method_data;
    UserManager *user_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // User Flag, [Callback Object, Callback Name]
    {
        int64_t flag = lib->core_api->godot_variant_as_int(p_args[0]);

        bool has_flag;
        enum EDiscordResult result =
            user_manager->internal->current_user_has_flag(user_manager->internal, flag, &has_flag);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant has_flag_variant;

            lib->core_api->godot_variant_new_int(&result_variant, result);
            lib->core_api->godot_variant_new_bool(&has_flag_variant, has_flag);

            const godot_variant *args[] = {&result_variant, &has_flag_variant};

            if (p_num_args == 3)
            {
                godot_object *callback_object = lib->core_api->godot_variant_as_object(p_args[0]);
                godot_string callback_name    = lib->core_api->godot_variant_as_string(p_args[1]);

                if (lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, NULL, lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", lib);

                lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("current_user_has_flag_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, lib);

            lib->core_api->godot_string_destroy(&signal_name);
            lib->core_api->godot_variant_destroy(&has_flag_variant);
            lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"current_user_has_flag()\" call. Expected 1 or 3.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

void register_user_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = user_manager_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = user_manager_destructor;
    destructor.method_data  = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle, "UserManager", "Object", constructor,
                                                               destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Get Current User
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = user_manager_get_current_user;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "UserManager", "get_current_user",
                                                                        attributes, method);
        }
        // Get User
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = user_manager_get_user;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "UserManager", "get_user", attributes,
                                                                        method);
        }
        // Get Current User Premium Type
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = user_manager_get_current_user_premium_type;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(
                p_handle, "UserManager", "get_current_user_premium_type", attributes, method);
        }
        // Current User Has Flag
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = user_manager_current_user_has_flag;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "UserManager",
                                                                        "current_user_has_flag", attributes, method);
        }
    }

    // Signals
    {
        godot_signal signal;

        // Current User Update
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("current_user_update");

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "UserManager", &signal);

            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Get Current User Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("get_current_user_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument user;
            {
                memset(&user, 0, sizeof(godot_signal_argument));
                user.name = p_lib->core_api->godot_string_chars_to_utf8("user");

                user.type = GODOT_VARIANT_TYPE_OBJECT;
            }

            godot_signal_argument args[] = {result, user};
            signal.args                  = args;
            signal.num_args              = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "UserManager", &signal);

            p_lib->core_api->godot_string_destroy(&user.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Get User Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("get_user_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument user;
            {
                memset(&user, 0, sizeof(godot_signal_argument));
                user.name = p_lib->core_api->godot_string_chars_to_utf8("user");

                user.type = GODOT_VARIANT_TYPE_OBJECT;
            }

            godot_signal_argument args[] = {result, user};
            signal.args                  = args;
            signal.num_args              = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "UserManager", &signal);

            p_lib->core_api->godot_string_destroy(&user.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Get Current User Premium Type Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("get_current_user_premium_type_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument premium_type;
            {
                memset(&premium_type, 0, sizeof(godot_signal_argument));
                premium_type.name = p_lib->core_api->godot_string_chars_to_utf8("premium_type");

                premium_type.type = GODOT_VARIANT_TYPE_INT;
            }

            godot_signal_argument args[] = {result, premium_type};
            signal.args                  = args;
            signal.num_args              = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "UserManager", &signal);

            p_lib->core_api->godot_string_destroy(&premium_type.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Current User Has Flag Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("current_user_has_flag_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument has_flag;
            {
                memset(&has_flag, 0, sizeof(godot_signal_argument));
                has_flag.name = p_lib->core_api->godot_string_chars_to_utf8("has_flag");

                has_flag.type = GODOT_VARIANT_TYPE_BOOL;
            }

            godot_signal_argument args[] = {result, has_flag};
            signal.args                  = args;
            signal.num_args              = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "UserManager", &signal);

            p_lib->core_api->godot_string_destroy(&has_flag.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
    }
}

void on_current_user_update(void *p_event_data)
{
    Core *core   = p_event_data;
    Library *lib = core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("current_user_update");
    object_emit_signal(core->users->object, &signal, 0, NULL, lib);
    lib->core_api->godot_string_destroy(&signal);
}
