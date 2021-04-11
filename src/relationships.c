#include "relationships.h"
#include "relationships/relationship.h"

#include "core.h"
#include "util.h"

#include <stdbool.h>

GDCALLINGCONV void *relationship_manager_constructor(godot_object *p_instance, void *p_method_data)
{
    Library *lib = p_method_data;

    RelationshipManager *relationship_manager = lib->core_api->godot_alloc(sizeof(RelationshipManager));
    memset(relationship_manager, 0, sizeof(RelationshipManager));

    relationship_manager->object = p_instance;
    relationship_manager->lib    = lib;

    return relationship_manager;
}

GDCALLINGCONV void relationship_manager_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib                              = p_method_data;
    RelationshipManager *relationship_manager = p_user_data;

    if (relationship_manager->filter_data)
    {
        if (relationship_manager->filter_data->callback_object)
            lib->core_api->godot_string_destroy(&relationship_manager->filter_data->callback_name);
        lib->core_api->godot_free(relationship_manager->filter_data);
    }

    lib->core_api->godot_free(relationship_manager);
}

bool filter(void *p_callback_data, struct DiscordRelationship *p_relationship)
{
    CallbackData *data                        = p_callback_data;
    Library *lib                              = data->lib;
    RelationshipManager *relationship_manager = data->data;

    godot_variant relationship_variant;

    godot_object *relationship_object = instantiate_custom_class("Relationship", "Resource", lib);
    relationship_reconstruct(relationship_object, p_relationship, lib);

    lib->core_api->godot_variant_new_object(&relationship_variant, relationship_object);

    const godot_variant *args[] = {&relationship_variant};

    godot_variant result_variant;
    object_call(data->callback_object, &data->callback_name, 1, args, &result_variant, lib);
    bool result = lib->core_api->godot_variant_as_bool(&result_variant);

    lib->core_api->godot_variant_destroy(&result_variant);
    lib->core_api->godot_variant_destroy(&relationship_variant);

    return true;
}

godot_variant relationship_manager_filter(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                          int p_num_args, godot_variant **p_args)
{
    Library *lib                              = p_method_data;
    RelationshipManager *relationship_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 2) // Filter Object, Filter Method
    {
        godot_object *filter_object = lib->core_api->godot_variant_as_object(p_args[0]);
        godot_string filter_name    = lib->core_api->godot_variant_as_string(p_args[1]);

        if (!relationship_manager->filter_data)
            relationship_manager->filter_data = lib->core_api->godot_alloc(sizeof(CallbackData));
        else if (relationship_manager->filter_data->callback_object)
            lib->core_api->godot_string_destroy(&relationship_manager->filter_data->callback_name);

        memset(relationship_manager->filter_data, 0, sizeof(CallbackData));
        relationship_manager->filter_data->lib             = lib;
        relationship_manager->filter_data->callback_name   = filter_name;
        relationship_manager->filter_data->callback_object = filter_object;

        relationship_manager->internal->filter(relationship_manager->internal, relationship_manager->filter_data,
                                               filter);

        lib->core_api->godot_string_destroy(&filter_name);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"filter()\" call. Expected 2.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant relationship_manager_get(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                                       godot_variant **p_args)
{
    Library *lib                              = p_method_data;
    RelationshipManager *relationship_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // User ID, [Callback Object, Callback Name]
    {
        int64_t user_id = lib->core_api->godot_variant_as_int(p_args[0]);

        godot_object *relationship_object = instantiate_custom_class("Relationship", "Resource", lib);
        Relationship *relationship        = lib->nativescript_api->godot_nativescript_get_userdata(relationship_object);
        enum EDiscordResult result =
            relationship_manager->internal->get(relationship_manager->internal, user_id, relationship->internal);

        relationship_reconstruct(relationship_object, relationship->internal, lib);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant relationship_variant;

            lib->core_api->godot_variant_new_int(&result_variant, result);
            lib->core_api->godot_variant_new_object(&relationship_variant, relationship_object);

            const godot_variant *args[] = {&result_variant, &relationship_variant};

            if (p_num_args == 3)
            {
                godot_object *callback_object = lib->core_api->godot_variant_as_object(p_args[1]);
                godot_string callback_name    = lib->core_api->godot_variant_as_string(p_args[2]);

                if (lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, NULL, lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", lib);

                lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("get_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, lib);

            lib->core_api->godot_string_destroy(&signal_name);
            lib->core_api->godot_variant_destroy(&relationship_variant);
            lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get()\" call. Expected 1 or 3.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant relationship_manager_get_at(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                          int p_num_args, godot_variant **p_args)
{
    Library *lib                              = p_method_data;
    RelationshipManager *relationship_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // Index, [Callback Object, Callback Name]
    {
        uint32_t index = (uint32_t)lib->core_api->godot_variant_as_uint(p_args[0]);

        godot_object *relationship_object = instantiate_custom_class("Relationship", "Resource", lib);
        Relationship *relationship        = lib->nativescript_api->godot_nativescript_get_userdata(relationship_object);
        enum EDiscordResult result =
            relationship_manager->internal->get_at(relationship_manager->internal, index, relationship->internal);

        relationship_reconstruct(relationship_object, relationship->internal, lib);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant relationship_variant;

            lib->core_api->godot_variant_new_int(&result_variant, result);
            lib->core_api->godot_variant_new_object(&relationship_variant, relationship_object);

            const godot_variant *args[] = {&result_variant, &relationship_variant};

            if (p_num_args == 3)
            {
                godot_object *callback_object = lib->core_api->godot_variant_as_object(p_args[1]);
                godot_string callback_name    = lib->core_api->godot_variant_as_string(p_args[2]);

                if (lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, NULL, lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", lib);

                lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("get_at_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, lib);

            lib->core_api->godot_string_destroy(&signal_name);
            lib->core_api->godot_variant_destroy(&relationship_variant);
            lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_at()\" call. Expected 1 or 3.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant relationship_manager_count(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                         int p_num_args, godot_variant **p_args)
{
    Library *lib                              = p_method_data;
    RelationshipManager *relationship_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 0 || p_num_args == 2) // [Callback Object, Callback Name]
    {
        int32_t count              = -1;
        enum EDiscordResult result = relationship_manager->internal->count(relationship_manager->internal, &count);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant count_variant;

            lib->core_api->godot_variant_new_int(&result_variant, result);
            lib->core_api->godot_variant_new_int(&count_variant, (int64_t)count);

            const godot_variant *args[] = {&result_variant, &count_variant};

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

            godot_string signal_name = lib->core_api->godot_string_chars_to_utf8("count_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, lib);

            lib->core_api->godot_string_destroy(&signal_name);
            lib->core_api->godot_variant_destroy(&count_variant);
            lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_at()\" call. Expected 1 or 3.", lib);
    }

    lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

void register_relationship_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = relationship_manager_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = relationship_manager_destructor;
    destructor.method_data  = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle, "RelationshipManager", "Reference",
                                                               constructor, destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Filter
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = relationship_manager_filter;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "RelationshipManager", "filter",
                                                                        attributes, method);
        }
        // Get
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = relationship_manager_get;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "RelationshipManager", "get",
                                                                        attributes, method);
        }
        // Get At
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = relationship_manager_get_at;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "RelationshipManager", "get_at",
                                                                        attributes, method);
        }
        // Count
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = relationship_manager_count;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "RelationshipManager", "count",
                                                                        attributes, method);
        }
    }

    // Signals
    {
        godot_signal signal;

        // Refresh
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("refresh");

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "RelationshipManager", &signal);

            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Relationship Update
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("relationship_update");

            godot_signal_argument relationship;
            {
                memset(&relationship, 0, sizeof(godot_signal_argument));
                relationship.name = p_lib->core_api->godot_string_chars_to_utf8("relationship");

                relationship.type = GODOT_VARIANT_TYPE_OBJECT;
            }

            godot_signal_argument args[] = {relationship};
            signal.args                  = args;
            signal.num_args              = 1;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "RelationshipManager", &signal);

            p_lib->core_api->godot_string_destroy(&relationship.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Get Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("get_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument relationship;
            {
                memset(&relationship, 0, sizeof(godot_signal_argument));
                relationship.name = p_lib->core_api->godot_string_chars_to_utf8("relationship");

                relationship.type = GODOT_VARIANT_TYPE_OBJECT;
            }

            godot_signal_argument args[] = {result, relationship};
            signal.args                  = args;
            signal.num_args              = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "RelationshipManager", &signal);

            p_lib->core_api->godot_string_destroy(&relationship.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Get At Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("get_at_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument relationship;
            {
                memset(&relationship, 0, sizeof(godot_signal_argument));
                relationship.name = p_lib->core_api->godot_string_chars_to_utf8("relationship");

                relationship.type = GODOT_VARIANT_TYPE_OBJECT;
            }

            godot_signal_argument args[] = {result, relationship};
            signal.args                  = args;
            signal.num_args              = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "RelationshipManager", &signal);

            p_lib->core_api->godot_string_destroy(&relationship.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Count Callback
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("count_callback");

            godot_signal_argument result;
            {
                memset(&result, 0, sizeof(godot_signal_argument));
                result.name = p_lib->core_api->godot_string_chars_to_utf8("result");

                result.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument count;
            {
                memset(&count, 0, sizeof(godot_signal_argument));
                count.name = p_lib->core_api->godot_string_chars_to_utf8("count");

                count.type = GODOT_VARIANT_TYPE_INT;
            }

            godot_signal_argument args[] = {result, count};
            signal.args                  = args;
            signal.num_args              = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "RelationshipManager", &signal);

            p_lib->core_api->godot_string_destroy(&count.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
    }
}

void on_refresh(void *p_event_data)
{
    Core *core   = p_event_data;
    Library *lib = core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("refresh");

    object_emit_signal(core->relationships->object, &signal, 0, NULL, lib);

    lib->core_api->godot_string_destroy(&signal);
}

void on_relationship_update(void *p_event_data, struct DiscordRelationship *p_relationship)
{
    Core *core   = p_event_data;
    Library *lib = core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("relationship_update");

    godot_variant relationship_variant;

    godot_object *relationship_object = instantiate_custom_class("Relationship", "Resource", lib);
    relationship_reconstruct(relationship_object, p_relationship, core->lib);

    lib->core_api->godot_variant_new_object(&relationship_variant, relationship_object);

    const godot_variant *args[] = {&relationship_variant};

    object_emit_signal(core->relationships->object, &signal, 1, args, lib);

    lib->core_api->godot_variant_destroy(&relationship_variant);
    lib->core_api->godot_string_destroy(&signal);
}
