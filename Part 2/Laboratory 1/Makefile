daemon: daemonize.o main.o
	cc daemonize.o main.o -o daemon

daemonize.o: daemonize.c
	cc -c daemonize.c

main.o: main.c
	cc -c main.c

clean:
	rm *.o daemon