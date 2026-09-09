#ifndef RESULTADO_H
#define RESULTADO_H

#include "simulacao.h"

typedef struct RegistroExecucao{
    int executou;
    int instancia;
} RegistroExecucao;

void registrar_execucao(RegistroExecucao *registros, int tempo, int instancia);

int gerar_saida(char *nome_arquivo,char *algoritmo,controle_instancias *controle,Tarefa *tarefas,int quantidade_tarefas,RegistroExecucao *registros,int tempo_total);

#endif