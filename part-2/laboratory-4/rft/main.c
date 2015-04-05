#include <stdio.h>

#include "rft.h"


int main (int argc, char *argv[])
{
    char *dir;

    if (argc < 2)
        dir = ".";
    else if (argc == 2)
        dir = argv[1];
    else
        return 1;

    printf("scanning [%s]\n", dir);

    return rft(dir);
}