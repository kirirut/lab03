CC = gcc
CFLAGS = -W -Wall -Wextra -std=c11
SRC_DIR = src
BUILD_DIR = build
INCLUDES = -I$(SRC_DIR)

PARENT_SRC = $(SRC_DIR)/parent.c
CHILD_SRC = $(SRC_DIR)/child.c
PARENT_OBJ = $(BUILD_DIR)/parent.o
CHILD_OBJ = $(BUILD_DIR)/child.o

PARENT_BIN = $(BUILD_DIR)/parent
CHILD_BIN = $(BUILD_DIR)/child

.PHONY: all clean dirs

all: dirs $(PARENT_BIN) $(CHILD_BIN)

dirs:
	mkdir -p $(BUILD_DIR)

$(PARENT_BIN): $(PARENT_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

$(CHILD_BIN): $(CHILD_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(BUILD_DIR)
