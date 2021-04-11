#ifndef IMAGES_H_
#define IMAGES_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

struct ImageManager
{
    struct IDiscordImageManager *internal;
    godot_object *object;

    Library *lib;
};

void register_image_manager(void *p_handle, Library *p_lib);

#endif // IMAGES_H_
