# Examples for AntTweakBar
# On Linux you may need to install libxmu-dev libglfw3-dev libsdl2-2.0-0 libsdl2-dev

#---- Release
CPPCFG    = -O3
LFLAGS    = -L../lib
OUT_DIR   = bin64

CPP       = g++
CC        = gcc
CPPFLAGS  = $(CPPCFG) -Wall -fPIC -fno-strict-aliasing
CFLAGS    = $(CPPCFG) -Wall -fPIC -fno-strict-aliasing
INCPATH   = -I../include -I/usr/local/include -I/usr/X11R6/include -I/usr/include -Iglad/include

STATIC_LIB = ../lib/libAntTweakBarGLFW3.a 
LIBS      = -L/usr/X11R6/lib -lGL -lGLU -lX11 -lXext -lXmu -lXrandr -lpthread -lm

DEL_FILE  = rm -f
DEL_DIR   = rm -rf

####### Files

SRC_FILES = TwSimpleGLFW3.c TwSimpleGLUT.c TwSimpleSDL.c TwAdvanced1.cpp TwString.cpp TwDualGLUT.c

####### Build rules

.PHONY: all clean

all: $(OUT_DIR)/TwSimpleGLUT $(OUT_DIR)/TwDualGLUT $(OUT_DIR)/TwSimpleGLFW3 
# $(OUT_DIR)/TwSimpleSDL

# Ensure output directory exists
$(OUT_DIR):
	mkdir -p $@

# GLAD compilation rule
glad.o: glad/src/glad.c
	$(CPP) -c $(CFLAGS) $(INCPATH) $< -o $@

# Build rules for each example
$(OUT_DIR)/TwSimpleGLUT: TwSimpleGLUT.c glad.o | $(OUT_DIR)
	@echo "===== Build TwSimpleGLUT ====="
	$(CPP) $(CFLAGS) $(INCPATH) $^ $(STATIC_LIB) $(LFLAGS) $(LIBS) -lglut -o $@

$(OUT_DIR)/TwDualGLUT: TwDualGLUT.c glad.o | $(OUT_DIR)
	@echo "===== Build TwDualGLUT ====="
	$(CPP) $(CFLAGS) $(INCPATH) $^ $(STATIC_LIB) $(LFLAGS) $(LIBS) -lglut -o $@

$(OUT_DIR)/TwSimpleGLFW3: TwSimpleGLFW3.c glad.o | $(OUT_DIR)
	@echo "===== Build TwSimpleGLFW3 ====="
	$(CPP) $(CFLAGS) $(INCPATH) $^ $(STATIC_LIB) $(LFLAGS) $(LIBS) -lglfw -o $@

# $(OUT_DIR)/TwSimpleSDL: TwSimpleSDL.c glad.o | $(OUT_DIR)
# 	@echo "===== Build TwSimpleSDL ====="
# 	$(CPP) $(CFLAGS) $(INCPATH) $^ $(STATIC_LIB) $(LFLAGS) $(LIBS) `sdl2-config --cflags --libs` -o $@

clean:
	@echo "===== Clean ====="
	-$(DEL_FILE) *.o
	-$(DEL_FILE) *~ core *.core *.stackdump
	-$(DEL_FILE) $(OUT_DIR)/*
	-$(DEL_DIR) $(OUT_DIR) 2>/dev/null || true
	@echo "Clean completed"



# @echo "===== Build TwAdvanced1 ===="
# $(CXX) $(CXXFLAGS) $(INCPATH) TwAdvanced1.cpp $(LFLAGS) -lglfw $(LIBS) -o $(OUT_DIR)/TwAdvanced1.out
# @echo $(EXP_SH) > $(OUT_DIR)/TwAdvanced1
# @echo $(EXP_PATH) >> $(OUT_DIR)/TwAdvanced1
# @chmod +x $(OUT_DIR)/TwAdvanced1
# @echo "To execute the example, run " $(OUT_DIR)/TwAdvanced1

# @echo "===== Build TwString ===="
# $(CXX) $(CXXFLAGS) $(INCPATH) TwString.cpp $(LFLAGS) -lglut $(LIBS) -o $(OUT_DIR)/TwString.out
# @echo $(EXP_SH) > $(OUT_DIR)/TwString
# @echo $(EXP_PATH) >> $(OUT_DIR)/TwString
# @chmod +x $(OUT_DIR)/TwString
# @echo "To execute the example, run " $(OUT_DIR)/TwString

# append dependencies to this Makefile
#depend:
#	@echo "===== Make dependencies ====="
#	makedepend -Y
#	makedepend -a -Y -- $(CXXFLAGS) $(INCPATH) -- $(SRC_FILES) $(NO_STDERR)


