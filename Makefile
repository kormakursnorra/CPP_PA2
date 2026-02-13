CXX := g++
CXXFLAGS := -std=c++98 -Wall -Wextra -g
LDFLAGS := 

SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
OBJ_DIR := obj

BST_TEST_TARGET := bst_test
DLL_TEST_TARGET := dll_test
HEAP_TEST_TARGET := heap_test
HASHMAP_TEST_TARGET := hashmap_test
DEQUE_TEST_TARGET := deque_test

BST_TEST_BIN := $(BIN_DIR)/$(BST_TEST_TARGET)
DLL_TEST_BIN := $(BIN_DIR)/$(DLL_TEST_TARGET)
HEAP_TEST_BIN := $(BIN_DIR)/$(HEAP_TEST_TARGET)
HASHMAP_TEST_BIN := $(BIN_DIR)/$(HASHMAP_TEST_TARGET)
DEQUE_TEST_BIN := $(BIN_DIR)/$(DEQUE_TEST_TARGET)

ALL_TARGETS := $(DLL_TEST_BIN) $(HEAP_TEST_BIN) $(HASHMAP_TEST_BIN) $(BST_TEST_BIN) $(DEQUE_TEST_BIN)

BST_TEST_SOURCES := src/BST/bst_test.cpp
DLL_TEST_SOURCES := src/DLL/dll_test.cpp
HEAP_TEST_SOURCES := src/Heap/heap.cpp src/Heap/heap_test.cpp
HASHMAP_TEST_SOURCES := src/HashMap/hashmap.cpp src/HashMap/hashmap_test.cpp
BST_TEST_SOURCES := src/BST/bst_test.cpp
DEQUE_TEST_SOURCES := src/Deque/deque_test.cpp

BST_TEST_OBJECTS := $(BST_TEST_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DLL_TEST_OBJECTS := $(DLL_TEST_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
HEAP_TEST_OBJECTS := $(HEAP_TEST_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
HASHMAP_TEST_OBJECTS := $(HASHMAP_TEST_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEQUE_TEST_OBJECTS := $(DEQUE_TEST_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(ALL_TARGETS)
	@echo " All test executables built" 

$(BST_TEST_BIN): $(BST_TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@chmod +x $@
	@echo "Build BST complete: $@"

$(DLL_TEST_BIN): $(DLL_TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@chmod +x $@
	@echo "Build DLL complete: $@"

$(HEAP_TEST_BIN): $(HEAP_TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@chmod +x $@
	@echo "Build Heap complete: $@"

$(HASHMAP_TEST_BIN): $(HASHMAP_TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@chmod +x $@
	@echo "Build HashMap complete: $@"

$(BST_TEST_BIN): $(BST_TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@chmod +x $@
	@echo "Build BST complete: $@"

$(DEQUE_TEST_BIN): $(DEQUE_TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@chmod +x $@
	@echo "Build Deque complete: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run-bst: $(BST_TEST_BIN)
	@echo "Running BST Test"
	./$(BST_TEST_BIN)

run-dll: $(DLL_TEST_BIN)
	@echo "Running DLL Test"
	./$(DLL_TEST_BIN)

run-heap: $(HEAP_TEST_BIN)
	@echo "Running Heap Test"
	./$(HEAP_TEST_BIN)

run-hashmap: $(HASHMAP_TEST_BIN)
	@echo "Running HashMap Test"
	./$(HASHMAP_TEST_BIN)

run-deque: $(DEQUE_TEST_BIN)
	@echo "Running Deque Test"
	./$(DEQUE_TEST_BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

rebuild: clean all

bst_test: $(BST_TEST_BIN)
heap_test: $(HEAP_TEST_BIN)
dll_test: $(DLL_TEST_BIN)
hashmap_test: $(HASHMAP_TEST_BIN)
deque_test: $(DEQUE_TEST_BIN)

.PHONY: all run-dll run-heap run-hashmap run-deque test clean rebuild list help dll_test heap_test hashmap_test bst_test deque_test
