#include "operaciones.h"
#include <stdio.h>
#include <string.h>

int _squareroot(int radicando, int inicio, int fin) {
    if (radicando == 0) return 0;
    if (radicando == 1) return 1;
    int medio = (inicio + fin) / 2;
    if (medio*medio > radicando ) return _squareroot(radicando, inicio, medio-1);
    if (medio * medio <= radicando && (medio+1)*(medio+1) > radicando) return medio;
    return _squareroot(radicando, medio + 1, fin);
}

int _pot(int base, int exponente) {
    if (exponente == 0) return 1;
    if (exponente == 1) return base;
    int aux = _pot(base, exponente / 2);
    if (exponente % 2 == 0) return aux * aux;
    else return base * aux * aux;
}

bool suma(int sumando_1, int sumando_2, int* resultado) {
    *resultado = sumando_1 + sumando_2;
    return true;
}

bool resta(int minuendo, int sustraendo, int* resultado) {
    *resultado = minuendo - sustraendo;
    return true;
}

bool mult(int multiplicando, int multiplicador, int* resultado) {
    *resultado = multiplicando * multiplicador;
    return true;
}

bool division(int dividendo, int divisor, int* resultado) {
    if (divisor == 0) return false;
    *resultado = dividendo / divisor;
    return true;
}

bool pot(int base, int exponente, int* resultado) {
    if (exponente < 0) return false;
    *resultado = _pot(base, exponente);
    return true;
}

bool squareroot(int radicando, int* resultado) {
    if (radicando < 0) return false;
    int inicio = 1;
    int fin = radicando;
    *resultado = _squareroot(radicando, inicio, fin);
    return true;
}

bool ter(int condicion, int caso_verdadero, int caso_falso, int* resultado) {
    if (condicion) *resultado = caso_verdadero;
    else *resultado = caso_falso;
    return true;
}

bool logaritmo(int argumento, int base, int* resultado) {
    if (base <= 1 || argumento <=0) return false;
    if (argumento == 1) {
        *resultado = 0;
        return true;
    }
    int cont = 0;
    while (argumento >= base) {
        argumento /= base;
        cont++;
    }
    *resultado = cont;
    return true;
}

bool squareroot(int* radicando, int* resultado) {
    if (!radicando) return false;
    int raiz = *radicando/2;
    while (!((raiz-1)*(raiz-1) < *radicando && (raiz+1)*(raiz+1) > *radicando)) {
        if (raiz*raiz < *radicando) raiz = (raiz + *radicando) / 2;
        else if (raiz*raiz > *radicando) raiz /= 2;
    }
    *resultado = raiz;
    return true;
}

bool ter(int* condicion, int* caso_verdadero, int* caso_falso, int* resultado) {
    if (!condicion || !caso_verdadero || !caso_falso) return false;
    if (*condicion) *resultado = *caso_verdadero;
    else *resultado = *caso_falso;
    return true;
}

bool logaritmo(int* argumento, int* base, int* resultado) {
    if (!argumento || !base) return false;
    printf("operacion logaritmo\n");
    return true;
}

bool se_encuentra(char* buscado, char** vector, int largo) {
    for (int i = 0; i < largo; i++) {
        if (strcmp(buscado, vector[i]) == 0) return true;
    }
    return false;
}