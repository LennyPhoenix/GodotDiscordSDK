#ifndef __PARTY_SIZE_H_
#define __PARTY_SIZE_H_

#include "types.h"

#include <gdnative_api_struct.gen.h>

typedef struct PartySize
{
    struct DiscordPartySize *internal;
    godot_object *object;
} PartySize;

void register_party_size(void *p_handle, Library *p_lib);

#endif // __PARTY_SIZE_H_
