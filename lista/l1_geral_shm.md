# Geral + SHM

## Discuta o uso do paralelismo como solução para aumento de desempenho.

Como os computadores atuais contam com processadores com múltiplos núcleos e threads torna-se interessante a busca pelo paralismo visando o ganho de desempenho ao tentar distribuir as tarefas entre os diversos núcloes e threads ou fazer com os múltiplos recursos sejam utilizado. Isso pode ser dado através de instruções e trechos de código sendo executadas ao mesmo tempo, dados divididos em partes distintas que podem ser manipuladas simultaneamente, etc. Dessa forma utiliza-se os de forma mais eficiente os diversos recursos disponíveis nos computadores ganhando-se desempenho em relação a execuções sequenciais ou apenas em um único núcleo do processador.

## Considerando o particionamento de programas, descreva as técnicas de decomposição de domínio e decomposição funcional.

_A decomposição de domínio ou paralelização de dados_ é relativa a técnicas de particionamento dos dados do problema de paralelização. Preferencialmente, dados são divididos em pequenos pedaços de mesmo tamanho. Computações são particionadas a seguir, associando-as às partes dos dados que irão manipular. Particionamento resulta em conjunto de **tarefas, cada uma contendo parte dos dados e um conjunto de operações** que deverão ser realizadas sobre eles.
Operações podem requerer dados de diversas tarefas, impondo a necessidade de **mecanismos de comunicação** para transferências entre elas.
<br>Abordagens principais consistem em:

- focalizar na maior estrutura de dados, ou
- na estrutura que é acessada mais frequentemente.

Um exemplo simples, no caso da multiplicação de matrizes, é dividir os elementos da matriz que precisa ser calculada. Como se vê nos modelos de particionamento ilustrados acima, a divisão pode ocorrer em linhas, em colunas, em blocos, de forma cíclica, e com diferentes granularidades. Ou seja, pode-se pensar em particionamento linha por linha ou de blocos de linhas, elemento a elemento ou grupos de elementos.

_A decomposição funcional_ é dirigido às computações a serem realizadas. Computações devem ser divididas em tarefas disjuntas. Independência das tarefas é desejável, o que favorece a sobreposição de suas execuções.
Idealmente, dados manipulados devem ser também disjuntos. Havendo sobreposições nos dados, comunicações podem ser necessárias entre as tarefas, ou dados podem ser replicados. Neste caso, contudo, decomposição de dados talvez possa ser mais adequada.

## Descreva características do código de uma aplicação que podem ser usadas para a sua paralelização automática.

# Isso quer dizer sobre características que favorecem a paralelização ou sobre ajustes que o compilador pode fazer?

### Caracteristicas do codigos

- Presença de loops for;
- Independência dos dados;

### Caracteristicas do problema

- Modularidade (modularity): possibilidade de decomposição das atividades em componentes mais simples, desenvolvidos separadamente como módulos independentes e combinados para a realização do programa. Usando interfaces definidas, modificações dos módulos são facilitadas. Projetos modulares reduzem a complexidade dos programas e facilitam a reutilização de código.
- Concorrência (concurrency): a existência de atividades que podem ser executadas simultaneamente favorece a paralelização.
- Escalabilidade (scalability): capacidade de variar a granularidade e o número de blocos paralelos, de forma a adaptar-se a ambientes com maiores números de processadores.
- Localidade (locality): dados manipulados nas operações de cada bloco paralelo são os mesmos ou estão armazenados em locais próximos (\*)

## Relacione aspectos de aplicações paralelas que podem ser relevantes nos seus mapeamentos em uma determinada arquitetura paralela.

- Comunicações e sincronizações é preciso considerar as comunicações necessárias entre os blocos paralelos. Comunicações entre tarefas também são usadas para sincronizações, seja para controle de acesso a recursos ou para coordenar seus andamentos relativos.

- Dependência de dados existem entre blocos de código quando a ordem de suas execuções afeta o resultado do programa. Ou seja, alguma relação entre os dados ou entre as operações pode fazer com que o resultado correto do programa dependa da ordem em que as tarefas são executadas.

- Granularidade e balanceameneto de carga relativo ao balanceamento de carga trata de procurar alocar quantidades equivalentes de trabalho entre as tarefas, de forma que todas tenham atividade a executar o tempo todo. Também é relevante considerar a quantidade de carga atribuída a cada tarefa. Para tanto, observa-se que tarefas tipicamente alternam períodos de computação (processamento) com operações de comunicação e/ou sincronização com outras tarefas.
  Uma medida da carga de cada tarefa é a granularidade, que pode ser definida em função da taxa de processamento em relação às comunicações. Fina: Tarefas paralelas relativamente pequenas em termos de código e tempo de execução; Comunicações são normalmente frequentes entre as tarefas, mas com pouco volume de dados. Grossa: Tarefas relativamente grandes; Comunicação pouco frequente entre as tarefas mas, normalmente, com grandes volumes de dados.

- Aspectos de Entrada e Saída Operações de E/S são comumente inibidoras do paralelismo e demoram algumas ordens de magnitude mais do que os tempos de manipulação de dados em memória. Além disso, operações de leitura de arquivo, por exemplo podem ser afetadas pela capacidade do servidor de arquivos de realizar múltiplas requisições ao mesmo tempo.

## Considerando a arquitetura de um sistema computacional multiprocessado, discuta aspectos da interligação de processadores e memória que podem ser relevantes no desempenho de aplicações paralelas.

Pipelining(interligação) do processador está relacionado à sobreposição de várias etapas da execução de instruções para obtenção de melhor desempenho. De maneira geral, trata-se de permitir que uma instrução seja executada enquanto outra está sendo decodificada e uma outra sendo buscada da memória (fetched), por exemplo.

- Velocidade de um pipeline está limitada pela etapa mais lenta.
- Processadores tipicamente usam várias etapas em seus pipelines (10 ~ 20).
- Ocorrência de desvios (jumps) no código, contudo, pode limitar a eficiência dos pipelines e introduz a necessidade de mecanismos de predição de desvios (branch prediction).
- Penalização por erro na predição significa descarte das instruções em execução no pipeline.
- Processadores incluem ainda a possibilidade de usar múltiplos pipelines. Dificuldade, contudo, incide em como alocar as instruções aos pipelines.

_Latência da memória_

- Relação entre o número de operações e os acessos à memória pode ser um indicador da capacidade de lidar com a vazão nos acessos à memória.
- Latência nos acessos à memória pode ser contornada com prefetching, multithreading e localidade espacial dos acessos.
- O posicionamento dos dados na memória e a reorganização dos acessos podem tem impacto significativo na localidade espacial e temporal.

_Cache:_ memória de acesso rápido, posicionada próxima ao processador (entre CPU e memória principal)

- Para dados que são usados repetidamente, latência de acesso pode ser reduzida pela ação do cache.

- Aplicações com elevados volumes de acesso à memória podem ser limitadas não pela taxa de processamento da CPU mas pela velocidade de acesso à memória (memory bound). Impacto do uso do cache pode ser significativo nessas aplicações.

- Quando o padrão de acesso aos dados envolve localidade temporal, ou seja, são reusados num intervalo curto de tempo, o uso dos caches pode acelerar significativamente os tempos para que os dados estejam disponíveis no processador. Para os casos em que dados próximos são usados em sequência, o que caracteriza a localidade espacial, o uso do cache também pode gerar aumento de desempenho, uma vez que os dados sempre são trazidos da memória em blocos do tamanho de uma linha de cache (cache line size).

## Considerando o posicionamento de dados na memória em um sistema multiprocessado, discuta aspectos que podem ser relevantes no desempenho de programas parelalos.

- Acessos à memória local são menos custosos que acessos remotos.
- Operações read e write são menos onerosas que send e receive.
- Localidade trata da frequência dos acessos a dados mais próximos, com acesso mais rápido do que a dados remotos.
- Assim como concorrência e escalabilidade, localidade é um requisito fundamental em programação paralela.

## Relacione mecanismos de comunicação e sincronização entre processos (IPC) em ambientes de programação com memória compartilhada.

Mecanismos de IPC utilizando de serviços do SO para compartilharem áreas de memória que processos podem acessar, utilizar os dados armazenados e/ou alterá-los. Enquanto ambientes de memória compartilhada os programas são baseados em tarefas(threads) que compartilham seus espaços de endereçamento, podendo ser acessadas por qualquer tarefa em questão.

_IPC_
Por outro lado, há serviços do SO que podem permitir a comunicação entre processos usando estruturas baseadas em memória apenas. Diversas estruturas podem ser usadas para isso: pipes e fifos, filas de mensagens, semáforos, sockets (unix domain) e arquivos mapeados em memória. Algumas dessas estruturas são consideradas mecanismos clássicos de IPC, como as filas de mensagem e os semáforos.

Em todos esses casos, informações sendo enviadas entre processos envolvem ainda a cópia de dados do user space para kernel space, na escrita, e a cópia de dados do kernel space para o user space na leitura.

Como melhoria extrema para a comunicação entre processos, o SO permite o compartilhamento explícito de áreas de dados entre eles. Para tanto, há chamadas de sistema que tratam da alocação de áreas de memória compartilhadas. Um processo pode pedir ao SO para associar uma variável (ponteiro) à área compartilhada criada. Esse ponteiro é ajustado para apontar para o início de uma página lógica não mapeada pela tabela de páginas. Após isso, o SO ajusta a tabela de páginas para que a página indicada pelo ponteiro aponte para a página física compartilhada. Pronto! Agora, esse endereço de memória apontado pelo ponteiro indicado serve para comunicação entre processos, sem sequer ser necessário fazer cópia de dados em memória. O que um processo escreve na área de memória compartilhada pode ser lido pelo outro, e vice-versa, sem intermédio do SO. Cabe à lógica da aplicação evitar conflitos de acesso, contudo, se for relevante.

_Memória Compartilhada_

Programas paralelos no modelo com memória compartilhada são comumente baseados em tarefas, mais especificamente em threads, que compartilham seus espaços de endereçamento. Deste modo, as comunicações e sincronizações entre os blocos paralelos podem ocorrer usando estruturas mantidas em áreas de memória compartilhada e são bastante simples.

O uso desse modelo de programa paralelo é típico em sistemas computacionais multiprocessadores, que têm a memória fisicamente compartilhada entre os processadores, e é feito usando bibliotecas para gerenciamento de threads, como pthreads e OpenMP.

## Descreva mecanismos de comunicação e sincronização em ambientes com memória distribuída.

Na programação paralela no modelo com memória distribuída, o programador assume que as tarefas paralelas estão potencialmente localizadas em computadores distintos, cada qual com sua memória local. Assim, comunicações entre as tarefas, seja para passagens de dados ou para sincronizações, precisam ocorrer via passagem de mensagem pela rede .

Essas mensagens são tratadas explicitamente pelo programador, ou por uma biblioteca específica, inserindo chamadas nos códigos das tarefas.

- Point to Point: comunicação envolvendo 1 origem e 1 destino.
- One to All Broadcast: 1 transmissor enviando para todos os outros processos em broadcast (supõe rede com suporte a broadcast).
- All to All Broadcast: broadcast de todos os processos para todos os outros, em rede com broadcast.
- One to All Personalized: difusão de mensagens com envio individualizado.
- All to All Personalized: difusão de mensagens com envio individualizado.
- Collective Communications (computations): 3 tipos de operações:
- Sincronização: processos aguardam todos os membros do grupo chegarem em um ponto de sincronização.
- Transmissão de dados: broadcast, scatter/gather, all to all.
- Collective Computation (reductions): um membro do grupo coleta dados de todos os outros e realiza alguma operação (min, max, add, multiply, etc.) sobre eles.

- Broadcast: informação é para todos os processos.
- Scatter: descreve o envio de cada elemento (ou subconjunto de elementos) de um vetor para um processo separado.
- Gather: é usado para que um processo colete valores individuais de cada processo. É normalmente utilizado depois que alguma operação foi aplicada de maneira distribuída sobre esses dados.
- Reduce: realiza uma comunicação do tipo gather e executa uma operação sobre os dados coletados.

# Pedir explicação sobre essa pergunta:

## Comente a sobreposição computação / comunicação com a realização de operações de entrada e saída de dados assíncronas.

_Sobrecarga de comunicação_

- gasto de tempo com comunicação: empacotamento, envio e/ou recebimento de dados;
- necessidade de mecanismos para sincronização de envio e recebimento, com possíveis tempos ociosos à espera de concluir transmissão;
- caso as comunicações saturem a capacidade dos meios de transmissão, outros problemas de desempenho podem surgir na aplicação.

# OpenMP

## Como é definida uma região paralela com OpenMP?

_Conceito_

A paralelização de trechos de códigos é feita como o uso de diretivas. Uma diretiva se aplica ao bloco de código imediatamente abaixo dela e cada diretiva pode ter ainda diferentes cláusulas (clauses), que controlam aspectos da aplicação desta diretiva, como o grau de paralelismo e a forma de paralelização.

_Implementacao_

Isso pode ser feito com a diretiva parallel, especificada como uma pragma no código. Vale observar que as linhas com pragmas são simplesmente ignoradas se o suporte específico não for habilitado na compilação.

```c
int main ()
{
  .. Código serial, executado por apenas 1 thread, como usual
  ...
  // Uso da diretiva parallel para criar uma região paralela:
  #pragma omp parallel
  {
 Seção paralela, executada por todas as threads do time
    printf("Hello, world!\n");
  }
  // Ao fim do bloco de código da região paralela, a thread master espera pela conclusão das demais
  // Apenas thread master (aquela que encontrou a região paralela e criou o time) prossegue execução
  printf("Goodbye\n");
  ...
}
```

## Como é determinado o grau de paralelismo (número de tarefas) que será empregado num trecho de código paralelo?

_Conceito_

When the initial thread encounters a parallel construct, it creates a team of threads, with the initial thread becoming the master of the team. All program statements enclosed by the parallel construct are executed in parallel by each thread in the team, including all routines called from within the enclosed statements.

_Codigo_

```c
int main ()
{
  .. Código serial, executado por apenas 1 thread, como usual
  ...
  // Uso da diretiva parallel para criar uma região paralela:
  #pragma omp parallel num_threads(4)
  {
 Seção paralela, executada por todas as threads do time
    printf("Hello, world!\n");
  }
  // Ao fim do bloco de código da região paralela, a thread master espera pela conclusão das demais
  // Apenas thread master (aquela que encontrou a região paralela e criou o time) prossegue execução
  printf("Goodbye\n");
  ...
}
```

## O que fazem as chamadas omp_get_num_threads() e omp_get_thread_num()?

_omp_get_num_threads_

returns the number of threads in the team executing the parallel region to which the routine region binds.

_omp_get_thread_num_

returns the thread number of the calling thread, within the team executing the parallel region to which the routine region binds. The thread number is an integer between 0 and one less than the value returned by omp_get_num_threads, inclusive. The thread number of the master thread of the team is 0. The routine returns 0 if it is called from the sequential part of a program.

## Para que serve e como funciona a diretiva single ? Como ela é aplicada numa região paralela?

_Conceito_

Aplicada dentro de uma região paralela, a diretiva single especifica que o código associado deve ser executado por apenas uma thread no time. Fica a critério da API determinar qual será, não sendo necessariamente a master. Theads no time que não executam a diretiva single esperam no final do código associado, exceto se a cláusula nowait for especificada.

_Codigo_

```c
#pragma omp single [clause ...]  newline
  structured_block

int main()
{
   int a;
   ...
#pragma omp parallel shared(a,vet) private(i)
{
   ...                         // Todas as threads do time executam essa parte
   #pragma omp single          // Só uma thread do time vai executar esse bloco
   {
      srand(time(NULL));
   }
                         // Uma barreira é usada aqui, se a cláusula nowait não for especificada
   ...                         // Todas as threads do time executam essa parte
   opt = rand();
   ...
} // fim da região paralela
   ...                         // Só a master thread prossegue
   return(0);
}
```

## Como funciona o modelo de divisão de trabalho com a diretiva sections no OpenMP?

_Conceito_

a diretiva sections permite especificar seções dentro dessa região que devem ser divididas entre as threads do time.

Cada section é executada apenas uma vez, por qualquer uma das threads no time. Dependendo do número de seções e do número de threads no time, pode haver threads executando mais de uma seções, assim como é possível que alguma thread não tenha seção para executar. O escalonamento das seções às threads depende da implementação do compilador e do suporte em tempo de execução.

Uma barreira é inserida automaticamente ao final das sections, exceto se a cláusula nowait for especificada.

_Código_

```c

#pragma omg sections [clause ...]  newline
{
  [#pragma omp section newline]
    bloco_de_código
  [#pragma omp section newline]
    bloco_de_código


  #pragma omp parallel shared(a,b) private(i,tnum)
  {
    ... // Todas as threads do time executam esse trecho

    #pragma omp sections
    {
      #pragma omp section
      {
         faça_isso();
      }
      #pragma omp section
      {
         faça_aquilo();
      }
      #pragma omp section
      {
         faça_ainda_outra_coisa();
      }
    }   // Fim das seções

    ... // Todas as threads do time executam esse threcho

  }    // Fim da região paralela
}


```

## Como funciona o modelo de divisão de trabalho com a diretiva for no OpenMP?

_Conceito_

A diretiva for especifica que as iterações do loop imediatamente abaixo devem ser executadas em paralelo, dividindo-as entre as threads do time.

Emitida dentro de uma região paralela, esta diretiva deve ser sucedida especificamente por um comando for.

_Código_

```c
#pragma omp parallel    // private(i)  // Não precisa declarar i como privada; isso é automático
  {
    // Todas as threads do time executam esse trecho do bloco de código de maneira replicada
    id = omp_get_thread_num();

    // Construção worksharing (for) divide as iterações entre as threads do time
    // Variável de controle do for (i) é feita privada para cada thread, automaticamente!
    // Diretiva for deve aparecer dentro de uma região paralela
    #pragma omp for         // O único comando permitido na linha abaixo da diretiva for é um for :-)
    for (i=0; i < num_it; i++) {
        printf("Thread %d tratando iteração %d\n", id, i);
        vet[i] = 2 * i;
    }
    // todas as threads replicam esse trecho de código, fora do for, mas dentro da região paralela

   } // fim da região paralela

```

```c
  #pragma omp parallel for      // O único comando permitido nesta forma de declaração paralela é o for
  for (i=0; i < NUM; i++) {     // (*)
    printf("Thread %d tratando iteração %d\n", omp_get_thread_num(), i);
    vet[i] = 2 * i;
  }
```

## Como podem ser divididas as iterações de um loop for entre tarefas usando OpenMP?

De acordo com as especificações, o comportamento da divisão de iterações pode variar como segue:

- STATIC: Loop iterations are divided into pieces of size chunk and then statically assigned to threads. If chunk is not specified, the iterations are evenly (if possible) divided contiguously among the threads.
- DYNAMIC: Loop iterations are divided into pieces of size chunk, and dynamically scheduled among the threads; when a thread finishes one chunk, it is dynamically assigned another. The default chunk size is 1.
- GUIDED: For a chunk size of 1, the size of each chunk is proportional to the number of unassigned iterations divided by the number of threads, decreasing to 1. For a chunk size with value k (greater than 1), the size of each chunk is determined in the same way with the restriction that the chunks do not contain fewer than k iterations (except for the last chunk to be assigned, which may have fewer than k iterations). The default chunk size is 1.
- RUNTIME: The scheduling decision is deferred until runtime by the environment variable OMP_SCHEDULE. It is illegal to specify a chunk size for this clause.
- AUTO: The scheduling decision is delegated to the compiler and/or runtime system.

## Quais políticas podem ser usadas para essa atribuição e como funcionam?

_Conceito_
A definição do escalonamento das iterações pode ocorrer de três formas: via cláusula na diretiva for, vi chamada à função omp_set_schedule(omp_sched_tkind, intchunk_size) e via variável de ambiente OMP_SCHEDULE.

## Para que serve a cláusula de redução, por exemplo, quando aplicada a um for paralelo?

## O que são tasks em OpeMP? Como são criadas e como se relacionam com as threads de uma região paralela?

Além de permitir a criação de tarefas implícitas, associadas às threads de um time numa região paralela, OpenMP permite a criação de tarefas sob demanda, dinamicamente, de maneira circunstancial ou recursiva, sem saber a priori quantas tarefas serão necessárias. Isso é feito com a diretiva task.

Na programação com tarefas (tasks), programador concentra-se em como particionar o código em blocos, que podem ser executados em paralelo; ou seja, em quais trechos de código podem ser transformados em tarefas independentes.

Nesse modelo, cabe ao sistema em tempo de execução determinar como serão o escalonamento e a execução das tarefas (tasks) criadas.

Resumidamente, uma tarefa (task) é um trecho de código a mais para ser executado por alguma das threads de um time já existente. Ou seja, a chamada task não cria uma nova thread para o time atual, mas apenas insere uma atividade a mais (tarefa) na lista de tarefas que o time de threads da região paralela atual tem para executar.

_Criacao_
A diretiva task é usada dentro de uma região paralela e define uma tarefa específica. Essa tarefa pode ser executada pela thread que encontrar essa diretiva, ou deferida para execução por qualquer outra thread no time de threads corrente.

Quando uma task é criada, se houver alguma thread ociosa no time da região paralela atual, a task pode ser executada imediatamente. Caso contrário, fica a critério do sistema em tempo de execução de OpenMP determinar quando esta task será executada.

```c
int
calc(int start, int finish)
{
   int i, dif;
   int sum = 0, sum1, sum2;

   if (finish-start <= MIN_BLK) {    // calcula
      // printf("Calculando %d -> %d\n", start, finish);

      for (i=start; i < finish; i++)
         sum++;

   } else{                           // divide, criando novas tasks
      // printf("Dividindo %d -> %d\n", start, finish);

      dif = finish - start;

      // variável de retorno deve ser compartilhada para que o valor retornado
      // não seja salvo em uma nova variável da nova task

      #pragma omp task shared(sum1)
      sum1 = calc(start, start + dif / 2);

      #pragma omp task shared(sum2)
      sum2 = calc(finish - dif / 2, finish);

      // Taskwait funciona como uma barreira para tasks, fazendo com que o fluxo de execução
      // seja pausado até que as tasks tenham sido completadas
      // taskwait faz com que threads suspendam o que estavam fazendo e passem a atuar nas tasks da fila.
      // The taskwait construct specifies a wait on the completion of child tasks of the current task.
      // Once all tasks have been processed, threads resume their normal execution flow.
      #pragma omp taskwait
      sum = sum1 + sum2;
   }

   return sum;
}
```

## Como são definidas variáveis privadas para cada thread de uma região paralela?

## Como são definidas variáveis compartilhadas entre as threads de uma região paralela?

## Como é possível prover exclusão mútua na manipulação de variáveis compartilhas entre as threads de uma região paralela?

## Para que serve e como funciona a primitiva atomic em OpenMP?
