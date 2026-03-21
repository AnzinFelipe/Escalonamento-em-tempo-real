#include <stdio.h>
#include <stdlib.h>

void criar_arquivo_saida(char tipo) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "w");
        fprintf(arquivo, "EXECUTION BY EDF\n");
        fprintf(arquivo, "\n");
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "w");
        fprintf(arquivo, "EXECUTION BY RATE\n");
        fprintf(arquivo, "\n");
        fclose(arquivo);
    }
}

void tarefa_finalizada(char tipo, double tempo, char nome[100]) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "a");
        fprintf(arquivo, "[%s] for %1.lf units - F\n", nome, tempo);
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "a");
        fprintf(arquivo, "[%s] for %1.lf units - F\n", nome, tempo);
        fclose(arquivo);
    }
}

void tarefa_interrompida(char tipo, double tempo, char nome[100]) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "a");
        fprintf(arquivo, "[%s] for %1.lf units - H\n", nome, tempo);
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "a");
        fprintf(arquivo, "[%s] for %1.lf units - H\n", nome, tempo);
        fclose(arquivo);
    }
}