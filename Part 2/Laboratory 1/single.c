#include "single.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <sys/stat.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

// extern int lockfile(int);

int
is_running(void)
{
	int  fd;
	char buf[16];

	fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if (fd < 0) {
		syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (lockf(fd, F_TLOCK, 0) < 0) {
		if (errno == EACCES 
	 	|| errno == EAGAIN) {
			close(fd);
			return(1);
	 	}
	 	syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
	 	exit(EXIT_FAILURE);
	}
	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf) + 1);

	return(0);
}