PROGNAME = bootloader

CC = cc65
AS = acme
LD = ld65

INCS =
LIBS =

LDS = linker.ld
CFLAGS = $(LIBS) $(INCS)
ASFLAGS =
LDFLAGS =

SRCDIR := src
OBJDIR := lib
BUILDDIR := bin

.PHONY: build
build: setup
	@ $(AS) $(ASFLAGS) -o $(OBJDIR)/boot.o -f plain $(SRCDIR)/boot.s
	-@ rm $(BUILDDIR)/boot.bin
	@ dd if=$(OBJDIR)/boot.o of=$(BUILDDIR)/boot.bin bs=128 skip=10 count=4
	@ dd if=$(OBJDIR)/boot.o of=$(BUILDDIR)/exboot.bin bs=128 skip=14 count=4

.PHONY: setup
setup:
	@ mkdir -p $(SRCDIR)
	@ mkdir -p $(OBJDIR)
	@ mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	-@ rm -r $(BUILDDIR)
	-@ rm -r $(OBJDIR)