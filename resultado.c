#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resultado.h"

void registrar_execucao(RegistroExecucao *registros, int tempo, int instancia){
    registros[tempo].executou = 1;
    registros[tempo].instancia = instancia;
}

int gerar_saida(char *nome_arquivo,char *algoritmo,controle_instancias *controle,Tarefa *tarefas,int quantidade_tarefas,RegistroExecucao *registros,int tempo_total){
    FILE *arquivo;
    int *perdidas;
    int *completas;
    int *mortas;
    int *execucoes;
    int tempo;
    int inicio;
    int fim;
    int instancia;
    int i;
    int j;

    arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL){
        return 0;
    }

    perdidas = calloc(quantidade_tarefas, sizeof(int));
    completas = calloc(quantidade_tarefas, sizeof(int));
    mortas = calloc(quantidade_tarefas, sizeof(int));
    execucoes = calloc(controle->quantidade, sizeof(int));

    if (perdidas == NULL || completas == NULL || mortas == NULL || execucoes == NULL){
        free(perdidas);
        free(completas);
        free(mortas);
        free(execucoes);
        fclose(arquivo);
        return 0;
    }

    if (strcmp(algoritmo, "rate") == 0){
        fprintf(arquivo, "EXECUTION BY RATE\n");
    }

    else{
        fprintf(arquivo, "EXECUTION BY EDF\n");
    }

    tempo = 0;

    while (tempo < tempo_total){
        if (registros[tempo].executou == 0){
            inicio = tempo;

            while (tempo < tempo_total && registros[tempo].executou == 0){
                tempo++;
            }

            fprintf(arquivo, "idle for %d units\n", tempo - inicio);
        }

        else{
            instancia = registros[tempo].instancia;
            inicio = tempo;

            while (tempo + 1 < tempo_total && registros[tempo + 1].executou == 1 && registros[tempo + 1].instancia == instancia){
                tempo++;
            }

            fim = tempo;

            for (j = inicio; j <= fim; j++){
                execucoes[registros[j].instancia]++;
            }

            if (execucoes[instancia] == controle->instancias[instancia].tarefa->burst){
                fprintf(arquivo, "[%s] for %d units - F\n", controle->instancias[instancia].tarefa->nome, fim - inicio + 1);
            }

            else if (controle->instancias[instancia].deadline == fim + 1){
                fprintf(arquivo, "[%s] for %d units - L\n", controle->instancias[instancia].tarefa->nome, fim - inicio + 1);
            }

            else{
                fprintf(arquivo, "[%s] for %d units - H\n", controle->instancias[instancia].tarefa->nome, fim - inicio + 1);
            }
            tempo++;
        }
    }

    for (i = 0; i < controle->quantidade; i++){
        if (controle->instancias[i].concluida){
            completas[controle->instancias[i].tarefa->ordem]++;
        }

        else if (controle->instancias[i].perdida){
            perdidas[controle->instancias[i].tarefa->ordem]++;
        }

        else{
            mortas[controle->instancias[i].tarefa->ordem]++;
        }
    }

    fprintf(arquivo, "LOST DEADLINES\n");

    for (i = 0; i < quantidade_tarefas; i++){
        fprintf(arquivo, "[%s] %d\n", tarefas[i].nome, perdidas[i]);
    }

    fprintf(arquivo, "COMPLETE EXECUTION\n");

    for (i = 0; i < quantidade_tarefas; i++){
        fprintf(arquivo, "[%s] %d\n", tarefas[i].nome, completas[i]);
    }

    fprintf(arquivo, "KILLED\n");

    for (i = 0; i < quantidade_tarefas; i++){
        fprintf(arquivo, "[%s] %d\n", tarefas[i].nome, mortas[i]);
    }

    free(perdidas);
    free(completas);
    free(mortas);
    free(execucoes);
    fclose(arquivo);
    return 1;
}