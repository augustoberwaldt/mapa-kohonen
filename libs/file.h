#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pathFile[100];

typedef struct base_file{
   int number[4];
}b_file;


/**
 * funcao responsavel por calcular o tamanho do arquivo
 * @param File arquivo
 * @return int
 */
int sizeFile(FILE *arquivo)
{
    long posicaoAtual = ftell(arquivo);
    long tamanho;
    fseek(arquivo, 0, SEEK_END);
    tamanho = ftell(arquivo);
    fseek(arquivo, posicaoAtual, SEEK_SET);
    return (int) tamanho;
}
void File_setPathFile(char path[])
{
    strcpy(pathFile, path);
}

b_file* File_readFile()
{
  FILE *arq = fopen(pathFile, "r");

  if (!arq) {
        printf("\n Erro na abertura do arquivo.\n");
        exit (1);
  }


  int fileSize   = sizeFile(arq);
  char *line = (char*) malloc(sizeof(char*)  * fileSize);
  char *result;
  int rows = 0;
  const char s[2] = ",";
  b_file  *b_f = (b_file*) malloc(sizeof(b_file)  * fileSize);
  while (!feof(arq)) {

    result = fgets(line, 100, arq);

    if (!result){
      	continue;
	}
    char *token = strtok(result, s);
    int count = 0;
    while (token != NULL) {
        float value =  atof(token);
        b_f[rows].number[count] = value;
        token = strtok(NULL, s);
        count++;
    }

    rows++;
  }

  return b_f;
}

