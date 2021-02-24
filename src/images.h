#ifndef IMAGES_H_
#define IMAGES_H_

#include "types.h"
#include "core.h"
#include "images/image_dimensions.h"
#include "images/image_handle.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

struct ImageManager
{
    struct IDiscordImageManager *internal;
    godot_object *object;

    Core *core;

    Library *lib;
};

void register_image_manager(void *p_handle, Library *p_lib);

#endif