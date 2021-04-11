#ifndef USERS_H_
#define USERS_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

struct UserManager
{
    struct IDiscordUserManager *internal;
    godot_object *object;

    Library *lib;
};

void register_user_manager(void *p_handle, Library *p_lib);

void on_current_user_update(void *p_event_data);

#endif // USERS_H_
