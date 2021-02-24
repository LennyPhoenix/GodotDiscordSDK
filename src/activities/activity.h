#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct Activity
{
    struct DiscordActivity *internal;
    godot_object *object;

    godot_object *timestamps;
    godot_object *assets;
    godot_object *party;
    godot_object *secrets;
} Activity;

struct DiscordActivity *activity_collapse(godot_object *p_instance, Library *p_lib);
void activity_reconstruct(godot_object *p_instance, struct DiscordActivity *p_activity, Library *p_lib);

void register_activity(void *p_handle, Library *p_lib);

#endif