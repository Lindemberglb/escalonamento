#ifndef TAREFA_H
#define TAREFA_H

typedef struct Tarefa{
    char nome[100];
    int periodo;
    int deadline;
    int burst;
    int ordem;
}Tarefa;

typedef struct Instancia{
    Tarefa *tarefa;
    int chegada;
    int deadline;
    int restante;
    int concluida;
    int perdida;
}Instancia;

Instancia criar_instancia(Tarefa *tarefa, int chegada);

int instancia_pronta(const Instancia *instancia, int tempo);

int instancia_perdeu_deadline(const Instancia *instancia, int tempo);

int deve_chegar(Tarefa *tarefa, int tempo);

void atualizar_instancia(Instancia *instancia, int tempo);

#endif