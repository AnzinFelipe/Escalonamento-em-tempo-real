#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "saida.h"
#include "rate.h"

int main (int argc, char *argv[]) {
    char tipo = 'r';
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("[ERRO] Arquivo não encontrado\n");
        exit(1);
    }
    criar_arquivo_saida(tipo);

    Atividade *atividade = NULL;
    char nome[100];
    double tempo_total, periodo, burst;
    int i = 0;
    while (1) {
        if (i == 0) {
            fscanf(arquivo, "%lf", &tempo_total);
            printf("%1.lf\n", tempo_total);
            i++;
        } else if (i == 1) {
            if (fscanf(arquivo, "%s %lf %lf", nome, &periodo, &burst) == EOF) {
                break;
            }
            adicionar_atividade(&atividade, nome, periodo, burst);
        }
    }
    executando_atividades(tipo, tempo_total, &atividade);
    //printf("Atividades na lista encadeada:\n");
    //printar_atividades(atividade);
    valores_tarefa_deadline(tipo, atividade);
    valores_tarefa_finalizada(tipo, atividade);
    valores_tarefa_morta(tipo, atividade);
    
    fclose(arquivo);

    return 0;
}

void adicionar_atividade(Atividade **head, char nome[100], double periodo, double burst) {
    Atividade *novo = (Atividade *)malloc(sizeof(Atividade));
    if (novo != NULL) {
        strcpy(novo->nome, nome);
        novo->periodo = periodo;
        novo->burst = burst;
        novo->burst_restante = burst;
        novo->tempo_executado = time(NULL) - periodo;
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
        printf("%s %1.lf %1.lf\n", head->nome, head->periodo, head->burst);
        head = head->prox;
    }
}

void executando_atividades(char tipo, float tempo_total, Atividade **head) {
    time_t tempo_inicio = time(NULL);
    time_t idle_executado = time(NULL);
    Atividade *menor_burst;
    Atividade *burst_atual = NULL;
    int idle_atual = 0;

    while(difftime(time(NULL), tempo_inicio) < tempo_total) {

        Atividade *aux = *head;
        menor_burst = NULL;

        while (aux != NULL) {
            if (difftime(time(NULL), aux->tempo_executado) >= aux->periodo) {
                if (burst_atual == aux && burst_atual->acabou == 0) {
                    //Função para escrever que atingiu o deadline
                    double valor_executado = difftime(time(NULL), burst_atual->burst_executado);
                    deadline_atingida(tipo, valor_executado, burst_atual->nome);
                    burst_atual->atingiu_deadline++;
                    burst_atual->morta++;
                }
                aux->acabou = 0;
                printf("Tarefa: %s foi iniciada\n", aux->nome);
                aux->tempo_executado = time(NULL);
                aux->iniciar_burst = 1;
                aux->burst_restante = aux->burst;
            }

            if (menor_burst == NULL && aux->acabou == 0) {
                menor_burst = aux;
            }
            if (menor_burst != NULL) {
                if (aux->acabou == 0) {
                    if (aux->burst < menor_burst->burst) {
                        menor_burst = aux;
                    }
                }
            }
            
            aux = aux->prox;
        }

        if(burst_atual != menor_burst) {
            
            if (burst_atual == NULL && idle_atual == 1) {
                //Saiu do idle
                double valor_executado = difftime(time(NULL), idle_executado);
                if (valor_executado > 0) {
                    idle(tipo, valor_executado);
                }
            } else if(burst_atual != NULL && burst_atual->acabou == 0) {
                double valor_executado = difftime(time(NULL), burst_atual->burst_executado);
                burst_atual->burst_restante = burst_atual->burst - valor_executado;
                if(burst_atual->burst_restante < 0) {
                    burst_atual->burst_restante = 0;
                }
                printf("A tarefa %s não finalizou, falta: %1.lf\n", burst_atual->nome, burst_atual->burst_restante);
                //Função para escrever que ant foi interrompida
                tarefa_interrompida(tipo, burst_atual->burst - burst_atual->burst_restante, burst_atual->nome);
            }

            if(menor_burst != NULL) {
                menor_burst->burst_executado = time(NULL);
                menor_burst->iniciar_burst = 0;
                idle_atual = 0;
            } else {
                idle_atual = 1;
                idle_executado = time(NULL);
            }

            burst_atual = menor_burst;
        }

        if (menor_burst == NULL) {
            //Nenhuma tarefa
            idle_atual = 1;
            burst_atual = NULL;
        } else {
            //Tarefa atual
            if (menor_burst->iniciar_burst == 1) {
                menor_burst->burst_executado = time(NULL);
                menor_burst->iniciar_burst = 0;
            }
            if (difftime(time(NULL), menor_burst->burst_executado) >= menor_burst->burst_restante) {
                printf("Tarefa: %s acabou\n", menor_burst->nome);
                //Função pra escrever q acabou
                tarefa_finalizada(tipo, menor_burst->burst_restante, menor_burst->nome);
                menor_burst->finalizou++;
                menor_burst->acabou = 1;
                menor_burst->burst_executado = time(NULL);
                burst_atual = NULL;
                idle_atual = 1;
                idle_executado = time(NULL);
            }
        }
    }
    if (burst_atual != NULL && burst_atual->acabou == 0) {
        //Função para escrever que interrompeu pelo tempo
        double valor_executado = difftime(time(NULL), burst_atual->burst_executado);
        tempo_acabou(tipo, valor_executado, burst_atual->nome);
        burst_atual->morta++;
    } else if (burst_atual == NULL && idle_atual == 1) {
        double valor_executado = difftime(time(NULL), idle_executado);
        if (valor_executado > 0) {
            idle(tipo, valor_executado);
        }
    }
}