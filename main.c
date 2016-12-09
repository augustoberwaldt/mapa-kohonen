#include <stdio.h>
#include <stdlib.h>
#include "libs/file.h";
#include <time.h>
#define line 20
#define column 20
#define were 100

float getRandom();
void print_r(float network_clone[column][line][4]);
void save_file(float network_clone[column][line][4], char name[]);
void printi_r(int network_activation_clone[column][line]);
void test (int network_activ_clone[line][column] , float network_tmp[line][column][4]  ,float network[line][column][4]);
/**
 *
 * main
 *
 **/
int main()
{

    int option = 0;



    srand(time(NULL));
    float network[20][20][4];
    int network_activation[20][20];
    float network_tmp[20][20][4];
    int l = 0, c = 0 ,
        close_line   = 0,
        close_column = 0,
        count = 0,
        i = 0
        ;
    int sAdressError_line   = 0,
        sAdressError_column = 0,
        sAdressError_data = 0,
        lfile = 0;

    float error = 0 ,
          less_error = 0 ,
          rate       = 0.008,
          close_rate = 0.003;

    /** inicializando o matriz **/
    for (l=0; l< line; l++) {
       for (c=0; c<column; c++) {
           network[l][c][0] = 0;
           network[l][c][1] = 0;
           network[l][c][2] = 0;
           network[l][c][3] = 0;
           network_activation[l][c] = 0;
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

    save_file(network , "./network.txt");
    save_file(network , "./network.csv");
    do {
        printf("Escolha a opcao desejada : \n");
        printf("Treinar Rede digite 1 \n");
        printf("Testar Rede digite  2 \n");
        printf("Sair digite  0 \n");
        scanf("%i",&option);

        if (option == 1) {
            do {
                for (lfile = 0;  lfile < File_getSizeFile(); lfile++) {
                    for (l = 0; l<line; l++) {
                       for (c = 0; c<column; c++) {
                          for (i = 0;  i < File_numWidth;  i++) {
                            network_tmp[l][c][i] = network[l][c][i] - data[lfile].number[i] ;
                          }

                          error  =  fabs(network_tmp[l][c][0]) +  fabs(network_tmp[l][c][1]) +
                                    fabs(network_tmp[l][c][2]) +  fabs(network_tmp[l][c][3]);


                          if (error < less_error || (l== 0 && c == 0)) {
                                less_error = error;
                                sAdressError_line = l;
                                sAdressError_column = c;
                                sAdressError_data  = lfile;
                          }
                       }
                    }

                    /** atualiza neuronio vencedor  **/
                    for (i = 0;  i <File_numWidth;  i++) {
                        network[sAdressError_line][sAdressError_column][i] =
                             network[sAdressError_line][sAdressError_column][i] +
                               (rate * (data[sAdressError_data].number[i] - network[sAdressError_line][sAdressError_column][i]));
                    }

                    /** atualiza neuronio vizinhos  **/
                    for (close_line = (sAdressError_line - 1); close_line <= (sAdressError_line + 1); close_line++) {

                          for (close_column = (sAdressError_line - 1); close_column <= (sAdressError_line + 1); close_column++) {

                                if ((close_line >= 0 && close_line < line) &&
                                    (close_column >= 0 && close_column < column)) {
                                      for (i = 0;  i <File_numWidth;  i++) {
                                          network[close_line][close_column][i] =
                                            network[close_line][close_column][i] +
                                                (close_rate * (data[sAdressError_data].number[i] - network[close_line][close_column][i]));

                                      }
                                 }
                          }
                    }
               }

               count++;
           } while(count <= were);
       } else if (option == 2) {
          test(network_activation, network_tmp, network);
             for (l=0; l< line; l++) {
               for (c=0; c<column; c++) {
                   network_activation[l][c] = 0;
               }
             }
       }

    } while(option != 0);

     save_file(network , "./network_after.txt");
     save_file(network , "./network_after.csv");

    return 0;
}

void test (int network_activ_clone[line][column] , float network_tmp[line][column][4]  ,float network[line][column][4])
{
       int lfile, l, c, i ,
       sAdressError_line = 0 ,
       sAdressError_column = 0;
       b_file *data  =  File_readFile();
       float error , less_error;
       for (lfile = 0;  lfile < File_getSizeFile(); lfile++) {
            for (l = 0; l<line; l++) {
               for (c = 0; c<column; c++) {
                  for (i = 0;  i < File_numWidth;  i++) {
                    network_tmp[l][c][i] = network[l][c][i] - data[lfile].number[i] ;
                  }

                  error  =  fabs(network_tmp[l][c][0]) +  fabs(network_tmp[l][c][1]) +
                          fabs(network_tmp[l][c][2]) + fabs(network_tmp[l][c][3]);


                  if (error < less_error || (l== 0 && c == 0)) {
                        less_error = error;
                        sAdressError_line = l;
                        sAdressError_column = c;
                  }
               }
            }

            network_activ_clone[sAdressError_line][sAdressError_column]++;
        }
        printi_r(network_activ_clone);
}

void print_r(float network_clone[column][line][4])
{
    int l, c;
    for (l=0; l< line; l++) {
       for (c=0; c< column; c++) {
           printf(
                  "[%.3f %.3f %.3f %.3f] \n",
                  network_clone[l][c][0],
                  network_clone[l][c][1],
                  network_clone[l][c][2],
                  network_clone[l][c][3]

                  );

       }
       printf("\n");
    }
}
void printi_r(int network_activation_clone[column][line])
{
    int l, c;
    for (l=0; l< line; l++) {
       for (c=0; c< column; c++) {
           printf(
                  "%4d",
                  network_activation_clone[l][c]
                  );

       }
       printf("\n");
    }
}

/**
 *
 *Salva dados no arquivo
 **/
void save_file(float network_clone[column][line][4], char name[])
{
    int l, c;
    FILE *arq = fopen(name, "w+");
    for (l=0; l< line; l++) {
       for (c=0; c< column; c++) {
              fprintf(arq, "%.3f, %.3f, %.3f, %.3f, \n" ,  network_clone[l][c][0],
                  network_clone[l][c][1],
                  network_clone[l][c][2],
                  network_clone[l][c][3]
              );
       }
       printf("\n");
    }
    fclose(arq);
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

