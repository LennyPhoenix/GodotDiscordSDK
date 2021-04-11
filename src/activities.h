#ifndef __ACTIVITIES_H_
#define __ACTIVITIES_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

struct ActivityManager
{
    struct IDiscordActivityManager *internal;
    godot_object *object;

    Library *lib;
};

void register_activity_manager(void *p_handle, Library *p_lib);

void on_activity_join(void *p_event_data, const char *p_join_secret);
void on_activity_spectate(void *p_event_data, const char *p_spectate_secret);
void on_activity_join_request(void *p_event_data, struct DiscordUser *p_user);
void on_activity_invite(void *p_event_data, enum EDiscordActivityActionType p_type, struct DiscordUser *p_user,
                        struct DiscordActivity *p_activity);

#endif // __ACTIVITIES_H_
