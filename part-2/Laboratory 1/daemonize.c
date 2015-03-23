#include <sys/stat.h>
#include <sys/resource.h>

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <fcntl.h>

#include "daemonize.h"

void
daemonize()
{
	int    			 i, fd0, fd1, fd2;
	pid_t  			 pid, sid;
	struct rlimit 	 rl;

	// reset mask, process can do with files anything
	umask(0);

	// get right(max) limit of files
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		exit(EXIT_FAILURE);

	// fork process
	if ((pid = fork()) < 0) 
		exit(EXIT_FAILURE);
	else if (pid != 0) // then exit parent process
		exit(EXIT_SUCCESS);
	

	// child will be session leader and group leader
	if ((sid = setsid()) < 0)
		exit(EXIT_FAILURE);
	// ho ho now it's DAEMON

	// change the current working directory
	if (chdir("/") < 0)
		exit(EXIT_FAILURE);

	// close all file descriptors
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	// open stdin, stdout, stderr for daemon in /dev/null
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog("DL", LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 
	|| fd1 != 1
	|| fd2 != 2) 
	{
		syslog(LOG_ERR, 
			   "unexpected file descriptors %d %d %d",
			   fd0, fd1, fd2);
		exit(EXIT_FAILURE);
	}
}