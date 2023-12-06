// Programa que se encarga de buscar polígonos convexos
// a partir de la entrada de coordenadas de un usuario.
//
// Se utilizan permutaciones para hacer todos los posibles casos
// ya que se pide que se ingresen los vectores en desorden.
// 
// Se utiliza una funcion de "es_convexo" en conjunto con la teoría
// de suma de ángulos internos para determinar si el polígono
// dentro de la función de permutaciones es válido.
//
// Para determinar la convexividad del polígono y sus ángulos se
// utilizo el producto cruz y el producto punto.
//
// Estudiantes:
// Oscar Porras Silesky / C16042
// Ismael Jimenez Carballo / B94009
// Sebastián Carvajal Sancho / C01764

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Se define estructura llamada Punto para 
// representar puntos en el espacio bidimensional.
typedef struct {
    // Componente x del punto.
    float x;
    // Componente y del punto.
    float y;
} Punto;

// Se establece un límite máximo para el número de vértices.
#define MAX_VERTICES 100

// Función para crear un vector desde el punto a hacia el punto b.
Punto crear_vector(Punto a, Punto b) {
    Punto vector;
    // Se calcula la componente x del vector.
    vector.x = b.x - a.x;
    // Se calcula la componente y del vector.
    vector.y = b.y - a.y;
    // Se retorna el vector resultante.
    return vector;
}

// Función para calcular el producto cruz entre dos vectores.
float producto_cruz(Punto a, Punto b) {
    float resultado = a.x * b.y - a.y * b.x;
    return resultado;
}

// Función para calcular el producto punto entre dos vectores.
float producto_punto(Punto a, Punto b) {
    // Se retorna el producto de las componentes x 
    // y la suma del producto de las componentes y.
    float resultado = a.x * b.x + a.y * b.y;
    return resultado;
}

// Función para calcular la magnitud de un vector.
float magnitud(Punto a) {
    // Se retorna la raíz cuadrada de la suma de 
    // los cuadrados de las componentes del vector.
    float resultado = sqrt(a.x * a.x + a.y * a.y);
    return resultado;
}

// Función para calcular el ángulo entre dos vectores.
float angulo_entre_vectores(Punto a, Punto b) {
    // Se calcula el producto punto de los vectores.
    float punto = producto_punto(a, b);
    float magnitud_a = magnitud(a);
    float magnitud_b = magnitud(b);
    // Se calcula el coseno inverso del ángulo.
    float angulo = acos(punto / (magnitud_a * magnitud_b));
    // Se convierte el ángulo de radianes a grados y se retorna.
    angulo = angulo * (180.0 / 3.14159265358979323846);
    return angulo;
}

// Función para verificar si un polígono es convexo.
int es_convexo(Punto vertices[], int n) {
    // Se verifica tener al menos 3 vértices.
    if (n < 3) return 0;

    // Se inicia el signo del producto cruz 
    // basado en los primeros dos vectores.
    Punto v1 = crear_vector(vertices[0], vertices[1]);
    Punto v2 = crear_vector(vertices[1], vertices[2]);
    float signo = producto_cruz(v1, v2);

    // Se itera sobre todos los 
    // vértices para verificar la convexidad
    for (int i = 1; i < n; i++) {
        // Se Crea dos vectores juntos con vértices cercanos
        v1 = crear_vector(vertices[i], vertices[(i + 1) % n]);
        v2 = crear_vector(vertices[(i + 1) % n], vertices[(i + 2) % n]);
        float prod_cruz = producto_cruz(v1, v2);

        // Si el signo cambia, el polígono no es convexo.
        if (signo * prod_cruz < 0) return 0;
    }
    // Si todos los productos cruz tienen 
    // el mismo signo, el polígono es convexo.
    return 1;
}

// Función para intercambiar dos puntos.
void swap(Punto *a, Punto *b) {
    // copia temporal del punto "a".
    Punto temp = *a;
     // Intercambio de los valores de "a" y "b".
    *a = *b;
    *b = temp;
}

// Genera todas las permutaciones de los vértices 
// y verifica si forman un polígono convexo.
void generar_permutaciones(Punto vertices[], int n, int inicio) {
    // Si se llega al fin de una permutacion.
    if (inicio == n) {
        if (es_convexo(vertices, n)) {
        // Se confirma si es convexo.
            float suma_angulos = 0.0;
            for (int i = 0; i < n; i++) {
                // Se calcula los vectores a partir de los vértices cercanos.
                Punto vector1 = crear_vector(vertices[i], vertices[(i + 1) % n]);
                Punto vector2 = crear_vector(vertices[i], vertices[(i - 1 + n) % n]);

                // Se calcula el ángulo entre los dos vectores.
                suma_angulos += angulo_entre_vectores(vector1, vector2);
            }

            if (fabs(suma_angulos - ((n - 2) * 180.0)) < 1e-6) {
                // Si la suma de los ángulos es la correcta, imprime los ángulos.
                for (int i = 0; i < n; i++) {
                    // Se calcula nuevamente los vectores para cada vértice.
                    Punto vector1 = crear_vector(vertices[i], vertices[(i + 1) % n]);
                    Punto vector2 = crear_vector(vertices[i], vertices[(i - 1 + n) % n]);

                    // Se calcula el ángulo entre los dos vectores.
                    float angulo = angulo_entre_vectores(vector1, vector2);
                    // Imprime el ángulo para el vértice actual.
                    printf("Ángulo en vértice %d: %f grados\n", i + 1, angulo);
                }
                // Se termina si se encuentra un polígono válido.
                exit(0);
            }
        }
        return;
    }
    // For que genera permutaciones intercambiando vértices,
    // se pone un vertice como referencia y se hacen todos
    // los polígonos posibles desde ese vértice.
    for (int i = inicio; i < n; i++) {
        // Intercambia el vértice en la posición 
        // "inicio" con el vértice en la posición "i".
        swap(&vertices[inicio], &vertices[i]);

        // Llama recursivamente a la función para 
        // generar permutaciones con el siguiente índice como "inicio".
        generar_permutaciones(vertices, n, inicio + 1);

        // Intercambia otra vez 
        // los vértices para restaurar el arreglo a su estado original
        // para el siguiente caso.
        swap(&vertices[inicio], &vertices[i]);
    }
}

int main() {
    // Se definen variables para el número de vértices y el índice del bucle.
    int n, i;
    printf("Ingrese el número de vértices del polígono (máximo %d): ", MAX_VERTICES);
    if (scanf("%d", &n) != 1) {
        printf("Entrada no válida. Por favor, asegúrese de ingresar un número.\n");
        // Termina el programa si la entrada no es válida.
        return 1;
    }

    // Se verifica que el número de vértices no exceda el máximo permitido.
    if (n > MAX_VERTICES) {
        printf("El polígono no puede tener más de %d vértices.\n", MAX_VERTICES);
        return 1;
    }

    // Se verifica que el polígono tenga 3 lados o más.
    if (n < 3) {
        printf("Un polígono debe tener al menos 3 lados.\n");
        // Se finaliza el programa si el polígono no tiene al menos 3 lados.
        return 1;
    }

    // Se define un arreglo para almacenar los vértices.
    Punto vertices[MAX_VERTICES];


    // Se piden las coordenadas de cada vértice del polígono.
    for (i = 0; i < n; i++) {
        printf("Ingrese el valor x de la coordenada %d: ", i + 1);
        scanf("%f", &vertices[i].x);
        printf("Ingrese el valor y de la coordenada %d: ", i + 1);
        scanf("%f", &vertices[i].y);
    }

    // Llamado a función para generar permutaciones y verificar cada una.
    generar_permutaciones(vertices, n, 0);
    // Mensaje final si no se encuentra un 
    // polígono convexo con las propiedades requeridas.
    printf("No se encontró un polígono convexo con las propiedades requeridas.\n");
    return 1;
}
