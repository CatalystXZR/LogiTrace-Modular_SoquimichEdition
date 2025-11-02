#include "LogiTraceManager.h" // Solo necesita conocer al Orquestador

using namespace std;

// El main.cpp es nuestro punto de entrada.
int main() {
    // 1. Creamos el objeto principal
    LogiTraceManager miSistemaLogiTrace;

    // 2. Lo ejecutamos
    miSistemaLogiTrace.run();

    return 0;
}