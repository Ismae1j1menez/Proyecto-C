#include <stdio.h>
#include <stdlib.h>

// Estaa macro es puesta aqui para que el el tamaño maximo de la 
// matriz sea conocida en la compilación y no se tenga que usar una
// memoria dinamica para establecer la matriz
#define MAX_CITIES 100
int distances[MAX_CITIES][MAX_CITIES];

void input_num_len_cities_matrix() {
    int num_cities;
    printf("Ingrese el número de ciudades: ");
    scanf("%d", &num_cities);

    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            // Convertir índices de ciudades a letras (A, B, C, ...)
            // Se aprovecha que los ASCII A tiene una uno mas que B, etc
            char city_from = 'A' + i;
            char city_to = 'A' + j;

            if (i == j) {
                distances[i][j] = -1;
            } else {
                printf("Ingrese la distancia de la ciudad %c a la ciudad %c: ", city_from, city_to);
                scanf("%d", &distances[i][j]);
            }
        }
    }

    // Se imprimen las letras de arriba
    printf("\nMatriz de Distancias:\n");
    printf("\n  ");
    for (int j = 0; j < num_cities; j++) {
        printf("%3c", 'A' + j);
    }
    printf("\n");

    // Imprimir la matriz de distancias
    for (int i = 0; i < num_cities; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < num_cities; j++) {
            printf("%3d", distances[i][j]);
        }
        printf("\n");
    }
}

void check_matrix_shortestpath() {
    
}

int main() {
    input_num_len_cities_matrix();
    return 0; 
}
