CC=gcc
INCDIRS=-I.
CFLAGS=-Wall -c -Wextra -g $(INCDIRS)
CFILES=stack.c min_stack.c
OBJECTS=stack.o min_stack.o
OUTPUT=my_stack


all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o  $(OUTPUT)

stack.o: stack/stack.c
	$(CC) $(CFLAGS) stack/stack.c


run: my_stack
	./$(OUTPUT)

clean:
	rm -rf *.o my_stack
