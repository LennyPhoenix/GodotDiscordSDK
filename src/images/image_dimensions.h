#ifndef IMAGE_DIMENSIONS_H_
#define IMAGE_DIMENSIONS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the ImageDimensions class.
 */
typedef struct ImageDimensions
{
    struct DiscordImageDimensions *internal;
    godot_object *object;
} ImageDimensions;

/**
 * @brief Register the ImageDimensions class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_image_dimensions(void *p_handle, Library *p_lib);

#endif // IMAGE_DIMENSIONS_H_
