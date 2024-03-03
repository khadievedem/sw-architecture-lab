ifeq ($(TARGET), 1)
OUT_TARGET_L = lib1F5DF16EE1BF43B999A434ED38FE8F3A.a
OUT_TARGET_C = lib1F5DF16EE1BF43B999A434ED38FFFFFF.a
ifeq ($(DEBUG), 1)
CONFIG_TARGET = StaticDebug
CCFLAGS_TARGET = -Wall -O3 -g -DECO_LIB
LDFLAGS_TARGET =
else
CONFIG_TARGET = StaticRelease
CCFLAGS_TARGET = -O3 -DECO_LIB
LDFLAGS_TARGET =
endif
else
OUT_TARGET_L = 1F5DF16EE1BF43B999A434ED38FE8F3A.so
OUT_TARGET_C = 1F5DF16EE1BF43B999A434ED38FFFFFF.so
ifeq ($(DEBUG), 1)
CONFIG_TARGET = DynamicDebug
CCFLAGS_TARGET = -Wall -O3 -fPIC -g -DECO_DLL
LDFLAGS_TARGET = -shared
else
CONFIG_TARGET = DynamicRelease
CCFLAGS_TARGET = -O3 -fPIC -DECO_DLL
LDFLAGS_TARGET = -shared
endif
endif

# source files.
SRC_L = \
../../../SourceFiles/CEcoLab1.c \
../../../SourceFiles/CEcoLab1Factory.c

SRC_C = \
../../../SourceFiles/CEcoComplex1.c \
../../../SourceFiles/CEcoComplex1Factory.c

# include directories
INCLUDES = \
-I ../../../HeaderFiles \
-I ../../../SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles

OBJ_L = $(SRC_L:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

OUT_L = $(OUT_TARGET_L)
OUT_C = $(OUT_TARGET_C)
OUT_DIR = ../../../BuildFiles/Linux/x64/$(CONFIG_TARGET)

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = $(CCFLAGS_TARGET) -DECO_LINUX -DUGUID_UTILITY

# compiler
GNU =
CC = gcc
AR = gcc-ar

ifeq ($(TARGET), 1)
CMD_TARGET=$(AR) rcs
else
CMD_TARGET=$(CC) -o
endif

# library paths
LIBS =-lc -lm -lgcc

# link flags
LDFLAGS = $(LDFLAGS_TARGET)

.SUFFIXES: .c

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT_L): $(OBJ_C) $(OBJ_L)
	mkdir -p $(OUT_DIR)
	$(CMD_TARGET) $(OUT_DIR)/$(OUT_L) $(OBJ_L) $(LDFLAGS)
	$(CMD_TARGET) $(OUT_DIR)/$(OUT_C) $(OBJ_C) $(LDFLAGS)
	rm $(OBJ_L)
	rm $(OBJ_C)

clean:
	rm $(OBJ) $(OUT_DIR)/$(OUT_L)
	rm $(OBJ) $(OUT_DIR)/$(OUT_C)

