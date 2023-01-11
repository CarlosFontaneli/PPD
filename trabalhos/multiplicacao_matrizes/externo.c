#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

float *A, *B, *C;

int main(int argc, char *argv[])
{
  int lin_a, col_a, lin_b, col_b, lin_c, col_c;
  int i, j, k;
  printf("Linhas A: ");
  scanf("%d", &lin_a);
  printf("Colunas A / Linhas B: ");
  scanf("%d", &col_a);
  lin_b = col_a;
  printf("Colunas B: ");
  scanf("%d", &col_b);
  printf("\n");

  lin_c = lin_a;
  col_c = col_b;

  A = (float *)malloc(lin_a * col_a * sizeof(float));
  B = (float *)malloc(lin_b * col_b * sizeof(float));
  C = (float *)malloc(lin_c * col_c * sizeof(float));

  srandom(time(NULL));

  for (i = 0; i < lin_a * col_a; i++)
    A[i] = (float)rand() / (float)RAND_MAX;

  for (i = 0; i < lin_b * col_b; i++)
    B[i] = (float)rand() / (float)RAND_MAX;

  printf("Matrizes com 1000 linhas e colunas \n");

  printf("Executando programa paralelo: paralelismo apenas no loop  externo \n");
#pragma omp parallel for
  for (i = 0; i < lin_c; i++)
    for (j = 0; j < col_c; j++)
    {
      C[i * col_c + j] = 0;
      for (k = 0; k < col_a; k++)
        C[i * col_c + j] = C[i * col_c + j] + A[i * col_a + k] * B[k * col_b + j];
    }

  return (0);
}