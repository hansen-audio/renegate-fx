# ReneGate Effect Plug-in

[![CMake (Linux, macOS, Windows)](https://github.com/hansen-audio/renegate-fx/actions/workflows/cmake.yml/badge.svg)](https://github.com/hansen-audio/renegate-fx/actions/workflows/cmake.yml)

## Summary

A simple VST 3 trance gate plug-in.

## Building the project

Execute the following commands on cli.

```
git clone https://www.github.com/hansen-audio/renegate-fx.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../renegate-fx
cmake --build .
```

> Linux: ```cmake -DCMAKE_BUILD_TYPE=[Debug|Release] ../renegate-fx```

> macOS:```cmake -GXcode ../renegate-fx```

> Windows 10: ```cmake -G"Visual Studio 16 2019" -A x64 ..\renegate-fx```

## License

Copyright 2021 Hansen Audio

VST 3 and the VST 3 logo are trademarks of Steinberg Media Technologies GmbH.
