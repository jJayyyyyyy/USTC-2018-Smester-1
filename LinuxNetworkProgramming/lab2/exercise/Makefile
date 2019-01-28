demo: main.o client.o server.o
	cc -o demo main.o client.o server.o

main.o: main.c client.h server.h
	cc -c main.c

client.o: client.c client.h
	cc -c client.c

server.o: server.c server.h
	cc -c server.c

clean:
	rm main.o client.o server.o

.PHONY : demo clean
