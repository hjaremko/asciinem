# Asciinem - dynamic terminal MMO RPG ![Build](https://github.com/hjaremko/asciinem/workflows/Build/badge.svg)

![Gameplay](https://i.imgur.com/XIWlsVC.png)

[comment]: <> (### Downloading)

[comment]: <> (Builds for Windows, Linux and macOS are available [here]&#40;https://github.com/hjaremko/asciinem/releases&#41;.)

### Controls
- `WSAD` - moving around

- `F` - fight around monsters

- `0..9` - using items from backpack with corresponding ids (equip, consume or drop)

- `q` - quit

### Building

#### Installing Conan *(required)*
```
$ pip install conan
```

#### Building project
```
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --config Release
```

#### Additional CMake options
 - `ENABLE_CLANG_TIDY` (requires `clang-tidy`)
 - `ENABLE_CPPCHECK` (requires `cppcheck`)
 - `ENABLE_SANITIZER_ADDRESS`
 - `ENABLE_SANITIZER_LEAK`
 - `ENABLE_SANITIZER_UNDEFINED_BEHAVIOR`
 - `ENABLE_SANITIZER_THREAD`
 - `ENABLE_SANITIZER_MEMORY`

##### Example, enabled clang-tidy and cppcheck
```
$ mkdir build && cd build
$ cmake .. -DENABLE_CLANG_TIDY=1 -DENABLE_CPPCHECK=1
$ cmake --build . --config Release
```

#### Troubleshooting
If you are having similar error:
```
Error opening terminal: xterm-256color.
```
Type these command in the terminal where you want to run the game:
```
export TERMINFO=/usr/share/terminfo
export TERM=xterm-basic
```

