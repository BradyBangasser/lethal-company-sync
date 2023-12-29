SRC_DIR := src
VERSION := 0.0.1
OUT_DIR := out
LIB_DIR := lib
CC := gcc
CXXC := g++
GFLAGS := -O2 -Wall -I include
CFLAGS := 
CPPFLAGS := 
LFLAGS :=-Llib -lssl -lcrypto -static -static-libgcc -static-libstdc++ -lz -lws2_32 -lcrypt32
EXE := lethal-sync-v$(VERSION).exe
CPP_STD := 17
C_STD := 11

LIB_OBJS := $(wildcard $(LIB_DIR)/*.o)

C_SOURCES := $(wildcard $(SRC_DIR)/*.c)
CPP_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

C_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.c.o, $(C_SOURCES))
CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OUT_DIR)/%.cpp.o, $(CPP_SOURCES))

$(EXE): $(CPP_OBJS) $(C_OBJS)
	$(CXXC) $(CPP_OBJS) $(C_OBJS) $(LIB_OBJS) $(GFLAGS) -o $(EXE) $(LFLAGS) 

$(OUT_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS) $(GFLAGS) -std=c$(C_STD)

$(OUT_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(CXXC) -c -o $@ $^ $(CPPFLAGS) $(GFLAGS) -std=c++$(CPP_STD)

clean:
	rm -rf out/* *.exe *.txt
	clear