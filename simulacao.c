
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulacao.h"

void inicializar_instancias(controle_instancias *controle){
    controle->instancias = NULL;
    controle->quantidade = 0;
    controle->capacidade = 0;
}

int adicionar_instancia(controle_instancias *controle, Tarefa *tarefa, int chegada){
    Instancia *novas_instancias;
    int nova_capacidade;

    if (controle->quantidade == controle->capacidade){
        if (controle->capacidade == 0){
            nova_capacidade = 10;
        }

        else{
            nova_capacidade = controle->capacidade * 2;
        }

        novas_instancias = realloc(controle->instancias, nova_capacidade * sizeof(Instancia));

        if (novas_instancias == NULL){
            return 0;
        }
        controle->instancias = novas_instancias;
        controle->capacidade = nova_capacidade;
    }

    controle->instancias[controle->quantidade] = criar_instancia(tarefa, chegada);
    controle->quantidade++;
    return 1;
}

void atualizar_deadlines(controle_instancias *controle, int tempo){
    for (int i = 0; i < controle->quantidade; i++){
        atualizar_instancia(&controle->instancias[i], tempo);
    }
}

void liberar_instancias(controle_instancias *controle){
    free(controle->instancias);
    controle->instancias = NULL;
    controle->quantidade = 0;
    controle->capacidade = 0;
}

int gerar_instancias_no_tempo(controle_instancias *controle, Tarefa *tarefas, int quantidade_tarefas, int tempo){
    for (int i = 0; i < quantidade_tarefas; i++){
        if (deve_chegar(&tarefas[i], tempo)){
            if (adicionar_instancia(controle, &tarefas[i], tempo) == 0){
                return 0;
            }
        }
    }
    return 1;
}

int existem_instancias_prontas(controle_instancias *controle, int tempo){
    for (int i = 0; i < controle->quantidade; i++){
        if (instancia_pronta(&controle->instancias[i], tempo)){
            return 1;
        }
    }
    return 0;
}

int selecionar_instancia(controle_instancias *controle, int tempo, char *algoritmo){
    int melhor = 0;
    int encontrou = 0;

    for (int i = 0; i < controle->quantidade; i++){
        if (instancia_pronta(&controle->instancias[i], tempo)){
            if (encontrou == 0){
                melhor = i;
                encontrou = 1;
            }

            else if (strcmp(algoritmo, "rate") == 0){
                if (controle->instancias[i].tarefa->periodo < controle->instancias[melhor].tarefa->periodo){
                    melhor = i;
                }

                else if (controle->instancias[i].tarefa->periodo ==controle->instancias[melhor].tarefa->periodo){
                    if (controle->instancias[i].tarefa->ordem < controle->instancias[melhor].tarefa->ordem){
                        melhor = i;
                    }
                }
            }

                else if (controle->instancias[i].deadline <controle->instancias[melhor].deadline){
                    melhor = i;
                }

                else if (controle->instancias[i].deadline ==controle->instancias[melhor].deadline){
                    if (controle->instancias[i].tarefa->ordem < controle->instancias[melhor].tarefa->ordem){
                        melhor = i;
                    }
                }
            }
        }
    return melhor;
}
