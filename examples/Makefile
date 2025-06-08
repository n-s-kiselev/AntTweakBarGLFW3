# ==============================================================================
# Cross-Platform Makefile for AntTweakBar Examples
# ------------------------------------------------------------------------------
# Supports:
#   - Linux (Debian/Arch)
#   - macOS (Intel & Apple Silicon)
#   - Windows 10/11 (with MinGW)
#
# Windows notes:
#   - Install MinGW (https://github.com/niXman/mingw-builds-binaries/releases)
#   - Add C:\mingw64\bin to PATH
#   - Run: mingw32-make rebuild && .\bin64\TwSimpleGLFW3.exe
#
# Author: Nikolai Kiselev
# Date:   June 6, 2025
# ==============================================================================

.PHONY: all clean rebuild

PROJECTS = TwSimpleGLUT TwDualGLUT TwSimpleGLFW3 TwAdvanced1 TwString
OUT_DIR = bin64
STATIC_LIB = ../lib/libAntTweakBarGLFW3.a
SRC_GLAD = glad/src/glad.c
OBJS_GLAD = glad.o
SRC_DIR = .
INCLUDE_DIRS = -I../include -Iglad/include

# Detect platform
ifeq ($(OS),Windows_NT)
    EXT = .exe
    CC = gcc
    CXX = g++
    PLATFORM_FLAG = -D OS_WINDOWS
    LIBS_COMMON = -lopengl32 -lgdi32 -lwinmm -lpthread
    LIB_GLFW = -lglfw3
    LIB_GLUT = -lglut32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        EXT =
        CC = gcc
        CXX = g++
        PLATFORM_FLAG = -D OS_LINUX
        LIBS_COMMON = -lGL -lGLU -lX11 -lXext -lXmu -lXrandr -lpthread -lm -ldl
        LIB_GLFW = -lglfw
        LIB_GLUT = -lglut
    else ifeq ($(UNAME_S),Darwin)
        EXT =
        CC = clang
        CXX = clang++
        PLATFORM_FLAG = -D OS_MACOS -DGL_SILENCE_DEPRECATION
        INCLUDE_DIRS += -I/opt/homebrew/include
        LIBS_COMMON = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
        LIB_GLFW = -lglfw
        LIB_GLUT = -framework GLUT
    endif
endif

CFLAGS = -Wall -O2 -fPIC -D_DEFAULT_SOURCE $(PLATFORM_FLAG) -I$(SRC_DIR) $(INCLUDE_DIRS)
CXXFLAGS = $(CFLAGS)

# Default build target
all: $(OUT_DIR) $(addprefix $(OUT_DIR)/,$(addsuffix $(EXT),$(PROJECTS)))

$(OUT_DIR):
	mkdir -p $@

# Build GLAD
glad.o: $(SRC_GLAD)
	$(CC) -c $< -o $@ $(CFLAGS)

# --- Build rules for examples ---
$(OUT_DIR)/TwSimpleGLUT$(EXT): TwSimpleGLUT.c glad.o | $(OUT_DIR)
	@echo "=== Building TwSimpleGLUT ==="
	$(CXX) $(CFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) $(LIB_GLUT) -o $@

$(OUT_DIR)/TwDualGLUT$(EXT): TwDualGLUT.c glad.o | $(OUT_DIR)
	@echo "=== Building TwDualGLUT ==="
	$(CXX) $(CFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) $(LIB_GLUT) -o $@

$(OUT_DIR)/TwSimpleGLFW3$(EXT): TwSimpleGLFW3.c glad.o | $(OUT_DIR)
	@echo "=== Building TwSimpleGLFW3 ==="
	$(CXX) $(CFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) $(LIB_GLFW) -o $@

$(OUT_DIR)/TwAdvanced1$(EXT): TwAdvanced1.cpp glad.o | $(OUT_DIR)
	@echo "=== Building TwAdvanced1 ==="
	$(CXX) $(CXXFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) $(LIB_GLFW) -o $@

$(OUT_DIR)/TwString$(EXT): TwString.cpp glad.o | $(OUT_DIR)
	@echo "=== Building TwString ==="
	$(CXX) $(CXXFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) $(LIB_GLUT) -o $@

clean:
	@echo "=== Cleaning ==="
ifeq ($(OS),Windows_NT)
	del /F /Q $(OUT_DIR)\*.exe *.o
else
	rm -f $(OUT_DIR)/*$(EXT) *.o
endif
	@echo "=== Done ==="

rebuild: clean all