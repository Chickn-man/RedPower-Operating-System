PROGNAME = rpos-kernel

CC = cl65 -I /usr/share/cc65/include
AS = ca65 -I /usr/share/cc65/asminc
AR = ar65

INCS = 
LIBS = 

LDS = ./cc65/rpc8.cfg
CFLAGS = -L $(LIBS) -I $(INCS) --cpu 65816 -Osir -g -T -t none
ASFLAGS = --cpu 65816 -g -t none
LDFLAGS = -C $(LDS) -L $(LIBS)

SRCDIR := lib
OBJDIR := ./
BUILDDIR := ./

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.c)
SSRC = $(call rwildcard,$(SRCDIR),*.s)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.s, $(OBJDIR)/%.o, $(SSRC))
DIRS = $(wildcard $(SRCDIR)/*)

.PHONY: build
build: setup archive

.PHONY: archive
archive: $(OBJS)
	@ echo !==== ARCHIVING $^
	@ cp /usr/share/cc65/lib/supervision.lib $(BUILDDIR)/$(PROGNAME).lib
	$(AR) a $(BUILDDIR)/$(PROGNAME).lib $(OBJS)

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
	-@ rm *.o
	-@ rm *.lib