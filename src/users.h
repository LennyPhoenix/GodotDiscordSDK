#ifndef USERS_H_
#define USERS_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the UserManager class.
 */
struct UserManager
{
    struct IDiscordUserManager *internal;
    godot_object *object;

    Library *lib;
};

/**
 * @brief Register the UserManager class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_user_manager(void *p_handle, Library *p_lib);

/**
 * @brief Discord event called when the current user updates.
 *
 * @param[in] p_event_data    The custom event data, in this case the Core object.
 */
void on_current_user_update(void *p_event_data);

#endif // USERS_H_
