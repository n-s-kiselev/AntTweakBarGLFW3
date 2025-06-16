# Cross-platform Makefile for AntTweakBarGLFW3
# On Linux one may need to install the following packages:
# sudo apt install libglfw3-dev \
# libgl1-mesa-dev \
# libgl1-mesa-glx \
# libx11-dev \ 
# freeglut3-dev \
# libxxf86vm-dev\
# libxmu-dev

# OS detection
ifeq ($(OS),Windows_NT)
    SHELL := cmd.exe
    .SHELLFLAGS := /C
    SO_EXT     = .dll
    CPPFLAGS  += -Wall -O2 -D_WIN32 -Wno-cast-function-type -Wno-invalid-offsetof -Wno-int-to-pointer-cast -fpermissive
    CXXFLAGS  += -Wall -O2 -D_WIN32
    LFLAGS     = -shared
    LIBS      += -lopengl32 -lgdi32 -luser32 -lkernel32 -lm -ldinput8 -ldxguid
    OUT_DIR    = ../lib
    CLEAN_OUT_DIR := $(subst /,\,$(OUT_DIR))
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
        SO_EXT     = .so
        SO_VERSION = 1
        CPPFLAGS  += -D_UNIX
        CXXFLAGS  += -D_UNIX
        LFLAGS     = -shared -Wl,-soname,lib$(TARGET)$(SO_EXT).$(SO_VERSION)
        LIBS      += -lGL -lX11 -lXxf86vm -lXext -lpthread -lm 
        OUT_DIR    = ../lib
	else ifeq ($(UNAME_S),Darwin)
        SO_EXT     = .dylib
        CPPFLAGS  += -D_MACOSX -ObjC++
        CXXFLAGS  += -D_MACOSX
        LFLAGS     = -dynamiclib -Wl,-undefined -Wl,dynamic_lookup
        LIBS      += -framework OpenGL -framework AppKit
        OUT_DIR    = ../lib
	endif
endif

# Toolchain
CPP       = g++
CC        = gcc
AR        = ar cqs
COPY      = cp -f
SYMLINK   = ln -sf

# Build configuration
CPPCFG    = -O3 -fno-strict-aliasing -Wall -fPIC
CPPFLAGS += $(CPPCFG) -D__PLACEMENT_NEW_INLINE
CCFLAGS  += $(CPPCFG)
INCPATH   = -I../include -I../external/glad/include -I/usr/local/include -I/usr/X11R6/include -I/usr/include

TARGET    = AntTweakBarGLFW3
SRC_COMMON = ../external/glad/src/glad.c TwColors.cpp TwFonts.cpp TwOpenGL.cpp TwOpenGLCore.cpp TwBar.cpp TwMgr.cpp \
             LoadOGL.cpp LoadOGLCore.cpp TwEventGLFW.c TwEventGLUT.c TwEventSDL.c \
             TwEventSDL12.c TwEventSDL13.c TwEventSFML.cpp

ifeq ($(OS),Windows_NT)
    SRC_FILES = $(SRC_COMMON)
else
    SRC_FILES = $(SRC_COMMON) TwEventX11.c
endif

# OBJS_1    = $(SRC_FILES:.c=.o)
# OBJS      = $(OBJS_1:.cpp=.o)
OBJS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRC_FILES)))



ifeq ($(OS),Windows_NT)
	MKDIR = if not exist "$(subst /,\,$(OUT_DIR))" mkdir "$(subst /,\,$(OUT_DIR))"
else
	MKDIR = mkdir -p $(OUT_DIR)
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(MKDIR)
	@echo "===== Linking $@ ====="
	$(CPP) $(LFLAGS) -o $(OUT_DIR)/lib$(TARGET)$(SO_EXT) $(OBJS) $(LIBS)
ifeq ($(UNAME_S),Linux)
	$(SYMLINK) lib$(TARGET)$(SO_EXT) $(OUT_DIR)/lib$(TARGET)$(SO_EXT).$(SO_VERSION)
endif
	$(AR) $(OUT_DIR)/lib$(TARGET).a $(OBJS)

glad.o: ../external/glad/src/glad.o
	$(CC) -c $(CCFLAGS) $(INCPATH) -o $@ $<

.cpp.o:
	@echo "===== Compiling $< ====="
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o $@ $<

.c.o:
	@echo "===== Compiling $< ====="
	$(CC) -c $(CCFLAGS) $(INCPATH) -o $@ $<

clean:
	@echo "===== Clean ====="
ifeq ($(OS),Windows_NT)
	del /F /Q *.o *~ core *.core *.stackdump $(CLEAN_OUT_DIR)\*.dll 2>nul || ver >nul
else
	rm -f *.o *~ core *.core *.stackdump
	find $(OUT_DIR) -name '*.a' -delete
	find $(OUT_DIR) -name '*.so*' -delete
	find $(OUT_DIR) -name '*.dylib' -delete
endif
	@echo "===== Cleaning done ====="

.PHONY: all clean