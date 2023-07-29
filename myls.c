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
   int num=0;
   while((option=getopt(argc,argv,"ilR"))!=-1){
      switch (option)
      {
      case 'i':
         myFile.options[num] = 'i';
         num++;
         printf("i\n");
         break;
      case 'l':
         myFile.options[num] = 'l';
         num++;
         printf("l\n");
         break;
      case 'R':
         myFile.options[num] = 'R';
         num++;
         printf("R\n");
         break;
      default:
         break;
      }
   }
   for(int i = 0; i<argc-num;i++){
     strcpy(myFile.file_list[i],argv[num+i]);
   }
   for(int i=0;i<3;i++){
      printf("testing option: %c\n",myFile.options[i]);
      printf("testing direciory %s\n",myFile.file_list[i]);
   }
   ls(myFile,".",0,1);
}