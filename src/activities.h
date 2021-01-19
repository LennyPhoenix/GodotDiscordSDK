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

GDCALLINGCONV void *activity_assets_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void activity_assets_destructor(godot_object *p_instance, Library *p_lib,
                                              struct DiscordActivityAssets *p_assets);

godot_variant activity_assets_get_large_image(godot_object *p_instance, Library *p_lib,
                                              struct DiscordActivityAssets *p_timestamps);
GDCALLINGCONV void activity_assets_set_large_image(godot_object *p_instance, Library *p_lib,
                                                   struct DiscordActivityAssets *p_timestamps,
                                                   godot_variant *p_large_image);

godot_variant activity_assets_get_large_text(godot_object *p_instance, Library *p_lib,
                                             struct DiscordActivityAssets *p_timestamps);
GDCALLINGCONV void activity_assets_set_large_text(godot_object *p_instance, Library *p_lib,
                                                  struct DiscordActivityAssets *p_timestamps,
                                                  godot_variant *p_large_text);

godot_variant activity_assets_get_small_image(godot_object *p_instance, Library *p_lib,
                                              struct DiscordActivityAssets *p_timestamps);
GDCALLINGCONV void activity_assets_set_small_image(godot_object *p_instance, Library *p_lib,
                                                   struct DiscordActivityAssets *p_timestamps,
                                                   godot_variant *p_small_image);

godot_variant activity_assets_get_small_text(godot_object *p_instance, Library *p_lib,
                                             struct DiscordActivityAssets *p_timestamps);
GDCALLINGCONV void activity_assets_set_small_text(godot_object *p_instance, Library *p_lib,
                                                  struct DiscordActivityAssets *p_timestamps,
                                                  godot_variant *p_small_text);

void register_activity_assets(void *p_handle, Library *p_lib);

GDCALLINGCONV void *party_size_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void party_size_destructor(godot_object *p_instance, Library *p_lib,
                                         struct DiscordPartySize *p_party_size);

godot_variant party_size_get_current_size(godot_object *p_instance, Library *p_lib,
                                          struct DiscordPartySize *p_party_size);
GDCALLINGCONV void party_size_set_current_size(godot_object *p_instance, Library *p_lib,
                                               struct DiscordPartySize *p_party_size,
                                               godot_variant *p_current_size);

godot_variant party_size_get_max_size(godot_object *p_instance, Library *p_lib,
                                      struct DiscordPartySize *p_party_size);
GDCALLINGCONV void party_size_set_max_size(godot_object *p_instance, Library *p_lib,
                                           struct DiscordPartySize *p_party_size,
                                           godot_variant *p_max_size);

void register_party_size(void *p_handle, Library *p_lib);

#endif