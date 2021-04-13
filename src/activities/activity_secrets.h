#ifndef ACTIVITY_SECRETS_H_
#define ACTIVITY_SECRETS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the ActivitySecrets class.
 */
typedef struct ActivitySecrets
{
    struct DiscordActivitySecrets *internal;
    godot_object *object;
} ActivitySecrets;

/**
 * @brief Register the ActivitySecrets class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_activity_secrets(void *p_handle, Library *p_lib);

#endif // ACTIVITY_SECRETS_H_
