echo -e "By running this script you agree to the Discord Developers ToS.\n"

echo Downloading the Discord Game SDK...
wget https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip
unzip discord_game_sdk -d dsdk

mkdir demo/bin/linux-32
mkdir demo/bin/linux-64
mkdir demo/bin/osx-32
mkdir demo/bin/osx-64

cp dsdk/c/discord_game_sdk.h src/discord_game_sdk.h 

cp dsdk/lib/x86/discord_game_sdk.dll.lib lib/discord_game_sdk.32.lib
cp dsdk/lib/x86_64/discord_game_sdk.dll.lib lib/discord_game_sdk.64.lib

cp dsdk/lib/x86_64/discord_game_sdk.so lib/libdiscord_game_sdk.so
cp dsdk/lib/x86_64/discord_game_sdk.dylib lib/libdiscord_game_sdk.dylib

cp dsdk/lib/x86_64/discord_game_sdk.so demo/bin/linux-64/libdiscord_game_sdk.so
cp dsdk/lib/x86_64/discord_game_sdk.dylib demo/bin/osx-64/libdiscord_game_sdk.dylib

cp dsdk/lib/x86_64/discord_game_sdk.so demo/bin/linux-32/libdiscord_game_sdk.so
cp dsdk/lib/x86_64/discord_game_sdk.dylib demo/bin/osx-32/libdiscord_game_sdk.dylib

rm -rf dsdk
rm discord_game_sdk.zip
