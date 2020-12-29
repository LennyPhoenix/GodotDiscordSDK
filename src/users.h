#ifndef USERS_H_
#define USERS_H_

#include "discord.h"
#include "core.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

typedef struct UserManager
{
    struct IDiscordUserManager *internal;
    godot_object *object;

    struct Core *core;

    struct Library *lib;
} UserManager;

void on_current_user_update(struct Core *p_core);

void *user_manager_constructor(godot_object *p_instance, struct Library *p_lib);
void user_manager_destructor(godot_object *p_instance, struct Library *p_lib,
                             struct UserManager *p_user_manager);

void register_user_manager(void *p_handle, struct Library *p_lib);

#endif