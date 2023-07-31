#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "printlong.h"
#include "printindexlong.h"
#include "printindexlongrecurse.h"
#include "printlongrecurse.h"
#include "printrecurse.h"
#include "printindexrecurse.h"
// #include <time.h>
#define MAX 256

struct fileArgs{
    char options[8];    // Options for ls command, e.g., 'i' for inode number display
    // So, there are 8 possible combinations of the letters 'i', 'R', and 'l':
    // i , R,  l, iR, Rl, il, iRl, no options
    char file_list[MAX][MAX];   // Array to store a list of files (currently not used)
};

// Function to list files in the specified directory with provided options
void ls(struct fileArgs myFile, int op_a, int op_l){
    struct dirent *d;
    // printf("line 18 TESTIGN : %s\n",myFile.file_list[0]);
    if(strcmp(myFile.file_list[0],"\0")==0){
        // DIR *dh = opendir(".");
        DIR *dh = opendir("/Users/willting/Desktop/300-asn4");
        // need the opendir to take in the file path argument
        if (dh == NULL) {
        perror("Error: Unable to read directory");
        exit(1);
    }
        // need the opendir to take in the file path argument

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
                else if (myFile.options[i] == 'l'){
                    // printf("line 36 here\n");
                    // printf("d_name: %s\n",d->d_name);
                    // print myFile.options[i]
                    printf("myFile.options[i]: %c\n",myFile.options[i]);
                    char full_path1[256];
                    snprintf(full_path1, sizeof(full_path1), "%s/%s", "/Users/willting/Desktop/300-asn4", d->d_name);
                    printlong(full_path1);
                    // printlong("/Users/willting/Desktop/300-asn4");
                    
                }
                else if (myFile.options[i] == 'li' || myFile.options[i] == 'il'){
                    // printf("line 36 here\n");
                    // printf("d_name: %s\n",d->d_name);
                    char full_path2[256];
                    snprintf(full_path2, sizeof(full_path2), "%s/%s", "/Users/willting/Desktop/300-asn4", d->d_name);
                    printindexlong(full_path2);
                    // printlong("/Users/willting/Desktop/300-asn4");
                    
                }
                else if (myFile.options[i] == 'iRl' || myFile.options[i] == 'ilR' || myFile.options[i] == 'liR' || myFile.options[i] == 'lRi' || myFile.options[i] == 'Ril' || myFile.options[i] == 'Rli'){
                    // printf("line 36 here\n");
                    // printf("d_name: %s\n",d->d_name);
                    char full_path3[256];
                    snprintf(full_path3, sizeof(full_path3), "%s/%s", "/Users/willting/Desktop/300-asn4", d->d_name);
                    printindexlongrecurse(full_path3);
                    // printlong("/Users/willting/Desktop/300-asn4");
                    
                }

                else if (myFile.options[i] == 'lR' || myFile.options[i] == 'Rl'){
                    // printf("line 36 here\n");
                    // printf("d_name: %s\n",d->d_name);
                    char full_path4[256];
                    snprintf(full_path4, sizeof(full_path4), "%s/%s", "/Users/willting/Desktop/300-asn4", d->d_name);
                    printlongrecurse(full_path4);
                    // printlong("/Users/willting/Desktop/300-asn4");
                    
                }
                else if (myFile.options[i] == 'R'){
                    // printf("line 36 here\n");
                    // printf("d_name: %s\n",d->d_name);
                    char full_path5[256];
                    snprintf(full_path5, sizeof(full_path5), "%s/%s", "/Users/willting/Desktop/300-asn4", d->d_name);
                    printrecurse(full_path5);
                    // printlong("/Users/willting/Desktop/300-asn4");
                    
                }

                else if (myFile.options[i] == 'iR' || myFile.options[i] == 'Ri'){
                    // printf("line 36 here\n");
                    // printf("d_name: %s\n",d->d_name);
                    printf("myFile.options[i]: %c\n",myFile.options[i]);
                    char full_path6[256];
                    snprintf(full_path6, sizeof(full_path6), "%s/%s", "/Users/willting/Desktop/300-asn4", d->d_name);
                    printindexrecurse(full_path6);
                    // printlong("/Users/willting/Desktop/300-asn4");
                    
                }
                
            }
            
            printf("%s ", d->d_name);   // Print the name of the file/directory
            
            if (op_l){
                printf("\n");   // Print a newline if long format option (op_l) is set
            }
        }
        closedir(dh);
    }
    
    else{    
        for(int i=0;myFile.file_list[i]!=NULL;i++){   
            DIR *dh = opendir(myFile.file_list[i]);
            // Check if the directory can be opened
            if (!dh){
                if (errno == ENOENT){
                    perror("Error: Nonexistent files or directories");
                }
                else{
                    perror("Error: Unable to read directory");
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
    }
}

