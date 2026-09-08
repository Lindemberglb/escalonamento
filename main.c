#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefa.h"

int main(int argc, char *argv[]){
    FILE *arquivo;
    Tarefa *tarefas = NULL;
    Tarefa tarefa;
    int tempo_total;
    int quantidade_tarefas = 0;
    int capacidade = 0;
    int resultado;

    if (argc != 3){
        fprintf(stderr, "erro. quantidade de argumentos invalida\n");
        return 1;
    }

    if (strcmp(argv[1], "rate") != 0 && strcmp(argv[1], "edf") != 0){
        fprintf(stderr, "erro. algoritmo invalido\n");
        return 1;
    }

    arquivo = fopen(argv[2], "r");

    if (arquivo == NULL){
        fprintf(stderr, "erro. nao foi possivel abrir o arquivo\n");
        return 1;
    }

    resultado = fscanf(arquivo, "%d", &tempo_total);

    if (resultado != 1 || tempo_total <= 0){
        fprintf(stderr, "erro. tempo total invalido\n");
        fclose(arquivo);
        return 1;
    }

    while (1){
        resultado = fscanf(arquivo,"%s %d %d %d", tarefa.nome, &tarefa.periodo, &tarefa.deadline, &tarefa.burst);
        if (resultado == EOF){
            break;
        }

        if (resultado != 4){
            fprintf(stderr, "erro. numero de campos invalido\n");
            free(tarefas);
            fclose(arquivo);
            return 1;
        }

        if (tarefa.periodo <= 0 || tarefa.deadline <= 0 || tarefa.burst <= 0){
            fprintf(stderr, "erro. valores devem ser positivos\n");
            free(tarefas);
            fclose(arquivo);
            return 1;
        }

        if (tarefa.burst > tarefa.deadline){
            fprintf(stderr, "erro. burst maior que deadline\n");
            free(tarefas);
            fclose(arquivo);
            return 1;
        }

        if (tarefa.deadline > tarefa.periodo){
            fprintf(stderr, "erro. deadline maior que periodo\n");
            free(tarefas);
            fclose(arquivo);
            return 1;
        }

        tarefa.ordem = quantidade_tarefas;

        if (quantidade_tarefas == capacidade){
            Tarefa *nova_lista;

            if (capacidade == 0){
                capacidade = 4;
            }

            else{
                capacidade *= 2;
            }

            nova_lista = realloc(tarefas, capacidade * sizeof(Tarefa));

            if (nova_lista == NULL){
                fprintf(stderr, "erro. nao foi possivel realocar memoria\n");
                free(tarefas);
                fclose(arquivo);
                return 1;
            }
            tarefas = nova_lista;
        }
        tarefas[quantidade_tarefas] = tarefa;
        quantidade_tarefas++;
    }

    fclose(arquivo);

    if (quantidade_tarefas == 0){
        fprintf(stderr, "erro. nenhuma tarefa encontrada\n");
        free(tarefas);
        return 1;
    }

    free(tarefas);

    return 0;
}