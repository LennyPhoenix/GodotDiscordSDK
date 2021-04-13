#ifndef RELATIONSHIPS_H_
#define RELATIONSHIPS_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the RelationshipManager class.
 */
struct RelationshipManager
{
    struct IDiscordRelationshipManager *internal;
    godot_object *object;

    CallbackData *filter_data;

    Library *lib;
};

/**
 * @brief Register the RelationshipManager class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_relationship_manager(void *p_handle, Library *p_lib);

/**
 * @brief Discord event called when the relationship list is cached.
 *
 * @param[in] p_event_data    The custom event data, in this case the Core object.
 */
void on_refresh(void *p_event_data);
/**
 * @brief Discord event called when a relationship is updated.
 *
 * @param[in] p_event_data      The custom event data, in this case the Core object.
 * @param[in] p_relationship    The updated relationship.
 */
void on_relationship_update(void *p_event_data, struct DiscordRelationship *p_relationship);

#endif // RELATIONSHIPS_H_
