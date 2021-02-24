#ifndef ACTIVITIES_H_
#define ACTIVITIES_H_

#include "types.h"
#include "core.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

struct ActivityManager
{
    struct IDiscordActivityManager *internal;
    godot_object *object;

    Core *core;

    Library *lib;
};

void register_activity_manager(void *p_handle, Library *p_lib);

void on_activity_join(Core *p_core, const char *p_join_secret);
void on_activity_spectate(Core *p_core, const char *p_spectate_secret);
void on_activity_join_request(Core *p_core, struct DiscordUser *p_user);
void on_activity_invite(Core *p_core, enum EDiscordActivityActionType p_type,
                        struct DiscordUser *p_user, struct DiscordActivity *p_activity);

#endif