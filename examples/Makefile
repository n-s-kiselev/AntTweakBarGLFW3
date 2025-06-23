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


AR = ar
RANLIB = ranlib

# === Config ===
PROJECTS =  TwSimpleGLUT TwDualGLUT TwString TwSimpleGLFW TwSimpleGLFW3 TwAdvanced1
OUT_DIR = bin64
STATIC_LIB = ../lib/libAntTweakBarGLFW3.a 
STATIC_LIB += -L../external/freeglut/lib

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
        $(GLFW_DIR)/src/platform.c \
        $(GLFW_DIR)/src/wgl_context.c \
        $(GLFW_DIR)/src/win32_init.c \
        $(GLFW_DIR)/src/win32_joystick.c \
        $(GLFW_DIR)/src/win32_monitor.c \
        $(GLFW_DIR)/src/win32_time.c \
        $(GLFW_DIR)/src/win32_thread.c \
        $(GLFW_DIR)/src/win32_module.c \
        $(GLFW_DIR)/src/wgl_context.c \
        $(GLFW_DIR)/src/win32_init.c \
        $(GLFW_DIR)/src/win32_window.c \
        $(GLFW_DIR)/src/egl_context.c \
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
            $(GLFW_DIR)/src/platform.c \
            $(GLFW_DIR)/src/egl_context.c \
            $(GLFW_DIR)/src/glx_context.c \
            $(GLFW_DIR)/src/x11_init.c \
            $(GLFW_DIR)/src/x11_monitor.c \
            $(GLFW_DIR)/src/x11_window.c \
            $(GLFW_DIR)/src/xkb_unicode.c \
            $(GLFW_DIR)/src/posix_time.c \
            $(GLFW_DIR)/src/posix_thread.c \
            $(GLFW_DIR)/src/posix_module.c \
            $(GLFW_DIR)/src/posix_poll.c \
            $(GLFW_DIR)/src/osmesa_context.c \
            $(GLFW_DIR)/src/linux_joystick.c
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
INCLUDE_DIRS = -I../include #AntTweakBar.h
INCLUDE_DIRS += -I$(GLAD_DIR)/include
INCLUDE_DIRS += -I$(GLFW_DIR)/include
INCLUDE_DIRS += -I$(FREEGLUT_DIR)/include

ifeq ($(OS),Windows_NT)
    SHELL := cmd.exe
    .SHELLFLAGS := /C
    EXT = .exe
    CC = gcc
    CPP = g++
    PLATFORM_FLAG = -DOS_WINDOWS -D_GLFW_WIN32 -DTW_STATIC 
    LIBS_COMMON = -lopengl32 -lgdi32 -lwinmm -lpthread
    LIBS_COMMON += -luser32 -lshell32 -lcomdlg32 -ladvapi32 -luuid -lole32 -lsetupapi
    LIBS_COMMON += -lwinspool -lcomctl32 -lgdiplus -lmpr
    CFLAGS += -D_WINDOWS -U__STRICT_ANSI__ -DNTDDI_VERSION=0x05000000
    CFLAGS += -D_WIN32_WINNT=0x0500 -D_WIN32_IE=0x0500
    FREEGLUT_FLAGS = -DFREEGLUT_LIB_PRAGMAS=0
    FREEGLUT_FLAGS += -D_WIN32_WINNT=0x0500 -U_XOPEN_SOURCE
    FREEGLUT_FLAGS += -DFREEGLUT_EXPORTS 
else
    ifeq ($(UNAME_S),Linux)
        EXT =
        CC = gcc
        CPP = g++
        PLATFORM_FLAG = -DOS_LINUX -D_DEFAULT_SOURCE -D_GLFW_X11 
        LIBS_COMMON = -lGL -lGLU -lX11 -lXext -lXmu -lXrandr -lpthread -lm -ldl
    else ifeq ($(UNAME_S),Darwin)
        EXT =
        CC = clang
        CPP = clang++
        PLATFORM_FLAG = -DOS_MACOS -D_DEFAULT_SOURCE -DGL_SILENCE_DEPRECATION -D_GLFW_COCOA
        INCLUDE_DIRS += -I/opt/homebrew/include
        LIBS_COMMON = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    endif
endif

CFLAGS = -Wall -O2 -fPIC -D_DEFAULT_SOURCE $(PLATFORM_FLAG) -I$(SRC_DIR) $(INCLUDE_DIRS)
CFLAGS += -I../external/freeglut/include -DWINVER=0x0500
CPPFLAGS = $(CFLAGS)

# === Build ===

all: $(OUT_DIR) glfw_objects $(addprefix $(OUT_DIR)/,$(addsuffix $(EXT),$(PROJECTS)))

$(OUT_DIR):
	mkdir -p $@

# GLUT
$(FREEGLUT_OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $(FREEGLUT_FLAGS) -I$(FREEGLUT_DIR)/include $< -o $@

$(FREEGLUT_LIB): $(FREEGLUT_OBJS)
	@echo "=== Creating FreeGLUT library ==="
	$(AR) cr $@ $^
	$(RANLIB) $@

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
	$(CPP) $(CFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) -o $@

$(OUT_DIR)/TwSimpleGLFW3$(EXT): TwSimpleGLFW3.c $(GLAD_OBJ) $(GLFW_OBJ)
	@echo "=== Building TwSimpleGLFW3 ==="
	$(CPP) $(CFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) -o $@

$(OUT_DIR)/TwAdvanced1$(EXT): TwAdvanced1.cpp $(GLAD_OBJ) $(GLFW_OBJ)
	@echo "=== Building TwAdvanced1 ==="
	$(CPP) $(CPPFLAGS) $^ $(STATIC_LIB) $(LIBS_COMMON) -o $@

$(OUT_DIR)/TwSimpleGLUT$(EXT): TwSimpleGLUT.c $(GLAD_OBJ)
	@echo "=== Building TwSimpleGLUT ==="
	$(CPP) $(CPPFLAGS) $< $(GLAD_OBJ) -L..\external\freeglut\lib\x64 -lfreeglut $(STATIC_LIB) -o $@ $(LIBS_COMMON)

$(OUT_DIR)/TwDualGLUT$(EXT): TwDualGLUT.c $(GLAD_OBJ)
	@echo "=== Building TwDualGLUT ==="
	$(CPP) $(CPPFLAGS) $< $(GLAD_OBJ) -L..\external\freeglut\lib\x64 -lfreeglut $(STATIC_LIB) -o $@ $(LIBS_COMMON)

$(OUT_DIR)/TwString$(EXT): TwString.cpp $(GLAD_OBJ)
	@echo "=== Building TwString ==="
	$(CPP) $(CPPFLAGS) $< $(GLAD_OBJ) -L..\external\freeglut\lib\x64 -lfreeglut $(STATIC_LIB) -o $@ $(LIBS_COMMON)


# === Clean ===

clean:
	@echo "=== Cleaning ==="
ifeq ($(OS),Windows_NT)
	@-del /F /Q $(subst /,\,$(OUT_DIR)\*$(EXT)) 2>nul
	@-del /F /Q $(subst /,\,$(GLAD_OBJ)) 2>nul
	@-for /r %%f in (*.o) do @del /F /Q "%%f" 2>nul
	@-del /F /Q $(subst /,\,$(FREEGLUT_OBJS)) 2>nul
	@-del /F /Q $(subst /,\,$(FREEGLUT_LIB)) 2>nul
else
	@-rm -f $(OUT_DIR)/*$(EXT)
	@-rm -f $(GLAD_OBJ)
	@-find . -name "*.o" -delete
	@-rm -f $(FREEGLUT_LIB)
endif
	@echo "=== Done ===