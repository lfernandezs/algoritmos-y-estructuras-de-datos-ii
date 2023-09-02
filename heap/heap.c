#include <stdlib.h>
#include "heap.h"
#include <stdio.h>

#define TAM_I 31
#define FACTOR_REDIMENSIONAR 2

/* Definición del struct heap */
struct heap {
    void** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

/* Prototipos de funciones auxiliares */
void upheap(void** arreglo, size_t pos, cmp_func_t cmp);
void downheap(void** arreglo, size_t tam, size_t pos, cmp_func_t cmp);
void swap(void** arreglo, size_t pos1, size_t pos2);
bool redimensionar(heap_t* heap, size_t tam);
void heapify(void *arreglo[], size_t n, cmp_func_t cmp);

/* Primitivas del heap */
heap_t *heap_crear(cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;
    heap->datos = malloc(sizeof(void*) * TAM_I);
    if (!heap->datos) {
        free(heap);
        return NULL;
    }
    heap->tam = TAM_I;
    heap->cant = 0;
    heap->cmp = cmp;
    return heap;
}

size_t heap_cantidad(const heap_t* heap) {
    return heap->cant;
}

bool heap_esta_vacio(const heap_t* heap) {
    return heap->cant == 0;
}

bool heap_encolar(heap_t* heap, void* elem) {
    if (heap->cant == heap->tam) {
        if (!redimensionar(heap, FACTOR_REDIMENSIONAR * heap->tam)) return false;
    }
    heap->datos[heap->cant] = elem;
    upheap(heap->datos, heap->cant, heap->cmp);
    heap->cant++;
    return true;
}

void *heap_ver_max(const heap_t* heap) {
    if (heap->cant > 0) return heap->datos[0];
    return NULL;
}

void *heap_desencolar(heap_t* heap) {
    if (heap->cant == 0) return NULL;
    if (heap->cant <= heap->tam / 4) redimensionar(heap, heap->tam / FACTOR_REDIMENSIONAR);
    void* dato = heap->datos[0];
    heap->datos[0] = heap->datos[heap->cant-1];
    downheap(heap->datos, heap->cant, 0, heap->cmp);
    heap->cant--;
    return dato;
}

void heap_destruir(heap_t* heap, void f(void* e)) {
    if (f) for(size_t i = 0; i < heap->cant; i++) f(heap->datos[i]);
    free(heap->datos);
    free(heap);
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heapify(arreglo, n, cmp);
    heap_t* heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;
    heap->datos = malloc(sizeof(void*) * n);
    if (!heap->datos) {
        free(heap);
        return NULL;
    }
    for (size_t i = 0; i < n; i ++) heap->datos[i] = arreglo[i];
    heap->cant = n;
    heap->tam = n;
    heap->cmp = cmp;
    return heap;
}

/* Heapsort */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    heapify(elementos, cant, cmp);
    for(size_t i = cant - 1; i > 0; i--) {
        swap(elementos, 0, i);
        downheap(elementos, i, 0, cmp);
    }
}

/* Funciones auxiliares */
void upheap(void** arreglo, size_t pos, cmp_func_t cmp) {
    if (pos == 0) return;
    size_t padre = (pos - 1) / 2;
    if (cmp(arreglo[padre], arreglo[pos]) < 0) {
        swap(arreglo, padre, pos);
        upheap(arreglo, padre, cmp);
    }
}

void downheap(void** arreglo, size_t tam, size_t pos, cmp_func_t cmp) {
    if (pos >= tam) return;
    size_t padre = pos;
    size_t izq = 2 * pos + 1;
    size_t der = 2 * pos + 2;
    if (izq < tam && cmp(arreglo[padre], arreglo[izq]) < 0) padre = izq;
    if (der < tam && cmp(arreglo[padre], arreglo[der]) < 0) padre = der;
    if (padre != pos) {
        swap(arreglo, pos, padre);
        downheap(arreglo, tam, padre, cmp);
    }
}

void swap(void** arreglo, size_t pos1, size_t pos2) {
    void* aux = arreglo[pos1];
    arreglo[pos1] = arreglo[pos2];
    arreglo[pos2] = aux;
}

bool redimensionar(heap_t* heap, size_t tam_nuevo) {
    void** datos_nuevo = realloc(heap->datos, sizeof(void*) * tam_nuevo);
    if (!datos_nuevo) return false;
    heap->datos = datos_nuevo;
    heap->tam = tam_nuevo;
    return true;
}

void heapify(void *arreglo[], size_t n, cmp_func_t cmp) {
    for(int i = (int)(n/2) + 1; i >= 0 ; i--) downheap(arreglo, n, i, cmp);
}  
