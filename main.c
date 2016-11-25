#include <stdio.h>
#include <stdlib.h>
#include "libs/file.h";
int main()
{

    File_setPathFile(".\\iris.txt");
    File_readFile();

    return 0;
}
