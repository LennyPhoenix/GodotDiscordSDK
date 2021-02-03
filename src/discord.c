#include "discord.h"

Library lib;

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options)
{
    lib.api = p_options->api_struct;
    lib.gdnlib = p_options->gd_native_library;

    for (unsigned int i = 0; i < lib.api->num_extensions; i++)
    {
        switch (lib.api->extensions[i]->type)
        {
        case GDNATIVE_EXT_NATIVESCRIPT:
            lib.nativescript_api = (godot_gdnative_ext_nativescript_api_struct *)lib.api->extensions[i];

            if (lib.nativescript_api->next)
            {
                const godot_gdnative_api_struct *extension = lib.nativescript_api->next;

                while (extension)
                {
                    if (extension->version.major == 1 && extension->version.minor == 1)
                    {
                        lib.nativescript_1_1_api = (const godot_gdnative_ext_nativescript_1_1_api_struct *)extension;
                    }

                    extension = extension->next;
                }
            }

            break;

        default:
            break;
        };
    };
}

void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options)
{
    lib.api = NULL;
    lib.nativescript_api = NULL;
    lib.nativescript_1_1_api = NULL;
}

void GDN_EXPORT godot_nativescript_init(void *p_handle)
{
    if (!lib.nativescript_1_1_api)
    {
        godot_string string = lib.api->godot_string_chars_to_utf8("Failed to load nativescript 1.1...");
        lib.api->godot_print(&string);
    }

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
}
