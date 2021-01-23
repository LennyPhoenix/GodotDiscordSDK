#ifndef IMAGES_H_
#define IMAGES_H_

#include "types.h"
#include "core.h"

#include "discord_game_sdk.h"

#include <math.h>
#include <stdlib.h>
#include <gdnative_api_struct.gen.h>

typedef struct ImageDimensions
{
    struct DiscordImageDimensions *internal;
    godot_object *object;
} ImageDimensions;

GDCALLINGCONV void *image_dimensions_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void image_dimensions_destructor(godot_object *p_instance, Library *p_lib,
                                               ImageDimensions *p_dimensions);

godot_variant image_dimensions_get_width(godot_object *p_instance, Library *p_lib,
                                         ImageDimensions *p_dimensions);
GDCALLINGCONV void image_dimensions_set_width(godot_object *p_instance, Library *p_lib,
                                              ImageDimensions *p_dimensions,
                                              godot_variant *p_width);

godot_variant image_dimensions_get_height(godot_object *p_instance, Library *p_lib,
                                          ImageDimensions *p_dimensions);
GDCALLINGCONV void image_dimensions_set_height(godot_object *p_instance, Library *p_lib,
                                               ImageDimensions *p_dimensions,
                                               godot_variant *p_height);

void register_image_dimensions(void *p_handle, Library *p_lib);

typedef struct ImageHandle
{
    struct DiscordImageHandle *internal;
    godot_object *object;
} ImageHandle;

GDCALLINGCONV void *image_handle_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void image_handle_destructor(godot_object *p_instance, Library *p_lib,
                                           ImageHandle *p_handle);

godot_variant image_handle_get_type(godot_object *p_instance, Library *p_lib,
                                    ImageHandle *p_handle);
GDCALLINGCONV void image_handle_set_type(godot_object *p_instance, Library *p_lib,
                                         ImageHandle *p_handle,
                                         godot_variant *p_type);

godot_variant image_handle_get_id(godot_object *p_instance, Library *p_lib,
                                  ImageHandle *p_handle);
GDCALLINGCONV void image_handle_set_id(godot_object *p_instance, Library *p_lib,
                                       ImageHandle *p_handle,
                                       godot_variant *p_id);

godot_variant image_handle_get_size(godot_object *p_instance, Library *p_lib,
                                    ImageHandle *p_handle);
GDCALLINGCONV void image_handle_set_size(godot_object *p_instance, Library *p_lib,
                                         ImageHandle *p_handle,
                                         godot_variant *p_size);

void register_image_handle(void *p_handle, Library *p_lib);

struct ImageManager
{
    struct IDiscordImageManager *internal;
    godot_object *object;

    Core *core;

    Library *lib;
};

GDCALLINGCONV void *image_manager_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void image_manager_destructor(godot_object *p_instance, Library *p_lib,
                                            ImageManager *p_image_manager);

godot_variant image_manager_fetch(godot_object *p_instance, Library *p_lib,
                                  ImageManager *p_image_manager,
                                  int p_num_args, godot_variant **p_args);

godot_variant image_manager_get_dimensions(godot_object *p_instance, Library *p_lib,
                                           ImageManager *p_image_manager,
                                           int p_num_args, godot_variant **p_args);

godot_variant image_manager_get_data(godot_object *p_instance, Library *p_lib,
                                     ImageManager *p_image_manager,
                                     int p_num_args, godot_variant **p_args);

void register_image_manager(void *p_handle, Library *p_lib);

#endif