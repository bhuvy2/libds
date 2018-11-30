OBJS_DIR=.objs
SOURCE_FILES=$(wildcard src/**/*c) $(wildcard src/*c)
HEADER_FILES=$(wildcard src/*h) $(wildcard src/**/*h)
FILE_DIRS=$(dir $(SOURCE_FILES))
CREATE_DIRS=$(patsubst %,$(OBJS_DIR)/%,$(FILE_DIRS))
OBJS_FILE=$(patsubst %.c,$(OBJS_DIR)/%.o,$(SOURCE_FILES))
TARGET_NAME=$(DEPLOY_DIR)/libds.a
INCLUDE_TARGETS=$(patsubst %,-I%,. src/ $(FILE_DIRS))
COMPILER_FLAGS=-c -fPIC -Wall -Wextra $(INCLUDE_TARGETS)
CC=gcc
DEPLOY_DIR=deploy/

.PHONY: all
all: $(TARGET_NAME)

$(TARGET_NAME): $(OBJS_FILE) | $(DEPLOY_DIR)
	ar rcs $@ $^
	cp $(HEADER_FILES) $(DEPLOY_DIR)

$(OBJS_FILE): $(OBJS_DIR)/%.o: %.c | $(CREATE_DIRS)
	$(CC) $(COMPILER_FLAGS) -o $@ $^

$(CREATE_DIRS) $(DEPLOY_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm $(TARGET_NAME)
	rm -rf $(OBJS_DIR)
