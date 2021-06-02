#include "networking.h"

#include "core.h"
#include "util.h"

GDCALLINGCONV void *network_manager_constructor(godot_object *p_instance, void *p_method_data)
{
    Library *lib = p_method_data;

    NetworkManager *network_manager = lib->core_api->godot_alloc(sizeof(NetworkManager));
    memset(network_manager, 0, sizeof(NetworkManager));

    network_manager->object = p_instance;
    network_manager->lib    = lib;

    return network_manager;
}

GDCALLINGCONV void network_manager_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    lib->core_api->godot_free(network_manager);
}

godot_variant network_manager_get_peer_id(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                          int p_num_args, godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 0)
    {
        uint64_t peer_id;
        network_manager->internal->get_peer_id(network_manager->internal, &peer_id);

        lib->core_api->godot_variant_new_uint(&result_variant, peer_id);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"get_peer_id()\" call. Expected 0.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

godot_variant network_manager_flush(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args,
                                    godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 0)
    {
        enum EDiscordResult result = network_manager->internal->flush(network_manager->internal);
        lib->core_api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"flush()\" call. Expected 0.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

godot_variant network_manager_open_peer(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                        int p_num_args, godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 2) // Peer ID, Route
    {

        uint64_t peer_id          = lib->core_api->godot_variant_as_uint(p_args[0]);
        godot_string route_string = lib->core_api->godot_variant_as_string(p_args[1]);

        godot_char_string route_char_string = lib->core_api->godot_string_utf8(&route_string);
        const char *route                   = lib->core_api->godot_char_string_get_data(&route_char_string);

        enum EDiscordResult result = network_manager->internal->open_peer(network_manager->internal, peer_id, route);

        lib->core_api->godot_variant_new_int(&result_variant, result);

        lib->core_api->godot_char_string_destroy(&route_char_string);
        lib->core_api->godot_string_destroy(&route_string);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"open_peer()\" call. Expected 2.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

godot_variant network_manager_update_peer(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                          int p_num_args, godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 2) // Peer ID, Route
    {
        uint64_t peer_id          = lib->core_api->godot_variant_as_uint(p_args[0]);
        godot_string route_string = lib->core_api->godot_variant_as_string(p_args[1]);

        godot_char_string route_char_string = lib->core_api->godot_string_utf8(&route_string);
        const char *route                   = lib->core_api->godot_char_string_get_data(&route_char_string);

        enum EDiscordResult result = network_manager->internal->update_peer(network_manager->internal, peer_id, route);

        lib->core_api->godot_variant_new_int(&result_variant, result);

        lib->core_api->godot_char_string_destroy(&route_char_string);
        lib->core_api->godot_string_destroy(&route_string);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"update_peer()\" call. Expected 2.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

godot_variant network_manager_close_peer(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                         int p_num_args, godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 1) // Peer ID
    {

        uint64_t peer_id = lib->core_api->godot_variant_as_uint(p_args[0]);

        enum EDiscordResult result = network_manager->internal->close_peer(network_manager->internal, peer_id);

        lib->core_api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"close_peer()\" call. Expected 1.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

godot_variant network_manager_open_channel(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                           int p_num_args, godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 3) // Peer ID, Channel ID, Reliable
    {
        uint64_t peer_id   = lib->core_api->godot_variant_as_uint(p_args[0]);
        uint8_t channel_id = (uint8_t)lib->core_api->godot_variant_as_uint(p_args[1]);
        bool reliable      = lib->core_api->godot_variant_as_bool(p_args[2]);

        enum EDiscordResult result =
            network_manager->internal->open_channel(network_manager->internal, peer_id, channel_id, reliable);

        lib->core_api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"open_channel()\" call. Exptected 3.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

godot_variant network_manager_close_channel(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                            int p_num_args, godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 2) // Peer ID, Channel ID
    {
        uint64_t peer_id   = lib->core_api->godot_variant_as_uint(p_args[0]);
        uint8_t channel_id = (uint8_t)lib->core_api->godot_variant_as_uint(p_args[1]);

        enum EDiscordResult result =
            network_manager->internal->close_channel(network_manager->internal, peer_id, channel_id);

        lib->core_api->godot_variant_new_int(&result_variant, result);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"close_channel()\" call. Exptected 2.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

godot_variant network_manager_send_message(godot_object *p_instance, void *p_method_data, void *p_user_data,
                                           int p_num_args, godot_variant **p_args)
{
    Library *lib                    = p_method_data;
    NetworkManager *network_manager = p_user_data;

    godot_variant result_variant;

    if (p_num_args == 3) // Peer ID, Channel ID, Message
    {
        uint64_t peer_id              = lib->core_api->godot_variant_as_uint(p_args[0]);
        uint8_t channel_id            = (uint8_t)lib->core_api->godot_variant_as_uint(p_args[1]);
        godot_pool_byte_array message = lib->core_api->godot_variant_as_pool_byte_array(p_args[2]);

        godot_pool_byte_array_read_access *read_access = lib->core_api->godot_pool_byte_array_read(&message);
        uint8_t *read_pointer = (uint8_t *)lib->core_api->godot_pool_byte_array_read_access_ptr(read_access);
        uint32_t size         = (uint32_t)lib->core_api->godot_pool_byte_array_size(&message);

        enum EDiscordResult result =
            network_manager->internal->send_message(network_manager->internal, peer_id, channel_id, read_pointer, size);

        lib->core_api->godot_pool_byte_array_read_access_destroy(read_access);
        lib->core_api->godot_variant_new_int(&result_variant, result);
        lib->core_api->godot_pool_byte_array_destroy(&message);
    }
    else
    {
        PRINT_ERROR("Invalid number of arguments for \"send_message()\" call. Expected 3.", lib);
        lib->core_api->godot_variant_new_nil(&result_variant);
    }

    return result_variant;
}

void register_network_manager(void *p_handle, Library *p_lib)
{
    godot_instance_create_func constructor;
    memset(&constructor, 0, sizeof(godot_instance_create_func));
    constructor.create_func = network_manager_constructor;
    constructor.method_data = p_lib;

    godot_instance_destroy_func destructor;
    memset(&destructor, 0, sizeof(godot_instance_destroy_func));
    destructor.destroy_func = network_manager_destructor;
    destructor.method_data  = p_lib;

    p_lib->nativescript_api->godot_nativescript_register_class(p_handle, "NetworkManager", "Object", constructor,
                                                               destructor);

    // Methods
    {
        godot_instance_method method;
        godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

        // Get Peer ID
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_get_peer_id;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "get_peer_id",
                                                                        attributes, method);
        }
        // Flush
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_flush;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "flush", attributes,
                                                                        method);
        }
        // Open Peer
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_open_peer;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "open_peer",
                                                                        attributes, method);
        }
        // Update Peer
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_update_peer;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "update_peer",
                                                                        attributes, method);
        }
        // Close Peer
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_close_peer;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "close_peer",
                                                                        attributes, method);
        }
        // Open Channel
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_open_channel;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "open_channel",
                                                                        attributes, method);
        }
        // Close Channel
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_close_channel;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "close_channel",
                                                                        attributes, method);
        }
        // Send Message
        {
            memset(&method, 0, sizeof(godot_instance_method));
            method.method      = network_manager_send_message;
            method.method_data = p_lib;

            p_lib->nativescript_api->godot_nativescript_register_method(p_handle, "NetworkManager", "send_message",
                                                                        attributes, method);
        }
    }

    // Signals
    {
        godot_signal signal;

        // Message
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("message");

            godot_signal_argument peer_id;
            {
                memset(&peer_id, 0, sizeof(godot_signal_argument));
                peer_id.name = p_lib->core_api->godot_string_chars_to_utf8("peer_id");

                peer_id.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument channel_id;
            {
                memset(&channel_id, 0, sizeof(godot_signal_argument));
                channel_id.name = p_lib->core_api->godot_string_chars_to_utf8("channel_id");

                channel_id.type = GODOT_VARIANT_TYPE_INT;
            }
            godot_signal_argument data;
            {
                memset(&data, 0, sizeof(godot_signal_argument));
                data.name = p_lib->core_api->godot_string_chars_to_utf8("data");

                data.type = GODOT_VARIANT_TYPE_POOL_BYTE_ARRAY;
            }

            godot_signal_argument args[] = {peer_id, channel_id, data};
            signal.args                  = args;
            signal.num_args              = 3;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "NetworkManager", &signal);

            p_lib->core_api->godot_string_destroy(&data.name);
            p_lib->core_api->godot_string_destroy(&channel_id.name);
            p_lib->core_api->godot_string_destroy(&peer_id.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
        // Route Update
        {
            memset(&signal, 0, sizeof(godot_signal));
            signal.name = p_lib->core_api->godot_string_chars_to_utf8("route_update");

            godot_signal_argument route;
            {
                memset(&route, 0, sizeof(godot_signal_argument));
                route.name = p_lib->core_api->godot_string_chars_to_utf8("route");

                route.type = GODOT_VARIANT_TYPE_STRING;
            }

            godot_signal_argument args[] = {route};
            signal.args                  = args;
            signal.num_args              = 1;

            p_lib->nativescript_api->godot_nativescript_register_signal(p_handle, "NetworkManager", &signal);

            p_lib->core_api->godot_string_destroy(&route.name);
            p_lib->core_api->godot_string_destroy(&signal.name);
        }
    }
}

void on_message(void *p_event_data, DiscordNetworkPeerId p_peer_id, DiscordNetworkChannelId p_channel_id,
                uint8_t *p_data, uint32_t p_data_length)
{
    Core *core   = p_event_data;
    Library *lib = core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("message");

    godot_variant peer_id_variant;
    godot_variant channel_id_variant;
    godot_variant data_variant;

    godot_pool_byte_array data;
    lib->core_api->godot_pool_byte_array_new(&data);
    lib->core_api->godot_pool_byte_array_resize(&data, (int64_t)p_data_length);

    godot_pool_byte_array_write_access *write_access = lib->core_api->godot_pool_byte_array_write(&data);
    uint8_t *write_pointer = lib->core_api->godot_pool_byte_array_write_access_ptr(write_access);
    memcpy(write_pointer, p_data, p_data_length);

    lib->core_api->godot_variant_new_uint(&peer_id_variant, p_peer_id);
    lib->core_api->godot_variant_new_uint(&channel_id_variant, (uint64_t)p_channel_id);
    lib->core_api->godot_variant_new_pool_byte_array(&data_variant, &data);

    const godot_variant *args[] = {&peer_id_variant, &channel_id_variant, &data_variant};

    object_emit_signal(core->networking->object, &signal, 3, args, lib);

    lib->core_api->godot_pool_byte_array_write_access_destroy(write_access);
    lib->core_api->godot_pool_byte_array_destroy(&data);
    lib->core_api->godot_variant_destroy(&data_variant);
    lib->core_api->godot_variant_destroy(&channel_id_variant);
    lib->core_api->godot_variant_destroy(&peer_id_variant);
    lib->core_api->godot_string_destroy(&signal);
}

void on_route_update(void *p_event_data, const char *p_route_data)
{
    Core *core   = p_event_data;
    Library *lib = core->lib;

    godot_string signal = lib->core_api->godot_string_chars_to_utf8("route_update");

    godot_variant route_variant;

    godot_string route_string = lib->core_api->godot_string_chars_to_utf8(p_route_data);
    lib->core_api->godot_variant_new_string(&route_variant, &route_string);

    const godot_variant *args[] = {&route_variant};

    object_emit_signal(core->networking->object, &signal, 1, args, lib);

    lib->core_api->godot_string_destroy(&route_string);
    lib->core_api->godot_variant_destroy(&route_variant);
    lib->core_api->godot_string_destroy(&signal);
}
