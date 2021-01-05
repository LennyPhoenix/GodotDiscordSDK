#ifndef IMAGES_H_
#define IMAGES_H_

#include "types.h"
#include "discord.h"
#include "core.h"

#include "discord_game_sdk.h"

#include <stdlib.h>
#include <gdnative_api_struct.gen.h>

GDCALLINGCONV void *image_dimensions_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void image_dimensions_destructor(godot_object *p_instance, Library *p_lib,
                                               struct DiscordImageDimensions *p_dimensions);

godot_variant image_dimensions_get_width(godot_object *p_instance, Library *p_lib,
                                         struct DiscordImageDimensions *p_dimensions);
GDCALLINGCONV void image_dimensions_set_width(godot_object *p_instance, Library *p_lib,
                                              struct DiscordImageDimensions *p_dimensions,
                                              godot_variant *p_width);

godot_variant image_dimensions_get_height(godot_object *p_instance, Library *p_lib,
                                          struct DiscordImageDimensions *p_dimensions);
GDCALLINGCONV void image_dimensions_set_height(godot_object *p_instance, Library *p_lib,
                                               struct DiscordImageDimensions *p_dimensions,
                                               godot_variant *p_height);

void register_image_dimensions(void *p_handle, Library *p_lib);

#endif