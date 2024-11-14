# Brutal
Brutal is an experimental 2D Game Engine which is being used to explore Game Engine Architecture, technologies and C++ coding techniques.

It is primaryly being developed on *nix platforms.

# Ubuntu system install
sudo apt install libgl1-mesa-dev libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev

- Run vpkg install from root to re-install if any errors occurs
- Close vscode and reopen and should be able to build cleanly after that.

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
