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

## Descreva mecanismos de comunicação e sincronização em ambientes com memória distribuída.

## Comente a sobreposição computação / comunicação com a realização de operações de entrada e saída de dados assíncronas.

# OpenMP

## Como é definida uma região paralela com OpenMP?

## Como é determinado o grau de paralelismo (número de tarefas) que será empregado num trecho de código paralelo?

## O que fazem as chamadas omp_get_num_threads() e omp_get_thread_num()?

## Para que serve e como funciona a diretiva single ? Como ela é aplicada numa região paralela?

## Como funciona o modelo de divisão de trabalho com a diretiva sections no OpenMP?

## Como funciona o modelo de divisão de trabalho com a diretiva for no OpenMP?

## Como podem ser divididas as iterações de um loop for entre tarefas usando OpenMP?

## Quais políticas podem ser usadas para essa atribuição e como funcionam?

## Para que serve a cláusula de redução, por exemplo, quando aplicada a um for paralelo?

## O que são tasks em OpeMP? Como são criadas e como se relacionam com as threads de uma região paralela?

## Como são definidas variáveis privadas para cada thread de uma região paralela?

## Como são definidas variáveis compartilhadas entre as threads de uma região paralela?

## Como é possível prover exclusão mútua na manipulação de variáveis compartilhas entre as threads de uma região paralela?

## Para que serve e como funciona a primitiva atomic em OpenMP?
