# Game Makefile

UNAME := $(shell uname)

CC ?= gcc
CXX ?= g++

CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2 -D_THREAD_SAFE
CPPFLAGS += -I../engine -I../engine/third_party -I../engine/third_party/glad/include -I../engine/third_party/glfw/include -I../engine/third_party/imgui -I../engine/third_party/imgui/backends -I../engine/third_party/stb

ifeq ($(UNAME), Darwin)
CPPFLAGS += -D_GLFW_COCOA
LDFLAGS += -L/opt/homebrew/lib -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation
else
LDFLAGS += -ldl -lm -lpthread -lGL
endif

OBJDIR := ../build/game
TARGET := $(OBJDIR)/voidscan
SRCS := src/main.cc
OBJS := $(patsubst src/%.cc,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) ../build/engine/libengine.a
	@mkdir -p $(OBJDIR)
	$(CXX) $(OBJS) -o $@ ../build/engine/libengine.a -lglfw $(LDFLAGS)

$(OBJDIR)/%.o: src/%.cc
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
