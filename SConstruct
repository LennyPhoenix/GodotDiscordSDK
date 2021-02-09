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

if host_platform == "windows":
    env.Append(ENV=os.environ)
    if env["bits"] == "64":
        env = Environment(TARGET_ARCH="amd64")
    elif env["bits"] == "32":
        env = Environment(TARGET_ARCH="x86")

    opts.Update(env)

if env["platform"] == "linux":
    env["target_name"] = "lib" + env["target_name"]

    if env['target'] == 'debug':
        env.Append(CCFLAGS=['-fPIC', '-g3', '-Og'])
        env.Append(CXXFLAGS=['-std=c++17'])
    else:
        env.Append(CCFLAGS=['-fPIC', '-O3'])
        env.Append(CXXFLAGS=['-std=c++17'])
        env.Append(LINKFLAGS=['-s'])

    env.Append(LIBS=["discord_game_sdk"])

# Check our platform specifics
elif env["platform"] == "osx":
    env["target_name"] = "lib" + env["target_name"]

    if env['target'] == 'debug':
        env.Append(CCFLAGS=['-g', '-O2', '-arch', 'x86_64'])
        env.Append(LINKFLAGS=['-arch', 'x86_64'])
    else:
        env.Append(CCFLAGS=['-g', '-O3', '-arch', 'x86_64'])
        env.Append(LINKFLAGS=['-arch', 'x86_64'])

    env.Append(LIBS=["discord_game_sdk"])

elif env["platform"] == "windows":
    env.Append(CPPDEFINES=['WIN32', '_WIN32', '_WINDOWS', '_CRT_SECURE_NO_WARNINGS'])
    env.Append(CCFLAGS=['-W3', '-GR'])
    if env['target'] == 'debug':
        env.Append(CPPDEFINES=['_DEBUG'])
        env.Append(CCFLAGS=['-EHsc', '-MDd', '-ZI'])
        env.Append(LINKFLAGS=['-DEBUG'])
    else:
        env.Append(CPPDEFINES=['NDEBUG'])
        env.Append(CCFLAGS=['-O2', '-EHsc', '-MD'])

    env.Append(LIBS=[f"discord_game_sdk.{env['bits']}"])

# Make sure our library includes the Godot headers.
env.Append(CPPPATH=[".", godot_headers_path])

env.Append(LIBPATH=["lib/"])

# Source Files
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.c")

folder_name = f"{env['platform']}-{env['bits']}/"

library = env.SharedLibrary(target=env["target_path"] + folder_name + env["target_name"], source=sources)
Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))
