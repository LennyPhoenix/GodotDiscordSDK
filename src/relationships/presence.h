#ifndef PRESENCE_H_
#define PRESENCE_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct Presence
{
    struct DiscordPresence *internal;
    godot_object *object;

    godot_object *activity;
} Presence;

struct DiscordPresence *presence_collapse(godot_object *p_instance, Library *p_lib);
void presence_reconstruct(godot_object *p_instance, struct DiscordPresence *p_presence, Library *p_lib);

void register_presence(void *p_handle, Library *p_lib);

#endif // PRESENCE_H_
