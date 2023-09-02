#include "cola.h"
#include <stdlib.h>

typedef struct nodo {
	void* dato;
	struct nodo* prox;
} nodo_t;

struct cola {
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

cola_t* cola_crear() {
	cola_t* cola = malloc(sizeof(cola_t));
	if (cola == NULL) return NULL;
	cola->prim = NULL;
	cola->ult = NULL;
	cola->largo = 0;
	return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {
	while (!cola_esta_vacia(cola)) {
		void* dato = cola_desencolar(cola);
		if (destruir_dato != NULL) {
			destruir_dato(dato);
		}
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t* cola) {
	return cola->prim == NULL && cola->ult == NULL;
}

bool cola_encolar(cola_t* cola, void* valor) {
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) return false;
	nodo->dato = valor;
	nodo->prox = NULL;
	if (cola_esta_vacia(cola)) {
		cola->prim = nodo;
	} else {
		cola->ult->prox = nodo;
	}
	cola->ult = nodo;
	cola->largo++;
	return true;
}

void* cola_ver_primero(const cola_t *cola) {
	if (cola->prim == NULL) return NULL;
	return cola->prim->dato;
}

void* cola_desencolar(cola_t *cola) {
	if (cola_esta_vacia(cola)) return NULL;
	void* valor = cola->prim->dato;
	nodo_t* aux = cola->prim;
	cola->prim = cola->prim->prox;
	if (cola->prim == NULL) cola->ult = NULL;
	free(aux);
	cola->largo--;
	return valor;
}

size_t cola_largo(cola_t *cola) {
	return cola->largo;
}
