#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Esta macro es puesta aqui para que el el tamaño maximo de la 
// matriz sea conocida en la compilación y no se tenga que usar una
// memoria dinamica para establecer la matriz
#define MAX_CITIES 100
int distances[MAX_CITIES][MAX_CITIES];

// Inicialización de variables globales con valores definidos
// variables tipo enteros y arreglos usados mas adelante
int best_distance = INT_MAX;
int best_path[MAX_CITIES];
int current_path[MAX_CITIES];

// Función quue itera con puros ciclos for todos los caminos posibles para llegar a un destino
// Esta función es llamada en input_num_len_cities_matrix()
void find_shortest_path(int origin, int destination, int num_cities, int path_length, int path_index) {
    current_path[path_index] = origin;
    // Revisar si el destino sea == a origen siempre y cuando 
    // el indice sea mayor a 0, porque si es cero es la misma 
    // ciudad
    if (origin == destination && path_index > 0) {
        // Primera iteración compara con INT_MAX, las demas
        // compara con la variable actualizada
        if (path_length < best_distance) {
            // Asigna el valor si realmente es la menor longitud
            best_distance = path_length;
            for (int i = 0; i <= path_index; i++) {
                best_path[i] = current_path[i];
            }
        }
        return;
    }
    
    // Itera sobre el numero de ciudades
    for (int i = 0; i < num_cities; i++) {
        // Revisa que haya una conexión siempre y cuando no sea -1 o cero porque no hay camino
        // Ademas se asume que no pueden haber caminos con distancias negativas para no complicar 
        // demasiado la lógica
        if (distances[origin][i] != -1 && distances[origin][i] != 0) {
            int cycle = 0;
            for (int j = 0; j <= path_index; j++) {
                // Esta condición permite identificar bucles infinitos que no llevan a nada
                // Si de A voy a B y de B a A esto crea un bucle infinito, pero facilmente se 
                // evita con la condicipon i = j, porque al ser iguales significa que paso por 
                // ahí una vez
                if (current_path[j] == i) {
                    // Se detecta el ciclo y se usa break para terminar la interación
                    cycle = 1;
                    break;
                }
            }
            // Recursividad para en caso de que se encuentre un ciclo
            if (!cycle) {
                find_shortest_path(i, destination, num_cities, path_length + distances[origin][i], path_index + 1);
            }
        }
    }
}

// Esta función es llamada en input_num_len_cities_matrix()
void print_best_path(int destination) {
    // Compara el valor de best_distance, siempre y cuando 
    // INT_MAX sea mayoe signifca que en alguna otra función 
    // best_distance cambio
    if (best_distance < INT_MAX) {
        printf("La distancia más corta es: %d\n", best_distance);
        printf("La mejor ruta es: ");
        for (int i = 0; i < MAX_CITIES && best_path[i] != destination; i++) {
            // Se aprovecha que los ASCII para pasar de A mas B solo se le suma
            // 1, esto perimte cambiar los ASCCI facilmente 
            printf("%c -> ", 'A' + best_path[i]);
        }
        printf("%c\n", 'A' + destination);
    } else {
        printf("No se encontró ruta desde la ciudad de origen a la de destino.\n");
    }
}

// Función llamada en el main
void input_num_len_cities_matrix() {
    // Falta revisar que se ingresen valores adecuados
    // Por lo menos que se salga del problema y se indique 
    // porque se salio o no es adecuado ingresar ciertos valores
    int num_cities;
    printf("Ingrese el número de ciudades: ");
    scanf("%d", &num_cities);

    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            // Condición de que siempre que i == j 
            // el valores es 0, porque no hay distancia
            // entre las dos ciudades
            if (i == j) {
                distances[i][j] = 0;
            } else {
                printf("Ingrese la distancia de la ciudad %c a la ciudad %c (-1 si no hay conexión): ", 'A' + i, 'A' + j);
                scanf("%d", &distances[i][j]);
            }
        }
    }

    printf("\nMatriz de Distancias:\n");
    printf("  ");
    // Para identificar las ciudades en la matriz, recordar 
    // si es posible que se acomode adecuadamente para distancias
    // muy grandes
    for (int j = 0; j < num_cities; j++) {
        printf("%3c", 'A' + j);
    }
    printf("\n");


    for (int i = 0; i < num_cities; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < num_cities; j++) {
            // Valores que se imprimen en la matriz, 
            // para observar la matriz ingresada por el
            // usuario
            if (distances[i][j] == 0) {
                printf("  -");
            } else {
                printf("%3d", distances[i][j]);
            }
        }
        printf("\n");
    }

    char origin_city, dest_city;
    printf("Ingrese la letra de la ciudad de origen (A, B, C, ...): ");
    scanf(" %c", &origin_city);
    printf("Ingrese la letra de la ciudad de destino (A, B, C, ...): ");
    scanf(" %c", &dest_city);

    int origin_city_index = origin_city - 'A';
    int dest_city_index = dest_city - 'A';

    // Aqui se llaman las funciones hechas en el código anterior
    find_shortest_path(origin_city_index, dest_city_index, num_cities, 0, 0);

    print_best_path(dest_city_index);
}

// Main, revisar si la función input_num_len_cities_matrix()
// Puede ser el main
int main() {
    input_num_len_cities_matrix();
    return 0;
}
