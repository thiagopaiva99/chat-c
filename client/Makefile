all: client clean

client: client.o 
	gcc client.o -o client

client.o: client.c
	gcc -c client.c

clean:
	rm *.o
