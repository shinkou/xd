CC := gcc
CCFLAGS :=
LDFLAGS :=

SRCDIR := src
BUILDDIR := build
TARGETS := xd
SRC := main xd utils
MAINS := $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(SRC) ) )
OBJ := $(MAINS)

.PHONY: all clean

all: $(BUILDDIR)/$(TARGETS)

clean:
	rm -rf $(BUILDDIR)

$(OBJ): $(BUILDDIR)/%.o : $(SRCDIR)/%.c
	@$(shell [ -d $(@D) ] || mkdir -p $(@D))
	$(CC) -c -o $@ $< $(CCFLAGS)

$(BUILDDIR)/$(TARGETS): $(OBJ)
	$(CC) -o $@ $(LIBS) $^ $(CCFLAGS) $(LDFLAGS)
