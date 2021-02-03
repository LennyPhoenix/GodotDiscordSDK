#ifndef ACTIVITIES_H_
#define ACTIVITIES_H_

#include "types.h"
#include "core.h"

#include "discord_game_sdk.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gdnative_api_struct.gen.h>

typedef struct ActivityTimestamps
{
    struct DiscordActivityTimestamps *internal;
    godot_object *object;
} ActivityTimestamps;

GDCALLINGCONV void *activity_timestamps_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void activity_timestamps_destructor(godot_object *p_instance, Library *p_lib,
                                                  ActivityTimestamps *p_timestamps);

godot_variant activity_timestamps_get_start(godot_object *p_instance, Library *p_lib,
                                            ActivityTimestamps *p_timestamps);
GDCALLINGCONV void activity_timestamps_set_start(godot_object *p_instance, Library *p_lib,
                                                 ActivityTimestamps *p_timestamps,
                                                 godot_variant *p_start);

godot_variant activity_timestamps_get_end(godot_object *p_instance, Library *p_lib,
                                          ActivityTimestamps *p_timestamps);
GDCALLINGCONV void activity_timestamps_set_end(godot_object *p_instance, Library *p_lib,
                                               ActivityTimestamps *p_timestamps,
                                               godot_variant *p_end);

void register_activity_timestamps(void *p_handle, Library *p_lib);

typedef struct ActivityAssets
{
    struct DiscordActivityAssets *internal;
    godot_object *object;
} ActivityAssets;

GDCALLINGCONV void *activity_assets_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void activity_assets_destructor(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_assets);

godot_variant activity_assets_get_large_image(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_timestamps);
GDCALLINGCONV void activity_assets_set_large_image(godot_object *p_instance, Library *p_lib,
                                                   ActivityAssets *p_timestamps,
                                                   godot_variant *p_large_image);

godot_variant activity_assets_get_large_text(godot_object *p_instance, Library *p_lib,
                                             ActivityAssets *p_timestamps);
GDCALLINGCONV void activity_assets_set_large_text(godot_object *p_instance, Library *p_lib,
                                                  ActivityAssets *p_timestamps,
                                                  godot_variant *p_large_text);

godot_variant activity_assets_get_small_image(godot_object *p_instance, Library *p_lib,
                                              ActivityAssets *p_timestamps);
GDCALLINGCONV void activity_assets_set_small_image(godot_object *p_instance, Library *p_lib,
                                                   ActivityAssets *p_timestamps,
                                                   godot_variant *p_small_image);

godot_variant activity_assets_get_small_text(godot_object *p_instance, Library *p_lib,
                                             ActivityAssets *p_timestamps);
GDCALLINGCONV void activity_assets_set_small_text(godot_object *p_instance, Library *p_lib,
                                                  ActivityAssets *p_timestamps,
                                                  godot_variant *p_small_text);

void register_activity_assets(void *p_handle, Library *p_lib);

typedef struct PartySize
{
    struct DiscordPartySize *internal;
    godot_object *object;

    bool bound;
} PartySize;

GDCALLINGCONV void *party_size_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void party_size_destructor(godot_object *p_instance, Library *p_lib,
                                         PartySize *p_party_size);

godot_variant party_size_get_current_size(godot_object *p_instance, Library *p_lib,
                                          PartySize *p_party_size);
GDCALLINGCONV void party_size_set_current_size(godot_object *p_instance, Library *p_lib,
                                               PartySize *p_party_size,
                                               godot_variant *p_current_size);

godot_variant party_size_get_max_size(godot_object *p_instance, Library *p_lib,
                                      PartySize *p_party_size);
GDCALLINGCONV void party_size_set_max_size(godot_object *p_instance, Library *p_lib,
                                           PartySize *p_party_size,
                                           godot_variant *p_max_size);

void register_party_size(void *p_handle, Library *p_lib);

typedef struct ActivityParty
{
    struct DiscordActivityParty *internal;
    godot_object *object;

    godot_object *size;
} ActivityParty;

GDCALLINGCONV void *activity_party_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void activity_party_destructor(godot_object *p_instance, Library *p_lib,
                                             ActivityParty *p_party);

godot_variant activity_party_get_id(godot_object *p_instance, Library *p_lib,
                                    ActivityParty *p_party);
GDCALLINGCONV void activity_party_set_id(godot_object *p_instance, Library *p_lib,
                                         ActivityParty *p_party,
                                         godot_variant *p_id);

godot_variant activity_party_get_privacy(godot_object *p_instance, Library *p_lib,
                                         ActivityParty *p_party);
GDCALLINGCONV void activity_party_set_privacy(godot_object *p_instance, Library *p_lib,
                                              ActivityParty *p_party,
                                              godot_variant *p_privacy);

godot_variant activity_party_get_size(godot_object *p_instance, Library *p_lib,
                                      ActivityParty *p_party);
GDCALLINGCONV void activity_party_set_size(godot_object *p_instance, Library *p_lib,
                                           ActivityParty *p_party,
                                           godot_variant *p_size);

void register_activity_party(void *p_handle, Library *p_lib);

typedef struct ActivitySecrets
{
    struct DiscordActivitySecrets *internal;
    godot_object *object;
} ActivitySecrets;

GDCALLINGCONV void *activity_secrets_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void activity_secrets_destructor(godot_object *p_instance, Library *p_lib,
                                               ActivitySecrets *p_secrets);

godot_variant activity_secrets_get_match(godot_object *p_instance, Library *p_lib,
                                         ActivitySecrets *p_secrets);
GDCALLINGCONV void activity_secrets_set_match(godot_object *p_instance, Library *p_lib,
                                              ActivitySecrets *p_secrets,
                                              godot_variant *p_match);

godot_variant activity_secrets_get_join(godot_object *p_instance, Library *p_lib,
                                        ActivitySecrets *p_secrets);
GDCALLINGCONV void activity_secrets_set_join(godot_object *p_instance, Library *p_lib,
                                             ActivitySecrets *p_secrets,
                                             godot_variant *p_join);

godot_variant activity_secrets_get_spectate(godot_object *p_instance, Library *p_lib,
                                            ActivitySecrets *p_secrets);
GDCALLINGCONV void activity_secrets_set_spectate(godot_object *p_instance, Library *p_lib,
                                                 ActivitySecrets *p_secrets,
                                                 godot_variant *p_spectate);

void register_activity_secrets(void *p_handle, Library *p_lib);

#endif