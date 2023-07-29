#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

void ls(const char *dir, int op_a, int op_l){
    struct  dirent *d;
    DIR *dh = opendir(dir);
    if (!dh){
        if (errno=ENOENT){
            perror("Directory does not exit");
        }
        else{
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }
    while((d = readdir(dh))!=NULL){
        if(!op_a && d->d_name[0]=='.'){
            continue;
        }
        printf("%s ", d->d_name);
        if(op_l){
            printf("\n");
        }
    }
    
}