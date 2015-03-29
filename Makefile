CC=gcc
CFLAGS=-Wall -o useradd
LDFLAGS=-lcrypt

all:
	$(CC) usersadd.c ua_struct.c ua_crypt.c $(CFLAGS) $(LDFLAGS)
