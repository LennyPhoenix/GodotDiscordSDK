#ifndef CORE_H_
#define CORE_H_

#include "types.h"
#include "users.h"
#include "util.h"

#include "discord_game_sdk.h"

#include <stdlib.h>
#include <gdnative_api_struct.gen.h>

GDCALLINGCONV void *core_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void core_destructor(godot_object *p_instance, Library *p_lib,
                                   Core *p_core);

godot_variant core_create(godot_object *p_instance, Library *p_lib,
                          Core *p_core,
                          int p_num_args, godot_variant **p_args);

godot_variant core_run_callbacks(godot_object *p_instance, Library *p_lib,
                                 Core *p_core,
                                 int p_num_args, godot_variant **p_args);

godot_variant core_get_user_manager(godot_object *p_instance, Library *p_lib,
                                    Core *p_core,
                                    int p_num_args, godot_variant **p_args);

godot_variant core_get_image_manager(godot_object *p_instance, Library *p_lib,
                                     Core *p_core,
                                     int p_num_args, godot_variant **p_args);

void register_core(void *p_handle, Library *p_lib);

#endif