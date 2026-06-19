# Simple C++ engine build system

CC ?= cc
CXX ?= c++
CFLAGS ?= -Wall -Wextra -O2
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
CPPFLAGS += -Iengine -Ithird_party/glad/include -Ithird_party/glfw/include
ifeq ($(shell uname),Darwin)
CPPFLAGS += -D_GLFW_COCOA
endif
AR ?= ar
ARFLAGS ?= rcs

BUILD_DIR := bin
LIB_DIR := lib
ENGINE_DIR := engine
GAME_DIR := game
THIRD_PARTY_DIR := third_party

ENGINE_LIB := $(LIB_DIR)/libengine.a
GLAD_LIB := $(LIB_DIR)/libglad.a
GLFW_LIB := $(LIB_DIR)/libglfw.a

ENGINE_OBJECTS := $(patsubst $(ENGINE_DIR)/%.cpp,$(BUILD_DIR)/engine_%.o,$(wildcard $(ENGINE_DIR)/*.cpp))
GAME_OBJECTS := $(patsubst $(GAME_DIR)/%.cpp,$(BUILD_DIR)/game_%.o,$(wildcard $(GAME_DIR)/*.cpp))
GLAD_OBJECTS := $(BUILD_DIR)/glad.o
GLFW_OBJECTS := $(patsubst $(THIRD_PARTY_DIR)/glfw/src/%.c,$(BUILD_DIR)/glfw_%.o,$(wildcard $(THIRD_PARTY_DIR)/glfw/src/*.c)) \
	$(patsubst $(THIRD_PARTY_DIR)/glfw/src/%.m,$(BUILD_DIR)/glfw_%.o,$(wildcard $(THIRD_PARTY_DIR)/glfw/src/*.m))
GAME_TARGET := $(BUILD_DIR)/engine_game

ifeq ($(shell uname),Darwin)
GLFW_LDLIBS := -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation
else
GLFW_LDLIBS := -pthread -ldl -lm
endif

.PHONY: all engine game run clean

all: engine game

engine: $(ENGINE_LIB)

game: $(GAME_TARGET)

$(ENGINE_LIB): $(ENGINE_OBJECTS)
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(GLAD_LIB): $(GLAD_OBJECTS)
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(GLFW_LIB): $(GLFW_OBJECTS)
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(GAME_TARGET): $(GAME_OBJECTS) $(ENGINE_LIB) $(GLAD_LIB) $(GLFW_LIB)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(GAME_OBJECTS) -L$(LIB_DIR) -lengine -lglad -lglfw $(GLFW_LDLIBS)

$(BUILD_DIR)/engine_%.o: $(ENGINE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/game_%.o: $(GAME_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/glad.o: $(THIRD_PARTY_DIR)/glad/src/glad.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/glfw_%.o: $(THIRD_PARTY_DIR)/glfw/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/glfw_%.o: $(THIRD_PARTY_DIR)/glfw/src/%.m
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

run: all
	./$(GAME_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)
