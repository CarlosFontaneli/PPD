/*
 ** Universidade Federal de São Carlos
 ** Departamento de Computação
 ** Prof. Hélio Crestana Guardia
 ** Sistemas Operacionais 2
 */

/*
 ** Programa :
 ** Comando:
 ** Objetivo: observar passagem de valores para função da thread.
              Nesse caso, usa-se vetor em que cada thread preenche
              os resultados da sua operação.
*/

/*
  Algoritmo de Monte Carlo para cálculo do valor de pi
  Dados um círculo de raio 1 inserido em um quadrado de lado 2.
  Relação entre pontos aleatórios que estão dentro do círculo
  e pontos no quadrado pode ser usada para cálculo de pi.

  Relação entre as áreas: (p*r^2)/(4*r^2)
  Considerando r=1: (p/4)=pontos_no_círculo/total_pontos
  p=4*pontos_no_círculo/total_pontos

  Considerando a geração de valores aleatórios entre 0 e 1 (raio)
  para as coordenadas x e y de um ponto, usa-se a equação do teorema
  de Pitágoras para determinar se ponto está dentro do círculo ou não:
  z^2=x^2+y^2
*/

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_THREADS 128
#define SAMPLES 1000000

int ___num_threads;
int _samples;
int __num_threads = 8;
long _hits[MAX_THREADS];

void *
partial_sum(void *arg)
{
  long ind = (long)arg;
  int num_samples_thread = _samples / __num_threads, hits, i;
  double x, y;
  unsigned short xi[3];

  xi[0] = 0.5;
  xi[1] = 0.5;
  xi[2] = ind;

  hits = 0;
  for (i = 0; i < num_samples_thread; i++)
  {
    x = erand48(xi);
    y = erand48(xi);
    if (x * x + y * y <= 1.0)
      hits++;
  }
  _hits[ind] = hits;
  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  long t;
  int total_hits = 0, status;

  if (argc > 1)
  {
    ___num_threads = atoi(argv[1]);
    if (___num_threads < 0 || ___num_threads > MAX_THREADS)
    {
      printf("Erro: max %d threads\n", MAX_THREADS);
      return (EXIT_FAILURE);
    }
  }
  else
    ___num_threads = MAX_THREADS;
  if (argc > 2)
    _samples = atoi(argv[2]);
  else
    _samples = SAMPLES;

  // vetor de pthread_t para salvamento dos identificadores das threads
  pthread_t threads[__num_threads];

  for (t = 0; t < __num_threads; t++)
  {
    status = pthread_create(&threads[t], NULL, partial_sum, (void *)t);

    // Checagem de criação da thread
    if (status)
    {
      printf("Falha da criacao da thread %ld (%d)\n", t, status);
      return (1);
    }
  }

  // loop de espera pelo término da execução das threads
  for (t = 0; t < __num_threads; t++)
  {

    // join ignorando o valor de retorno
    status = pthread_join(threads[t], NULL);

    // Somas parciais
    total_hits += _hits[t];

    if (status)
    {
      printf("Erro em pthread_join da thread %ld (%d)\n", t, status);
      return (2);
    }
  }
  /*
  - Fazer um loop de criação de threads;
  - Definir o numero de samples por thread;
  - Fazer as somas parciais dos hits e juntar dps na soma total;
  */

  // pi=4*pontos_no_circulo/total
  // printf("Pi: %.16f\n",(float)4*(float)total_hits/(float)SAMPLES /* * ___num_threads */);
  printf("Pi: %.16f\n", (float)4 * (float)total_hits / (float)_samples /* * ___num_threads */);

  return (0);
}
