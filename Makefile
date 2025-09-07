SRC_DIR=src
BUILD_DIR=build
HEADERS_DIR=include

CC=clang

INCLUDE_DIRS= $(HEADERS_DIR) $(wildcard $(HEADERS_DIR)/*/)
BUILD_INCLUDE_DIRS := $(patsubst $(HEADERS_DIR)%,$(BUILD_DIR)%,$(INCLUDE_DIRS))

FLAGS= -std=c17 -Wall -Wextra -g $(addprefix -I,$(INCLUDE_DIRS)) -MMD -MP

SOURCES=$(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS   =$(OBJECTS:.o=.d )

BUILD ?= debug

FLAGS_DEBUG = -g -Wall -Wextra -Wpedantic \
              -Wshadow -Wconversion -Wsign-conversion 

FLAGS_RELEASE = -Wall -Wextra -Wpedantic -Werror \
                -Wshadow -Wconversion -Wsign-conversion \
                -Wformat=2 -Wnull-dereference -O2

ifeq ($(BUILD),release)
    FLAGS = $(FLAGS_RELEASE)
else
    FLAGS = $(FLAGS_DEBUG)
endif

FLAGS += $(addprefix -I,$(INCLUDE_DIRS)) -MMD -MP



BINARY=kilo

all: $(BINARY)

$(BINARY): $(OBJECTS) 
	@echo compile $^ into $@ 
	$(CC) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_INCLUDE_DIRS)
	@echo compile $< into $@ 
	$(CC) $(FLAGS) -c -o $@ $<

$(BUILD_INCLUDE_DIRS):
	mkdir -p $@

-include $(DEPS)


clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPS)