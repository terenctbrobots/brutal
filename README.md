# Brutal
Brutal is an experimental 2D Game Engine which is being used to explore Game Engine Architecture, technologies and C++ coding techniques.

It is primaryly being developed on *nix platforms.

The planned features are:
- Animated sprites with different animations
- Tilemaps
- Multiple draw layers
- In-game editor (You can toggle the editor on/off), support for hot-reloading
- JSON used for all game data
- LUA Scripting
- Entity Component System

# Ubuntu system install
...
sudo apt install libgl1-mesa-dev libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev
sudo apt install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config
...

- Run vpkg install from root to re-install if any errors occurs
- Close vscode and reopen and should be able to build cleanly after that.

# Window build
Still working on converting the code.

# Running tests
/brutal_test --gtest_filter="*Sprite*" will only run Sprite tests

# Packages used
- VCPKG
- Google Unit Test
- RayLib and RayLib GUI
- nlohmann JSON library
- EnTT
- doxygen for documentation when I get round to it
- CMake and ninja
- CLang 18 
