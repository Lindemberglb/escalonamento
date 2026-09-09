#ifndef RESULTADO_H
#define RESULTADO_H

#include "tarefa.h"

typedef struct RegistroExecucao{
    int executou;
    int instancia;
} RegistroExecucao;

void registrar_execucao(RegistroExecucao *registros, int tempo, int instancia);
char estado_instancia(Instancia *instancia);

#endif