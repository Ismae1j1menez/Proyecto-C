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

int main() {
    Punto p1 = {1, 2};
    Punto p2 = {4, 6};
    Punto vector = crear_vector(p1, p2);
    return 0;
}