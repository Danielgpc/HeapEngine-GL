# Engine Makefile

UNAME := $(shell uname)

CC ?= gcc
CXX ?= g++
AR ?= ar
ARFLAGS ?= rcs

CFLAGS ?= -Wall -Wextra -O2 -D_THREAD_SAFE
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2 -D_THREAD_SAFE
CPPFLAGS += -I. -Ithird_party -Ithird_party/glad/include -Ithird_party/glfw/include -Ithird_party/imgui -Ithird_party/imgui/backends -Ithird_party/stb

ifeq ($(UNAME), Darwin)
CPPFLAGS += -D_GLFW_COCOA
endif

OBJDIR := ../build/engine
LIB := $(OBJDIR)/libengine.a

ENGINE_SRCS := $(wildcard src/*.cc)
ENGINE_OBJS := $(patsubst src/%.cc,$(OBJDIR)/%.o,$(ENGINE_SRCS))

GLAD_OBJ := $(OBJDIR)/glad.o
IMGUI_CORE_SRCS := $(wildcard third_party/imgui/*.cpp)
IMGUI_CORE_OBJS := $(patsubst third_party/imgui/%.cpp,$(OBJDIR)/%.o,$(IMGUI_CORE_SRCS))

ifeq ($(UNAME), Darwin)
IMGUI_BACKEND_SRCS := third_party/imgui/backends/imgui_impl_glfw.cpp third_party/imgui/backends/imgui_impl_opengl3.cpp
else
IMGUI_BACKEND_SRCS := third_party/imgui/backends/imgui_impl_glfw.cpp third_party/imgui/backends/imgui_impl_opengl3.cpp
endif
IMGUI_BACKEND_OBJS := $(patsubst third_party/imgui/backends/%.cpp,$(OBJDIR)/backends/%.o,$(IMGUI_BACKEND_SRCS))

all: $(LIB)

$(LIB): $(ENGINE_OBJS) $(GLAD_OBJ) $(IMGUI_CORE_OBJS) $(IMGUI_BACKEND_OBJS)
	@mkdir -p $(OBJDIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: src/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(GLAD_OBJ): third_party/glad/src/glad.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJDIR)/backends/%.o: third_party/imgui/backends/%.cpp
	@mkdir -p $(OBJDIR)/backends
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: third_party/imgui/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(ENGINE_OBJS) $(GLAD_OBJ) $(IMGUI_CORE_OBJS) $(IMGUI_BACKEND_OBJS) $(LIB)

.PHONY: all clean
