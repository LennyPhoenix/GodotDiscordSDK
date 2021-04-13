#ifndef ACTIVITY_TIMESTAMPS_H_
#define ACTIVITY_TIMESTAMPS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the ActivityTimestamps class.
 */
typedef struct ActivityTimestamps
{
    struct DiscordActivityTimestamps *internal;
    godot_object *object;
} ActivityTimestamps;

/**
 * @brief Register the ActivityTimestamps class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_activity_timestamps(void *p_handle, Library *p_lib);

#endif // ACTIVITY_TIMESTAMPS_H_
