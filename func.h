#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#define MAX 256

struct fileArgs{
    char options[3];
    char file_list[MAX][MAX];
};
void ls(struct fileArgs myFile, const char *dir, int op_a, int op_l){
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
        for(int i=0;myFile.options[i]!=NULL;i++){
            if(myFile.options[i]=='i'){
                printf("%ju         ",d->d_ino);
            }
        }
        printf("%s ", d->d_name);
        if(op_l){
            printf("\n");
        }
    }
    
}