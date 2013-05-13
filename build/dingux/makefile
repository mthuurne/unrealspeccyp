FLAVOR = release
#FLAVOR = debug

#DEVICE = a320
DEVICE = gcw0

$(info Building for $(DEVICE) in $(FLAVOR) mode...)

SRC_PATH = ../..
OBJ_BASE = $(DEVICE)-$(FLAVOR)

PROJECT_NAME = unreal_speccy_portable
SRCFOLDERS = . z80 tools tools/zlib tools/libpng tools/tinyxml snapshot ui platform platform/custom_ui platform/linux platform/sdl devices devices/fdd devices/input devices/sound
CXXSRCS = $(foreach dir, $(SRCFOLDERS), $(wildcard $(SRC_PATH)/$(dir)/*.cpp))
CSRCS = $(foreach dir, $(SRCFOLDERS), $(wildcard $(SRC_PATH)/$(dir)/*.c))

CXX = mipsel-$(DEVICE)-linux-uclibc-g++
C = mipsel-$(DEVICE)-linux-uclibc-gcc
SYSROOT = /opt/$(DEVICE)-toolchain/usr/mipsel-$(DEVICE)-linux-uclibc/sysroot/

DIST_PATH = $(OBJ_BASE)
OBJ_PATH = $(OBJ_BASE)
CXX_OBJS = $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(CXXSRCS))
CXX_DEPS = $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.d,$(CXXSRCS))
C_OBJS = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(CSRCS))
C_DEPS = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.d,$(CSRCS))
BIN_TARGET = $(DIST_PATH)/$(PROJECT_NAME)

STD_OPTS  = -G0 -Wall -c -fmessage-length=0 -fno-builtin -fno-exceptions -fno-pic
ifeq ($(FLAVOR),debug)
STD_OPTS += -g -O0 -DDEBUG
else
STD_OPTS += -O3 -fomit-frame-pointer -DNDEBUG
endif
CXXFLAGS  = $(STD_OPTS) -fno-rtti -fno-threadsafe-statics -D_LINUX -DUSE_SDL -DSDL_KEYS_DINGOO `$(SYSROOT)/usr/bin/sdl-config --cflags`
CFLAGS    = $(STD_OPTS)
LFLAGS    = -s `$(SYSROOT)/usr/bin/sdl-config --libs`

all: build

mkdirs:
	mkdir -p $(DIST_PATH)
	mkdir -p $(foreach dir, $(SRCFOLDERS), $(OBJ_PATH)/$(dir))
	
$(CXX_OBJS): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(C_OBJS): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(C) $(CFLAGS) -o $@ $<

$(BIN_TARGET): $(CXX_OBJS) $(C_OBJS)
	$(CXX) $(LFLAGS) $^ -o$(BIN_TARGET)

build: mkdirs $(BIN_TARGET)

clean:
	rm -rf $(CXX_OBJS)
	rm -rf $(CXX_DEPS)
	rm -rf $(C_OBJS)
	rm -rf $(C_DEPS)
	rm -rf $(BIN_TARGET)

.PHONY: mkdirs clean build all
