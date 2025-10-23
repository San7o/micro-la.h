# SPDX-License-Identifier: MIT
# Author:  Giovanni Santini
# Mail:    giovanni.santini@proton.me
# License: MIT

#
# Compiler flags
#
STD          = c99
CFLAGS       = -Wall -Werror -Wpedantic -Wextra -std=$(STD)
DEBUG_FLAGS  = -ggdb
LDFLAGS      = -lm
TEST_LDFLAGS = -lSDL3
CC?          = gcc

#
# Project files
#
OUT_NAME  = example
OBJ       = example.o
TEST_NAME = quaternion_test
TEST_OBJ  = tests/quaternion_test.o

#
# Commands
#
all: $(OUT_NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(OUT_NAME)

run: $(OUT_NAME)
	chmod +x $(OUT_NAME)
	./$(OUT_NAME)

test: $(TEST_NAME)
	chmod +x $(TEST_NAME)
	./$(TEST_NAME)

clean:
	rm -f $(OBJ) $(TEST_OBJ)

distclean:
	rm -f $(OUT_NAME) $(TEST_NAME)

$(OUT_NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(CFLAGS) -o $(OUT_NAME)

$(TEST_NAME): $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(LDFLAGS) $(TEST_LDFLAGS) $(CFLAGS) -o $(TEST_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
