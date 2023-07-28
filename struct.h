#include <stdio.h>

#define MAX 256

struct fileArgs{
    char* options;
    char* file_list[MAX];
};