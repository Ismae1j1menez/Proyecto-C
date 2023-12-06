#include <stdio.h>
#include <stdlib.h>

int memdin(int **array, int *tamano, int *columnas, float valor, int **direccion){
    int status = 0;
    if (valor < 0 || valor != (int)valor) {
        // Sannity check por si es negativo y decimal
        printf("El valor de las posiciones debe de ser positivo y entero\n");
        status = -1;
        goto exit;
        }
        // Se crea un array para reservar con memoria dinamica los valores
        // Arbitrarios ingresados por el usuario
        // Esto es posible con la funcion realloc donde se cambia el tamanno
        // Del array para que pueda almacenar la cantidad arbitraria del
        // Usuario
        *array = (int *)realloc(*array, (*tamano + 1) * sizeof(int));

        // Estas lineas de codigo agregan el valor al final de la matriz
        // Apuntada por array y luego incrementa el tamanno de la matriz
        (*array)[*tamano] = valor;
        (*tamano)++;

        // Aqui verifica si los valores digitados por el usuario es el mayor
        // en asignarse para columnas, donde nuevamente se utiliza la direccion de 
        // Columnas para actualizar el valor
        if (valor > *columnas) {
            *columnas = valor;
        }

        // Se obtiene la direccion del array del primer elemento en la fila
        // Al solo haber una fila, solo habra un valor 
        *direccion = *array;
        exit:
        return status;
        }

int main(){
    // Definimos las variables a utilizar
    int tamannoArray = 0;
    int columnas = 0;
    int *direccionFila;
    float cant_max;

    // Preguntamos al usuario cuantos numeros va a poner
    // Como en los requerimientos nos dicen que solo la funcion debe
    // de recibir los numeros arbitrarios, no hay problema que esta 
    // Solicitud este afuera
    printf("Cuanta cantidad de numeros enteros planea colocar: ");
    scanf("%f", &cant_max);
    if (cant_max <= 0 || cant_max != (int)cant_max){
        printf("La cantidad de numeros enteros siempre debe de ser positivo y entera\n");
        exit(1);
    }
    // Como aun no se le ha asignado una direccion de memoria valida
    // Se le asigna null hasta que ya adquiera una direccion valida
    int *array = NULL;
    // Impresion de solicitud de valores y anannidura de valores al array
    for (int i = 0; i < cant_max; i++) {
        float valor;
        printf("Ingrese el numero de las posiciones de la matriz 1xM: ");
        scanf("%f", &valor);
        // Ocupo pasarle la direccion de memoria a todos los que tienen "&" ya que estos van a tener cambios
        // y necesito que sean modificados
        int status = memdin(&array, &tamannoArray, &columnas, valor, &direccionFila);
        
        if (status == -1){
            exit(1);
        }
        
    }

    // Calcular el número mayor
    // Se inicializa la variable tomando el primer valor
    int maximo = array[0];

    // Se aplica un for con el rango del tamanno del array
    // y se pregunta indice por indice si es mayor que el primer valor
    // De serlo, se actualiza el valor
    for (int i = 1; i < tamannoArray; i++) {
        if (array[i] > maximo) {
            maximo = array[i];
        }
    }

    // Es muy importante obtener el numero mayor, ya que en el se basa todo
    // Al obtener el numero mayor en una cantidad de numeros arbitrarios donde
    // Cada numero representa una posicion, el numero mayor va a ser la mayor longitud
    // Del tamanno de la matriz, siendo la matriz decidida como 1xM donde M va a ser
    // El numero mayor hallado en el array de numeros arbitrarios

    // Creacion de la reserva de memoria dinamica para la matriz de 1xM
    // Se observa como columnas que sera el numero mayor digitado por el usuario
    // Se multiplicara con sizeof para obtener el tamanno total de bytes para almacenar
    // un array de columnas, luego se hace casting con int * a entero y se guarda
    // en *filaArray que se encarga de modificar los elementos
    int *filaArray = (int *)malloc(columnas * sizeof(int));

    // Se imprime la matriz 1xM donde M fue el valor mayor
    printf("Matriz de 1x%d\n", columnas);
    for (int i = 0; i < columnas; i++) {
        printf("%d ", filaArray[i]);
    }
    printf("\n");

    // Como se devuelve en tipo Void, hay que hacer casting para obtener su valor
    printf("Dirección de memoria del primer elemento de la fila: %p\n", (void *)direccionFila);

    // Se libera la memoria usada
    free(array);
    free(filaArray);   

    return 0;
}