#ifndef SAIDA
#define SAIDA

#include <stdio.h>
#include "atividade.h"

void criar_arquivo_saida(char tipo);

void tarefa_finalizada(char tipo, int tempo, char nome[100]);

void tarefa_interrompida(char tipo, int tempo, char nome[100]);

void deadline_atingida(char tipo, int tempo, char nome[100]);

void tempo_acabou(char tipo, int tempo, char nome[100]);

void idle(char tipo, int tempo);

void valores_tarefa_finalizada(char tipo, Atividade *head);

void valores_tarefa_deadline(char tipo, Atividade *head);

void valores_tarefa_morta(char tipo, Atividade *head);

#endif