#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Esta macro es puesta aquí para que el tamaño máximo de la 
// matriz sea conocida en la compilación y solo se ingresan los valores
// en la matriz
#define MAX_CITIES 30
int distances[MAX_CITIES][MAX_CITIES];

// Inicialización de variables globales con valores definidos
// variables tipo enteros y arreglos usados más adelante
int best_distance = INT_MAX;
int best_path[MAX_CITIES];
int current_path[MAX_CITIES];

// Función que itera con puros ciclos for todos los caminos posibles para llegar a un destino
// Esta función es llamada en input_num_len_cities_matrix()
void find_shortest_path(int origin, int destination, int num_cities, int path_length, int path_index) {
    current_path[path_index] = origin;
    // Revisar si el destino sea == a origen siempre y cuando 
    // el índice sea mayor a 0, porque si es cero es la misma 
    // ciudad
    if (origin == destination && path_index > 0) {
        // Primera iteración compara con INT_MAX, las demás
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
    
    // Itera sobre el número de ciudades
    for (int i = 0; i < num_cities; i++) {
        // Revisa que haya una conexión siempre y cuando no sea -1 o cero porque no hay camino
        // Además se asume que no puede haber caminos con distancias negativas para no complicar 
        // demasiado la lógica
        if (distances[origin][i] != -1 && distances[origin][i] != 0) {
            int cycle = 0;
            for (int j = 0; j <= path_index; j++) {
                // Esta condición permite identificar bucles infinitos que no llevan a nada
                // Si de A voy a B y de B a A esto crea un bucle infinito, pero fácilmente sé 
                // evita con la condición i = j, porque al ser iguales significa que paso por 
                // ahí una vez
                if (current_path[j] == i) {
                    // Se detecta el ciclo y se usa break para terminar la iteración
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
    // INT_MAX sea menor significa que en alguna otra función 
    // best_distance fue actualizado
    if (best_distance < INT_MAX) {
        printf("La distancia más corta es: %d\n", best_distance);
        printf("La mejor ruta es: ");
        for (int i = 0; i < MAX_CITIES && best_path[i] != destination; i++) {
            // Se aprovecha que los ASCII para pasar de A más B solo se le suma
            // 1, esto permite cambiar los ASCCI fácilmente
            printf("%c -> ", 'A' + best_path[i]);
        }
        printf("%c\n", 'A' + destination);
    } else {
        printf("No se encontró ruta desde la ciudad de origen a la de destino.\n");
    }
}

// Función llamada en el main
void input_num_len_cities_matrix() {
    int num_cities;
    printf("Ingrese el número de ciudades: ");
    // Si se recibe un 0 es que no se pudo interpretar correctamente 
    // lo ingresado por el usuario, al contrario de sí se recibe 1, 
    // por lo que se revisa si lo que retorna el scanf, como se espera, 
    // un entero entonces si es 1 se interpreta un entero correctamente
    if (scanf("%d", &num_cities) != 1) {
        printf("Entrada inválida. Por favor, ingrese un número entero.\n");
        exit(EXIT_FAILURE);
    }

    if (num_cities < 0) {
        printf("El número no puede ser negativo.\n");
        exit(EXIT_FAILURE);
    }

    if (num_cities > 30) {
        printf("Se admiten máximo 30 ciudades.\n");
        exit(EXIT_FAILURE);
    }

    if (num_cities == 0) {
        printf("No hay ciudades, por lo que no hay camino para analizar.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_cities; i++) {
        for (int j = i + 1; j < num_cities; j++) {
            // Condición de que siempre que i == j 
            // los valores es 0, porque no hay distancia
            // entre las dos ciudades
            if (i == j) {
                distances[i][j] = 0;
            } else {
                printf("Ingrese la distancia de la ciudad %c a la ciudad %c (-1 si no hay conexión): ", 'A' + i, 'A' + j);
                if (scanf("%d", &distances[i][j]) != 1) {
                    printf("Entrada inválida. Por favor, ingrese un número entero.\n");
                    exit(EXIT_FAILURE);
                }

                if (distances[i][j] < 0 && distances[i][j] != -1) {
                    printf("No se aceptan distancias negativas.\n");
                    exit(EXIT_FAILURE);
                }

                if (distances[i][j] == 0) {
                    printf("Si entre las ciudades no hay camino, ingresar -1.\n");
                    exit(EXIT_FAILURE);
                }

                // Para que refleje el valor y no hayan incongruencias
                distances[j][i] = distances[i][j];
            }
        }
    }

    printf("\nMatriz de Distancias:\n");
    printf("  ");
    for (int j = 0; j < num_cities; j++) {
        printf("%3c", 'A' + j);
    }
    printf("\n");


    for (int i = 0; i < num_cities; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < num_cities; j++) {
            // Valores que se imprimen en la matriz, 
            // para observar la matriz ingresada por él
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

    // Se revisa que la entrada es una letra válida, es decir mayúscula que 
    // representa una ciudad, o que la letra mayúscula este definida en la matriz
    if (origin_city_index < 0 || origin_city_index >= num_cities ||
        dest_city_index < 0 || dest_city_index >= num_cities) {
        printf("\nEntrada inválida. Por favor, ingrese letras que representen ciudades válidas, solo mayusculas.\n");
        printf("\nLa ciudad también debe estar dentro de la tabla definida.\n");
        exit(EXIT_FAILURE);
    }

    // Aquí se llaman las funciones hechas en el código anterior
    find_shortest_path(origin_city_index, dest_city_index, num_cities, 0, 0);

    print_best_path(dest_city_index);
}

// Puede ser el main
int main() {
    char salir = 's';
    do {
        input_num_len_cities_matrix();
        printf("Desea calcular otra ruta?, s/n ");
		scanf(" %c", &salir);
		} while(salir == 's' || salir == 'S');
    return 0;
}
