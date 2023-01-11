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
#include <omp.h>

#define NELEM (1 << 30)
#define NTHREADS 1
#define MAX_THREADS 128

int __num_threads;

int main(int argc, char *argv[])
{
	int i;
	float *vet;
	double sum;
	long int nelem;

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

	if (!vet)
	{
		perror("Erro na alocacao do vetor de elementos.");
		return EXIT_FAILURE;
	}

	// gerar sempre a mesma sequência de valores?
	srand(42);

// atribuição de valores (0<val<=1) aos elementos do vetor
#pragma omp parallel for
	for (i = 0; i < nelem; i++)
		// vet[i] = 1;
		vet[i] = (float)((float)rand() / (float)RAND_MAX);

	// soma sequencial dos elementos do vetor
	sum = 0;
#pragma omp parallel for reduction(+ \
																	 : sum)
	for (i = 0; i < nelem; i++)
		sum += vet[i];

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

	printf("sum: %f\n", sum);

	free(vet);

	return (0);
}
