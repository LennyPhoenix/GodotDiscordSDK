#ifndef __RELATIONSHIPS_H_
#define __RELATIONSHIPS_H_

#include "types.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

struct RelationshipManager
{
    struct IDiscordRelationshipManager *internal;
    godot_object *object;

    CallbackData *filter_data;

    Library *lib;
};

void register_relationship_manager(void *p_handle, Library *p_lib);

void on_refresh(void *p_event_data);
void on_relationship_update(void *p_event_data, struct DiscordRelationship *p_relationship);

#endif // __RELATIONSHIPS_H_
