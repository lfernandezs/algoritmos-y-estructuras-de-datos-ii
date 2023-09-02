#include "pila.h"
#include <stdlib.h>

#define TAMANO_INICIAL 2
#define FACTOR_AGRANDAR 2
#define FACTOR_ACHICAR 2
#define FACTOR_EVALUAR 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

 pila_t* pila_crear(void){
   pila_t* pila = malloc(sizeof(pila_t));
   if (pila == NULL){
     return NULL;
   }
   pila->datos = malloc(TAMANO_INICIAL * sizeof(void*));
   if (pila->datos == NULL){
     free(pila);
     return NULL;
   }
   pila->cantidad = 0;
   pila->capacidad = TAMANO_INICIAL;

   return pila;
 }

 void pila_destruir(pila_t* pila){
   free(pila->datos);
   free(pila);
 }

 bool pila_esta_vacia(const pila_t *pila){
   return (pila->cantidad == 0);
 }

 bool pila_apilar(pila_t *pila, void* valor) {
   if (pila->capacidad == pila->cantidad) {
     void** datos_nuevo = realloc(pila->datos, sizeof(void*) * FACTOR_AGRANDAR * pila->capacidad);
     if (datos_nuevo == NULL) {
       return false;
     }
     pila->datos = datos_nuevo;
     pila->capacidad = FACTOR_AGRANDAR * pila->capacidad;
   }
   pila->datos[pila->cantidad] = valor;
   pila->cantidad++;
   return true;
 }

 void* pila_ver_tope(const pila_t *pila){
   if (pila->cantidad == 0){
     return NULL;
   }
   return pila->datos[pila->cantidad-1];
 }

 void* pila_desapilar(pila_t *pila){
   if (pila->cantidad == 0){
     return NULL;
   }
   void* valor = pila->datos[pila->cantidad-1];
   pila->cantidad--;
   if ((pila->cantidad) <= (pila->capacidad/FACTOR_EVALUAR) && pila->capacidad > TAMANO_INICIAL+1) { // Para que la capacidad mínima sea 2
     void** datos_nuevo = realloc(pila->datos, sizeof(void*) * pila->capacidad / FACTOR_ACHICAR);
     if (datos_nuevo != NULL) {
       pila->datos = datos_nuevo;
       pila->capacidad = pila->capacidad / FACTOR_ACHICAR;
     }
   }
   return valor;
 }
