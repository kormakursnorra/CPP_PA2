CXX := g++
CXXFLAGS := -std=c++98 -Wall -Wextra -g
LDFLAGS := 

SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
OBJ_DIR := obj

TARGET := main

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

rebuild: clean all


help:
	@echo "Available targets:"
	@echo "  all (default) - Build the project"
	@echo "  run           - Build and run the program"
	@echo "  clean         - Remove all build artifacts"
	@echo "  rebuild       - Clean and build from scratch"
	@echo "  help          - Show this help message"

.PHONY: all run clean rebuild help
