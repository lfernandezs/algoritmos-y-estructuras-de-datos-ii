#include <stdbool.h>

/*
 Recibe dos números enteros y un puntero a un entero.
 En el puntero guarda el resultado de la suma de dichos
 enteros y devuelve true.
*/
bool suma(int sumando_1, int sumando_2, int* resultado);

/*
 Recibe dos números enteros y un puntero a un entero.
 En el puntero guarda el resultado del primero menos
 el segundo entero y devuelve true.
*/
bool resta(int minuendo, int sustraendo, int* resultado);

/*
 Recibe dos números enteros y un puntero a un entero.
 En el puntero guarda el resultado de la multiplicacion
 de dichos enteros y devuelve true.
*/
bool mult(int multiplicando, int multiplicador, int* resultado);

/*
 Recibe dos números enteros y un puntero a un entero.
 En el puntero guarda el resultado de la división del
 primerio por el segundo entero. Si la división no es
 válida, devuelve false.
*/
bool division(int dividendo, int divisor, int* resultado);

/*
 Recibe dos números enteros y un puntero a un entero.
 En el puntero guarda el resultado de el primer entero
 elevado al segundo. Si la potencia es válida, devuelve
 true.
*/
bool pot(int base, int exponente, int* resultado);

/*
 Recibe un número entero y un puntero a un entero.
 En el puntero guarda el resultado de la raiz de
 dicho entero. Si operación es válida, devuelve
 true.
*/
bool squareroot(int radicando, int* resultado);

/*
 Recibe dos números enteros y un puntero a un entero.
 En el puntero guarda el resultado del logaritmo del
 primer entero en la base del segundo. Si la operación
 es válida, devuelve true.
*/
bool logaritmo(int argumento, int base, int* resultado);

/*
 Recibe tres enteros y un puntero a un entero.
 En el puntero, si el primer entero es distinto a cero,
 guarda el segundo, sino, guarda el tercero. Devuelve true.
*/
bool ter(int condicion, int caso_verdadero, int caso_falso, int* resultado);
