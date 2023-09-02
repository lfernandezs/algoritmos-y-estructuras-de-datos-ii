#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CAPACIDAD_INICIAL 30;

typedef enum {vacio, ocupado, borrado} estado_t;

/* Definición del struct campo */
typedef struct campo {
  char* clave;
  void* valor;
  estado_t estado;
} campo_t;

/* Definición del struct hash */
struct hash {
  size_t capacidad;
  size_t cantidad;
  size_t borrados;
  campo_t* campos;
  hash_destruir_dato_t hash_destruir_dato;
};

/* Definición del struct iterador */
struct hash_iter{
  const hash_t* hash;
  size_t pos;
};

/* Prototipos de funciones*/
void inicializar_campos(hash_t* hash);
size_t buscar_posicion_no_ocupada(const hash_t* hash, const char* clave);
bool redimensionar_hash(hash_t* hash);
size_t buscar_posicion_clave(const hash_t* hash, const char* clave);

/* *****************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/

/* Función de hash */
size_t f_hash(const char *key, size_t h_size) {
  size_t hash_val = 5381;
  while (*key != '\0') hash_val = ((hash_val << 5) + hash_val) + (size_t) *key++;
  return (hash_val % h_size);
}

/* Funciones cátedra */
hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
  hash_t* hash = malloc(sizeof(hash_t));
  if (!hash) return NULL;
  hash->capacidad = CAPACIDAD_INICIAL;
  hash->cantidad = 0;
  hash->borrados = 0;
  hash->hash_destruir_dato = destruir_dato;
  hash->campos = calloc(hash->capacidad, sizeof(campo_t));
  if (!hash->campos) {
    free(hash);
    return NULL;
  }
  return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
  if (clave == NULL) return false;
  if (((float)hash->cantidad + (float)hash->borrados)/ (float)hash->capacidad > 0.7) {
    if (!redimensionar_hash(hash)) return false;
  }
  size_t pos = buscar_posicion_clave(hash, clave); // Busco si la clave ya se encuentra
  if (pos >= hash->capacidad) {
    pos = buscar_posicion_no_ocupada(hash, clave);
    if (hash->campos[pos].estado == borrado) hash->borrados--;
    hash->campos[pos].clave = strdup(clave);
    hash->cantidad++;
  } else {
    if (hash->hash_destruir_dato) hash->hash_destruir_dato(hash->campos[pos].valor);
  }
  hash->campos[pos].valor = dato;
  hash->campos[pos].estado = ocupado;
  return true;

}

void *hash_borrar(hash_t *hash, const char *clave){
  size_t pos = buscar_posicion_clave(hash, clave);
  if (pos >= hash->capacidad) return NULL;
  void* valor = hash->campos[pos].valor;
  free(hash->campos[pos].clave);
  hash->campos[pos].estado = borrado;
  hash->campos[pos].clave = NULL;
  hash->campos[pos].valor = NULL;
  hash->cantidad --;
  hash->borrados++;
  return valor;
}

void *hash_obtener(const hash_t *hash, const char *clave){
  size_t pos = buscar_posicion_clave(hash, clave);
  if (pos >= hash->capacidad) return NULL;
  return hash->campos[pos].valor;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
  size_t pos = buscar_posicion_clave(hash, clave);
  return (pos < hash->capacidad);
}

size_t hash_cantidad(const hash_t *hash){
  return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
  for (int i = 0; i < hash->capacidad; i++) {
    if (hash->campos[i].estado == ocupado) {
      free(hash->campos[i].clave);
      if (hash->hash_destruir_dato) hash->hash_destruir_dato(hash->campos[i].valor);
    }
  }
  free(hash->campos);
  free(hash);
}

/*funciones nuestras */
bool redimensionar_hash(hash_t* hash) {
  campo_t* campos_nuevos = calloc(hash->capacidad * 2, sizeof(campo_t));
  if (!campos_nuevos) return false;
  campo_t* campos_viejos = hash->campos;
  hash->campos = campos_nuevos;
  size_t capacidad_anterior = hash->capacidad;
  hash->capacidad *= 2;
  hash->cantidad = 0;
  hash->borrados = 0;
  for (int i = 0; i < capacidad_anterior; i++) {
    if (campos_viejos[i].clave != NULL) {
      hash_guardar(hash, campos_viejos[i].clave, campos_viejos[i].valor);
      free(campos_viejos[i].clave);
    }
  }
  free(campos_viejos);
  return true;
}


size_t buscar_posicion_no_ocupada(const hash_t* hash, const char* clave) {
  size_t pos = f_hash(clave, hash->capacidad);
  while (hash->campos[pos].estado == ocupado) {
    if (pos == hash->capacidad - 1) pos = 0;
    else pos++;
  }
  return pos;
}

size_t buscar_posicion_clave(const hash_t* hash, const char* clave) {
  size_t pos = f_hash(clave, hash->capacidad);
while (hash->campos[pos].estado != ocupado || strcmp(hash->campos[pos].clave, clave) != 0) {
    if (hash->campos[pos].estado == vacio) return hash->capacidad; // Devuelvo una posición inválida si no se encuentra la clave
    if (pos >= hash->capacidad - 1) pos = 0;
    else pos++;
  }
  return pos;
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash){
  hash_iter_t* iter = malloc(sizeof(hash_iter_t));
  if(!iter) return NULL;
  iter->hash = hash;
  iter->pos = 0;
  while (iter->pos < iter->hash->capacidad && iter->hash->campos[iter->pos].clave == NULL) {
    iter->pos++;
  }
  return iter;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
  return (iter->pos == iter->hash->capacidad);
}

bool hash_iter_avanzar(hash_iter_t *iter){
  if (hash_iter_al_final(iter)) return false;
  iter->pos++;
  while (iter->pos < iter->hash->capacidad && iter->hash->campos[iter->pos].clave == NULL) {
    iter->pos++;
  }
  return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
  if (hash_iter_al_final(iter)) return NULL;
  return iter->hash->campos[iter->pos].clave;
}

void hash_iter_destruir(hash_iter_t* iter){
  free(iter);
}
