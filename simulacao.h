#ifndef SIMULACAO_H
#define SIMULACAO_H
#include "tarefa.h"

typedef struct controle_instancias{
    Instancia *instancias;
    int quantidade;
    int capacidade;
}controle_instancias;

void inicializar_instancias(controle_instancias *controle);
int adicionar_instancia(controle_instancias *controle, Tarefa *tarefa, int chegada);
void atualizar_deadlines(controle_instancias *controle, int tempo);
void liberar_instancias(controle_instancias *controle);

#endif