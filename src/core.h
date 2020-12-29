#ifndef CORE_H_
#define CORE_H_

#include "discord.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

typedef struct Discord
{
    struct IDiscordCore *core;
} Discord;

void *core_constructor(godot_object *p_instance, void *p_method_data);
void core_destructor(godot_object *p_instance, struct Library *p_lib,
                     struct Discord *p_discord);

godot_variant core_create(godot_object *p_instance, struct Library *p_lib,
                          struct Discord *p_discord,
                          int p_num_args, godot_variant **p_args);
godot_variant core_run_callbacks(godot_object *p_instance, struct Library *p_lib,
                                 struct Discord *p_discord,
                                 int p_num_args, godot_variant **p_args);

void register_core(void *p_handle, struct Library *p_lib);

#endif