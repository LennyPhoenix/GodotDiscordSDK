#ifndef USERS_H_
#define USERS_H_

#include "types.h"
#include "core.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

struct UserManager
{
    struct IDiscordUserManager *internal;
    godot_object *object;

    Core *core;

    Library *lib;
};

void register_user_manager(void *p_handle, Library *p_lib);

void on_current_user_update(Core *p_core);

#endif