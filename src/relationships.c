#include "relationships.h"

#include "util.h"
#include "relationships/relationship.h"

#include <stdbool.h>

GDCALLINGCONV void *relationship_manager_constructor(godot_object *p_instance, Library *p_lib)
{
    RelationshipManager *relationship_manager = p_lib->core_api->godot_alloc(sizeof(RelationshipManager));
    memset(relationship_manager, 0, sizeof(RelationshipManager));

    relationship_manager->object = p_instance;
    relationship_manager->lib = p_lib;

    return relationship_manager;
}

GDCALLINGCONV void relationship_manager_destructor(godot_object *p_instance, Library *p_lib,
                                                   RelationshipManager *p_relationship_manager)
{
    if (p_relationship_manager->filter_data)
    {
        if (p_relationship_manager->filter_data->callback_object)
            p_lib->core_api->godot_string_destroy(&p_relationship_manager->filter_data->callback_name);
        p_lib->core_api->godot_free(p_relationship_manager->filter_data);
    }

    p_lib->core_api->godot_free(p_relationship_manager);
}

bool filter(CallbackData *p_data, struct DiscordRelationship *p_relationship)
{
    Library *lib = p_data->lib;

    godot_variant relationship_variant;

    godot_object *relationship_object = instantiate_custom_class("Relationship", "Resource", lib);
    relationship_reconstruct(relationship_object, p_relationship, lib);

    lib->core_api->godot_variant_new_object(&relationship_variant, relationship_object);

    godot_variant *args[] = {&relationship_variant};

    godot_variant result_variant;
    object_call(p_data->callback_object, &p_data->callback_name, 1, args, &result_variant, lib);
    bool result = lib->core_api->godot_variant_as_bool(&result_variant);

    lib->core_api->godot_variant_destroy(&result_variant);
    lib->core_api->godot_variant_destroy(&relationship_variant);

    return true;
}

godot_variant relationship_manager_filter(godot_object *p_instance, Library *p_lib,
                                          RelationshipManager *p_relationship_manager,
                                          int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 2) // Filter Object, Filter Method
    {
        godot_object *filter_object = p_lib->core_api->godot_variant_as_object(p_args[0]);
        godot_string filter_name = p_lib->core_api->godot_variant_as_string(p_args[1]);

        if (!p_relationship_manager->filter_data)
            p_relationship_manager->filter_data = p_lib->core_api->godot_alloc(sizeof(CallbackData));
        else if (p_relationship_manager->filter_data->callback_object)
            p_lib->core_api->godot_string_destroy(&p_relationship_manager->filter_data->callback_name);

        memset(p_relationship_manager->filter_data, 0, sizeof(CallbackData));
        p_relationship_manager->filter_data->core = p_relationship_manager->core;
        p_relationship_manager->filter_data->lib = p_lib;
        p_relationship_manager->filter_data->callback_name = filter_name;
        p_relationship_manager->filter_data->callback_object = filter_object;

        p_relationship_manager->internal->filter(p_relationship_manager->internal, p_relationship_manager->filter_data, filter);

        p_lib->core_api->godot_string_destroy(&filter_name);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"filter()\" call. Expected 2.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

    return result_variant;
}

godot_variant relationship_manager_get(godot_object *p_instance, Library *p_lib,
                                       RelationshipManager *p_relationship_manager,
                                       int p_num_args, godot_variant **p_args)
{
    godot_variant result_variant;

    if (p_num_args == 1 || p_num_args == 3) // User ID, [Callback Object, Callback Name]
    {
        int64_t user_id = p_lib->core_api->godot_variant_as_int(p_args[0]);

        godot_object *relationship_object = instantiate_custom_class("Relationship", "Resource", p_lib);
        Relationship *relationship = p_lib->nativescript_api->godot_nativescript_get_userdata(relationship_object);
        enum EDiscordResult result = p_relationship_manager->internal->get(p_relationship_manager->internal,
                                                                           user_id, relationship->internal);

        relationship_reconstruct(relationship_object, relationship->internal, p_lib);

        // Run Callback
        {
            godot_variant result_variant;
            godot_variant relationship_variant;

            p_lib->core_api->godot_variant_new_int(&result_variant, result);
            p_lib->core_api->godot_variant_new_object(&relationship_variant, relationship_object);

            godot_variant *args[] = {&result_variant, &relationship_variant};

            if (p_num_args == 3)
            {
                godot_object *callback_object = p_lib->core_api->godot_variant_as_object(p_args[1]);
                godot_string callback_name = p_lib->core_api->godot_variant_as_string(p_args[2]);

                if (p_lib->core_1_1_api->godot_is_instance_valid(callback_object))
                    object_call(callback_object, &callback_name, 2, args, NULL, p_lib);
                else
                    PRINT_ERROR("Callback object is not a valid instance.", p_lib);

                p_lib->core_api->godot_string_destroy(&callback_name);
            }

            godot_string signal_name = p_lib->core_api->godot_string_chars_to_utf8("get_callback");
            object_emit_signal_deferred(p_instance, &signal_name, 2, args, p_lib);

            p_lib->core_api->godot_string_destroy(&signal_name);
            p_lib->core_api->godot_variant_destroy(&relationship_variant);
            p_lib->core_api->godot_variant_destroy(&result_variant);
        }
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get()\" call. Expected 1 or 3.", p_lib);
    }

    p_lib->core_api->godot_variant_new_nil(&result_variant);

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
    destructor.method_data = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle,
                                                               "RelationshipManager", "Reference",
                                                               constructor, destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Filter
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = relationship_manager_filter;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "RelationshipManager", "filter",
                                                                        attributes, method);
        }
        // Get
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method = relationship_manager_get;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle,
                                                                        "RelationshipManager", "get",
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

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "RelationshipManager", &signal);

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
            signal.args = args;
            signal.num_args = 1;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "RelationshipManager", &signal);

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
            signal.args = args;
            signal.num_args = 2;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle,
                                                                        "RelationshipManager", &signal);

            p_lib->core_api->godot_string_destroy(&relationship.name);
            p_lib->core_api->godot_string_destroy(&result.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
    }
}

void on_refresh(Core *p_core)
{
    Library *lib = p_core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("refresh");

    object_emit_signal(p_core->relationships->object, &signal, 0, NULL, lib);

    lib->core_api->godot_string_destroy(&signal);
}

void on_relationship_update(Core *p_core, struct DiscordRelationship *p_relationship)
{
    Library *lib = p_core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("relationship_update");

    godot_variant relationship_variant;

    godot_object *relationship_object = instantiate_custom_class("Relationship", "Resource", lib);
    relationship_reconstruct(relationship_object, p_relationship, p_core->lib);

    lib->core_api->godot_variant_new_object(&relationship_variant, relationship_object);

    godot_variant *args[] = {&relationship_variant};

    object_emit_signal(p_core->relationships->object, &signal, 1, args, lib);

    lib->core_api->godot_variant_destroy(&relationship_variant);
    lib->core_api->godot_string_destroy(&signal);
}
