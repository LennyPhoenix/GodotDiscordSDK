#pragma once

#include <Godot.hpp>

#include "types.hpp"
#include "core.hpp"
#include "application_manager.hpp"
#include "user_manager.hpp"
#include "image_manager.hpp"
#include "activity_manager.hpp"
#include "relationship_manager.hpp"
#include "lobby_manager.hpp"
#include "network_manager.hpp"
#include "overlay_manager.hpp"
#include "storage_manager.hpp"
#include "store_manager.hpp"
#include "voice_manager.hpp"
#include "achievement_manager.hpp"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o)
{
    Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o)
{
    Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle)
{
    Godot::nativescript_init(handle);
}