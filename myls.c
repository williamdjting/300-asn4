#include "secret_headers.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <time.h>

int main( int argc, char *argv[] )  {
   struct fileArgs myFile;

   int option;
   int num = 0;

   // Process command-line options using getopt
   while ((option = getopt(argc, argv, "ilR")) != -1) {
      switch (option) {
         case 'i':
            // Option 'i' is present, add it to the options array in myFile
            myFile.options[num] = 'i';
            num++;
            printf("i\n"); // Debugging: Print to confirm the 'i' option is found
            break;
         case 'l':
            // Option 'l' is present, add it to the options array in myFile
            myFile.options[num] = 'l';
            num++;
            printf("l\n"); // Debugging: Print to confirm the 'l' option is found
            break;
         case 'R':
            // Option 'R' is present, add it to the options array in myFile
            myFile.options[num] = 'R';
            num++;
            printf("R\n"); // Debugging: Print to confirm the 'R' option is found
            break;
         default:
            // Invalid option or missing argument, do nothing for now
            break;
      }
   }
   if(num==0){
      ls(myFile, 0, 1);
   }
   // Store the remaining command-line arguments as file_list in myFile struct
   for (int i = 0; i < argc - num; i++) {
      strcpy(myFile.file_list[i], argv[num + i]);
      printf("MAIN TESTING: %s\n",argv[num + i]);
   }

   // Debugging: Print the options and file_list
   for (int i = 0; i < 3; i++) {
      printf("testing option: %c\n", myFile.options[i]);
      printf("testing directory: %s\n", myFile.file_list[i]);
   }

   // Call the ls function with the provided options and file_list
   // ls(myFile, 0, 1); // Listing current directory with options: 'i', long format

   return 0;
}
