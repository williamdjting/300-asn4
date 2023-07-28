#include "secret_headers.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )  {
   struct fileArgs myFile;
   if( argc == 2 ) {
      if(argv[1][0] == '-'){
         myFile.options = argv[1];
      }
      printf("%s\n",myFile.options);
   }
   else if( argc > 2 ) {
      if(argv[1][0] == '-'){
         myFile.options = argv[1];
         
      }
      
   }
   else {
      system("ls -1");
   }
}