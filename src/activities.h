#ifndef ACTIVITIES_H_
#define ACTIVITIES_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the ActivityManager class.
 */
struct ActivityManager
{
    struct IDiscordActivityManager *internal;
    godot_object *object;

    Library *lib;
};

/**
 * @brief Register the ActivityManager class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_activity_manager(void *p_handle, Library *p_lib);

/**
 * @brief Discord event called when an activity is joined.
 *
 * @param[in] p_event_data     The custom event data, in this case the Core object.
 * @param[in] p_join_secret    The join secret for the activity.
 */
void on_activity_join(void *p_event_data, const char *p_join_secret);
/**
 * [DEPRECATED]
 * @brief Discord event called when an activity is spectated.
 *
 * @param[in] p_event_data         The custom event data, in this case the Core object.
 * @param[in] p_spectate_secret    The spectate secret for the activity.
 */
void on_activity_spectate(void *p_event_data, const char *p_spectate_secret);
/**
 * @brief Discord event called when someone requests to join your activity.
 *
 * @param[in] p_event_data    The custom event data, in this case the Core object.
 * @param[in] p_user          The user requesting to join.
 */
void on_activity_join_request(void *p_event_data, struct DiscordUser *p_user);
/**
 * @brief Discord event called when someone invites you to join an activity.
 *
 * @param[in] p_event_data    The custom event data, in this case the Core object.
 * @param[in] p_type          The type of activity action, will be a JOIN in most cases
 *                            as specating is now deprecated.
 * @param[in] p_activity      The activity that you were invited to.
 */
void on_activity_invite(void *p_event_data, enum EDiscordActivityActionType p_type, struct DiscordUser *p_user,
                        struct DiscordActivity *p_activity);

#endif // ACTIVITIES_H_
