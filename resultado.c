#include "resultado.h"

void registrar_execucao(RegistroExecucao *registros, int tempo, int instancia){
    registros[tempo].executou = 1;
    registros[tempo].instancia = instancia;
}

char estado_instancia(Instancia *instancia){
    if (instancia->concluida){
        return 'F';
    }

    if (instancia->perdida){
        return 'L';
    }

    return 'H';
}