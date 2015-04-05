rft: rft.o main.o
	cc rft.o main.o -o rft

rft.o: rft.c rft.h
	cc -c rft.c

main.o: main.c
	cc -c main.c



.PHONY: unstall uninstall clean

install:
	cp -v rft /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/rft

clean:
	-rm *.o rft