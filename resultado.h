#ifndef RESULTADO_H
#define RESULTADO_H

typedef struct RegistroExecucao{
    int executou;
    int instancia;
} RegistroExecucao;

void registrar_execucao(RegistroExecucao *registros, int tempo, int instancia);

#endif