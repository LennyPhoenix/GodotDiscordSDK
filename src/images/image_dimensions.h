#ifndef __IMAGE_DIMENSIONS_H_
#define __IMAGE_DIMENSIONS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct ImageDimensions
{
    struct DiscordImageDimensions *internal;
    godot_object *object;
} ImageDimensions;

void register_image_dimensions(void *p_handle, Library *p_lib);

#endif // __IMAGE_DIMENSIONS_H_
