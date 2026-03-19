#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Atividade {
    char nome[100];
    float periodo;
    float burst;
    struct Atividade *prox;
} Atividade;

void adicionar_atividade(Atividade **head, char nome[100], float periodo, float burst);
void printar_atividades(Atividade *head);

int main (int argc, char *argv[]) {
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("[ERRO] Arquivo não encontrado\n");
        exit(1);
    }

    Atividade *atividade = NULL;
    char nome[100];
    float tempo_total, periodo, burst;
    int i = 0;
    while (1) {
        if (i == 0) {
            fscanf(arquivo, "%f", &tempo_total);
            printf("%1.f\n", tempo_total);
            i++;
        } else if (i == 1) {
            if (fscanf(arquivo, "%s %f %f", nome, &periodo, &burst) == EOF) {
                break;
            }
            adicionar_atividade(&atividade, nome, periodo, burst);
            printf("%s %1.f %1.f\n", nome, periodo, burst);
        }
    }
    printf("Atividades na lista encadeada:\n");
    printar_atividades(atividade);
    
    fclose(arquivo);

    return 0;
}

void adicionar_atividade(Atividade **head, char nome[100], float periodo, float burst) {
    Atividade *novo = (Atividade *)malloc(sizeof(Atividade));
    if (novo != NULL) {
        strcpy(novo->nome, nome);
        novo->periodo = periodo;
        novo->burst = burst;
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
        printf("%s %1.f %1.f\n", head->nome, head->periodo, head->burst);
        head = head->prox;
    }
}