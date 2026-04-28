#include "atividade.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "saida.h"

void adicionar_atividade(Atividade **head, char nome[100], int periodo, int burst) {
    Atividade *novo = (Atividade *)malloc(sizeof(Atividade));
    if (novo != NULL) {
        strcpy(novo->nome, nome);
        novo->periodo = periodo;
        novo->burst = burst;
        novo->burst_restante = burst;
        novo->tempo_executado = -periodo;
        novo->acabou = 1;
        novo->iniciar_burst = 0;
        novo->atingiu_deadline = 0;
        novo->finalizou = 0;
        novo->morta = 0;
        novo->prox = NULL;
        if (*head == NULL) {
            *head = novo;
        } else {
            Atividade *aux = *head;
            while(aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }
}

void printar_atividades(Atividade *head) {
    while(head != NULL) {
        printf("%s %d %d\n", head->nome, head->periodo, head->burst);
        head = head->prox;
    }
}

void liberar_atividades(Atividade *head) {
    Atividade *aux;
    while(head != NULL) {
        aux = head;
        head = head->prox;
        free(aux);
    }
}

void executando_atividades_edf(char tipo, float tempo_total, Atividade **head) {
    int tick;
    int idle_executado = 0;
    Atividade *menor_deadline;
    Atividade *burst_atual = NULL;
    int idle_atual = 0;

    for (tick = 0; tick < tempo_total; tick++) {

        Atividade *aux = *head;
        menor_deadline = NULL;

        while (aux != NULL) {
            if ((tick - aux->tempo_executado) >= aux->periodo) {
                if (burst_atual == aux && burst_atual->acabou == 0) {
                    int valor_executado = tick - burst_atual->burst_executado;
                    deadline_atingida(tipo, valor_executado, burst_atual->nome);
                    burst_atual->atingiu_deadline++;
                    burst_atual->morta++;
                }
                aux->acabou = 0;
                aux->tempo_executado = tick;
                aux->iniciar_burst = 1;
                aux->burst_restante = aux->burst;
            }

            if (menor_deadline == NULL && aux->acabou == 0) {
                menor_deadline = aux;
            }
            if (menor_deadline != NULL) {
                if (aux->acabou == 0) {
                    if (aux->tempo_executado + aux->periodo < (menor_deadline->tempo_executado + menor_deadline->periodo)) {
                        menor_deadline = aux;
                    }
                }
            }
            
            aux = aux->prox;
        }

        if(burst_atual != menor_deadline) {
            
            if (burst_atual == NULL && idle_atual == 1) {
                int valor_executado = tick - idle_executado;
                if (valor_executado > 0) {
                    idle(tipo, valor_executado);
                }
            } else if(burst_atual != NULL && burst_atual->acabou == 0) {
                int valor_executado = tick - burst_atual->burst_executado;
                burst_atual->burst_restante = burst_atual->burst - valor_executado;
                if(burst_atual->burst_restante < 0) {
                    burst_atual->burst_restante = 0;
                }
                tarefa_interrompida(tipo, burst_atual->burst - burst_atual->burst_restante, burst_atual->nome);
            }

            if(menor_deadline != NULL) {
                menor_deadline->burst_executado = tick;
                menor_deadline->iniciar_burst = 0;
                idle_atual = 0;
            } else {
                idle_atual = 1;
                idle_executado = tick;
            }

            burst_atual = menor_deadline;
        }

        if (menor_deadline == NULL) {
            idle_atual = 1;
            burst_atual = NULL;
        } else {
            if (menor_deadline->iniciar_burst == 1) {
                menor_deadline->burst_executado = tick;
                menor_deadline->iniciar_burst = 0;
            }
            if ((tick - menor_deadline->burst_executado) >= menor_deadline->burst_restante) {
                tarefa_finalizada(tipo, menor_deadline->burst_restante, menor_deadline->nome);
                menor_deadline->finalizou++;
                menor_deadline->acabou = 1;
                menor_deadline->burst_executado = tick;
                burst_atual = NULL;
                idle_atual = 1;
                idle_executado = tick;
                tick--;
                continue;
            }
        }
    }
    if (burst_atual != NULL && burst_atual->acabou == 0) {
        int valor_executado = tick - burst_atual->burst_executado;
        tempo_acabou(tipo, valor_executado, burst_atual->nome);
        burst_atual->morta++;
    } else if (burst_atual == NULL && idle_atual == 1) {
        int valor_executado = tick - idle_executado;
        if (valor_executado > 0) {
            idle(tipo, valor_executado);
        }
    }
}

void executando_atividades_rate(char tipo, float tempo_total, Atividade **head) {
    int tick;
    int idle_executado = 0;
    Atividade *menor_periodo;
    Atividade *periodo_atual = NULL;
    int idle_atual = 0;

    for (tick = 0; tick < tempo_total; tick++) {

        Atividade *aux = *head;
        menor_periodo = NULL;

        while (aux != NULL) {
            if ((tick - aux->tempo_executado) >= aux->periodo) {
                if (periodo_atual == aux && periodo_atual->acabou == 0) {
                    int valor_executado = tick - periodo_atual->burst_executado;
                    deadline_atingida(tipo, valor_executado, periodo_atual->nome);
                    periodo_atual->atingiu_deadline++;
                    periodo_atual->morta++;
                }
                aux->acabou = 0;
                aux->tempo_executado = tick;
                aux->iniciar_burst = 1;
                aux->burst_restante = aux->burst;
            }

            if (menor_periodo == NULL && aux->acabou == 0) {
                menor_periodo = aux;
            }
            if (menor_periodo != NULL ) {
                if (aux->acabou == 0) {
                    if (aux->periodo < menor_periodo->periodo) {
                        menor_periodo = aux;
                    }
                }
            }
            
            aux = aux->prox;
        }

        if(periodo_atual != menor_periodo) {
            
            if (periodo_atual == NULL && idle_atual == 1) {
                int valor_executado = tick - idle_executado;
                if (valor_executado > 0) {
                    idle(tipo, valor_executado);
                }
            } else if(periodo_atual != NULL && periodo_atual->acabou == 0) {
                int valor_executado = tick - periodo_atual->burst_executado;
                periodo_atual->burst_restante = periodo_atual->burst - valor_executado;
                if(periodo_atual->burst_restante < 0) {
                    periodo_atual->burst_restante = 0;
                }
                tarefa_interrompida(tipo, periodo_atual->burst - periodo_atual->burst_restante, periodo_atual->nome);
            }

            if(menor_periodo != NULL) {
                menor_periodo->burst_executado = tick;
                menor_periodo->iniciar_burst = 0;
                idle_atual = 0;
            } else {
                idle_atual = 1;
                idle_executado = tick;
            }

            periodo_atual = menor_periodo;
        }

        if (menor_periodo == NULL) {
            idle_atual = 1;
            periodo_atual = NULL;
        } else {
            if (menor_periodo->iniciar_burst == 1) {
                menor_periodo->burst_executado = tick;
                menor_periodo->iniciar_burst = 0;
            }
            if ((tick - menor_periodo->burst_executado) >= menor_periodo->burst_restante) {
                tarefa_finalizada(tipo, menor_periodo->burst_restante, menor_periodo->nome);
                menor_periodo->finalizou++;
                menor_periodo->acabou = 1;
                menor_periodo->burst_executado = tick;
                periodo_atual = NULL;
                idle_atual = 0;
                idle_executado = tick;
                tick--;
                continue;
            }
        }
    }
    if (periodo_atual != NULL && periodo_atual->acabou == 0) {
        int valor_executado = tick - periodo_atual->burst_executado;
        tempo_acabou(tipo, valor_executado, periodo_atual->nome);
        periodo_atual->morta++;
    } else if (periodo_atual == NULL && idle_atual == 1) {
        int valor_executado = tick - idle_executado;
        if (valor_executado > 0) {
            idle(tipo, valor_executado);
        }
    }
}