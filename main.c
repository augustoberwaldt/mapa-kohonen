#include <stdio.h>
#include <stdlib.h>
#include "libs/file.h";
#include <time.h>

float getRandom();

/**
 *
 * main
 *
 **/
int main()
{
    srand(time(NULL));
    float network[20][20][4];
    float network_tmp[20][20][4];
    int error = 0 , less_error = 0,l = 0, c = 0;


    /** inicializando o matriz **/
    for (l=0; l<20; l++) {
       for (c=0; c<20; c++) {
           network[l][c] = 0;
           network_tmp[l][c] = 0;
       }
    }

    /** realizando o parse do arquivo **/
    File_setPathFile(".\\iris.txt");
    b_file *data  =  File_readFile();

    /** gerando  aleatoriamente os valores **/
    for (l=0; l<20; l++) {
       for (c=0; c<20; c++) {
            network[l][c][0] = getRandom();
            network[l][c][1] = getRandom();
            network[l][c][2] = getRandom();
            network[l][c][3] = getRandom();
       }
    }


    for (l=0; l<20; l++) {
       for (c=0; c<20; c++) {
           network_tmp[l][c][0] = network[l][c][0] - data[l].number[0] ;
           network_tmp[l][c][1] = network[l][c][1] - data[l].number[1] ;
           network_tmp[l][c][2] = network[l][c][2] - data[l].number[2] ;
           network_tmp[l][c][3] = network[l][c][3] - data[l].number[3] ;
           error  =  network_tmp[l][c][0] +  network_tmp[l][c][1] + network_tmp[l][c][2] + network_tmp[l][c][3];

           if (error < less_error || (l== 0 && c == 0)) {
                less_error = error;
           }
       }
    }



    return 0;
}

/**
 *
 * gera numero aleatorio
 *
 **/
float getRandom()
{
    return (float)(rand() % ((int)File_maxNumber * 10))/ 10;
}

