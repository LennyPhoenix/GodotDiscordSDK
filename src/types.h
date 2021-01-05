#ifndef TYPES_H_
#define TYPES_H_

#include "discord_game_sdk.h"

#include <stdlib.h>
#include <gdnative_api_struct.gen.h>

typedef struct Library
{
    const godot_gdnative_core_api_struct *api;
    const godot_gdnative_ext_nativescript_api_struct *nativescript_api;
    const godot_gdnative_ext_nativescript_1_1_api_struct *nativescript_1_1_api;

    const godot_object *gdnlib;
} Library;

typedef struct Core Core;

typedef struct CallbackData
{
    godot_object *callback_object;
    godot_string callback_name;

    void *data;

    Library *lib;
    Core *core;
} CallbackData;

typedef struct UserManager
{
    struct IDiscordUserManager *internal;
    godot_object *object;

    Core *core;

    Library *lib;
} UserManager;

struct Core
{
    struct IDiscordCore *internal;
    godot_object *object;

    UserManager *users;
    struct IDiscordUserEvents *user_events;

    Library *lib;
};

#endif