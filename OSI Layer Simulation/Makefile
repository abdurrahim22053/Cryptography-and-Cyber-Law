CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2
all: osi_server osi_client
osi_server: server.c osi_common.h
	$(CC) $(CFLAGS) -o osi_server server.c
osi_client: client.c osi_common.h
	$(CC) $(CFLAGS) -o osi_client client.c
clean:
	rm -f osi_server osi_client
.PHONY: all clean
