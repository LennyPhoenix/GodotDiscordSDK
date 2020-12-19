#pragma once

#include "types.hpp"
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

namespace godot
{

    class Core final
    {
    public:
        static Result Create(ClientId clientId, std::uint64_t flags, Core **instance);

        ~Core();

        Result RunCallbacks();
        void SetLogHook(LogLevel minLevel, std::function<void(LogLevel, char const *)> hook);

        godot::ApplicationManager &ApplicationManager();
        godot::UserManager &UserManager();
        godot::ImageManager &ImageManager();
        godot::ActivityManager &ActivityManager();
        godot::RelationshipManager &RelationshipManager();
        godot::LobbyManager &LobbyManager();
        godot::NetworkManager &NetworkManager();
        godot::OverlayManager &OverlayManager();
        godot::StorageManager &StorageManager();
        godot::StoreManager &StoreManager();
        godot::VoiceManager &VoiceManager();
        godot::AchievementManager &AchievementManager();

    private:
        Core() = default;
        Core(Core const &rhs) = delete;
        Core &operator=(Core const &rhs) = delete;
        Core(Core &&rhs) = delete;
        Core &operator=(Core &&rhs) = delete;

        IDiscordCore *internal_;
        Event<LogLevel, char const *> setLogHook_;
        godot::ApplicationManager applicationManager_;
        godot::UserManager userManager_;
        godot::ImageManager imageManager_;
        godot::ActivityManager activityManager_;
        godot::RelationshipManager relationshipManager_;
        godot::LobbyManager lobbyManager_;
        godot::NetworkManager networkManager_;
        godot::OverlayManager overlayManager_;
        godot::StorageManager storageManager_;
        godot::StoreManager storeManager_;
        godot::VoiceManager voiceManager_;
        godot::AchievementManager achievementManager_;
    };

} // namespace godot
