#ifndef ATIVIDADE
#define ATIVIDADE
#include <time.h>

typedef struct Atividade {
    char nome[100];
    double periodo;
    double burst;
    double burst_restante;
    time_t tempo_executado;
    time_t burst_executado;
    int acabou;
    int iniciar_burst;
    int atingiu_deadline;
    int finalizou;
    int morta;
    struct Atividade *prox;
} Atividade;

void adicionar_atividade(Atividade **head, char nome[100], double periodo, double burst);

void printar_atividades(Atividade *head);

void liberar_atividades(Atividade *head);

void executando_atividades_edf(char tipo, float tempo_total, Atividade **head);

void executando_atividades_rate(char tipo, float tempo_total, Atividade **head);

#endif