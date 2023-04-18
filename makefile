CC=gcc
CFLAGS=-Wall
LDFLAGS=-lMLV
REPOBJ=bin/main.o bin/frame.o bin/logic.o
OBJ=main.o frame.o logic.o
MAIN=exe/main
BIN=bin/

all: $(OBJ)
	$(CC) $(REPOBJ) $(LDFLAGS) -o $(MAIN)

main.o: src/main.c src/include/frame.h src/include/logic.h
	$(CC) -c src/main.c $(CFLAGS) -o $(BIN)$@

logic.o: src/logic.c src/include/logic.h src/include/frame.h
	$(CC) -c src/logic.c $(CFLAGS) -o $(BIN)$@

frame.o: src/frame.c src/include/logic.h
	$(CC) -c src/frame.c $(CFLAGS) -o $(BIN)$@

clean:
	rm -rf $(BIN)*.o $(MAIN)

doc:
	doxygen generated-docs/Doxyfile
run:
	make
	./$(MAIN)

report:
	less Rapport.txt

open_doc:
	firefox generated-docs/html/index.html