PROGNAME = kernel

VERSION_REL = 0
VERSION_MAJ = 8
VERSION_MIN = 0
VERSION_FIX = 0

CC = cl65
AS = ca65
LD = ld65

INCS = -I ./cc65/include -I /usr/share/cc65/include
LIBS = 

LDS = ./cc65/rpc8.cfg
CFLAGS = $(LIBS) $(INCS) --cpu 65c02 -t none -O -g --standard cc65 -DVERSION_REL=$(VERSION_REL) -DVERSION_MAJ=$(VERSION_MAJ) -DVERSION_MIN=$(VERSION_MIN) -DVERSION_FIX=$(VERSION_FIX)
ASFLAGS = --cpu 65816 -g -t none
LDFLAGS = -C $(LDS)

SRCDIR := src
OBJDIR := lib
BUILDDIR := bin

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.c)
SSRC = $(call rwildcard,$(SRCDIR),*.s)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.s, $(OBJDIR)/%.o, $(SSRC))
DIRS = $(wildcard $(SRCDIR)/*)

.PHONY: build
build: setup link

.PHONY: link
link: $(OBJS) cc65
	@ echo !==== LINKING $^
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/$(PROGNAME) -m $(BUILDDIR)/$(PROGNAME).map $(OBJS) ./cc65/rpos-kernel.lib

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $^
	@

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	@ echo !==== ASSEMBLING $^
	@ mkdir -p $(@D)
	$(AS) $(ASFLAGS) $^  -o $@

.PHONY: setup
setup:
	@ mkdir -p $(SRCDIR)
	@ mkdir -p $(OBJDIR)
	@ mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	-@ rm -r $(BUILDDIR)
	-@ rm -r $(OBJDIR)
	@ make -C cc65 clean

.PHONY: cc65
cc65:
	make -C cc65