#ifndef ACTIVITIES_H_
#define ACTIVITIES_H_

#include "types.h"
#include "core.h"

#include "discord_game_sdk.h"

#include <stdlib.h>
#include <gdnative_api_struct.gen.h>

GDCALLINGCONV void *activity_timestamps_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void activity_timestamps_destructor(godot_object *p_instance, Library *p_lib,
                                                  struct DiscordActivityTimestamps *p_timestamps);

godot_variant activity_timestamps_get_start(godot_object *p_instance, Library *p_lib,
                                            struct DiscordActivityTimestamps *p_timestamps);
GDCALLINGCONV void activity_timestamps_set_start(godot_object *p_instance, Library *p_lib,
                                                 struct DiscordActivityTimestamps *p_timestamps,
                                                 godot_variant *p_start);

godot_variant activity_timestamps_get_end(godot_object *p_instance, Library *p_lib,
                                          struct DiscordActivityTimestamps *p_timestamps);
GDCALLINGCONV void activity_timestamps_set_end(godot_object *p_instance, Library *p_lib,
                                               struct DiscordActivityTimestamps *p_timestamps,
                                               godot_variant *p_end);

void register_activity_timestamps(void *p_handle, Library *p_lib);

#endif