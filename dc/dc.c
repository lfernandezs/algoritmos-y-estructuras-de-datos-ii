#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include "pila.h"
#include "cadenas.h"
#include "operaciones.h"
#include <stdlib.h>

#define CANT_OPERADORES 8


void print_error(pila_t* pila, char** ecuacion) {
    printf("ERROR\n");
    free_strv(ecuacion);
    pila_destruir(pila);
}

bool aplicar_operador(int* op_1, int* op_2, int* ternario, char* operador, int* resultado) {
    if (!op_1) return false;
    if (strcmp(operador, "sqrt") == 0) return squareroot(*op_1, resultado);
    if (!op_2) return false;
    if (strcmp(operador, "+") == 0) return suma(*op_1, *op_2, resultado);
    if (strcmp(operador, "-") == 0) return resta(*op_1, *op_2, resultado);
    if (strcmp(operador, "*") == 0) return mult(*op_1, *op_2, resultado);
    if (strcmp(operador, "/") == 0) return division(*op_1, *op_2, resultado);
    if (strcmp(operador, "^") == 0) return pot(*op_1, *op_2, resultado);
    if (strcmp(operador, "log") == 0) return logaritmo(*op_1, *op_2, resultado);
    if (!ternario) return false;
    if (strcmp(operador, "?") == 0) return ter(*op_1, *op_2, *ternario, resultado);
    return false;
}

void calcular(char* linea) {
    pila_t* pila = pila_crear();
    char** ecuacion = split(linea, ' ');
    size_t largo = 0;
    while (ecuacion[largo]) largo++;
    int aux[largo]; // Donde guardo los punteros a los números.
    int* operando_1 = NULL;
    int* operando_2 = NULL;
    int* ternario = NULL;
    int resultado = 0;
    for (int i = 0; ecuacion[i]; i++) {
        if (strcmp(ecuacion[i], "\0") == 0) continue;
        if (is_digit(ecuacion[i]) || (ecuacion[i][0] == '-' && is_digit(ecuacion[i] + 1))) {
            aux[i] = atoi(ecuacion[i]);
            pila_apilar(pila, &aux[i]);

        } else {
            operando_1 = pila_desapilar(pila);
            printf("operando 1: %i\n", *operando_1);
            operando_2 = pila_desapilar(pila);
            printf("operando 2: %i\n", *operando_2);
            ternario = pila_desapilar(pila);
            bool coherencia = aplicar_operador(operando_1, operando_2, ternario, ecuacion[i], &resultado);
            if (coherencia == false) {
                print_error(pila, ecuacion);
                return;
            }
            if (ternario && strcmp(ecuacion[i], "?") != 0) pila_apilar(pila, ternario); // Apilo las variables que no usé
            if (operando_2 && strcmp(ecuacion[i], "sqrt") == 0) pila_apilar(pila, operando_2);
            aux[i] = resultado;
            pila_apilar(pila, &aux[i]);
        }
        printf("resultado*: %i\n", resultado);
    }
    pila_desapilar(pila);
    if (!pila_esta_vacia(pila)) {
        print_error(pila, ecuacion);
        return;
    }
    printf("%i\n", resultado);
    free_strv(ecuacion);
    pila_destruir(pila);
}

void evaluar_lineas() {
    char* linea = NULL;
    size_t tam = 0;
    while (getline(&linea, &tam, stdin) > 0) {
        if (*linea == '\n') continue;
        rstrip(linea, '\n');
        calcular(linea);
    }
    free(linea);
}

int main() {
    evaluar_lineas();
    return 0;
}