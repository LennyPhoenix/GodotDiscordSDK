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

#endif // NETWORKING_H_
