##si copian el del telegram va con error de*** missing separator.  Stop.

CC = g++
SOURCE = clases
OBJ = sudoku.o $(SOURCE)/clases.o
OUT = output.bin
OUTDIR = bin
HEADER = clases.h
CFLAGS = -I./$(SOURCE) -c -Wall

MKDIR = mkdir -p


edit: $(OBJ)
	$(MKDIR) $(OUTDIR)
	$(CC) -o $(OUTDIR)/$(OUT) $(OBJ)

clases.o: clases.cpp $(HEADER)
	$(CC) $(CFLAGS) clases.cpp

sudoku.o: sudoku.cpp $(SOURCE)/$(HEADER)
	$(CC) $(CFLAGS) sudoku.cpp

.PHONY: clean
clean:
	rm $(OUTDIR)/$(OUT) $(OBJ)
	rmdir $(OUTDIR)

run:
	$(OUTDIR)/$(OUT)