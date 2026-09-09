#include <stdio.h>
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

int deve_chegar(Tarefa *tarefa, int tempo){
    if (tempo < 0){
        return 0;
    }
    return tempo % tarefa->periodo == 0;
}

void atualizar_instancia(Instancia *instancia, int tempo){
    if (instancia->concluida || instancia->perdida){
        return;
    }

    if (tempo >= instancia->deadline && instancia->restante > 0){
        instancia->restante = 0;
        instancia->perdida = 1;
    }
}

void executar_instancia(Instancia *instancia){
    if (instancia->restante > 0){
        instancia->restante--;
    }

    if (instancia->restante == 0){
        instancia->concluida = 1;
    }
}