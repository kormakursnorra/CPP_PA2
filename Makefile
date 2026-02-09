CXX := g++
CXXFLAGS := -std=c++98 -Wall -Wextra -g
LDFLAGS := 

SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
OBJ_DIR := obj

DLL_TEST_TARGET := dll_test
HEAP_TEST_TARGET := heap_test

DLL_TEST_BIN := $(BIN_DIR)/$(DLL_TEST_TARGET)
HEAP_TEST_BIN := $(BIN_DIR)/$(HEAP_TEST_TARGET)

DLL_SOURCES := src/DLL/dll_test.cpp
HEAP_SOURCES := src/Heap/heap_test.cpp

ALL_TARGETS := $(DLL_TEST_BIN) $(HEAP_TEST_BIN)

DLL_TEST_OBJECTS := $(DLL_TEST_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
HEAP_TEST_OBJECTS := $(HEAP_TEST_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(ALL_TARGETS)
	@echo " All test executables built" 

$(DLL_TEST_BIN): $(DLL_TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@chmod +x $@
	@echo "Build complete: $@"

$(HEAP_TEST_BIN): $(HEAP_TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@chmod +x $@
	@echo "Build complete: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run-dll: $(DLL_TEST_BIN)
	@echo "Running DLL Test"
	./$(DLL_TEST_BIN)

run-heap: $(HEAP_TEST_BIN)
	@echo "Running Heap Test"
	./$(HEAP_TEST_BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

rebuild: clean all

dll_test: $(DLL_TEST_BIN)
heap_test: $(HEAP_TEST_BIN)

.PHONY: all run-dll run-heap test clean rebuild list help dll_test heap_test
