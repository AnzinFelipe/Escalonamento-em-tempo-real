#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "saida.h"
#include "atividade.h"

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
    executando_atividades_rate(tipo, tempo_total, &atividade);
    //printf("Atividades na lista encadeada:\n");
    //printar_atividades(atividade);
    valores_tarefa_deadline(tipo, atividade);
    valores_tarefa_finalizada(tipo, atividade);
    valores_tarefa_morta(tipo, atividade);
    
    fclose(arquivo);

    return 0;
}