# ==============================================================================
# Karte
# ------------------------------------------------------------------------------
# Makefile
# ==============================================================================

CC := gcc

SRCDIR := src
BUILDDIR := build
TARGET := bin/karte

SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.d)

INC := -Iinclude
CFLAGS := $(INC) -std=c11 -g -MMD -MP -Wall -Wextra -Wpedantic -Werror -O0
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	$(RM) $(TARGET) $(OBJECTS) $(DEPS)

.PHONY: clean
-include $(DEPS)
