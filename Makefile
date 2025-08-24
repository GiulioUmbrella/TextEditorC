SRC_DIR=src
BUILD_DIR=build

CC=gcc
FLAGS=-g -O0 -Wall -Wextra -MMD -MP

SOURCES=$(wildcard $(SRC_DIR)/*.c )
OBJECTS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))


BINARY=kilo

all: $(BINARY)

$(BINARY): $(OBJECTS) 
	@echo compile $^ into $@ 
	$(CC) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo compile $< into $@ 
	$(CC) $(FLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@


clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPS)