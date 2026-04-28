#ifndef ATIVIDADE
#define ATIVIDADE
#include <time.h>

typedef struct Atividade {
    char nome[100];
    int periodo;
    int burst;
    int burst_restante;
    int tempo_executado;
    int burst_executado;
    int acabou;
    int iniciar_burst;
    int atingiu_deadline;
    int finalizou;
    int morta;
    struct Atividade *prox;
} Atividade;

void adicionar_atividade(Atividade **head, char nome[100], int periodo, int burst);

void printar_atividades(Atividade *head);

void liberar_atividades(Atividade *head);

void executando_atividades_edf(char tipo, float tempo_total, Atividade **head);

void executando_atividades_rate(char tipo, float tempo_total, Atividade **head);

#endif