CC = gcc
CFLAGS = -Wall -O3
SRC_DIR = src
BUILD_DIR = build

TARGETS = $(BUILD_DIR)/demo_swarm $(BUILD_DIR)/demo_immune $(BUILD_DIR)/demo_search

all: $(BUILD_DIR) $(TARGETS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/demo_swarm: $(SRC_DIR)/logical_bubbles.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/demo_immune: $(SRC_DIR)/immune_swarm.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/demo_search: $(SRC_DIR)/swarm_searcher.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
