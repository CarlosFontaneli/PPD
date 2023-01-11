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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>

#define NELEM (1 << 30)
#define NTHREADS 1
#define MAX_THREADS 128

int __num_threads;
float *vet;
long double *_partial_sums;
long int nelem;

void *partial_sum(void *arg)
{
  int nelem_thread, ind = (long)arg, i;
  long double sum = 0;

  nelem_thread = nelem / __num_threads;
  for (i = 0; i < nelem_thread; i++)
  {
    sum += vet[i * ind];
  }
  _partial_sums[ind] = sum;
  pthread_exit(NULL);
}

void *fill_array(void *arg)
{
  int nelem_thread, ind = (long)arg, i;

  nelem_thread = nelem / __num_threads;
  for (i = 0; i < nelem_thread; i++)
  {
    vet[i * ind] = 1;
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  int status;
  long double sum = 0;
  long t = 0;

  // int nthreads;
  // pthread_t *threads;

  if (argc > 1)
  {
    __num_threads = atoi(argv[1]);
    if (__num_threads < 0 || __num_threads > MAX_THREADS)
    {
      printf("Erro: max %d threads\n", MAX_THREADS);
      return (EXIT_FAILURE);
    }
  }
  else
    __num_threads = MAX_THREADS;

  if (argc > 2)
    nelem = atoi(argv[2]);
  else
    nelem = NELEM;

  // alocação do vetor
  vet = (float *)malloc(nelem * sizeof(float));
  _partial_sums = (long double *)malloc(__num_threads * sizeof(long double));
  // vetor de pthread_t para salvamento dos identificadores das threads
  pthread_t threads[__num_threads];

  if (!vet)
  {
    perror("Erro na alocacao do vetor de elementos.");
    return EXIT_FAILURE;
  }

  // gerar sempre a mesma sequência de valores?
  srand(42);

  // atribuição de valores (0<val<=1) aos elementos do vetor
  for (t = 0; t < __num_threads; t++)
  {
    status = pthread_create(&threads[t], NULL, fill_array, (void *)t);

    // Checagem de criação da thread
    if (status)
    {
      printf("Falha da criacao da thread %ld (%d)\n", t, status);
      return (1);
    }
    else
    {
      printf("Preenchimento do vetor: thread %ld\n", t);
    }
  }

  // loop de espera pelo término da execução das threads
  for (t = 0; t < __num_threads; t++)
  {

    // join ignorando o valor de retorno
    status = pthread_join(threads[t], NULL);

    if (status)
    {
      printf("Erro em pthread_join da thread %ld (%d)\n", t, status);
      return (2);
    }
  }

  /* for (i = 0; i < nelem; i++)
    vet[i] = 1; */

  for (t = 0; t < __num_threads; t++)
  {
    status = pthread_create(&threads[t], NULL, partial_sum, (void *)t);

    // Checagem de criação da thread
    if (status)
    {
      printf("Falha da criacao da thread %ld (%d)\n", t, status);
      return (1);
    }
    else
    {
      printf("Soma dos elementos: thread %ld\n", t);
    }
  }

  // loop de espera pelo término da execução das threads
  for (t = 0; t < __num_threads; t++)
  {

    // join ignorando o valor de retorno
    status = pthread_join(threads[t], NULL);

    // Somas parciais
    printf("Soma parcial %ld = %Lf\n", t, _partial_sums[t]);
    sum += _partial_sums[t];

    if (status)
    {
      printf("Erro em pthread_join da thread %ld (%d)\n", t, status);
      return (2);
    }
  }
  /* // soma sequencial dos elementos do vetor
  sum = 0;
  for (i = 0; i < nelem; i++)
    sum += vet[i]; */

  // Como fazer a soma em paralelo?
  // Criar as threads, atribuindo uma parte do vetor para cada uma delas
  // loop de pthread_create...
  // for(i=0; i < nthreads; i++) {
  //		...
  // }

  // Juntar as somas parciais? Em qual tarefa?
  // loop de pthread_join...
  // for(i=0; i < nthreads; i++) {
  //		...
  // }

  // libera o vetor de ponteiros para as threads
  // free(threads);
  printf("sum: %Lf\n", sum);

  free(vet);

  return (0);
}
