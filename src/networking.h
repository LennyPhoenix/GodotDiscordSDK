#ifndef NETWORKING_H_
#define NETWORKING_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for NetworkManager class.
 */
struct NetworkManager
{
    struct IDiscordNetworkManager *internal;
    godot_object *object;

    Library *lib;
};

/**
 * @brief Register the NetworkManager class with Godot.
 */
void register_network_manager(void *p_handle, Library *p_lib);

/**
 * @brief Discord event called when a message is received from a network peer.
 * 
 * @param[in] p_event_data     The custom event data, in this case the Core object.
 * @param[in] p_peer_id        The peer ID of the message sender.
 * @param[in] p_channel_id     The ID of the message's channel.
 * @param[in] p_data           The message data.
 * @param[in] p_data_length    The length of the message data.
 */
void on_message(void *p_event_data, DiscordNetworkPeerId p_peer_id, DiscordNetworkChannelId p_channel_id,
                uint8_t *p_data, uint32_t p_data_length);
/**
 * @brief Discord event called when the current networking route is changed.
 *
 * @param[in] p_event_data    The custom event data, in this case the Core object.
 * @param[in] p_route_data    The new route data for the user.
 */
void on_route_update(void *p_event_data, const char *p_route_data);

#endif // NETWORKING_H_
