OBJS_DIR=.objs
TEST_EXE_DIR=exe
SOURCE_FILES=$(wildcard **/*c) $(wildcard *c)
TEST_TARGETS=$(patsubst %.c,$(TEST_EXE_DIR)/%,$(SOURCE_FILES))
INCLUDE_TARGETS=$(patsubst %,-I%,.)

COMPILER_FLAGS=-Wall -Wextra $(INCLUDE_TARGETS) -g -I $(LIBS) -L$(LIBS)
CC=gcc

LIBS=libs
.PHONY: all
all: $(TEST_TARGETS)

$(TEST_TARGETS): $(TEST_EXE_DIR)/% : %.c | $(LIBS) $(TEST_EXE_DIR)
	gcc $(COMPILER_FLAGS) $^ $(LIBS)/libds.a -lcheck -lm -lrt -lpthread -lsubunit -o $@

$(LIBS):
	make -C ..
	mv ../deploy $(LIBS)

$(TEST_EXE_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(TEST_EXE_DIR)
