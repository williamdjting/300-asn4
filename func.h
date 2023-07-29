#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#define MAX 256

struct fileArgs{
    char options[3];    // Options for ls command, e.g., 'i' for inode number display
    char file_list[MAX][MAX];   // Array to store a list of files (currently not used)
};

// Function to list files in the specified directory with provided options
void ls(struct fileArgs myFile, const char *dir, int op_a, int op_l){
    struct dirent *d;
    DIR *dh = opendir(dir);

    // Check if the directory can be opened
    if (!dh){
        if (errno == ENOENT){
            perror("Directory does not exist");
        }
        else{
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);   // Exit the program with failure status
    }

    // Loop through directory entries and list files
    while ((d = readdir(dh)) != NULL){
        // Skip hidden files if op_a is not set (0)
        if (!op_a && d->d_name[0] == '.'){
            continue;
        }

        // Iterate through the options provided in myFile struct
        for (int i = 0; myFile.options[i] != '\0'; i++){
            if (myFile.options[i] == 'i'){
                printf("%ju         ", d->d_ino);  // Display inode number
            }
        }
        
        printf("%s ", d->d_name);   // Print the name of the file/directory
        
        if (op_l){
            printf("\n");   // Print a newline if long format option (op_l) is set
        }
    }

    closedir(dh);   // Close the directory after listing its contents
}

