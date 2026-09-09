# Scheduler

Simulador de escalonamento de tarefas periódicas usando os algoritmos de Rate e Edf

## Arquivos

**main.c**

Responsável pelo programa principal, leitura e validação do arquivo de entrada e controle da simulação.

**tarefa.c**

Responsável pela criação, execução e controle das instâncias das tarefas, incluindo seus deadlines.

**tarefa.h**

Contém as estruturas Tarefa e Instancia e as declarações das funções relacionadas às tarefas.

**simulacao.c**

Responsável pelo controle das instâncias durante a simulação e pela seleção da tarefa de maior prioridade de acordo com o algoritmo.

**simulacao.h**

possui a estrutura de controle das instâncias e as declarações das funções utilizadas na simulação.

**resultado.c**

Responsável pelo registro dos períodos de execução e pela geração dos arquivos de saída com a execução, deadlines perdidos, execuções concluídas e instâncias que permaneceram pendentes no final da simulação.

**resultado.h**

possui a estrutura utilizada para registrar as execuções e as declarações das funções relacionadas à geração dos resultados.

## Compilação

Para compilar o programa deve executar:

```text
make
```

make gera o executável:

```text
scheduler
```

Para remover o executável compilado:

```text
make clean
```

## Execução

O algoritmo deve ser informado na execução.

Para utilizar Rate:

```text
./scheduler rate arquivo.txt
```

Para utilizar Edf:

```text
./scheduler edf arquivo.txt
```

O programa gera um arquivo de saída de acordo com o algoritmo utilizado:

```text
rate_gllb.out ou edf_gllb.out
```

Durante uma execução normal o programa não imprime o resultado da simulação no terminal.

## Entrada

A primeira linha do arquivo informa o tempo total da simulação.

Cada linha seguinte representa uma tarefa no formato:

```text
[nome] [periodo] [deadline] [burst]
```

Ex:

```text
100
ATT 20 12 8
NAV 50 30 15
```

Os valores devem ser positivos e obedecer: C <= D <= P

## Testes

Os arquivos utilizados nos testes estão na pasta testes.

**voo.txt**

Utiliza o exemplo apresentado na atividade.

**comparacao.txt**

Utilizado para comparar os comportamentos dos algoritmos rate e edf. Nesse teste, o rate perde deadlines de uma tarefa enquanto o edf consegue concluir as instâncias.

**invalido.txt**

Utilizado para testar arquivo com campo faltando.

**killed.txt**

Utilizado para verificar o comportamento de uma instância que permanece incompleta quando a simulação termina.

**desempate.txt**

Utilizado para verificar a regra de desempate pela ordem das tarefas no arquivo.

**nao_numerico.txt**

Utilizado para testar valor não numérico.

**nao_positivo.txt**

Utilizado para testar valor não positivo.

**deadline_maior_periodo.txt**

Utilizado para testar a condição D > P.

**burst_maior_deadline.txt**

Utilizado para testar a condição C > D.

Ex de execução dos testes:

```text
./scheduler rate testes/comparacao.txt
./scheduler edf testes/comparacao.txt
```

Também foram realizados testes com várias situações de entrada inválida como número incorreto de argumentos, algoritmo inválido, arquivo inexistente, campos faltando, valores que não são números ou que não são positivos e casos em que D > P ou C > D.

## Sistema operacional

O programa foi desenvolvido e testado em ambiente Linux utilizando Ubuntu no WSL.
