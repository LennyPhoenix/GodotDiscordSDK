#ifndef UTIL_H_
#define UTIL_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define PRINT_WARNING(Error, Lib) Lib->core_api->godot_print_warning(Error, __func__, __FILE__, __LINE__);

#define PRINT_ERROR(Error, Lib) Lib->core_api->godot_print_error(Error, __func__, __FILE__, __LINE__);

#define INIT_OBJECT(Name, Class, InternalClass, Lib, Instance)          \
    Class *Name = Lib->core_api->godot_alloc(sizeof(Class));            \
    memset(Name, 0, sizeof(Class));                                     \
                                                                        \
    Name->internal = Lib->core_api->godot_alloc(sizeof(InternalClass)); \
    memset(Name->internal, 0, sizeof(InternalClass));                   \
                                                                        \
    Name->object = Instance;

/**
 * @brief   Get the path of a .gdns file from the name of a class.
 *
 * @details Fetches the full res:// path of a .gdns script using a class name and the .gdnlib
 *          path.
 *
 * @param[in] p_class_name    The name of the class to fetch the .gdns file for.
 * @param[in] p_lib           The library object, containing some helpful structs and the
 *                            gdnlib object.
 *
 * @return    The path of the .gdns file.
 */
godot_string get_script_path(godot_string *p_class_name, Library *p_lib);

/**
 * @brief   Instantiate a custom GDNative class.
 *
 * @details Fetches a .gdns script, then instantiates a class with the name and base given.
 *
 * @param[in] p_class_name    The name of the class to instantiate.
 * @param[in] p_base          The base that the class inherits from.
 * @param[in] p_lib           The library object, containing some helpful structs.
 *
 * @return    The instantiated object.
 */
godot_object *instantiate_custom_class(const char *p_class_name, const char *p_base, Library *p_lib);

/**
 * @brief   Emit a signal from an object with the given args.
 *
 * @details Emits a signal from an object with the name and arguments given. The signal will
 *          be called immediately, so use `object_emit_signal_deferred` for a delayed emission.
 *
 * @param[in] p_object         The object to emit a signal from.
 * @param[in] p_signal_name    The name of the signal to emit.
 * @param[in] p_num_args       The number of args to pass.
 * @param[in] p_args           The arguments to pass to the signal.
 * @param[in] p_lib            The library object, containing some helpful structs.
 *
 * @return    The error returned, if applicable.
 */
godot_variant_call_error object_emit_signal(godot_object *p_object, godot_string *p_signal_name, int p_num_args,
                                            const godot_variant **p_args, Library *p_lib);

/**
 * @brief   Emit a delayed signal from an object with the given args.
 *
 * @details Emits a signal from an object with the name and arguments given. The signal will
 *          be emitted with `call_deferred`, delaying it by 1 tick.
 *
 * @param[in] p_object         The object to emit a signal from.
 * @param[in] p_signal_name    The name of the signal to emit.
 * @param[in] p_num_args       The number of args to pass.
 * @param[in] p_args           The arguments to pass to the signal.
 * @param[in] p_lib            The library object, containing some helpful structs.
 *
 * @return    The error returned, if applicable.
 */
godot_variant_call_error object_emit_signal_deferred(godot_object *p_object, godot_string *p_signal_name,
                                                     int p_num_args, const godot_variant **p_args, Library *p_lib);

/**
 * @brief   Helper function to call a method on an object.
 *
 * @details Calls a method on an object with the name and arguments given.
 *
 * @param[in]  p_object         The object to call a method on.
 * @param[in]  p_signal_name    The name of the method to call.
 * @param[in]  p_num_args       The number of args to pass.
 * @param[in]  p_args           The arguments to pass to the method.
 * @param[out] r_return         The variant returned by the method, if applicable.
 * @param[in]  p_lib            The library object, containing some helpful structs.
 *
 * @return     The error returned, if applicable.
 */
godot_variant_call_error object_call(godot_object *p_object, godot_string *p_method_name, int p_num_args,
                                     const godot_variant **p_args, godot_variant *r_return, Library *p_lib);

/**
 * @brief   Helper function to reference an object.
 *
 * @details Increments the ref-counter of an object inheriting Reference.
 *
 * @param[in] p_object    The object to reference.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void godot_reference(godot_object *p_object, Library *p_lib);
/**
 * @brief   Helper function to unreference an object.
 *
 * @details Decrements the ref-counter of an object inheriting Reference, destroying it
 *          if the counter is now zero.
 *
 * @param[in] p_object    The object to unreference.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void godot_unreference(godot_object *p_object, Library *p_lib);

#endif
