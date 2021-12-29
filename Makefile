CC = gcc

all:  mem_1 memlayout
	$(CC) -m32 mem_1.o memlayout.o -o mem_1

mem_1: mem_1.c memlayout
	$(CC) $(CFLAGS) -m32 -c mem_1.c memlayout.c

memlayout: memlayout.c
	$(CC) $(CFLAGS) -m32 -c memlayout.c
clean:
	rm *.o mem_1