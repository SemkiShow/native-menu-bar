# Native Menu Bar

[![Mac Build](https://github.com/thomashope/native-menu-bar/actions/workflows/mac-build.yml/badge.svg)](https://github.com/thomashope/native-menu-bar/actions/workflows/mac-build.yml) [![Windows Build](https://github.com/thomashope/native-menu-bar/actions/workflows/windows-build.yaml/badge.svg)](https://github.com/thomashope/native-menu-bar/actions/workflows/windows-build.yaml)

![mac screenshot](./screenshots/mac.png) ![windows screenshot](./screenshots/windows.png)

Native Menu Bar is a C API for adding menus to your application using native UI on Windows and Mac, and using GTK2 or GTK3 backends on supported platforms e.g. Linux.

Library setup is slightly different depending on the backend implementation and will probbaly require some `#ifdef`s in your code. See the examples for more info.

User interaction is forwarded to your application as events which can be responded to using the same code on all platforms.

Features:

* Menu bar with menus and submenus
* Regular menu items
* Checkmark menu items
* Enable and disable (grey out) menu items
* Keyboard mnemonics supported platforms (Win32 and GTK)
* Only 2 files for easy integration, .h and .c
* Compiles cleanly on MSVC and clang

Please note that this library is not thread safe on any platform. You should not attempt to call any API functions from different threads at the same time.

## Notes

The API provides different functions for checkable menu items `nmb_insertCheckMenuItem` and regular menu items `nmb_insertMenuItem`. This distinction is required by GTK backends which renders the two differently, but not WIN32 or Cocoa. If you don't care about GTK you can use regular menu items everywhere and set/check their checked state with `nmb_set/isMenuItemChecked`.

Keyboard mnemonics allow users to jump to specific menu items by pressing a corresponding key on their keyboard. To use mnemonics place an underscore `_` character before the letter in the caption you would like to become the mnemonic. Mnemonics are available on Win32 and GTK backends. Cocoa does require manually specified mnemonics since users can start typing any caption name to jump to it automatically.

Currently the library supports both GTK2 and GTK3. At the time of writing GTK2 and 3 on MacOS have strange behaviour around window resizing and respond to mouse input inconsistently. The GTK2 backend also issues deprecation warnings when compiling.

## Building

In general you can use this library by simply adding `native_menu_bar.h` and `native_menu_bar.c` to your project.

On mac `native_menu_bar.c` should be compiled as Objective-C. You can do this by either changing the extension from `.c` to `.m`, or explicitly set it to compile as Objective-C within XCode.

Additionally on mac, Automatic Reference Counting (ARC) should be disabled for `native_menu_bar.c`. If you have ARC enabled for you project you can disable it for individual files by adding the flag `-fno-objc-arc` in _project name_ > Targets > _project name_ > Build Phases > Compile Sources.


## Building Examples

On Mac:

```sh
brew install sdl2 gtk+ gtk+3
cd examples
./premake xcode4
open ./build/xcode4/examples.xcworkspace
```

Then select and run the example projects from within Xcode.

On Windows:

Run the following commands in Git Bash (or some other bash for windows prompt).

```sh
cd examples
./premake vs2022
start ./build/vs2022/examples.sln
```

## Contributing

Contributions are welcome. See [TODO](TODO.md) for things to work on and notes about current progress.
