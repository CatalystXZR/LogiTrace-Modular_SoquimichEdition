#include "LogiTraceManager.h" // Solo necesita conocer al Orquestador de nuestro sistema

using namespace std;

int main() {
    // 1. Creamos el objeto principal para que funcione todo y luego simplemente lo ejecutamos.
    LogiTraceManager miSistemaLogiTrace;
    miSistemaLogiTrace.run();

    return 0;
}