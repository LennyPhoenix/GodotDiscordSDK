#ifndef IMAGES_H_
#define IMAGES_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the ImageManager class.
 */
struct ImageManager
{
    struct IDiscordImageManager *internal;
    godot_object *object;

    Library *lib;
};

/**
 * @brief Register the ImageManager class with Godot.
 */
void register_image_manager(void *p_handle, Library *p_lib);

#endif // IMAGES_H_
