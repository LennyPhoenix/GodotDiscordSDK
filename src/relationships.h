#ifndef RELATIONSHIPS_H_
#define RELATIONSHIPS_H_

#include "types.h"
#include "core.h"

#include "discord_game_sdk.h"

#include <gdnative_api_struct.gen.h>

struct RelationshipManager
{
    struct IDiscordRelationshipManager *internal;
    godot_object *object;

    Core *core;

    Library *lib;
};

void register_relationship_manager(void *p_handle, Library *p_lib);

void on_refresh(Core *p_core);

#endif