#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072

// Función recursiva que cuenta el número de veces que aparece 'key' en el arreglo 'a'
long count_key_parallel(long *a, long start, long end, long key) {
    if (start > end) return 0;

    if (start == end) {
        // Caso base: si solo hay un elemento, verificamos si es igual a 'key'
        return (a[start] == key) ? 1 : 0;
    }

    long mid = (start + end) / 2;
    long left_count = 0, right_count = 0;

    // Creación de tareas paralelas
    #pragma omp task shared(left_count)
    left_count = count_key_parallel(a, start, mid, key);  // Conteo en la mitad izquierda

    #pragma omp task shared(right_count)
    right_count = count_key_parallel(a, mid + 1, end, key);  // Conteo en la mitad derecha

    #pragma omp taskwait  // Espera a que ambas tareas terminen

    return left_count + right_count;
}

int main() {
    long a[N], key = 42, nkey = 0;

    // Inicialización del arreglo con valores aleatorios
    for (long i = 0; i < N; i++) a[i] = rand() % N;

    // Asignación de algunos elementos específicos con el valor 'key' para asegurar su presencia
    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;

    // Ejecutamos la versión secuencial para contar el número de veces que aparece 'key'
    nkey = count_key(N, a, key);  
    printf("Numero de veces que 'key' aparece secuencialmente: %ld\n", nkey);

    // Contamos las ocurrencias en paralelo usando OpenMP y la función recursiva
    long nkey_parallel = 0;
    #pragma omp parallel
    {
        #pragma omp single
        {
            nkey_parallel = count_key_parallel(a, 0, N - 1, key);  // Llamada inicial a la función paralela
        }
    }

    printf("Numero de veces que 'key' aparece en paralelo: %ld\n", nkey_parallel);

    return 0;
}