CC=gcc
CFLAGS=-Wall -g -I.
DEPS = main.h budget.h data.h ordering.h
OBJ = main.o budget.o data.o ordering.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


budgetTracker: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)