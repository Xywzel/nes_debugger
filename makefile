# Compiler
CC := g++

# Directories
SRCDIR := src
OBJDIR := obj
BINDIR := bin
INCDIR := inc

# Note
# := Expand when definited, better performance
# = Expand when used, can addapt to dynamic part

# Output
TARGET := nes_debugger

# Compiler options
STD := -std=c++17
DEBUG := -g
WARNINGS := -pedantic -Wall -Wextra
OPTIMIZE := -march=native -O3
GENDEPS := -MMD
INCLUDES := -I$(INCDIR) -I$(SRCDIR)

# SDL if needed
SDL_LIBS = -lSDL2_image -lSDL2_mixer
SDL_COMP = $(shell sdl2-config --cflags)
SDL_LINK = $(shell sdl2-config --libs)

# GLFW if needed
GLFW_LINK = $(shell pkg-config --static --libs glfw3)
GLFW_COMP = $(shell pkg-config --cflags glfw3)

# Vulkan if needed
VUL_LINK = $(shell pkg-config --static --libs vulkan)
VUL_COMP = $(shell pkg-config --cflags vulkan)

SOURCES = $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.cpp=.o))
DEPENDENCIES = $(OBJECTS:%.o=%.d)

CFLAGS = $(STD) $(DEBUG) $(WARNINGS) $(INCLUDES) $(GLFW_COMP) $(VUL_COMP) $(GENDEPS)
LFLAGS = $(STD) $(WARNINGS) $(GLFW_LINK) $(VUL_LINK)

all: $(BINDIR)/$(TARGET)
	@echo "Done"

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "Linking $< ..."
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@ $(LFLAGS)

-include $(DEPENDENCIES)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling $< ..."
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/hardware
	@mkdir -p $(OBJDIR)/math
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo cleaning
	find . -name \*.o -type f -delete
	find . -name \*.d -type f -delete
	rm -rf $(BINDIR)/$(TARGET)
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)
