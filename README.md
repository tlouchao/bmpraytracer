# C++ Ray Tracer
Based on ssloy's [Tiny Ray Tracer](https://github.com/ssloy/tinyraytracer/wiki) project.

## Installation & Usage
Write to a BMP file in the `build` directory:

```
git clone https://github.com/tlouchao/bmpraytracer.git
cd bmpraytracer
mkdir build
cd build
cmake ..
make
```

After fetching dependencies with CMake in VS Code, add the `gtest/gtest.h` header file path \
to `c_cpp_properties.json` under the `.vscode` directory, in order for tests to compile (if tests are enabled):
```
"configurations": [
    {
        "includePath": [
            "${workspaceFolder}/**",
            "${workspaceFolder}/build/_deps/googletest-src/googletest/include"
        ],
     ...
    }
```
