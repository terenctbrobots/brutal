# brutal
Brutal Game

#Ubuntu system install
sudo apt install libgl1-mesa-dev libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev

- Run vpkg install from root to re-install if any errors occurs
- Close vscode and reopen and should be able to build cleanly after that.

#Running tests
/brutal_test --gtest_filter="Sprite*" will only run Sprite tests