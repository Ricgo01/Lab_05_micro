#include <stdio.h>
#include <omp.h>

// Función para calcular el factorial de un número
void calcular_factorial(int n) {
    int i;
    unsigned long long factorial = 1;

    for (i = 1; i <= n; i++) {
        factorial *= i;  // Multiplicamos para calcular el factorial
    }

    printf("Factorial de %d es %llu\n", n, factorial);
}

// Función para generar la serie de Fibonacci hasta un número dado
void generar_fibonacci(int n) {
    int a = 0, b = 1, temp;

    printf("Serie de Fibonacci hasta %d: %d, %d", n, a, b);

    for (int i = 2; i < n; i++) {
        temp = a + b;   // Calculamos el siguiente número de Fibonacci
        a = b;
        b = temp;
        printf(", %d", b);  // Mostramos el siguiente número en la serie
    }

    printf("\n");
}

// Función para encontrar el máximo en un arreglo
void encontrar_maximo(int arr[], int size) {
    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];  // Actualizamos el máximo si encontramos un número mayor
        }
    }

    printf("El máximo en el arreglo es %d\n", max);
}

int main() {
    int n = 5;  // Un número para calcular el factorial y la serie de Fibonacci
    int arr[] = {3, 1, 7, 0, 5, 9, 2};  // Un arreglo de ejemplo para encontrar el máximo
    int size = sizeof(arr) / sizeof(arr[0]);  // Tamaño del arreglo

    // Iniciamos la región paralela
    #pragma omp parallel
    {
        // Creamos diferentes secciones para ejecutar cada función en paralelo
        #pragma omp sections
        {
            #pragma omp section
            {
                calcular_factorial(n);  // Ejecutamos la función que calcula el factorial
            }

            #pragma omp section
            {
                generar_fibonacci(n);  // Ejecutamos la función que genera la serie de Fibonacci
            }

            #pragma omp section
            {
                encontrar_maximo(arr, size);  // Ejecutamos la función que encuentra el máximo en un arreglo
            }
        }
    }

    return 0;
}