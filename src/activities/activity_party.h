#ifndef ACTIVITY_PARTY_H_
#define ACTIVITY_PARTY_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct ActivityParty
{
    struct DiscordActivityParty *internal;
    godot_object *object;

    godot_object *size;
} ActivityParty;

struct DiscordActivityParty *activity_party_collapse(godot_object *p_instance, Library *p_lib);
void activity_party_reconstruct(godot_object *p_instance, struct DiscordActivityParty *p_party, Library *p_lib);

void register_activity_party(void *p_handle, Library *p_lib);

#endif