CC = gcc
CFLAGS = -Wall -Wextra -fexec-charset=UTF-8 -Iinclude
LIBS = -lpthread -lm -lncurses
TARGET = tocador
BUILD_DIR = build

$(TARGET): $(BUILD_DIR)/main.o lib/miniaudio.o
	$(CC) -o $(TARGET) $(BUILD_DIR)/main.o lib/miniaudio.o $(LIBS)

$(BUILD_DIR)/main.o: src/main.c include/miniaudio.h
				mkdir -p $(BUILD_DIR)
				$(CC) $(CFLAGS) -c src/main.c -o $(BUILD_DIR)/main.o

clean: 
			rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
