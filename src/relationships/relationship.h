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

struct DiscordRelationship *relationship_collapse(godot_object *p_instance, Library *p_lib);
void relationship_reconstruct(godot_object *p_instance, struct DiscordRelationship *p_relationship, Library *p_lib);

void register_relationship(void *p_handle, Library *p_lib);

#endif // RELATIONSHIP_H_
