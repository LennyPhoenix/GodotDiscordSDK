# Godot Discord Game SDK

**NOTE:** This wrapper is still under development.

> A Discord Game SDK wrapper for Godot, written using GDNative C for Windows, Linux and MacOS.

## Docs

For detailed documentation and instructions, head to [the wiki](https://github.com/LennyPhoenix/GodotDiscordSDK/wiki).

## Downloading

To download precompiled binaries for every commit, head to [the actions page](https://github.com/LennyPhoenix/GodotDiscordSDK/actions), or download [a specific release](https://github.com/LennyPhoenix/GodotDiscordSDK/releases).

## Compiling & Installing

- Clone the repository: `git clone https://github.com/LennyPhoenix/GodotDiscordSDK.git`
  - Update submodules:
  
  ```cmd
  cd GodotDiscordSDK
  git submodule update --init --recursive --remote
  ```

- Either:
  - Run the setup script:

    - Windows: `setup.bat`
    - Linux/OSX: `./setup.sh`

  - Or manually setup:
  
    - Download the [Discord Game SDK (2.5.6)](https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip).

    - Place the `discord_game_sdk.dll.lib` file from the `lib/x86` folder of the SDK in [the lib folder](lib/) of the repo and rename it to `discord_game_sdk.32.lib`.

      Do the same with the `discord_game_sdk.dll.lib` file from the `lib/x86_64` folder, renaming it to `discord_game_sdk.64.lib`.

    - Make sure to place the appropriate Discord Game SDK shared library in [the demo's bin directory](demo/bin/) (ensure it is also placed in any exports, this should be automatic if it is selected as a dependency).

      These files can be retrieved from the `lib/x86` and `lib/x86_64` folders of the SDK. (`x86` being 32-Bit, and `x86_64` being 64-Bit)

      > NOTE: On Linux/OSX you may have to add `lib` to the beginning of these shared library's names.
  
- Install SCons: (If not already installed)
  - Download and install [Python](https://python.org/downloads) (Make sure to add to PATH)
  - Install SCons: `python -m pip install -U scons`
  - (Optional) Reload your terminal to update the path variables.
  
- Compile the library:
  - Windows Example: `scons platform=windows bits=64`
  
- The compiled binaries will be available from [the demo's bin directory](demo/bin/).

  **NOTE**: The output directory for the compiled binaries can be changed by passing the `target_path` parameter in `scons`, e.g `scons platform=windows bits=64 target_path=project/bin`

- These may now be used in a GDNative library in your godot project. See [the demo project](demo/) for an example.

- Ensure that the `.gdns` files are all located in the same folder as the `.gdnlib` folder, otherwise the library will not work.

- All the classes required can be accessed from the `Discord` class as preloaded constants.
