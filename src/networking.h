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
 * @brief Discord event called when the current networking route is changed.
 *
 * @param[in] p_event_data    The custom event data, in this case the Core object.
 * @param[in] p_route_data    The new route data for the user.
 */
void on_route_update(void *p_event_data, const char *p_route_data);

#endif // NETWORKING_H_
