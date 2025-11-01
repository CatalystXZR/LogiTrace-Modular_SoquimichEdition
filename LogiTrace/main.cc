#include "LogiTraceManager.h"

// El main.cpp es nuestro punto de entrada.
// Gracias al patrón Facade, es INCREÍBLEMENTE simple.
// Su única responsabilidad es crear el Manager y llamarlo.
int main() {
    // 1. Creamos el objeto principal
    LogiTraceManager miSistemaLogiTrace;

    // 2. Lo ejecutamos
    miSistemaLogiTrace.run();

    // 3. Cuando 'run()' termina, el programa finaliza.
    return 0;
}