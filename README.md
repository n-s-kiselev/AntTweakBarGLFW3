# AntTweakBar (GLFW3)

[AntTweakBar](https://anttweakbar.sourceforge.io/doc) (**ATB**) is a small and
easy-to-use C/C++ library developed by
[Philippe Decaudin](https://phildec.users.sourceforge.net/) that adds a
lightweight, intuitive GUI to OpenGL-based graphics programs for real-time
parameter tweaking.

This fork focuses on **GLFW3 and the OpenGL Core Profile**
(`TW_OPENGL_CORE`), built with a single cross-platform
[`nob.c`](https://github.com/tsoding/nob.h) build script instead of the
original per-platform Makefiles/Visual Studio projects. For the legacy
GLFW2/FreeGLUT/OpenGL-compatibility-profile line of this library instead, see
the sibling repository
[n-s-kiselev/AntTweakBar-Legacy](https://github.com/n-s-kiselev/AntTweakBar-Legacy).


## Building

Bootstrap the build tool once, from the repository root:

```sh
gcc nob.c -o nob
```

Then:

```sh
./nob            # build the library (lib/libAntTweakBarGLFW3.{a,so/dylib/dll})
./nob -clean     # remove all generated build output
./nob -examples  # build the example programs (requires ./nob to have run first)
./nob -help      # list all flags
```

`./nob` produces:

- `lib/libAntTweakBarGLFW3.a` — static library
- `lib/libAntTweakBarGLFW3.so` (Linux) / `lib/libAntTweakBarGLFW3.dylib`
  (macOS) / `lib/libAntTweakBarGLFW3.dll` + `.dll.a` (Windows/MinGW) —
  dynamic library

`./nob -examples` compiles the only four examples this fork keeps, adapted to
GLFW3+[GLAD](https://glad.dav1d.de/)+Core Profile
(`TwSimpleGLFW21.c`, `TwSimpleGLFW33.c`, `TwSimpleGLFW34.c`, `TwAdvanced1.cpp`)
statically against `lib/libAntTweakBarGLFW3.a` into `build/examples/`, and
fails with a clear message if the library hasn't been built yet.

GLFW3 ([external/glfw](external/glfw), unity build via
[`glfw_unity.c`](external/glfw/glfw_unity.c)) and
[GLAD](https://glad.dav1d.de/) ([external/glad](external/glad)) are vendored
and built from source; no system GLFW3 install is needed. The GLUT-based
examples (`TwSimpleGLUT.c`, `TwDualGLUT.c`, `TwString.cpp`), the SDL/SFML
examples, and the untouched legacy DirectX9/10/11 examples have been removed
from `examples/` — `external/freeglut` has no buildable source for
Linux/macOS (headers and prebuilt Windows DLLs only), and DirectX/SDL/SFML
are out of scope for this GLFW3/Core-Profile-focused fork. See
[`docs/plans/nob-build-system.md`](docs/plans/nob-build-system.md) for
details.

Supported platforms: Linux, macOS, and Windows (MinGW). Only macOS has been
build-verified directly; Linux/Windows compile flags are carried over from
this repository's own former `src/Makefile`/`examples/Makefile` (since
removed - see below).

`nob.c` is the only build system for this fork. The legacy `src/Makefile`,
`examples/Makefile`, and MSVC `.vcproj`/`.vcxproj`/`.sln`/`.vcxproj.filters`
files have been removed, along with the Direct3D9/10/11 renderer backend and
the native-Win32 `TwEventWin` event helper (dead code only those legacy
projects still compiled - never built by `nob.c`, and gated behind a
`TW_USE_DIRECT3D` macro that was never defined anywhere in this repo).

## License

See [`License.txt`](License.txt).
