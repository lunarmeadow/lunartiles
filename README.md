# lunartiles

A tilemap-based level editor for the Moonbeam engine.

Designed to be as modular and abstract as possible, to allow relatively simple adaption of any level format.

lunartiles is licensed under GPL-3.0+.

## Building

To create a build folder, use either

`cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DUSE_ASAN=ON`
or
`cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`

To build, run

`cmake --build build -j`

and then run the lunartiles executable in the `build/` folder in the repo's root directory.

## Attributions
[stb](https://github.com/nothings/stb) - public domain single-header libraries
