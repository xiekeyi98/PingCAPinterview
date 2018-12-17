DIR_SRC = ./src
DIR_BIN = ./bin
DIR_OBJ = ./obj

CC = g++
CFLAGSDEBUG = -g -Wall -Wextra -Wshadow
CFLAGS = -o2

TARGET = main
BIN_TARGET = $(DIR_BIN)/$(TARGET)

SRCS = $(wildcard *.cpp ${DIR_SRC}/*.cpp)
OBJS = $(patsubst %cpp,$(DIR_OBJ)/%o,$(notdir $(SRCS)));

all:$(BIN_TARGET)

$(DIR_OBJ)/%.o: $(SRCS)
	mkdir -p ${DIR_OBJ} 
	$(CC) $(CFLAGS) -c -o $@ $< 

$(BIN_TARGET):$(OBJS)
	mkdir -p ${DIR_BIN}
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -rf $(DIR_OBJ)/
