#ifndef RELATIONSHIP_H_
#define RELATIONSHIP_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct Relationship
{
    struct DiscordRelationship *internal;
    godot_object *object;

    godot_object *user;
    godot_object *presence;
} Relationship;

void register_relationship(void *p_handle, Library *p_lib);

#endif