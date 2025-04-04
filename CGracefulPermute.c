// Incluye la biblioteca estándar para entrada y salida de datos
#include <stdio.h>
// Incluye funciones estándar como abs()
#include <stdlib.h>
// Incluye funciones para medir el tiempo de ejecución
#include <time.h>

// Define el valor máximo permitido para N
#define MAX_N 20  

// Variable global para almacenar el número ingresado por el usuario
int n;
// Arreglo para almacenar la permutación actual
int perm[MAX_N];             
// Contador global de permutaciones "gráciles" generadas
unsigned long long count = 0; 

// Función recursiva para generar permutaciones con diferencias únicas
void permute(int idx, int usedMask, int diffMask) {
    // Si se completó la permutación, incrementar el contador y retornar
    if (idx == n) {
        count++;
        return;
    }

    // Calcular los números disponibles no usados aún
    int available = (~usedMask) & ((1 << (n + 1)) - 2);

    // Mientras haya números disponibles
    while (available) {
        // Obtener el bit menos significativo disponible
        int lsb = available & -available;
        // Obtener el número correspondiente al bit activado
        int number = __builtin_ctz(lsb) + 1;

        if (idx > 0) {
            // Calcular la diferencia con el número anterior
            int diff = abs(number - perm[idx - 1]);
            // Verificar si esa diferencia ya fue utilizada
            if (diffMask & (1 << diff)) {
                // Eliminar ese número de los disponibles y continuar
                available ^= lsb;
                continue;
            }
            // Asignar el número a la posición actual
            perm[idx] = number;
            // Llamada recursiva actualizando máscaras
            permute(idx + 1, usedMask | lsb, diffMask | (1 << diff));
        } else {
            // Si es el primer número, no se calcula diferencia
            perm[idx] = number;
            permute(idx + 1, usedMask | lsb, diffMask);
        }
        // Eliminar el número ya procesado de la máscara available
        available ^= lsb;
    }
}

// Función principal
int main() {
    // Pedir al usuario el valor de N
    printf("Introduce el valor de N (máx. %d): ", MAX_N);
    scanf("%d", &n);
    
    // Verificar que N esté en el rango válido
    if (n > MAX_N || n < 1) {
        printf("Error: N debe estar entre 1 y %d.\n", MAX_N);
        return 1;
    }

    // Tomar el tiempo inicial
    clock_t start = clock();
    // Iniciar la generación de permutaciones
    permute(0, 0, 0);
    // Tomar el tiempo final
    clock_t end = clock();

    // Calcular el tiempo total en segundos
    double tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    // Mostrar el número total de permutaciones generadas
    printf("Total de permutaciones graciles generadas: %llu\n", count);
    // Mostrar el tiempo de ejecución
    printf("Tiempo de ejecución: %.6f segundos\n", tiempo);

    // Fin del programa
    return 0;
}

