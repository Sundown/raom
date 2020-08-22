CFLAGS += -Wall -pedantic -Ofast -std=c89

.PHONY: raom

raom:
	$(CC) $(CFLAGS) $(wildcard src/*.c) -o raom

run: raom
	./raom
