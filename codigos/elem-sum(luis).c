/*
 ** Universidade Federal de São Carlos
 ** Departamento de Computação
 ** Prof. Hélio Crestana Guardia
 */

/*
 ** Programa : soma dos elementos de um vetor
 ** Comando:
 ** Objetivo: observar passagem de valores para função da thread.
              Nesse caso, usa-se vetor em que cada thread preenche
              os resultados da sua operação.
*/

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NELEM (1 << 30)
#define NTHREADS 1
#define MAX_THREADS 128

void *partial_sum(void *arg);

typedef struct {
  double *result;
  int start_index;
  int end_index;
  float *array;
} partial_sum_arg_t;

int main(int argc, char *argv[]) {
  int i;
  float *vet;
  long int nelem;
  int nthreads;

  // int nthreads;
  pthread_t *threads;

  if (argc > 1)
    nelem = atoi(argv[1]);
  else
    nelem = NELEM;

  if (argc > 2) {
    nthreads = atoi(argv[2]);
    if (nthreads <= 0 || nthreads > MAX_THREADS) {
      printf("Erro: max %d threads\n", MAX_THREADS);
      return EXIT_FAILURE;
    }
  } else {
    nthreads = NTHREADS;
  }

  // alocação dos ponteiros para threads
  threads = (pthread_t *)malloc(sizeof(pthread_t *));

  // alocação do vetor
  vet = (float *)malloc(nelem * sizeof(float));

  if (!vet) {
    perror("Erro na alocacao do vetor de elementos.");
    return EXIT_FAILURE;
  }

  // gerar sempre a mesma sequência de valores?
  srand(time(NULL));

  printf("Iniciando vetor...\n");
  // atribuição de valores (0<val<=1) aos elementos do vetor
  for (i = 0; i < nelem; i++)
    vet[i] = (float)((float)rand() / (float)RAND_MAX);

  // Como fazer a soma em paralelo?
  // Criar as threads, atribuindo uma parte do vetor para cada uma delas
  // loop de pthread_create...
  double results[nthreads];
  partial_sum_arg_t args[nthreads];
  int elems_per_thread = nelem / nthreads;

  printf("Iniciando execução das threads...\n");
  for (i = 0; i < nthreads; i++) {
    args[i].result = &results[i];
    args[i].start_index = elems_per_thread * i;
    args[i].end_index = args[i].start_index + elems_per_thread;
    args[i].array = vet;

    pthread_create(&threads[i], NULL, partial_sum, (void *)&args[i]);
  }

  // Juntar as somas parciais? Em qual tarefa?
  // loop de pthread_join...
  for (i = 0; i < nthreads; i++) {
    pthread_join(threads[i], NULL);
  }

  // libera o vetor de ponteiros para as threads
  free(threads);

  // coletando resultados
  double sum = 0;
  for (int i = 0; i < nthreads; i++) {
    sum += results[i];
  }

  // soma sequencial dos elementos do vetor
  /* double sum_seq = 0; */
  /* for (i = 0; i < nelem; i++) */
  /*   sum_seq += vet[i]; */

  /* printf("Sequential sum: %f\n", sum_seq); */

  printf("Sum: %f\n", sum);

  free(vet);

  return (0);
}

void *partial_sum(void *arg) {
  partial_sum_arg_t *args = (partial_sum_arg_t *)arg;

  double result = 0;

  for (int i = args->start_index; i < args->end_index; i++)
    result += args->array[i];

  printf("Resultado parcial: %f\n", result);
  *args->result = result;

  pthread_exit(NULL);
}
