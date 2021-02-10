@echo off
curl.exe --output discord_game_sdk.zip --url https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip
powershell.exe "Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('discord_game_sdk.zip', 'dsdk');"

mkdir demo\bin\windows-32
mkdir demo\bin\windows-64

copy dsdk\lib\x86\discord_game_sdk.dll demo\bin\windows-32\discord_game_sdk.dll
copy dsdk\lib\x86\discord_game_sdk.dll.lib lib\discord_game_sdk.32.lib

copy dsdk\lib\x86_64\discord_game_sdk.dll demo\bin\windows-64\discord_game_sdk.dll
copy dsdk\lib\x86_64\discord_game_sdk.dll.lib lib\discord_game_sdk.64.lib

del discord_game_sdk.zip
RMDIR /S /Q dsdk
