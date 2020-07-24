CC=g++

VPATH = src

SRC = ./src/

INC = -I./src/

all: server client clientTest serverTest

server: server.o log.o
	$(CC) -g $^ -o $@

client: client.o log.o tcp.o
	$(CC) -g $^ -o $@

clientTest: clientTest.o tcp.o myqueue.o file.o 
	$(CC) -g $^ -lpthread -o $@

serverTest: serverTest.o tcp.o

log.o: log.h
tcp.o: tcp.h

clean:
	rm *.o server client
