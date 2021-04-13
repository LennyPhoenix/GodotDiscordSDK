#ifndef IMAGE_HANDLE_H_
#define IMAGE_HANDLE_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the ImageHandle class.
 */
typedef struct ImageHandle
{
    struct DiscordImageHandle *internal;
    godot_object *object;
} ImageHandle;

/**
 * @brief Register the ImageHandle class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_image_handle(void *p_handle, Library *p_lib);

#endif // IMAGE_HANDLE_H_
