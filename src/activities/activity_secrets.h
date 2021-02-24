#ifndef ACTIVITY_SECRETS_H_
#define ACTIVITY_SECRETS_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct ActivitySecrets
{
    struct DiscordActivitySecrets *internal;
    godot_object *object;
} ActivitySecrets;

void register_activity_secrets(void *p_handle, Library *p_lib);

#endif