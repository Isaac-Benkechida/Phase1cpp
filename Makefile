TOPDIR  := ./

SRCDIR  := $(TOPDIR)src/
OBJDIR  := $(TOPDIR)obj/
BINDIR  := $(TOPDIR)
NAME    := program
EXE     := $(BINDIR)$(NAME)

SFILES  := cpp
OFILES  := o
CC      := g++
CFLAGS  := -Wall -Wextra -O0 -std=gnu++20 -pedantic -march=native -Wnull-dereference -Wconversion -pthread -flto -pipe -g -fsanitize=address,undefined
LDFLAGS := -fsanitize=address,undefined

SOURCES := $(shell find $(SRCDIR) -name "*.$(SFILES)")
OBJECTS := $(patsubst $(SRCDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(SOURCES))

.PHONY: all clean

all: directories $(EXE)

# Create necessary directories
directories:
	@mkdir -p $(OBJDIR)

$(EXE): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)  # Use LDFLAGS for linking

$(OBJDIR)%.$(OFILES): $(SRCDIR)%.$(SFILES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@  # Use CFLAGS for compiling

test:
	python3 tests3.py $(TOPDIR)$(EXE)

clean:
	@rm -f $(EXE)
	@rm -rf $(OBJDIR)
