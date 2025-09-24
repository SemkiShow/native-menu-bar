function ExampleProject(name)
    project(name)
    kind "WindowedApp"
    location ("build/".._ACTION)
    targetdir ("bin/".. _ACTION.."/"..name.."/%{cfg.buildcfg}")
    language "C++"
    cppdialect "C++98"
    cdialect "c99"
    architecture "x86_64"
    warnings "Default"
    flags "MultiProcessorCompile"
    warnings "Extra"
    -- fatalwarnings "All" -- GTK issues some warnings
    files { "common.h" }
end

function getCommandOutput(command)
    local handle = io.popen(command)
    local result = handle:read("*a")
    handle:close()
    return result
end

local is_mac = _TARGET_OS == "macosx"
local is_windows = _TARGET_OS == "windows"

workspace "examples"

	location ("build/".._ACTION)
    configurations { "Debug", "Release" }

    filter { "configurations:Debug" }
        defines { "CONFIG_DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "CONFIG_RELEASE" }
        optimize "On"

    filter { "files:../*.c", "action:xcode*" }
        compileas "Objective-C" 

    filter {}


if is_windows then

    ExampleProject "example_win32"

        files {
            "example_win32.c",
            "../native_menu_bar.h",
            "../native_menu_bar.c",
        }

elseif is_mac then

    ExampleProject "example_cocoa"

        links {
            "Cocoa.framework"
        }

        files {
            "Info.plist",
            "example_cocoa.m",
            "../native_menu_bar.h",
            "../native_menu_bar.c",
        }

end

ExampleProject "example_gtk2"

    files {
        "example_gtk.c",
        "../native_menu_bar.h",
        "../native_menu_bar.c",
    }

    defines { "NMB_USE_GTK2" }

    if is_mac then files "Info.plist" end

    do
        local cflags = getCommandOutput("pkg-config --cflags gtk+-2.0")
        local libs = getCommandOutput("pkg-config --libs gtk+-2.0")
        buildoptions(cflags)
        linkoptions(libs)
    end

ExampleProject "example_gtk3"

    files {
        "example_gtk.c",
        "../native_menu_bar.h",
        "../native_menu_bar.c",
    }

    defines { "NMB_USE_GTK3" }

    if is_mac then files "Info.plist" end

    do
        local cflags = getCommandOutput("pkg-config --cflags gtk+-3.0")
        local libs = getCommandOutput("pkg-config --libs gtk+-3.0")
        buildoptions(cflags)
        linkoptions(libs)
    end


ExampleProject "example_sdl2"

    files {
        "example_sdl2.c",
        "../native_menu_bar.h",
        "../native_menu_bar.c",
    }

    filter "action:vs*"

        externalincludedirs {
            "lib/sdl2/windows/include"
        }

        libdirs {
            "lib/sdl2/windows/lib/x64",
        }

        links {
            "SDL2",
            "SDL2main",
        }

        postbuildcommands {
            "{COPYFILE} " .. _MAIN_SCRIPT_DIR .. "/lib/sdl2/windows/lib/x64/SDL2.dll %{cfg.buildtarget.directory}",
        }

    filter "action:xcode*"

        links {
            "Cocoa.framework",
            "SDL2"
        }

        libdirs {
            "/opt/homebrew/lib"
        }

        externalincludedirs {
            "/opt/homebrew/include/SDL2"
        }

        files {
            "Info.plist"
        }
