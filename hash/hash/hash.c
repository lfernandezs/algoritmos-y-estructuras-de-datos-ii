#include "hash.h"
#include <stdlib.h>


typedef enum {vacio, ocupado, borrado} estado_t;

typedef struct campo {
  const char* clave;
  void* valor;
  estado_t estado;
} campo_t;

struct hash {
  size_t capacidad;
  size_t cantidad;
  campo_t* campos;
  hash_destruir_dato_t hash_destruir_dato;
};

void inicializar_campos(hash_t* hash);

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
  hash_t* hash = malloc(sizeof(hash_t));
  if (hash == NULL) return NULL;
  hash->capacidad = 11;
  hash->cantidad = 0;
  hash->campos = malloc(sizeof(campo_t) * hash->capacidad);
  if (hash->campos == NULL) {
    free(hash);
    return NULL;
  }
  inicializar_campos(hash);
  hash->hash_destruir_dato = destruir_dato;
  return hash;
}

void inicializar_campos(hash_t* hash) {
  for (int i = 0; i < hash->capacidad; i++) {
    hash->campos[i].clave = NULL;
    hash->campos[i].valor = NULL;
    hash->campos[i].estado = vacio;
  }
}
