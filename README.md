# Escalonamento em Tempo Real

## Como compilar e executar

para compilar escreva:

- _make clean_
- _make rate_ ou _make edf_

para executar:

- _./rate [namefile]_ ou _./edf [namefile]_

para testar:

- *make test_rate* ou *make test_edf*

## Descrição dos arquivos:

- rate.c: estrutura principal do algoritmo rate-monotonic.

- edf.c: estrutura principal do algoritmo earliest-deadline-first.

- atividade.h: define a struct de tarefas e as funções para executar das tarefas de acordo com o algoritmo utilizado.

- atividade.c: contêm as funções da biblioteca atividade.h. A função para adicionar as tarefas em uma lista encadeada e as funções para executar as tarefas com o escalonamento de acordo com o algoritmo.

- saida.h: define as funções de escrita no arquivo de saída.

- saida.c: contêm as funções da biblioteca saida.h. As funções de escrita das ocorrências das terafas dentro do arquivo final de acordo com o algoritmo usado.

## O código foi implementado em um sistema operacional **LINUX**