# Renegate Effect Plug-in

A simple VST 3 plug-in.

## Building the project

Execute the following commands on cli.

```
git clone https://www.github.com/hansen-audio/renegate.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../renegate
cmake --build .
```

> Linux: ```cmake -DCMAKE_BUILD_TYPE=[Debug|Release] ../renegate```

> macOS:```cmake -GXcode ../renegate```

> Windows 10: ```cmake -G"Visual Studio 16 2019" -A x64 ..\renegate```

## License

Copyright 2021 Hansen Audio

Licensed under the GPLv3: http://www.gnu.org/licenses/gpl-3.0.html

VST 3 and the VST 3 logo are trademarks of Steinberg Media Technologies GmbH.
