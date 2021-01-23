#!/usr/bin/env python
import os
import sys

# Try to detect the host platform automatically.
# This is used if no `platform` argument is passed
if sys.platform.startswith("linux"):
    host_platform = "linux"
elif sys.platform == "darwin":
    host_platform = "osx"
elif sys.platform == "win32" or sys.platform == "msys":
    host_platform = "windows"
else:
    raise ValueError(
        "Could not detect platform automatically, please specify with "
        "platform=<platform>"
    )

env = Environment(ENV=os.environ)

is64 = sys.maxsize > 2**32
if (
    env["TARGET_ARCH"] == "amd64" or
    env["TARGET_ARCH"] == "emt64" or
    env["TARGET_ARCH"] == "x86_64" or
    env["TARGET_ARCH"] == "arm64-v8a"
):
    is64 = True

opts = Variables([], ARGUMENTS)
opts.Add(EnumVariable(
    "platform",
    "Target platform",
    host_platform,
    allowed_values=("linux", "osx", "windows"),
    ignorecase=2
))
opts.Add(EnumVariable(
    "bits",
    "Target platform bits",
    "64" if is64 else "32",
    ("32", "64")
))
opts.Add(BoolVariable(
    "use_llvm",
    "Use the LLVM compiler - only effective when targeting Linux",
    False
))
# Must be the same setting as used for cpp_bindings
opts.Add(EnumVariable(
    "target",
    "Compilation target",
    "debug",
    allowed_values=("debug", "release"),
    ignorecase=2
))
opts.Add(PathVariable(
    "target_path",
    "The path where the lib is installed.",
    "demo/bin/"
))
opts.Add(PathVariable(
    "target_name",
    "The library name.",
    "gdsdk",
    PathVariable.PathAccept
))

# Define the relative path to the Godot headers.
godot_headers_path = "godot_headers/"

opts.Update(env)
Help(opts.GenerateHelpText(env))

env["STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME"] = 1

if host_platform == "windows":
    env.Append(ENV=os.environ)
    if env["bits"] == "64":
        env = Environment(TARGET_ARCH="amd64")
    elif env["bits"] == "32":
        env = Environment(TARGET_ARCH="x86")

    opts.Update(env)

if env["platform"] == "linux":
    env["target_name"] = "lib" + env["target_name"]

    if env["use_llvm"]:
        env["CC"] = "clang"

    if env["target"] in ("debug", "d"):
        env.Append(CCFLAGS=["-fPIC", "-g3", "-Og"])
    else:
        env.Append(CCFLAGS=["-fPIC", "-g", "-O3"])

    if env["bits"] == "64":
        env.Append(CCFLAGS=["-m64"])
        env.Append(LINKFLAGS=["-m64"])

    env.Append(LIBS=["discord_game_sdk"])

# Check our platform specifics
elif env["platform"] == "osx":
    env["target_name"] = "lib" + env["target_name"]

    if env["target"] in ("debug", "d"):
        env.Append(CCFLAGS=["-g", "-O2", "-arch", "x86_64"])
        env.Append(LINKFLAGS=["-arch", "x86_64"])
    else:
        env.Append(CCFLAGS=["-g", "-O3", "-arch", "x86_64"])
        env.Append(LINKFLAGS=["-arch", "x86_64"])

    env.Append(LIBS=["discord_game_sdk"])

elif env["platform"] == "windows":
    env.Append(CCFLAGS=["-DWIN32", "-D_WIN32", "-D_WINDOWS", "-W3", "-GR"])
    if env["target"] in ("debug", "d"):
        env.Append(CCFLAGS=["-EHsc", "-D_DEBUG", "-MDd"])
    else:
        env.Append(CCFLAGS=["-O2", "-EHsc", "-DNDEBUG", "-MD"])

    env.Append(LIBS=[f"discord_game_sdk.{env['bits']}"])

# Make sure our library includes the Godot headers.
env.Append(CPPPATH=[".", godot_headers_path])

# Make sure our library looks in the target path for any other
# libraries it may need. The path needs to be project-relative.
env.Append(LINKFLAGS=["-Wl,-rpath,gdnative/" + env["platform"]])
env.Append(LIBPATH=["lib/"])

# Source Files
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.c")

folder_name = f"{env['platform']}-{env['bits']}/"

library = env.SharedLibrary(target=env["target_path"] + folder_name + env["target_name"], source=sources)
Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))
