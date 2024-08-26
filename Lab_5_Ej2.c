#include <omp.h>
#include <stdio.h>

#define N 10000  // Definimos una constante N que representa el límite superior de la sumatoria

int main() {
    long long resultado = 0;  // Variable para almacenar la sumatoria

    double tiempoInicio = omp_get_wtime();  // Capturamos el tiempo de inicio utilizando OpenMP

    // Iniciamos una región paralela con la directiva 'parallel for' para dividir la iteración entre varios hilos
    #pragma omp parallel for reduction(+:resultado)
    for (int i = 1; i<=N; i++)
    {
        resultado += i;  // Cada hilo suma su valor parcial a la variable 'resultado'
    }

    double tiempoFinal = omp_get_wtime();  // Capturamos el tiempo de finalización

    // Mostramos un mensaje personalizado (YUSGIMIMAIMONY EPAAAAAA)
    printf("YUSGIMIMAIMONY EPAAAAAA\n");

    // Imprimimos el resultado de la sumatoria y el tiempo que tomó la operación
    printf("La sumatoria final fue de: %lld como un tiempo de %f segundos", resultado, tiempoFinal - tiempoInicio);

    return 0;  // Finalizamos el programa
}