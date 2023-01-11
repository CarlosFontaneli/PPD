## Semana 1

_Modelos de programação_

- Memória Compartilhada: baseados em tarefas, mais especificamente em threads, que compartilham seus espaços de endereçamento. Deste modo, as comunicações e sincronizações entre os blocos paralelos podem ocorrer usando estruturas mantidas em áreas de memória compartilhada e são bastante simples. O uso desse modelo de programa paralelo é típico em sistemas computacionais multiprocessadores, que têm a memória fisicamente compartilhada entre os processadores, e é feito usando bibliotecas para gerenciamento de threads, como pthreads e OpenMP.

- Memória Distribuída: o programador assume que as tarefas paralelas estão potencialmente localizadas em computadores distintos, cada qual com sua memória local. Assim, comunicações entre as tarefas, seja para passagens de dados ou para sincronizações, precisam ocorrer via passagem de mensagem pela rede . Essas mensagens são tratadas explicitamente pelo programador, ou por uma biblioteca específica, inserindo chamadas nos códigos das tarefas. Esse modelo é chamado de programação com passagem de mensagem (Message Passing Parallel Programming) e é comumente implementado com bibliotecas de programação como MPI.

- Paralelismo de Dados: usa-se elementos de processamento para realizar as mesmas operações, simultaneamente, sobre partes disjuntas dos dados. Aceleradores, como as GPUs, têm sido usadas para esse modelo de programação. Nesses casos, criam-se programas que têm partes de seus processamentos, tipicamente aqueles que envolvem manipulações vetoriais, transferidos para aceleradores, como as GPUs, interligados ao sistema computacional.

- Hibrída: É claro que o modelo de programação adotado pode ser uma combinação desses modelos já descritos.

_Granularidade_: está relacionada ao volume de operações nos blocos de código que podem ser executados em paralelo.

- Fina: Tarefas paralelas relativamente pequenas em termos de código e tempo de execução; Comunicações são normalmente frequentes entre as tarefas, mas com pouco volume de dados.

- Grossa: Tarefas relativamente grandes; Comunicação pouco frequente entre as tarefas mas, normalmente, com grandes volumes de dados.

Com granularidade fina há potencialmente mais atividades que podem ser executadas simultaneamente. Se for preciso sincronizar as atividades, contudo, pode ser que as sobrecargas de comunicação entre esses blocos prejudiquem o desempenho da aplicação.

Como veremos, o grau de paralelismo mais adequado para uma aplicação paralela vai estar relacionado ao grau de paralelismo da arquitetura do sistema computacional onde ela será executada.

Desempenho está condicionado também à obtenção do melhor balanceamento entre processamento e comunicação, ou entre execução de instruções e acessos à memória para leitura ou escrita.

_Características que favorecem a paralelização_:

- Modularidade (modularity): possibilidade de decomposição das atividades em componentes mais simples, desenvolvidos separadamente como módulos independentes e combinados para a realização do programa. Usando interfaces definidas, modificações dos módulos são facilitadas. Projetos modulares reduzem a complexidade dos programas e facilitam a reutilização de código.
- Concorrência (concurrency): a existência de atividades que podem ser executadas simultaneamente favorece a paralelização.
- Escalabilidade (scalability): capacidade de variar a granularidade e o número de blocos paralelos, de forma a adaptar-se a ambientes com maiores números de processadores.
- Localidade (locality): dados manipulados nas operações de cada bloco paralelo são os mesmos ou estão armazenados em locais próximos (\*)

_Produto escalar, efeitos da posição na memória_

Como se sabe, quando uma instrução do processador faz uma referência de leitura a um dado na memória, não apenas o conteúdo desta posição de memória é trazido para dentro do processador, mas é feita uma cópia de uma sequência de bytes correspondente ao tamanho de uma linha de cache da memória para o cache do processador.

Na arquitetura ia64, cada linha de cache comumente têm tamanho de 64 bytes.

Assim, em acessos subsequentes a posições da memória consecutivas a onde está armazenado o valor solicitado já vão estar presentes no cache do processador. Com isso, os tempos de acesso a esses dados são menores e o desempenho do programa tende a ser melhor.
