#include <stdio.h>
#include <stdlib.h>
#include "rate.h"

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

void deadline_atingida(char tipo, double tempo, char nome[100]) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "a");
        fprintf(arquivo, "[%s] for %1.lf units - L\n", nome, tempo);
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "a");
        fprintf(arquivo, "[%s] for %1.lf units - L\n", nome, tempo);
        fclose(arquivo);
    }
}

void tempo_acabou(char tipo, double tempo, char nome[100]) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "a");
        fprintf(arquivo, "[%s] for %1.lf units - K\n", nome, tempo);
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "a");
        fprintf(arquivo, "[%s] for %1.lf units - K\n", nome, tempo);
        fclose(arquivo);
    }
}

void idle(char tipo, double tempo) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "a");
        fprintf(arquivo, "idle for %1.lf units\n", tempo);
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "a");
        fprintf(arquivo, "idle for %1.lf units\n", tempo);
        fclose(arquivo);
    }
}

void valores_tarefa_finalizada(char tipo, Atividade *head) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "a");
        fprintf(arquivo, "COMPLETE EXECUTION\n");
        fprintf(arquivo, "\n");
        while(head != NULL) {
            fprintf(arquivo, "[%s] %d\n", head->nome, head->finalizou);
            head = head->prox;
        }
        fprintf(arquivo, "\n");
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "a");
        fprintf(arquivo, "COMPLETE EXECUTION\n");
        fprintf(arquivo, "\n");
        while(head != NULL) {
            fprintf(arquivo, "[%s] %d\n", head->nome, head->finalizou);
            head = head->prox;
        }
        fprintf(arquivo, "\n");
        fclose(arquivo);
    }
}

void valores_tarefa_deadline(char tipo, Atividade *head) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "a");
        fprintf(arquivo, "\n");
        fprintf(arquivo, "LOST DEADLINES\n");
        fprintf(arquivo, "\n");
        while(head != NULL) {
            fprintf(arquivo, "[%s] %d\n", head->nome, head->atingiu_deadline);
            head = head->prox;
        }
        fprintf(arquivo, "\n");
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "a");
        fprintf(arquivo, "\n");
        fprintf(arquivo, "LOST DEADLINES\n");
        fprintf(arquivo, "\n");
        while(head != NULL) {
            fprintf(arquivo, "[%s] %d\n", head->nome, head->atingiu_deadline);
            head = head->prox;
        }
        fprintf(arquivo, "\n");
        fclose(arquivo);
    }
}

void valores_tarefa_morta(char tipo, Atividade *head) {
    if (tipo == 'e') {
        FILE *arquivo = fopen("edf_ifcvd.out", "a");
        fprintf(arquivo, "KILLED\n");
        fprintf(arquivo, "\n");
        while(head != NULL) {
            fprintf(arquivo, "[%s] %d\n", head->nome, head->morta);
            head = head->prox;
        }
        fclose(arquivo);
    } else if (tipo == 'r') {
        FILE *arquivo = fopen("rate_ifcvd.out", "a");
        fprintf(arquivo, "KILLED\n");
        fprintf(arquivo, "\n");
        while(head != NULL) {
            fprintf(arquivo, "[%s] %d\n", head->nome, head->morta);
            head = head->prox;
        }
        fclose(arquivo);
    }
}
