#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <syslog.h>

#include "daemonize.h"
#include "single.h"

sigset_t mask;

extern void daemonize();
extern int is_running(void);


void
reread(void)
{
	/* ... */
}

void *
thr_fn(void *arg)
{
	int err, signo;

	for (;;) {
		err = sigwait(&mask, &signo);
		if (err != 0) {
			syslog(LOG_ERR, "sigwait failed");
			exit(1);
		}

		switch (signo) {
		case SIGHUP:
			syslog(LOG_INFO, "Re-reading configuration file");
			reread();
			break;

		case SIGTERM:
			syslog(LOG_INFO, "got SIGTERM; exiting");
			exit(0);

		default:
			syslog(LOG_INFO, "unexpected signal %d\n", signo);
		}
	}

	return(0);
}

int 
main()
{
	int				 err;
	pthread_t		 tid;
	char			 *cmd;
	struct sigaction sa;
	FILE *fp = NULL;


	daemonize();

	if (is_running()) {
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		exit(EXIT_FAILURE); // can't restore SIGHUP default
	sigfillset(&mask);
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
		exit(EXIT_FAILURE); // SIG_BLOCK error"

	err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err != 0)
		exit(EXIT_FAILURE); // can't create thread
	


	// Open a log file in write mode.
	fp = fopen("Log.txt", "w+");
	
	while (1) {
		sleep(1);
		fprintf(fp, "Tik\n");
		fflush(fp);
		sleep(1);
		fprintf(fp, "Tak\n");
		fflush(fp);
	}

	fclose(fp);

	exit(EXIT_SUCCESS);
}