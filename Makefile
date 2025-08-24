SRC_DIR=src
BUILD_DIR=build
HEADERS_DIR=include

CC=gcc
FLAGS=-g -O0 -Wall -Wextra -I$(HEADERS_DIR)   -MMD -MP

SOURCES=$(wildcard $(SRC_DIR)/*.c )
OBJECTS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS   =$(OBJECTS:.o=.d )

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

-include $(DEPS)

demo: $(SRC_DIR)/main.c $(SRC_DIR)/terminal.c
	$(CC)  -DEDITOR_DEMO -I$(HEADERS_DIR)  $(SRC_DIR)/main.c $(SRC_DIR)/terminal.c -o demo

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPS)