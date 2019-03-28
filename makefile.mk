a.out:client.o server.o
	gcc client.o server.o -lm
client.o:client.c header.h
	gcc -c client.c
server.o:server.c
	gcc -c server.c
