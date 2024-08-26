#include <stdio.h>
#include <omp.h>

int main() {
    int variable1 = 0;  // Esta variable será compartida entre todos los hilos
    int variable2 = 0;  // Esta variable será privada para cada hilo

    // Primera prueba: usando shared para variable1 y private para variable2
    printf("Primera prueba: shared variable1, private variable2\n");

    #pragma omp parallel for shared(variable1) private(variable2)
    for (int i = 0; i < 10; i++) {
        variable1 += 1;  // Todos los hilos modifican la misma variable1
        variable2 = i;   // Cada hilo tiene su propia copia de variable2
        printf("Hilo %d, variable1 = %d, variable2 = %d\n", omp_get_thread_num(), variable1, variable2);
    }

    printf("Resultado final: variable1 = %d, variable2 = %d (Nota: variable2 solo muestra el valor del último hilo)\n\n", variable1, variable2);

    // Segunda prueba: usando private para ambas variables
    variable1 = 0;  // Reiniciamos variable1 para la segunda prueba

    printf("Segunda prueba: private variable1, private variable2\n");

    #pragma omp parallel for private(variable1, variable2)
    for (int i = 0; i < 10; i++) {
        variable1 += 1;  // Ahora cada hilo tiene su propia copia de variable1
        variable2 = i;   // Cada hilo tiene su propia copia de variable2
        printf("Hilo %d, variable1 = %d, variable2 = %d\n", omp_get_thread_num(), variable1, variable2);
    }

    printf("Resultado final: variable1 = %d, variable2 = %d (Nota: Los valores de variable1 y variable2 son locales a cada hilo y no se combinan)\n\n", variable1, variable2);

    return 0;
}