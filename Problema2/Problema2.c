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

float magnitud(Punto a) {
    float resultado = sqrt(a.x * a.x + a.y * a.y);
    printf("Magnitud: %f\n", resultado);
    return resultado;
}

float angulo_entre_vectores(Punto a, Punto b) {
    float punto = producto_punto(a, b);
    float magnitud_a = magnitud(a);
    float magnitud_b = magnitud(b);
    float angulo = acos(punto / (magnitud_a * magnitud_b));
    angulo = angulo * (180.0 / 3.14159265358979323846);
    printf("Ángulo entre vectores: %f grados\n", angulo);
    return angulo;
}

int main() {
    Punto p1 = {1, 2};
    Punto p2 = {4, 6};
    Punto vector = crear_vector(p1, p2);
    float cruz = producto_cruz(p1, p2);
    float punto = producto_punto(p1, p2);
    float magn = magnitud(vector);
    float angulo = angulo_entre_vectores(p1, p2);
    return 0;
}