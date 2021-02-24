#ifndef ACTIVITY_ASSETS_H_
#define ACTIVITY_ASSETS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct ActivityAssets
{
    struct DiscordActivityAssets *internal;
    godot_object *object;
} ActivityAssets;

void register_activity_assets(void *p_handle, Library *p_lib);

#endif