#ifndef DISCORD_H_
#define DISCORD_H_

#include "core.h"

#include <gdnative_api_struct.gen.h>

typedef struct Library
{
    const godot_gdnative_core_api_struct *api;
    const godot_gdnative_ext_nativescript_api_struct *nativescript_api;
    const godot_gdnative_ext_nativescript_1_1_api_struct *nativescript_1_1_api;
} Library;

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options);
void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options);
void GDN_EXPORT godot_nativescript_init(void *p_handle);

#endif