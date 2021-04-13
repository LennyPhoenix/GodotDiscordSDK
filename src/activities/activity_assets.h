#ifndef ACTIVITY_ASSETS_H_
#define ACTIVITY_ASSETS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the ActivityAssets class.
 */
typedef struct ActivityAssets
{
    struct DiscordActivityAssets *internal;
    godot_object *object;
} ActivityAssets;

/**
 * @brief Register the ActivityAssets class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_activity_assets(void *p_handle, Library *p_lib);

#endif // ACTIVITY_ASSETS_H_
