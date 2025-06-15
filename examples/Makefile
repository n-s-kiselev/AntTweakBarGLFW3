# ==============================================================================
# Cross-Platform Makefile for AntTweakBar Examples
# ------------------------------------------------------------------------------
# Supports:
#   - Linux (Debian/Arch)
#   - macOS (Intel & Apple Silicon) brew install messa
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

.PHONY: all clean rebuild glfw_objects

# === Config ===
PROJECTS =  TwSimpleGLFW TwSimpleGLFW3 TwAdvanced1 TwSimpleGLUT TwDualGLUT TwString
OUT_DIR = bin64
STATIC_LIB = ../lib/libAntTweakBarGLFW3.a

# GLAD
GLAD_DIR = ../external/glad
GLAD_SRC = $(GLAD_DIR)/src/glad.c
GLAD_OBJ = $(GLAD_DIR)/src/glad.o

# GLFW
GLFW_DIR = ../external/glfw

ifeq ($(OS),Windows_NT)
    GLFW_SRC = \
        $(GLFW_DIR)/src/context.c \
        $(GLFW_DIR)/src/init.c \
        $(GLFW_DIR)/src/input.c \
        $(GLFW_DIR)/src/monitor.c \
        $(GLFW_DIR)/src/vulkan.c \
        $(GLFW_DIR)/src/window.c \
        $(GLFW_DIR)/src/wgl_context.c \
        $(GLFW_DIR)/src/win32_init.c \
        $(GLFW_DIR)/src/win32_joystick.c \
        $(GLFW_DIR)/src/win32_monitor.c \
        $(GLFW_DIR)/src/win32_time.c \
        $(GLFW_DIR)/src/win32_thread.c \
        $(GLFW_DIR)/src/win32_window.c \
        $(GLFW_DIR)/src/osmesa_context.c
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        GLFW_SRC = \
            $(GLFW_DIR)/src/context.c \
            $(GLFW_DIR)/src/init.c \
            $(GLFW_DIR)/src/input.c \
            $(GLFW_DIR)/src/monitor.c \
            $(GLFW_DIR)/src/vulkan.c \
            $(GLFW_DIR)/src/window.c \
            $(GLFW_DIR)/src/x11_init.c \
            $(GLFW_DIR)/src/x11_monitor.c \
            $(GLFW_DIR)/src/x11_window.c \
            $(GLFW_DIR)/src/glx_context.c \
            $(GLFW_DIR)/src/posix_time.c \
            $(GLFW_DIR)/src/posix_thread.c \
            $(GLFW_DIR)/src/posix_module.c \
            $(GLFW_DIR)/src/posix_poll.c \
            $(GLFW_DIR)/src/osmesa_context.c \
            $(GLFW_DIR)/src/xkb_unicode.c
    else ifeq ($(UNAME_S),Darwin)
    GLFW_SRC = \
        $(GLFW_DIR)/src/context.c \
        $(GLFW_DIR)/src/init.c \
        $(GLFW_DIR)/src/input.c \
        $(GLFW_DIR)/src/monitor.c \
        $(GLFW_DIR)/src/vulkan.c \
        $(GLFW_DIR)/src/window.c \
        $(GLFW_DIR)/src/platform.c \
        $(GLFW_DIR)/src/egl_context.c \
        $(GLFW_DIR)/src/nsgl_context.m \
        $(GLFW_DIR)/src/cocoa_init.m \
        $(GLFW_DIR)/src/cocoa_joystick.m \
        $(GLFW_DIR)/src/cocoa_monitor.m \
        $(GLFW_DIR)/src/cocoa_window.m \
        $(GLFW_DIR)/src/cocoa_time.c \
        $(GLFW_DIR)/src/posix_time.c \
        $(GLFW_DIR)/src/posix_thread.c \
        $(GLFW_DIR)/src/posix_module.c \
        $(GLFW_DIR)/src/posix_poll.c \
        $(GLFW_DIR)/src/osmesa_context.c
    endif
endif

GLFW_OBJ = $(GLFW_SRC:.c=.o)
GLFW_OBJ := $(GLFW_OBJ:.m=.o)

SRC_DIR = .
INCLUDE_DIRS = -I../include -I$(GLAD_DIR)/include -I$(GLFW_DIR)/include

ifeq ($(OS),Windows_NT)
    EXT = .exe
    CC = gcc
    CXX = g++
    PLATFORM_FLAG = -D OS_WINDOWS
    LIBS_COMMON = -lopengl32 -lgdi32 -lwinmm -lpthread
    LIB_GLUT = -lglut32
else
    ifeq ($(UNAME_S),Linux)
        EXT =
        CC = gcc
        CXX = g++
        PLATFORM_FLAG = -D OS_LINUX
        LIBS_COMMON = -lGL -lGLU -lX11 -lXext -lXmu -lXrandr -lpthread -lm -ldl
        LIB_GLUT = -lglut
    else ifeq ($(UNAME_S),Darwin)
        EXT =
        CC = clang
        CXX = clang++
        PLATFORM_FLAG = -D OS_MACOS -DGL_SILENCE_DEPRECATION -D_GLFW_COCOA
        INCLUDE_DIRS += -I/opt/homebrew/include
        LIBS_COMMON = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
        LIB_GLUT = -lfreeglut
    endif
endif

CFLAGS = -Wall -O2 -fPIC -D_DEFAULT_SOURCE $(PLATFORM_FLAG) -I$(SRC_DIR) $(INCLUDE_DIRS)
CXXFLAGS = $(CFLAGS)

# === Build ===

all: $(OUT_DIR) glfw_objects $(addprefix $(OUT_DIR)/,$(addsuffix $(EXT),$(PROJECTS)))

$(OUT_DIR):
	mkdir -p $@

# GLAD
$(GLAD_OBJ): $(GLAD_SRC)
	$(CC) -c $< -o $@ $(CFLAGS)

# GLFW: .c
%.o: %.c
	$(CC) -c $(CFLAGS) -I../external/glfw/include $< -o $@

# GLFW: .m (macOS only)
%.o: %.m
	$(CC) -ObjC -c $(CFLAGS) -I../external/glfw/include $< -o $@

glfw_objects: $(GLFW_OBJ)
	@echo "GLFW object files built."

# === Per-example build ===

$(OUT_DIR)/TwSimpleGLFW$(EXT): TwSimpleGLFW.c $(GLAD_OBJ) $(GLFW_OBJ)
	@echo "=== Building TwSimpleGLFW ==="
	$(CXX) $(CFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) -o $@

$(OUT_DIR)/TwSimpleGLFW3$(EXT): TwSimpleGLFW3.c $(GLAD_OBJ) $(GLFW_OBJ)
	@echo "=== Building TwSimpleGLFW3 ==="
	$(CXX) $(CFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) -o $@

$(OUT_DIR)/TwAdvanced1$(EXT): TwAdvanced1.cpp $(GLAD_OBJ) $(GLFW_OBJ)
	@echo "=== Building TwAdvanced1 ==="
	$(CXX) $(CXXFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) -o $@

# === Clean ===

clean:
	@echo "=== Cleaning ==="
ifeq ($(OS),Windows_NT)
	del /F /Q $(OUT_DIR)\*.exe *.o 2>nul
	del /F /Q $(subst /,\,$(GLAD_OBJ)) 2>nul
	for %%f in ($(subst /,\,$(GLFW_OBJ))) do @del /F /Q %%f 2>nul
else
	rm -f $(OUT_DIR)/*$(EXT) *.o $(GLFW_OBJ)
endif
	@echo "=== Done ==="