# Simple C++ engine build system

CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
CPPFLAGS += -Iengine -Ithird_party
AR ?= ar
ARFLAGS ?= rcs

BUILD_DIR := bin
LIB_DIR := lib
ENGINE_DIR := engine
GAME_DIR := game

ENGINE_LIB := $(LIB_DIR)/libengine.a
ENGINE_OBJECTS := $(patsubst $(ENGINE_DIR)/%.cpp,$(BUILD_DIR)/engine_%.o,$(wildcard $(ENGINE_DIR)/*.cpp))
GAME_OBJECTS := $(patsubst $(GAME_DIR)/%.cpp,$(BUILD_DIR)/game_%.o,$(wildcard $(GAME_DIR)/*.cpp))
GAME_TARGET := $(BUILD_DIR)/engine_game

.PHONY: all engine game run clean

all: engine game

engine: $(ENGINE_LIB)

game: $(GAME_TARGET)

$(ENGINE_LIB): $(ENGINE_OBJECTS)
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(GAME_TARGET): $(GAME_OBJECTS) $(ENGINE_LIB)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(GAME_OBJECTS) -L$(LIB_DIR) -lengine

$(BUILD_DIR)/engine_%.o: $(ENGINE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/game_%.o: $(GAME_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

run: all
	./$(GAME_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)
