#ifndef CORE_H_
#define CORE_H_

#include "discord.h"
#include "users.h"
#include "util.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

typedef struct Core
{
    struct IDiscordCore *internal;
    godot_object *object;

    struct UserManager *users;
    struct IDiscordUserEvents *user_events;

    struct Library *lib;
} Core;

void *core_constructor(godot_object *p_instance, struct Library *p_lib);
void core_destructor(godot_object *p_instance, struct Library *p_lib,
                     struct Core *p_core);

godot_variant core_create(godot_object *p_instance, struct Library *p_lib,
                          struct Core *p_core,
                          int p_num_args, godot_variant **p_args);
godot_variant core_run_callbacks(godot_object *p_instance, struct Library *p_lib,
                                 struct Core *p_core,
                                 int p_num_args, godot_variant **p_args);

godot_variant core_get_user_manager(godot_object *p_instance, struct Library *p_lib,
                                    struct Core *p_core,
                                    int p_num_args, godot_variant **p_args);

void register_core(void *p_handle, struct Library *p_lib);

#endif