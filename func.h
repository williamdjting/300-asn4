#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h> 
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
    int num_files;  // Number of files in the file_list array
};

// Function to list files in the specified directory with provided options
void ls(struct fileArgs myFile, int op_a, int op_l){
    int i;
    for(i=0;i<myFile.num_files;i++){
        printf("TESTING FILELIST %s\n",myFile.file_list[i]);
        struct stat fileStat;
        if (stat(myFile.file_list[i],&fileStat)<0){
            perror("Error getting file stats");
            return;
        }
        else if (S_ISREG(fileStat.st_mode)) {
            char directory[MAX];
            strncpy(directory,myFile.file_list[i],sizeof(directory));
            dirname(directory);
            DIR *dir = opendir(directory);
            if (dir == NULL) {
                perror("Error opening directory");
                return;
            }
            if(strcmp(myFile.options, "i")==0){
                printf("%ld         ",fileStat.st_ino);
            }
            printf("%s \n", basename(myFile.file_list[i]));
        }
        
        // printf("line 18 TESTIGN : %s\n",myFile.file_list[0]);
        else if(S_ISDIR(fileStat.st_mode)){   
            printf("WROKING\n");

            struct dirent *d; 
            if(strcmp(myFile.file_list[i],"\0")==0){
                // DIR *dh = opendir(".");
                DIR *dh = opendir(".");
                // need the opendir to take in the file path argument
                // if (dh == NULL) {
                // perror("Error: Unable to read directory");
                // exit(1);
            // }
                // need the opendir to take in the file path argument

                // Loop through directory entries and list files
                while ((d = readdir(dh)) != NULL){
                    // Skip hidden files if op_a is not set (0)
                    if (!op_a && d->d_name[0] == '.'){
                        continue;
                    }

                    // Iterate through the options provided in myFile struct
                    // for (int i = 0; myFile.options[i] != '\0'; i++){
                        if (strcmp(myFile.options, "i")==0){
                            printf("%ju         ", d->d_ino);  // Display inode number
                        }
                        else if (strcmp(myFile.options , "l")==0){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            // print myFile.options[i]
                            printf("myFile.options: %s\n",myFile.options);
                            char full_path1[256];
                            snprintf(full_path1, sizeof(full_path1), "%s/%s", ".", d->d_name);
                            printlong(full_path1);
        
                            
                        }
                        else if ( (strcmp(myFile.options , "li")==0) || (strcmp(myFile.options, "il")==0)){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            char full_path2[256];
                            snprintf(full_path2, sizeof(full_path2), "%s/%s", ".", d->d_name);
                            printindexlong(full_path2);
            
                            
                        }
                        else if ( (strcmp(myFile.options , "iRl")==0) || (strcmp(myFile.options , "ilR")==0) || (strcmp(myFile.options , "liR")==0) || (strcmp(myFile.options ,  "lRi")==0) || (strcmp(myFile.options , "Ril")==0) || (strcmp(myFile.options, "Rli")==0 )){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            char full_path3[256];
                            snprintf(full_path3, sizeof(full_path3), "%s/%s", ".", d->d_name);
                            printindexlongrecurse(full_path3);

                            
                        }

                        else if ((strcmp(myFile.options, "lR")==0) || (strcmp(myFile.options , "Rl")==0)){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            char full_path4[256];
                            snprintf(full_path4, sizeof(full_path4), "%s/%s", ".", d->d_name);
                            printlongrecurse(full_path4);

                            
                        }
                        else if (strcmp(myFile.options, "R")==0){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            char full_path5[256];
                            snprintf(full_path5, sizeof(full_path5), "%s/%s", ".", d->d_name);
                            printrecurse(full_path5);
                            
                        }

                        else if ((strcmp(myFile.options, "iR")==0) || (strcmp(myFile.options, "Ri")==0)){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            printf("myFile.options: %s\n",myFile.options);
                            char full_path6[256];
                            snprintf(full_path6, sizeof(full_path6), "%s/%s", ".", d->d_name);
                            printindexrecurse(full_path6);
                            
                        }
                        
                    // }
                    
                    printf("%s ", d->d_name);   // Print the name of the file/directory
                    
                    if (op_l){
                        printf("\n");   // Print a newline if long format option (op_l) is set
                    }
                }
                closedir(dh);
            }
            
            else{    
                for(i; i  < myFile.num_files;i++){   
                    DIR *dh = opendir(myFile.file_list[i]);
                    // Check if the directory can be opened
                    if (!dh){
                        if (errno == ENOENT){
                            perror("Error: Nonexistent files or directories");
                            // print myFile.file_list[i]
                            printf("line 129 myFile.file_list[i]: %s\n",myFile.file_list[i]);
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
                        // for (int i = 0; myFile.options[i] != '\0'; i++){
                        //     if (myFile.options[i] == 'i'){
                        //         printf("%ju         ", d->d_ino);  // Display inode number
                        //     }
                        // }
                        if (strcmp(myFile.options, "i")==0){
                            printf("%ju         ", d->d_ino);  // Display inode number
                        }
                        else if (strcmp(myFile.options , "l")==0){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            // print myFile.options[i]
                            printf("myFile.options: %s\n",myFile.options);
                            char full_path1[256];
                            snprintf(full_path1, sizeof(full_path1), "%s/%s", myFile.file_list[i], d->d_name);
                            printlong(full_path1);
                            // printlong("/Users/willting/Desktop/300-asn4");
                            
                        }
                        else if ( (strcmp(myFile.options , "li")==0) || (strcmp(myFile.options, "il")==0)){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            char full_path2[256];
                            snprintf(full_path2, sizeof(full_path2), "%s/%s", myFile.file_list[i], d->d_name);
                            printindexlong(full_path2);
                            // printlong("/Users/willting/Desktop/300-asn4");
                            
                        }
                        else if ( (strcmp(myFile.options , "iRl")==0) || (strcmp(myFile.options , "ilR")==0) || (strcmp(myFile.options , "liR")==0) || (strcmp(myFile.options ,  "lRi")==0) || (strcmp(myFile.options , "Ril")==0) || (strcmp(myFile.options, "Rli")==0 )){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            char full_path3[256];
                            snprintf(full_path3, sizeof(full_path3), "%s/%s", myFile.file_list[i], d->d_name);
                            printindexlongrecurse(full_path3);
                            // printlong("/Users/willting/Desktop/300-asn4");
                            
                        }

                        else if ((strcmp(myFile.options, "lR")==0) || (strcmp(myFile.options , "Rl")==0)){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            char full_path4[256];
                            snprintf(full_path4, sizeof(full_path4), "%s/%s", myFile.file_list[i], d->d_name);
                            printlongrecurse(full_path4);
                            // printlong("/Users/willting/Desktop/300-asn4");
                            
                        }
                        else if (strcmp(myFile.options, "R")==0){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            char full_path5[256];
                            snprintf(full_path5, sizeof(full_path5), "%s/%s", myFile.file_list[i], d->d_name);
                            printrecurse(full_path5);
                            // printlong("/Users/willting/Desktop/300-asn4");
                            
                        }

                        else if ((strcmp(myFile.options, "iR")==0) || (strcmp(myFile.options, "Ri")==0)){
                            // printf("line 36 here\n");
                            // printf("d_name: %s\n",d->d_name);
                            printf("myFile.options: %s\n",myFile.options);
                            char full_path6[256];
                            snprintf(full_path6, sizeof(full_path6), "%s/%s", myFile.file_list[i], d->d_name);
                            printindexrecurse(full_path6);
                            // printlong("/Users/willting/Desktop/300-asn4");
                            
                        }
                        
                        printf("%s ", d->d_name);   // Print the name of the file/directory
                        
                        if (op_l){
                            printf("\n");   // Print a newline if long format option (op_l) is set
                        }
                    }
                    printf("\n");

                    closedir(dh);   // Close the directory after listing its contents
                }
            }
        }
    }

}

