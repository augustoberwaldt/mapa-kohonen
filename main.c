#include <stdio.h>
#include <stdlib.h>
#include "libs/file.h";
#include <time.h>
#define line 20
#define column 20
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
    int l = 0, c = 0 ,
        close_line   = 0,
        close_column = 0 ;
    int sAdressError_line   = 0,
        sAdressError_column = 0,
        sAdressError_data = 0,
        lfile = 0;

    float error = 0 ,
          less_error = 0 ,
          rate       = 0.5,
          close_rate = 0.3;

    /** inicializando o matriz **/
    for (l=0; l< line; l++) {
       for (c=0; c<column; c++) {
           network[l][c][0] = 0;
           network[l][c][1] = 0;
           network[l][c][2] = 0;
           network[l][c][3] = 0;
           network_tmp[l][c][0] = 0;
           network_tmp[l][c][1] = 0;
           network_tmp[l][c][2] = 0;
           network_tmp[l][c][3] = 0;
       }
    }

    /** realizando o parse do arquivo **/
    File_setPathFile(".\\iris.txt");
    b_file *data  =  File_readFile();

    /** gerando  aleatoriamente os valores **/
    for (l=0; l<line; l++) {
       for (c=0; c<column; c++) {
            network[l][c][0] = getRandom();
            network[l][c][1] = getRandom();
            network[l][c][2] = getRandom();
            network[l][c][3] = getRandom();
       }
    }

    for (lfile = 0;  lfile < File_getSizeFile(); lfile++) {
        for (l=0; l<line; l++) {
           for (c=0; c<column; c++) {
               network_tmp[l][c][0] = network[l][c][0] - data[lfile].number[0] ;
               network_tmp[l][c][1] = network[l][c][1] - data[lfile].number[1] ;
               network_tmp[l][c][2] = network[l][c][2] - data[lfile].number[2] ;
               network_tmp[l][c][3] = network[l][c][3] - data[lfile].number[3] ;

               error  =  fabs(network_tmp[l][c][0]) +  fabs(network_tmp[l][c][1]) +
                      fabs(network_tmp[l][c][2]) + fabs(network_tmp[l][c][3]);

               if (error < less_error || (l== 0 && c == 0)) {
                    less_error = error;
                    sAdressError_line = l;
                    sAdressError_column = c;
                    sAdressError_data  = lfile;
               }
           }
        }

        /** atualiza neuronio vencedor  **/
        network[sAdressError_line][sAdressError_column][0] =
             network[sAdressError_line][sAdressError_column][0] +
               (rate * (data[sAdressError_data].number[0])- network[sAdressError_line][sAdressError_column][0]);

        network[sAdressError_line][sAdressError_column][1] =
             network[sAdressError_line][sAdressError_column][1] +
               (rate * (data[sAdressError_data].number[1])- network[sAdressError_line][sAdressError_column][1]);

        network[sAdressError_line][sAdressError_column][2] =
             network[sAdressError_line][sAdressError_column][2] +
               (rate * (data[sAdressError_data].number[2])- network[sAdressError_line][sAdressError_column][2]);

        network[sAdressError_line][sAdressError_column][3] =
             network[sAdressError_line][sAdressError_column][3] +
               (rate * (data[sAdressError_data].number[3])- network[sAdressError_line][sAdressError_column][3]);


        for (close_line = (sAdressError_line - 1); close_line <= (sAdressError_line + 1); close_line++) {

          for (close_column = (sAdressError_line - 1); close_column <= (sAdressError_line + 1); close_column++) {

            if ((close_line >= 0 && close_line < line) &&
                (close_column >= 0 && close_column < column)) {

                  network[close_line][close_column][0] =
                    network[close_line][close_column][0] +
                        (close_rate * (data[sAdressError_data].number[0])- network[close_line][close_column][0]);

                  network[close_line][close_column][1] =
                    network[close_line][close_column][1] +
                        (close_rate * (data[sAdressError_data].number[1])- network[close_line][close_column][1]);

                  network[close_line][close_column][2] =
                    network[close_line][close_column][2] +
                        (close_rate * (data[sAdressError_data].number[2])- network[close_line][close_column][2]);

                  network[close_line][close_column][3] =
                    network[close_line][close_column][0] +
                        (close_rate * (data[sAdressError_data].number[0])- network[close_line][close_column][0]);

            }
          }
        }
   }

   for (l=0; l< line; l++) {
       for (c=0; c< column; c++) {
           printf(
                  "[%f %f %f %f] \n",
                  network[l][c][0],
                  network[l][c][1],
                  network[l][c][2],
                  network[l][c][3]

                  );
       }
       printf("\n");
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

