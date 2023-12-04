#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Punto;

Punto crear_vector(Punto a, Punto b) {
    Punto vector;
    vector.x = b.x - a.x;
    vector.y = b.y - a.y;
    printf("Vector creado: (%f, %f)\n", vector.x, vector.y);
    return vector;
}

float producto_cruz(Punto a, Punto b) {
    float resultado = a.x * b.y - a.y * b.x;
    printf("Producto cruz: %f\n", resultado);
    return resultado;
}

float producto_punto(Punto a, Punto b) {
    float resultado = a.x * b.x + a.y * b.y;
    printf("Producto punto: %f\n", resultado);
    return resultado;
}

int main() {
    Punto p1 = {1, 2};
    Punto p2 = {4, 6};
    Punto vector = crear_vector(p1, p2);
    float cruz = producto_cruz(p1, p2);
    float punto = producto_punto(p1, p2);
    return 0;
}