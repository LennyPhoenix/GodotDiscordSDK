#include "discord.h"

#include "types.h"
#include "core.h"
#include "users.h"
#include "users/user.h"
#include "images.h"
#include "images/image_handle.h"
#include "images/image_dimensions.h"
#include "activities.h"
#include "activities/activity_timestamps.h"
#include "activities/activity_assets.h"
#include "activities/party_size.h"
#include "activities/activity_party.h"
#include "activities/activity_secrets.h"
#include "activities/activity.h"

Library lib;

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options)
{
    lib.core_api = p_options->api_struct;

    if (lib.core_api->next)
    {
        const godot_gdnative_api_struct *extension = lib.core_api->next;

        while (extension)
        {
            if (extension->version.major == 1 && extension->version.minor == 1)
            {
                lib.core_1_1_api = (const godot_gdnative_core_1_1_api_struct *)extension;
            }

            extension = extension->next;
        }
    }

    for (unsigned int i = 0; i < lib.core_api->num_extensions; i++)
    {
        switch (lib.core_api->extensions[i]->type)
        {
        case GDNATIVE_EXT_NATIVESCRIPT:
            lib.nativescript_api = (const godot_gdnative_ext_nativescript_api_struct *)lib.core_api->extensions[i];

        default:
            break;
        };
    };

    lib.gdnlib = p_options->gd_native_library;
}

void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options)
{
    lib.core_api = NULL;
    lib.core_1_1_api = NULL;
    lib.nativescript_api = NULL;
}

void GDN_EXPORT godot_nativescript_init(void *p_handle)
{
    register_core(p_handle, &lib);

    // Users
    register_user(p_handle, &lib);
    register_user_manager(p_handle, &lib);

    // Images
    register_image_dimensions(p_handle, &lib);
    register_image_handle(p_handle, &lib);
    register_image_manager(p_handle, &lib);

    // Activities
    register_activity_timestamps(p_handle, &lib);
    register_activity_assets(p_handle, &lib);
    register_party_size(p_handle, &lib);
    register_activity_party(p_handle, &lib);
    register_activity_secrets(p_handle, &lib);
    register_activity(p_handle, &lib);
    register_activity_manager(p_handle, &lib);
}
