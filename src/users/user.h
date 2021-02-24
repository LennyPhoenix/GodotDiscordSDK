#ifndef USER_H_
#define USER_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct User
{
    struct DiscordUser *internal;
    godot_object *object;
} User;

void register_user(void *p_handle, Library *p_lib);

#endif