#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "saida.h"
#include "atividade.h"

int main (int argc, char *argv[]) {

    if (argc > 2) {
        printf("[ERRO] Número incorreto de argumentos\n");
        exit(1);
    }

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
            if (fscanf(arquivo, "%lf", &tempo_total) == 0) {
                printf("[ERRO] conteúdo dentro do arquivo inválido\n");
                exit(1);
            }
            printf("%lf\n", tempo_total);
            i++;
        } else if (i == 1) {
            int variaveis_corretas = fscanf(arquivo, "%s %lf %lf", nome, &periodo, &burst);
            if (variaveis_corretas == EOF) {
                break;
            } else if (variaveis_corretas != 3) {
                printf("[ERRO] conteúdo dentro do arquivo inválido\n");
                exit(1);
            }
            adicionar_atividade(&atividade, nome, periodo, burst);
        }
    }
    executando_atividades_rate(tipo, tempo_total, &atividade);
    valores_tarefa_deadline(tipo, atividade);
    valores_tarefa_finalizada(tipo, atividade);
    valores_tarefa_morta(tipo, atividade);
    liberar_atividades(atividade);
    
    fclose(arquivo);

    return 0;
}