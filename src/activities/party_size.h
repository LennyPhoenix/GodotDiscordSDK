#ifndef PARTY_SIZE_H_
#define PARTY_SIZE_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

/**
 * @brief User data struct for the PartySize class.
 */
typedef struct PartySize
{
    struct DiscordPartySize *internal;
    godot_object *object;
} PartySize;

/**
 * @brief Register the PartySize class with Godot.
 *
 * @param[in] p_handle    The object handle.
 * @param[in] p_lib       The library object, containing some helpful structs.
 */
void register_party_size(void *p_handle, Library *p_lib);

#endif // PARTY_SIZE_H_
