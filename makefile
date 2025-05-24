CC=gcc
CFLAGS=-I.
DEPS = main.h budget.h
OBJ = main.o budget.o data.o ordering.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


budgetTracker: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)