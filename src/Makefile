# Cross-platform Makefile for AntTweakBarGLFW3

# Detect platform
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
    CPPFLAGS  += -D_MACOSX -arch x86_64 -ObjC++
    CXXFLAGS  += -D_MACOSX -arch x86_64
    LFLAGS     = -dynamiclib -Wl,-undefined -Wl,dynamic_lookup
    LIBS      += -framework OpenGL -framework GLUT -framework AppKit
    OUT_DIR    = ../lib
endif

# Toolchain
CPP       = g++
CC        = gcc
AR        = ar cqs
COPY      = cp -f
DEL_FILE  = rm -f
SYMLINK   = ln -sf

# Build configuration
CPPCFG    = -O3 -fno-strict-aliasing -Wall -fPIC
CPPFLAGS += $(CPPCFG) -D__PLACEMENT_NEW_INLINE
CCFLAGS  += $(CPPCFG)
INCPATH   = -I../include -Iglad/include -I/usr/local/include -I/usr/X11R6/include -I/usr/include

TARGET    = AntTweakBarGLFW3
SRC_FILES = TwColors.cpp TwFonts.cpp TwOpenGL.cpp TwOpenGLCore.cpp TwBar.cpp TwMgr.cpp \
            LoadOGL.cpp LoadOGLCore.cpp TwEventGLFW.c TwEventGLUT.c TwEventSDL.c \
            TwEventSDL12.c TwEventSDL13.c TwEventSFML.cpp TwEventX11.c

OBJS_1    = $(SRC_FILES:.c=.o)
OBJS      = $(OBJS_1:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "===== Linking $@ ====="
	$(CPP) $(LFLAGS) -o $(OUT_DIR)/lib$(TARGET)$(SO_EXT) $(OBJS) $(LIBS)
ifeq ($(UNAME_S),Linux)
	$(SYMLINK) lib$(TARGET)$(SO_EXT) $(OUT_DIR)/lib$(TARGET)$(SO_EXT).$(SO_VERSION)
endif
	$(AR) $(OUT_DIR)/lib$(TARGET).a $(OBJS)

.cpp.o:
	@echo "===== Compiling $< ====="
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o $@ $<

.c.o:
	@echo "===== Compiling $< ====="
	$(CC) -c $(CCFLAGS) $(INCPATH) -o $@ $<

clean:
	@echo "===== Cleaning up ====="
	-$(DEL_FILE) *.o *~ core *.core *.stackdump
	-find . -name '*.o' -delete
	-find $(OUT_DIR) -name '*.a' -delete
	-find $(OUT_DIR) -name '*.so*' -delete
	-find $(OUT_DIR) -name '*.dylib' -delete

.PHONY: all clean