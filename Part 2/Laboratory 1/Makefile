daemon: daemonize.o single.o main.o
	cc -pthread daemonize.o single.o main.o -o daemon

daemonize.o: daemonize.c daemonize.h
	cc -pthread -c daemonize.c

single.o: single.c single.h
	cc -pthread -c single.c

main.o: main.c
	cc -pthread -c main.c

.PHONY = clean
clean:
	-rm *.o daemon