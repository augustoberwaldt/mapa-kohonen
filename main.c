#include <stdio.h>
#include <stdlib.h>
#include "libs/file.h";


int main()
{

    File_setPathFile(".\\iris.txt");
    b_file *b  =  File_readFile();

   printf("%f" ,b[1].number[0]);
   printf("%f" ,b[1].number[1]);
   printf("%f" ,b[1].number[2]);
   printf("%f" ,b[1].number[3]);

   return 0;
}
