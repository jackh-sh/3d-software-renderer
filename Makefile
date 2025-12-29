.PHONY: all build run clean configure rebuild

BUILD_DIR := build
EXECUTABLE := $(BUILD_DIR)/App

all: build run

build: $(BUILD_DIR)/Makefile
	@cmake --build $(BUILD_DIR)

run: build
	@./$(EXECUTABLE)

configure:
	@cmake -B $(BUILD_DIR) -S .

$(BUILD_DIR)/Makefile:
	@cmake -B $(BUILD_DIR) -S .

clean:
	@rm -rf $(BUILD_DIR)

rebuild: clean build
