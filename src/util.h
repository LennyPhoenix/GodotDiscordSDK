#ifndef UTIL_H_
#define UTIL_H_

#include "discord.h"

#include <gdnative_api_struct.gen.h>

godot_object *instantiate_custom_class(const char *p_class_name, const char *p_base,
                                       struct Library *p_lib);

#endif