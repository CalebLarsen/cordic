CC := clang
CFLAGS := -g -Wall -fsanitize=address -fno-omit-frame-pointer
LD := clang
LDFLAGS := -fsanitize=address

all: cordic
	@echo "Running cordic\n======="
	@./cordic

cordic: cordic.o main.o fixed.o
	$(LD) $(LDFLAGS) -o cordic cordic.o main.o fixed.o
	
cordic.o: cordic.S
	$(CC) $(CFLAGS) -c cordic.S

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

test: test.o fixed.o
	$(LD) $(LDFLAGS) -o test test.o fixed.o
	./test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

fixed.o: fixed.c fixed.h
	$(CC) $(CFLAGS) -c fixed.c

help: help.o fixed.o
	$(LD) $(LDFLAGS) -o help help.o fixed.o

help.o: help.c
	$(CC) $(CFLAGS) -c help.c

PHONY: clean
clean:
	rm -f *.o
	rm -f cordic
	rm -f test
	rm -f help

PHONY: debug
debug: cordic
	lldb --file cordic --source db-commands

PHONY: db
db: cordic
	lldb --file cordic --source db-commands
