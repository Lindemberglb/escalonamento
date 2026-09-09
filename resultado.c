#include "resultado.h"

void registrar_execucao(RegistroExecucao *registros, int tempo, int instancia){
    registros[tempo].executou = 1;
    registros[tempo].instancia = instancia;
}