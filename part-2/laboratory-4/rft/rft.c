#include "rft.h"

#include <sys/stat.h>

#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define TAB_SIZE 2


static
int recursive_file_tree (const char *dirname, int depth)
{
    struct dirent *dirent;
    struct stat   statbuf;
    DIR *dp;

    if ((dp = opendir(dirname)) == NULL) {
        fprintf(stderr, "cannot open directory [%s]\n", dirname);
        return 1;
    }

    chdir(dirname);

    while ((dirent = readdir(dp)) != NULL) {
        lstat(dirent->d_name, &statbuf);

        if (S_ISDIR(statbuf.st_mode)) {
            if (!strcmp(".", dirent->d_name) 
            || !strcmp("..", dirent->d_name))
                continue;

            printf("%*s%s/\n", depth * TAB_SIZE, "", dirent->d_name);

            recursive_file_tree(dirent->d_name, depth + 1);
        } else {
            printf("%*s%s\n", depth * TAB_SIZE, "", dirent->d_name);
        }
    }

    chdir("..");
    closedir(dp);

    return 0;
}

int rft (const char *dirname)
{
    return recursive_file_tree(dirname, 0);
}