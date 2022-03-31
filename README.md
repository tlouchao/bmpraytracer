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

In VS Code, add the following value to `.vscode -> c_cpp_properties.json -> configurations -> includePath`,
in order for VS Code to recognize `gtest/gtest.h` as a header file (if tests are enabled):
```
 "${workspaceFolder}/build/_deps/googletest-src/googletest/include"
```