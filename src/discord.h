#ifndef DISCORD_H_
#define DISCORD_H_

#include "types.h"
#include "core.h"
#include "users.h"
#include "images.h"

#include <stdlib.h>
#include <gdnative_api_struct.gen.h>

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options);
void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options);
void GDN_EXPORT godot_nativescript_init(void *p_handle);

#endif