#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("[ERRO] Arquivo não encontrado\n");
        exit(1);
    }

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
            printf("%s %1.f %1.f\n", nome, periodo, burst);
        }
    }
    
    fclose(arquivo);

    return 0;
}