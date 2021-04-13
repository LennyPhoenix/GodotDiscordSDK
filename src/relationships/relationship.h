#ifndef RELATIONSHIP_H_
#define RELATIONSHIP_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the Relationship class.
 */
typedef struct Relationship
{
    struct DiscordRelationship *internal;
    godot_object *object;

    godot_object *user;
    godot_object *presence;
} Relationship;

/**
 * @brief Helper function to collapse all members into one internal struct.
 *
 * @details Collapses all members of the Relationship into one internal struct
 *          recursively, allowing it to be used by the SDK.
 *
 * @param[in] p_instance    The object instance of the Relationship.
 * @param[in] p_lib         The library object, containing some helpful structs.
 *
 * @return    The collapsed internal struct.
 */
struct DiscordRelationship *relationship_collapse(godot_object *p_instance, Library *p_lib);
/**
 * @brief Helper function to reconstruct an internal struct into a full Godot object.
 *
 * @details Reconstructs a full Godot object from an internal struct.
 *
 * @param[in] p_instance        The object instance of the Relationship.
 * @param[in] p_relationship    The internal struct to build a Godot object for.
 * @param[in] p_lib             The library object, containing some helpful structs.
 */
void relationship_reconstruct(godot_object *p_instance, struct DiscordRelationship *p_relationship, Library *p_lib);

/**
 * @brief Register the Relationship class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_relationship(void *p_handle, Library *p_lib);

#endif // RELATIONSHIP_H_
