CC=gcc
FILENAME=cifrado1
BIN_DIR=bin
FLAGS= -Wall -Wextra -Wpedantic -Wunreachable-code -Wconversion -Wshadow -Wcast-align -Waggregate-return -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wfloat-equal

build:$(BIN_DIR)/$(FILENAME)

$(BIN_DIR)/$(FILENAME): $(FILENAME).o
	mkdir -p $(BIN_DIR)
	$(CC) $(FILENAME).o -o $(BIN_DIR)/$(FILENAME)

$(FILENAME).o: $(FILENAME).c
	$(CC) $(FILENAME).c $(FLAGS) -c -o $(FILENAME).o

run: $(BIN_DIR)/$(FILENAME)
	./$(BIN_DIR)/$(FILENAME)

clean:
	rm -rf $(FILENAME).o
	rm -rf $(BIN_DIR)
