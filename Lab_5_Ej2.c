#include <omp.h>
#include <stdio.h>

#define N 10000

int main() {
    long long resultado = 0;

    double tiempoInicio = omp_get_wtime();

    #pragma omp parallel for reduction(+:resultado)
    for (int i = 1; i<=N; i++)
    {
        resultado += i;
    }

    double tiempoFinal = omp_get_wtime();

    printf("YUSGIMIMAIMONY EPAAAAAA\n");
    printf("La sumatoria final fue de: %d como un tiempo de %f segundos", resultado,tiempoFinal);

    return 0;
}