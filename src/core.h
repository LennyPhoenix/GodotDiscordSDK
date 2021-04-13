#ifndef CORE_H_
#define CORE_H_

#include "activities.h"
#include "images.h"
#include "relationships.h"
#include "types.h"
#include "users.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the Core class.
 */
struct Core
{
    struct IDiscordCore *internal;
    godot_object *object;

    CallbackData *hook_data;

    // Managers
    UserManager *users;
    struct IDiscordUserEvents *user_events;
    ImageManager *images;
    ActivityManager *activities;
    struct IDiscordActivityEvents *activity_events;
    RelationshipManager *relationships;
    struct IDiscordRelationshipEvents *relationship_events;

    Library *lib;
};

/**
 * @brief Register the Core class with Godot.
 */
void register_core(void *p_handle, Library *p_lib);

#endif // CORE_H_
