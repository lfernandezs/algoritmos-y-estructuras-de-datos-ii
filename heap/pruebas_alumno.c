#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
 
int comparar_numeros(const void* a, const void* b) {
    if (*(int*)a > *(int*)b) return 1;
    else if (*(int*)a == *(int*)b) return 0;
    return -1;
}

void prueba_heap_nuevo() {

    /* Declaro Variables */
    heap_t* heap = heap_crear(comparar_numeros);
    
    /* Inicio de pruebas */
	printf("\nPRUEBA HEAP NUEVO\n");
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("El máximo del heap es NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

void prueba_heap_crear_arr() {

	/* Declaro Variables */
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	void* arreglo[5] = {&a, &b, &c, &d, &e};
	heap_t* heap = heap_crear_arr(arreglo, 5, comparar_numeros);

	/* Inicio de pruebas */
	printf("\nPRUEBA HEAP NUEVO DE ARREGLO\n");
	print_test("La cantidad de elementos es 5", heap_cantidad(heap) == 5);
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El máximo del heap es e", heap_ver_max(heap) == &e);
	print_test("Desencolar devuelve a e", heap_desencolar(heap) == &e);
	print_test("La cantidad de elementos es 4", heap_cantidad(heap) == 4);
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El máximo del heap es d", heap_ver_max(heap) == &d);
	print_test("Desencolar devuelve a d", heap_desencolar(heap) == &d);
	print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El máximo del heap es c", heap_ver_max(heap) == &c);
	print_test("Desencolar devuelve a c", heap_desencolar(heap) == &c);
	print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El máximo del heap es b", heap_ver_max(heap) == &b);
	print_test("Desencolar devuelve a b", heap_desencolar(heap) == &b);\
	print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El máximo del heap es a", heap_ver_max(heap) == &a);
	print_test("Desencolar devuelve a a", heap_desencolar(heap) == &a);
	print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
	print_test("El heap está vacío", heap_esta_vacio(heap));
	print_test("El máximo del heap es NULL", heap_ver_max(heap) == NULL);
	print_test("Desencolar devuelve a NULL", heap_desencolar(heap) == NULL);
	
	heap_destruir(heap, NULL);		
}

void prueba_encolar_y_desencolar() {

    /* Declaro Variables*/
    heap_t* heap = heap_crear(comparar_numeros);
    int a = 0;
    int b = 1;
    int c = 2;

    /* Inicio de pruebas */
	printf("\nPRUEBA ENCOLAR Y DESENCOLAR\n");
    print_test("Se encoló a", heap_encolar(heap, &a));
    print_test("Se encoló b", heap_encolar(heap, &b));
    print_test("Se encoló c", heap_encolar(heap, &c));
    print_test("El máximo es c", heap_ver_max(heap) == &c);
    print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("El heap no está vacío", !heap_esta_vacio(heap));
    print_test("Desencolar devuelve c", heap_desencolar(heap) == &c);
    print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("El heap no está vacío", !heap_esta_vacio(heap));
    print_test("El máximo es b", heap_ver_max(heap) == &b);
    print_test("Desencolar devuelve b", heap_desencolar(heap) == &b);
    print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("El heap no está vacío", !heap_esta_vacio(heap));
    print_test("El máximo es a", heap_ver_max(heap) == &a);
    print_test("Desencolar devuelve a", heap_desencolar(heap) == &a);
    print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("El máximo del heap es NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar devuelve NULL", heap_desencolar(heap) == NULL);
    heap_encolar(heap, &a);
    heap_desencolar(heap);
    heap_encolar(heap, &b);
    heap_desencolar(heap);
    heap_encolar(heap, &a);
    heap_desencolar(heap);
    heap_encolar(heap, &b);
    heap_desencolar(heap);
    heap_encolar(heap, &a);
    heap_encolar(heap, &b);
    print_test("Se encoló y desencoló varias veces sin errores", true);
    print_test("El heap no está vacío", !heap_esta_vacio(heap));    
    
    heap_destruir(heap, NULL);
}

void prueba_encolar_null() {

    /* Declaro Variables */
    heap_t* heap = heap_crear(comparar_numeros);

    /* Inicio de pruebas */
	printf("\nPRUEBA ENCOLAR NULL\n");
    heap_encolar(heap, NULL);
    print_test("NULL se encoló correctamente", heap_ver_max(heap) == NULL);
    print_test("El heap no está vacío", !heap_esta_vacio(heap));
    heap_desencolar(heap);
    print_test("El heap está vacío", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
}

void prueba_heap_desencolar_destruir() {
    
    /* Declaro Variables */
    heap_t* heap = heap_crear(comparar_numeros);
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int));
    *a = 1;
    *b = 2;
    *c = 3;

    /* Inicio de pruebas */
    heap_encolar(heap, a);
    heap_encolar(heap, b);
    heap_encolar(heap, c);
    heap_destruir(heap, free);
}

void prueba_heap_volumen() {

    /* Declaro Variables */
	int prueba = 0; // Si algo falla, su valor es -1
    int* vector = malloc(sizeof(int) * 1000);
	heap_t* heap = heap_crear(comparar_numeros);
	
	/* Inicio de pruebas */
	printf("\nPRUEBA HEAP VOLUMEN\n");
	for (int i = 0; i < 1000; i++) {
    	vector[i] = i;
		heap_encolar(heap, vector+i);
     	if (heap_ver_max(heap) != vector+i) prueba = -1;
   	}
   	for (int i = 999; i >= 0 ; i--) {
    	void* valor = heap_desencolar(heap);
     	if (valor != vector+i) {
       		prueba = -1;
       		break;
     	}
   	}
   	print_test("Se cumple la invariante para 1000 casos", prueba == 0);
	heap_destruir(heap, NULL);
   	free(vector);
}

void prueba_heap_sort() {

	/* Declaro Variables */
	int prueba = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	void* arreglo[5] = {&d, &e, &c, &a, &b};

	/* Inicio de pruebas */
    printf("\nPRUEBAS HEAPSORT\n");
	heap_sort(arreglo, 5, comparar_numeros);
	for (int i = 0; i < 5; i++) if (*(int*)arreglo[i] != i+1) prueba = -1;
	print_test("El arreglo esta ordenado", prueba == 0);
}

 void pruebas_heap_alumno(void) {
    prueba_heap_nuevo();
    prueba_heap_crear_arr();
    prueba_encolar_y_desencolar();
    prueba_encolar_null();
    prueba_heap_desencolar_destruir();
    prueba_heap_volumen();
    prueba_heap_sort();
 }