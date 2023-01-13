## O que são extensões SIMD de processadores?

IMD (Single Instruction, Multiple Data) é um modo de execução que está associado à realização simultânea da mesma operação sobre diferentes dados (paralelismo de dados).

## De que maneira essas extensões são usadas em programas escritos em C?

_Compiler Auto-Vectorization_
Dependendo das operações que precisam ser executadas, o compilador tenta aplicar a vetorização do código quando são usadas as opções de otimização -O2 ou superiores.

Basic block vectorization, aka SLP, is enabled by the flag -ftree-slp-vectorize, and requires the same platform dependent flags as loop vectorization. Basic block SLP is enabled by default at -O3 and when -ftree-vectorize is enabled.

## Caracterize e ilustre um trecho de código que tem potencial para ser beneficiado pelo uso da vetorização.

```c
int a[256], b[256], c[256];
foo (int n, int x) {
   int i;

   /* feature: support for unknown loop bound  */
   /* feature: support for loop invariants  */
   for (i=0; i<n; i++){
      b[i] = x;
   }

   /* feature: general loop exit condition  */
   /* feature: support for bitwise operations  */
   while (n--){
      a[i] = b[i]&c[i]; i++;
   }
}
```

## Qual é o efeito do uso das extensões SIMD num programa?
