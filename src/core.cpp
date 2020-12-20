#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "core.hpp"

namespace godot
{

    int Core::create(int client_id, int flags)
    {
        DiscordCreateParams params{};
        params.client_id = client_id;
        params.flags = flags;
        params.event_data = this;

        int result = DiscordCreate(DISCORD_VERSION, &params, &internal_);
        return result;
    }

    Core::~Core()
    {
        if (internal_)
        {
            internal_->destroy(internal_);
            internal_ = nullptr;
        }
    }

    int Core::run_callbacks()
    {
        return internal_->run_callbacks(internal_);
    }

} // namespace godot
