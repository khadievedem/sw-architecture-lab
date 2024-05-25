ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = /
	SWALLOW_OUTPUT =
endif 

# source files.
INC = \
-I ../../../HeaderFiles \
-I ../../../SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles

# source files.
SRC = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoMutex1Lab.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoMutex1LabFactory.c
 
OBJ = $(SRC:.c=.o)

OUT = lib2F48BBCBE4884CC08ECFC45990017215.a
OUT_DIR = ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)STM32$(SLASH)arm-gcc$(SLASH)StaticRelease

LD_SCRIPT = ./STM32F427VITX_FLASH.ld

# C++ compiler flags (-g -O3 -Wall)
CCFLAGS = -T $(LD_SCRIPT) -Wall -O3 -Wno-missing-braces -mthumb -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mfloat-abi=hard -msoft-float -mfpu=vfp -specs=nosys.specs -DECO_LIB -DECO_STM32 -DUGUID_UTILITY

CCC = arm-none-eabi-gcc
AR  = arm-none-eabi-ar

# library paths
LIBS = -lc -lm -lgcc
 
# compile flags
LDFLAGS = -g
 
.SUFFIXES: .c

all: $(OUT)

.c.o:
	$(CCC) $(INC) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	mkdir -p $(OUT_DIR)
	$(AR) rcs $(OUT_DIR)$(SLASH)$(OUT) $(OBJ)

clean:
	$(RM) $(OUT_DIR)/$(OUT)

