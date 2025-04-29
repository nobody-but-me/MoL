
INCLUDE := -I./include/ -I./lib/
CFLAGS := -lglfw -lm -Wall -Wno-int-conversion
CC := gcc

SRC_PATH := ./src

TARGET := ./build/Mol
SRCS := $(wildcard $(SRC_PATH)/*.c)
OBJS := ./objs/mol.o

run: $(TARGET)
	$(TARGET)
	rm -rf ./*.o

$(TARGET): $(OBJS)
	$(CC) ./*.o -o ./build/Mol $(INCLUDE) $(CFLAGS)

$(OBJS): ./objs
	$(CC) -c $(SRCS) $(INCLUDE) $(CFLAGS)

./objs: ./build
	mkdir -p ./objs

./build:
	mkdir -p ./build

.PHONY: clean
clean:
	rm -rf ./build ./objs
