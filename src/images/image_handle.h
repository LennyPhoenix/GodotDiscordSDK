#ifndef IMAGE_HANDLE_H_
#define IMAGE_HANDLE_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct ImageHandle
{
    struct DiscordImageHandle *internal;
    godot_object *object;
} ImageHandle;

void register_image_handle(void *p_handle, Library *p_lib);

#endif