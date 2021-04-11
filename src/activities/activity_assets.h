#ifndef __ACTIVITY_ASSETS_H_
#define __ACTIVITY_ASSETS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct ActivityAssets
{
    struct DiscordActivityAssets *internal;
    godot_object *object;
} ActivityAssets;

void register_activity_assets(void *p_handle, Library *p_lib);

#endif // __ACTIVITY_ASSETS_H_
