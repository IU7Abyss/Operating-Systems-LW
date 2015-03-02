#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"

#include "daemonize.h"

int main()
{
	FILE *fp= NULL;

	daemonize();

	// Open a log file in write mode.
	fp = fopen("Log.txt", "w+");
	
	while (1)
	{
		//Dont block context switches, let the process sleep for some time
		sleep(1);
		fprintf(fp, "Logging info...\n");
		fflush(fp);
		// Implement and call some function that does core work for this daemon.
	}
	fclose(fp);

	exit(EXIT_SUCCESS);
}