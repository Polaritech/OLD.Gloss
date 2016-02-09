# Generic Loader for Operating System Software (GLOSS)
# Makefile

.PHONY: all clean install
all:

MAKEFILE += --no-builtin-rules
.SUFFIXES:

# Build Tools
CC := x86_64-elf-gcc-5.3.0
CXX := x86_64-elf-g++-5.3.0
LD := x86_64-elf-ld-2.26
AS := yasm

# Basic Command Line Tools
RM := rm -rf
MKDIR := mkdir -p
TR := tr
FIND := find

# Build Commands
BUILD.o.c = $(CC) $(CPPFLAGS) $(CFLAGS) -c
BUILD.o.cpp = $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c
BUILD.o.asm = $(AS) $(ASFLAGS)
OUTPUT.file = -o $@

# Redefine VPATH
vpath
vpath %.c Source
vpath %.cpp Source
vpath %.asm Source

# Object Files (Built From Source Files)
OBJ_C := $(addprefix Build/Objects/,$(patsubst %.c,%.o,$(shell find Source -type f -name '*.c' | sed 's/Source\///g')))
OBJ_CXX := $(addprefix Build/Objects/,$(patsubst %.cpp,%.o,$(shell find Source -type f -name '*.cpp' | sed 's/Source\///g')))
OBJ_ASM := $(addprefix Build/Objects/,$(patsubst %.asm,%.o,$(shell find Source -type f -name '*.asm' | sed 's/Source\///g')))
OBJ := $(OBJ_C) $(OBJ_CXX) $(OBJ_ASM)

# Default Rules
Build/Objects/%.o: %.c
	@$(MKDIR) $(@D)
	@$(BUILD.o.c) $(OUTPUT.file) $<
Build/Objects/%.o: %.cpp
	@$(MKDIR) $(@D)
	@$(BUILD.o.cpp) $(OUTPUT.file) $<
Build/Objects/%.o: %.asm
	@$(MKDIR) $(@D)
	@$(BUILD.o.asm) $(OUTPUT.file) $<

# Define Specials
OBJ := $(filter-out Build/Objects/BootISO9660.o, $(OBJ))
Build/Binaries/BootISO9660.bin: Build/Objects/BootISO9660.o
	@$(MKDIR) $(@D)
	@cat $< > $@
#Build/Binaries/Common.bin: Build/Objects/Common.o
#	@$(MKDIR) $(@D)
#	@cat $< > $@
#Build/Binaries/Gloss.sys: $(OBJ))
#	@$(MKDIR) $(@D)
#	@$(CC) $(CPPFLAGS) $(CFLAGS) -T link.ld $(OUTPUT.file) $< $(LDFLAGS)
Build/Image/Boot.iso: Build/Binaries/BootISO9660.bin
	@$(MKDIR) $(@D)
	@$(MKDIR) Build/Structure/ISO/boot
	@cp Build/Binaries/BootISO9660.bin Build/Structure/ISO
	@mv Build/Structure/ISO/BootISO9660.bin Build/Structure/ISO/boot/bootsect.bin
	@xorriso -as mkisofs -R -J -c boot/bootcat.bin -b boot/bootsect.bin -no-emul-boot -boot-load-size 4 $(OUTPUT.file) Build/Structure/ISO

all: Build/Image/Boot.iso
