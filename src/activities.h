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

godot_variant activity_party_get_size(godot_object *p_instance, Library *p_lib,
                                      ActivityParty *p_party);
GDCALLINGCONV void activity_party_set_size(godot_object *p_instance, Library *p_lib,
                                           ActivityParty *p_party,
                                           godot_variant *p_size);

void activity_party_collapse(godot_object *p_instance, Library *p_lib);

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

typedef struct Activity
{
    struct DiscordActivity *internal;
    godot_object *object;

    godot_object *timestamps;
    godot_object *assets;
    godot_object *party;
    godot_object *secrets;
} Activity;

GDCALLINGCONV void *activity_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void activity_destructor(godot_object *p_instance, Library *p_lib,
                                       Activity *p_activity);

godot_variant activity_get_application_id(godot_object *p_instance, Library *p_lib,
                                          Activity *p_activity);
GDCALLINGCONV void activity_set_application_id(godot_object *p_instance, Library *p_lib,
                                               Activity *p_activity,
                                               godot_variant *p_application_id);

godot_variant activity_get_name(godot_object *p_instance, Library *p_lib,
                                Activity *p_activity);
GDCALLINGCONV void activity_set_name(godot_object *p_instance, Library *p_lib,
                                     Activity *p_activity,
                                     godot_variant *p_name);

godot_variant activity_get_state(godot_object *p_instance, Library *p_lib,
                                 Activity *p_activity);
GDCALLINGCONV void activity_set_state(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity,
                                      godot_variant *p_state);

godot_variant activity_get_details(godot_object *p_instance, Library *p_lib,
                                   Activity *p_activity);
GDCALLINGCONV void activity_set_details(godot_object *p_instance, Library *p_lib,
                                        Activity *p_activity,
                                        godot_variant *p_details);

godot_variant activity_get_timestamps(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity);
GDCALLINGCONV void activity_set_timestamps(godot_object *p_instance, Library *p_lib,
                                           Activity *p_activity,
                                           godot_variant *p_timestamps);

godot_variant activity_get_assets(godot_object *p_instance, Library *p_lib,
                                  Activity *p_activity);
GDCALLINGCONV void activity_set_assets(godot_object *p_instance, Library *p_lib,
                                       Activity *p_activity,
                                       godot_variant *p_assets);

godot_variant activity_get_party(godot_object *p_instance, Library *p_lib,
                                 Activity *p_activity);
GDCALLINGCONV void activity_set_party(godot_object *p_instance, Library *p_lib,
                                      Activity *p_activity,
                                      godot_variant *p_party);

godot_variant activity_get_secrets(godot_object *p_instance, Library *p_lib,
                                   Activity *p_activity);
GDCALLINGCONV void activity_set_secrets(godot_object *p_instance, Library *p_lib,
                                        Activity *p_activity,
                                        godot_variant *p_secrets);

godot_variant activity_get_instance(godot_object *p_instance, Library *p_lib,
                                    Activity *p_activity);
GDCALLINGCONV void activity_set_instance(godot_object *p_instance, Library *p_lib,
                                         Activity *p_activity,
                                         godot_variant *p_is_instance);

void activity_collapse(godot_object *p_instance, Library *p_lib);

void register_activity(void *p_handle, Library *p_lib);

struct ActivityManager
{
    struct IDiscordActivityManager *internal;
    godot_object *object;

    Core *core;

    Library *lib;
};

GDCALLINGCONV void *activity_manager_constructor(godot_object *p_instance, Library *p_lib);
GDCALLINGCONV void activity_manager_destructor(godot_object *p_instance, Library *p_lib,
                                               ActivityManager *p_activity_manager);

godot_variant activity_manager_register_command(godot_object *p_instance, Library *p_lib,
                                                ActivityManager *p_activity_manager,
                                                int p_num_args, godot_variant **p_args);
godot_variant activity_manager_register_steam(godot_object *p_instance, Library *p_lib,
                                              ActivityManager *p_activity_manager,
                                              int p_num_args, godot_variant **p_args);

godot_variant activity_manager_update_activity(godot_object *p_instance, Library *p_lib,
                                               ActivityManager *p_activity_manager,
                                               int p_num_args, godot_variant **p_args);

godot_variant activity_manager_clear_activity(godot_object *p_instance, Library *p_lib,
                                              ActivityManager *p_activity_manager,
                                              int p_num_args, godot_variant **p_args);

godot_variant activity_manager_send_request_reply(godot_object *p_instance, Library *p_lib,
                                                  ActivityManager *p_activity_manager,
                                                  int p_num_args, godot_variant **p_args);

godot_variant activity_manager_send_invite(godot_object *p_instance, Library *p_lib,
                                           ActivityManager *p_activity_manager,
                                           int p_num_args, godot_variant **p_args);

godot_variant activity_manager_accept_invite(godot_object *p_instance, Library *p_lib,
                                             ActivityManager *p_activity_manager,
                                             int p_num_args, godot_variant **p_args);

void register_activity_manager(void *p_handle, Library *p_lib);

void on_activity_join(Core *p_core, const char *p_join_secret);
void on_activity_spectate(Core *p_core, const char *p_spectate_secret);
void on_activity_join_request(Core *p_core, struct DiscordUser *p_user);
void on_activity_invite(Core *p_core, enum EDiscordActivityActionType p_type,
                        struct DiscordUser *p_user, struct DiscordActivity *p_activity);

#endif