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

namespace discord
{

    class Core final
    {
    public:
        static Result Create(ClientId clientId, std::uint64_t flags, Core **instance);

        ~Core();

        Result RunCallbacks();
        void SetLogHook(LogLevel minLevel, std::function<void(LogLevel, char const *)> hook);

        discord::ApplicationManager &ApplicationManager();
        discord::UserManager &UserManager();
        discord::ImageManager &ImageManager();
        discord::ActivityManager &ActivityManager();
        discord::RelationshipManager &RelationshipManager();
        discord::LobbyManager &LobbyManager();
        discord::NetworkManager &NetworkManager();
        discord::OverlayManager &OverlayManager();
        discord::StorageManager &StorageManager();
        discord::StoreManager &StoreManager();
        discord::VoiceManager &VoiceManager();
        discord::AchievementManager &AchievementManager();

    private:
        Core() = default;
        Core(Core const &rhs) = delete;
        Core &operator=(Core const &rhs) = delete;
        Core(Core &&rhs) = delete;
        Core &operator=(Core &&rhs) = delete;

        IDiscordCore *internal_;
        Event<LogLevel, char const *> setLogHook_;
        discord::ApplicationManager applicationManager_;
        discord::UserManager userManager_;
        discord::ImageManager imageManager_;
        discord::ActivityManager activityManager_;
        discord::RelationshipManager relationshipManager_;
        discord::LobbyManager lobbyManager_;
        discord::NetworkManager networkManager_;
        discord::OverlayManager overlayManager_;
        discord::StorageManager storageManager_;
        discord::StoreManager storeManager_;
        discord::VoiceManager voiceManager_;
        discord::AchievementManager achievementManager_;
    };

} // namespace discord
