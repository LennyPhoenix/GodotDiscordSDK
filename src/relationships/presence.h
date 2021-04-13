#ifndef PRESENCE_H_
#define PRESENCE_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the Presence class.
 */
typedef struct Presence
{
    struct DiscordPresence *internal;
    godot_object *object;

    godot_object *activity;
} Presence;

/**
 * @brief Helper functino to collapse all members into one internal struct.
 *
 * @details Collapses all members of the Presence into one internal struct
 *          recursively, allowing it to be used by the SDK.
 *
 * @param[in] p_instance    The object instance of the Presence.
 * @param[in] p_lib         The library object, containing some helpful structs.
 *
 * @return    The collapsed internal struct.
 */
struct DiscordPresence *presence_collapse(godot_object *p_instance, Library *p_lib);
/**
 * @brief Helper function to reconstruct and internal struct into a full Godot object.
 *
 * @details Reconstructs a full Godot object from an internal struct.
 *
 * @param[in] p_instance        The object instance of the Presence.
 * @param[in] p_relationship    The internal struct to build a Godot object for.
 * @param[in] p_lib             The library object, containing some helpful structs.
 */
void presence_reconstruct(godot_object *p_instance, struct DiscordPresence *p_presence, Library *p_lib);

/**
 * @brief Register the Presence class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_presence(void *p_handle, Library *p_lib);

#endif // PRESENCE_H_
