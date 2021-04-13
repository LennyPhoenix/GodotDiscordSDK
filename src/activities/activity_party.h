#ifndef ACTIVITY_PARTY_H_
#define ACTIVITY_PARTY_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the ActivityParty class.
 */
typedef struct ActivityParty
{
    struct DiscordActivityParty *internal;
    godot_object *object;

    godot_object *size;
} ActivityParty;

/**
 * @brief Helper function to collapse all members into one internal struct.
 *
 * @details Collapses all members of the ActivityParty into one internal struct
 *          recursively, allowing it to be used by the SDK.
 *
 * @param[in] p_instance    The object instance of the ActivityParty.
 * @param[in] p_lib         The library object, containing some helpful structs.
 *
 * @return    The collapsed internal struct.
 */
struct DiscordActivityParty *activity_party_collapse(godot_object *p_instance, Library *p_lib);
/**
 * @brief Helper function to reconstruct an internal struct into a full Godot object.
 *
 * @details Reconstructs a full Godot object from an internal struct.
 *
 * @param[in] p_instance        The object instance of the ActivityParty.
 * @param[in] p_relationship    The internal struct to build a Godot object for.
 * @param[in] p_lib             The library object, containing some helpful structs.
 */
void activity_party_reconstruct(godot_object *p_instance, struct DiscordActivityParty *p_party, Library *p_lib);

/**
 * @brief Register the ActivityParty class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_activity_party(void *p_handle, Library *p_lib);

#endif // ACTIVITY_PARTY_H_
