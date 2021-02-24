#include "users.h"
#include "users/user.h"

#include "util.h"

GDCALLINGCONV void *user_manager_constructor(godot_object *p_instance, Library *p_lib)
{
    UserManager *user_manager = p_lib->core_api->godot_alloc(sizeof(UserManager));

    user_manager->object = p_instance;
    user_manager->lib = p_lib;

    return user_manager;
}

GDCALLINGCONV void user_manager_destructor(godot_object *p_instance, Library *p_lib,
                                           UserManager *p_user_manager)
{
    p_lib->core_api->godot_free(p_user_manager);
}

godot_variant user_manager_get_current_user(godot_object *p_instance, Library *p_lib,
                                            UserManager *p_user_manager,
                                            int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 0 || p_num_args == 2) // [Callback Object, Callback Name]
    {
        godot_object *user_object = instantiate_custom_class("User", "Resource", p_lib);
        User *user = p_lib->nativescript_api->godot_nativescript_get_userdata(user_object);
        enum EDiscordResult result = p_user_manager->internal->get_current_user(p_user_manager->internal, user->internal);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant user_variant;

            p_lib->core_api->godot_variant_new_int(&result_variant, result);
            p_lib->core_api->godot_variant_new_object(&user_variant, user_object);

            godot_variant *args[] = {&result_variant, &user_variant};

            if (p_num_args == 2)
            {
                godot_object *callback_object = p_lib->core_api->godot_variant_as_object(p_args[0]);
                godot_string callback_name = p_lib->core_api->godot_variant_as_string(p_args[1]);

                if (p_lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, p_lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", p_lib);

                p_lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = p_lib->core_api->godot_string_chars_to_utf8("get_current_user_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, p_lib);

            p_lib->core_api->godot_string_destroy(&signal_name);
            p_lib->core_api->godot_variant_destroy(&user_variant);
            p_lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_current_user()\" call. Expected 0 or 2.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

void get_user_callback(CallbackData *p_data,
                       enum EDiscordResult p_result, struct DiscordUser *p_user)
{
    Library *lib = p_data->lib;

    godot_variant result_variant;
    godot_variant user_variant;

    godot_object *user_object = instantiate_custom_class("User", "Resource", lib);
    User *user = lib->nativescript_api->godot_nativescript_get_userdata(user_object);

    memcpy(user->internal, p_user, sizeof(struct DiscordUser));

    lib->core_api->godot_variant_new_int(&result_variant, p_result);
    lib->core_api->godot_variant_new_object(&user_variant, user_object);

    godot_variant *args[] = {&result_variant, &user_variant};

    if (p_data->callback_object)
    {
        if (lib->core_1_1_api->godot_is_instance_valid(p_data->callback_object))
            object_call(p_data->callback_object, &p_data->callback_name, 2, args, lib);
        else
            PRINT_ERROR("Callback object is no longer a valid instance.", lib);

        lib->core_api->godot_string_destroy(&p_data->callback_name);
    }

    godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("get_user_callback");
    object_emit_signal(p_data->core->users->object, &signal_name, 2, args, lib);

    lib->core_api->godot_string_destroy(&signal_name);
    lib->core_api->godot_variant_destroy(&user_variant);
    lib->core_api->godot_variant_destroy(&result_variant);
    lib->core_api->godot_free(p_data);
}

godot_variant user_manager_get_user(godot_object *p_instance, Library *p_lib,
                                    UserManager *p_user_manager,
                                    int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // ID, [Callback Object, Callback Name]
    {
        int64_t id = p_lib->core_api->godot_variant_as_int(p_args[0]);

        godot_object *user_object = instantiate_custom_class("User", "Resource", p_lib);

        CallbackData *callback_data = p_lib->core_api->godot_alloc(sizeof(CallbackData));
        memset(callback_data, 0, sizeof(CallbackData));
        callback_data->core = p_user_manager->core;
        callback_data->lib = p_lib;

        if (p_num_args == 3)
        {
            godot_object *callback_object = p_lib->core_api->godot_variant_as_object(p_args[1]);
            godot_string callback_name = p_lib->core_api->godot_variant_as_string(p_args[2]);
            callback_data->callback_object = callback_object;
            callback_data->callback_name = callback_name;
        }

        p_user_manager->internal->get_user(p_user_manager->internal,
                                           id,
                                           callback_data, get_user_callback);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_user()\" call. Expected 1 or 3.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant user_manager_get_current_user_premium_type(godot_object *p_instance, Library *p_lib,
                                                         UserManager *p_user_manager,
                                                         int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 0 || p_num_args == 2) // [Callback Object, Callback Name]
    {
        enum EDiscordPremiumType premium_type;
        enum EDiscordResult result = p_user_manager->internal->get_current_user_premium_type(p_user_manager->internal, &premium_type);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant premium_type_variant;

            p_lib->core_api->godot_variant_new_int(&result_variant, result);
            p_lib->core_api->godot_variant_new_int(&premium_type_variant, premium_type);

            godot_variant *args[] = {&result_variant, &premium_type_variant};

            if (p_num_args == 2)
            {
                godot_object *callback_object = p_lib->core_api->godot_variant_as_object(p_args[0]);
                godot_string callback_name = p_lib->core_api->godot_variant_as_string(p_args[1]);

                if (p_lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, p_lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", p_lib);

                p_lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = p_lib->core_api->godot_string_chars_to_utf8("get_current_user_premium_type_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, p_lib);

            p_lib->core_api->godot_string_destroy(&signal_name);
            p_lib->core_api->godot_variant_destroy(&premium_type_variant);
            p_lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_current_user_premium_type()\" call. Expected 0 or 2.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant user_manager_current_user_has_flag(godot_object *p_instance, Library *p_lib,
                                                 UserManager *p_user_manager,
                                                 int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // User Flag, [Callback Object, Callback Name]
    {
        int64_t flag = p_lib->core_api->godot_variant_as_int(p_args[0]);

        bool has_flag;
        enum EDiscordResult result = p_user_manager->internal->current_user_has_flag(p_user_manager->internal,
                                                                                     flag, &has_flag);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant has_flag_variant;

            p_lib->core_api->godot_variant_new_int(&result_variant, result);
            p_lib->core_api->godot_variant_new_bool(&has_flag_variant, has_flag);

            godot_variant *args[] = {&result_variant, &has_flag_variant};

            if (p_num_args == 3)
            {
                godot_object *callback_object = p_lib->core_api->godot_variant_as_object(p_args[0]);
                godot_string callback_name = p_lib->core_api->godot_variant_as_string(p_args[1]);

                if (p_lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, p_lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", p_lib);

                p_lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = p_lib->core_api->godot_string_chars_to_utf8("current_user_has_flag_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, p_lib);

            p_lib->core_api->godot_string_destroy(&signal_name);
            p_lib->core_api->godot_variant_destroy(&has_flag_variant);
            p_lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"current_user_has_flag()\" call. Expected 1 or 3.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

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
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = user_manager_get_current_user;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "UserManager", "get_current_user",
                                                                        attributes, method);
        }
        // Get User
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = user_manager_get_user;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "UserManager", "get_user",
                                                                        attributes, method);
        }
        // Get Current User Premium Type
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = user_manager_get_current_user_premium_type;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "UserManager", "get_current_user_premium_type",
                                                                        attributes, method);
        }
        // Current User Has Flag
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = user_manager_current_user_has_flag;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "UserManager", "current_user_has_flag",
                                                                        attributes, method);
        }
    }

    // Signals
    {
        godot_signal signal;

        // Current User Update
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("current_user_update");

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "UserManager", &signal);

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
            signal.args = args;
            signal.num_args = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "UserManager", &signal);

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
            signal.args = args;
            signal.num_args = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "UserManager", &signal);

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
            signal.args = args;
            signal.num_args = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "UserManager", &signal);

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
            signal.args = args;
            signal.num_args = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "UserManager", &signal);

            p_lib->core_api->godot_string_destroy(&has_flag.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
    }
}

void on_current_user_update(Core *p_core)
{
    godot_string signal = p_core->lib->core_api->godot_string_chars_to_utf8("current_user_update");
    object_emit_signal(p_core->users->object, &signal, 0, NULL, p_core->lib);
    p_core->lib->core_api->godot_string_destroy(&signal);
}
