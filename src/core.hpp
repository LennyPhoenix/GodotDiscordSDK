#pragma once

#include "ffi.h"

#include <Godot.hpp>
#include <Reference.hpp>

namespace godot
{

    class Core : public Reference
    {
        GODOT_CLASS(Core, Reference)

    public:
        static void _register_methods()
        {
            register_method("create", &Core::create);
            register_method("run_callbacks", &Core::run_callbacks);
        }

        void _init() {}

        int create(int client_id, int flags);

        ~Core();

        int run_callbacks();

    private:
        IDiscordCore *internal_;
    };

} // namespace godot