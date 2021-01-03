#ifndef UTIL_H_
#define UTIL_H_

#include "discord.h"

#include <stdbool.h>
#include <gdnative_api_struct.gen.h>

godot_string get_script_path(godot_string *name,
                             struct Library *p_lib);

godot_object *instantiate_custom_class(const char *p_class_name, const char *p_base,
                                       struct Library *p_lib);

godot_variant_call_error object_emit_signal(godot_object *p_object,
                                            godot_string *p_signal_name,
                                            int p_num_args, godot_variant **p_args,
                                            struct Library *p_lib);

godot_variant_call_error object_call(godot_object *p_object,
                                     godot_string *p_method_name,
                                     int p_num_args, godot_variant **p_args,
                                     struct Library *p_lib);

#endif