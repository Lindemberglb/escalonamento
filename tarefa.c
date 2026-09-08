#include "tarefa.h"

Instancia criar_instancia(Tarefa *tarefa, int chegada){
    Instancia instancia;
    instancia.tarefa = tarefa;
    instancia.chegada = chegada;
    instancia.deadline = chegada + tarefa->deadline;
    instancia.restante = tarefa->burst;
    instancia.concluida = 0;
    instancia.perdida = 0;
    return instancia;
}

int instancia_pronta(const Instancia *instancia, int tempo){
    if (instancia->concluida){
        return 0;
    }

    if (instancia->perdida){
        return 0;
    }

    if (tempo < instancia->chegada){
        return 0;
    }

    if (instancia->restante <= 0){
        return 0;
    }

    if (tempo >= instancia->deadline){
        return 0;
    }
    return 1;
}

int instancia_perdeu_deadline(const Instancia *instancia, int tempo){
    if (instancia->concluida || instancia->perdida){
        return 0;
    }

    if (instancia->restante <= 0){
        return 0;
    }

    if (tempo >= instancia->deadline){
        return 1;
    }
    return 0;
}