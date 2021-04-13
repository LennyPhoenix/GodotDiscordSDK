#ifndef USER_H_
#define USER_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the User class.
 */
typedef struct User
{
    struct DiscordUser *internal;
    godot_object *object;
} User;

/**
 * @brief Register the User class with Godot.
 */
void register_user(void *p_handle, Library *p_lib);

#endif // USER_H_
