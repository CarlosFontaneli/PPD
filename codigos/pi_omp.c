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
#include <omp.h>

#define MAX_THREADS 128
// #define SAMPLES 2147483647
// #define SAMPLES INT_MAX
#define SAMPLES 1000000

int _num_threads;
int _samples;
long total_hits = 0;

int main(int argc, char **argv)
{
  double x, y;
  unsigned short xi[3];

  // pthread_t threads[MAX_THREADS];
  // int hits[MAX_THREADS];

  if (argc > 1)
  {
    _num_threads = atoi(argv[1]);
    if (_num_threads < 0 || _num_threads > MAX_THREADS)
    {
      printf("Erro: max %d threads\n", MAX_THREADS);
      return (EXIT_FAILURE);
    }
  }
  else
    _num_threads = MAX_THREADS;
  if (argc > 2)
    _samples = atoi(argv[2]);
  else
    _samples = SAMPLES;

    // double erand48(unsigned short xsubi[3]);
    // nd48() and erand48() functions return non-negative double-precision floating-point
    // values uniformly distributed between [0.0, 1.0).
    // The functions erand48(), nrand48() and jrand48() require the calling program to
    // provide storage for the successive Xi values in the array argument xsubi.
    // The functions are initialized by placing the initial value of Xi into the array
    // before calling the function for the first time.

    // xi[0]=0.5; xi[1]=0.5; xi[2]=ind;

    /* #pragma omp parallel private(x, y)
      {
        long local_hits = 0;
        for (long i = 0; i < _samples; i++)
        {
          x = erand48(xi);
          y = erand48(xi);
          if (x * x + y * y <= 1.0)
            // #pragma omp critical
            // #pragma omp atomic
            // total_hits++;
            local_hits++;
        }
    #pragma omp atomic
        total_hits += local_hits;
      } */

#pragma omp parallel for private(x, y) reduction(+ \
                                                 : total_hits)

  for (long i = 0; i < _samples; i++)
  {
    x = erand48(xi);
    y = erand48(xi);
    if (x * x + y * y <= 1.0)
      total_hits++;
  }

  // pi=4*pontos_no_circulo/total
  // printf("Pi: %.16f\n",(float)4*(float)total_hits/(float)SAMPLES /* * _num_threads */);
  printf("Pi: %.16f\n", (float)4 * (float)total_hits / (float)_samples /* * _num_threads */);

  return (0);
}
