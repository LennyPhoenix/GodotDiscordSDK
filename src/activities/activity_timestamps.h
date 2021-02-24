#ifndef ACTIVITY_TIMESTAMPS_H_
#define ACTIVITY_TIMESTAMPS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct ActivityTimestamps
{
    struct DiscordActivityTimestamps *internal;
    godot_object *object;
} ActivityTimestamps;

void register_activity_timestamps(void *p_handle, Library *p_lib);

#endif