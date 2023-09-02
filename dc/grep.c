#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cola.h"

bool is_digit(char* cadena) {
  for (int i = 0; cadena[i] != '\0'; i++) {
    if ('0' > cadena[i] || cadena[i] > '9') return false;
  }
  return true;
}

bool evaluar_comandos(int argc, char** argv) {
  if (argc < 3 || argc > 4) {
    fprintf(stderr, "%s", "Cantidad de parametros erronea\n");
    return false;
  }
  if (!is_digit(argv[2])) {
    fprintf(stderr, "%s", "Tipo de parametro incorrecto\n");
    return false;
  }
  if (argc == 4) {
    FILE* file = fopen(argv[3], "r");
    if (!file) {
      fprintf(stderr, "%s", "No se pudo leer el archivo indicado\n");
      return false;
    }
    fclose(file);
  }
  return true;
}

char* evaluar_path(int argc, char** argv) {
  char* path;
  if (argc == 4) path = argv[3];
  else path = NULL;
  return path;
}

void buscar_coincidencias(char* cadena, int contexto, char* path) {
  FILE* file;
  if (path == NULL) file = stdin;
  else file = fopen(path, "r");
  cola_t* cola = cola_crear();
  char* linea = NULL;
  size_t tam = 0;
  while (getline(&linea, &tam, file) > 0) {
    if (cola_largo(cola) > contexto) free(cola_desencolar(cola));
    cola_encolar(cola, strdup(linea));
    if (strstr(linea, cadena)) {
      while (!cola_esta_vacia(cola)) {
        char* aparicion= (char*)cola_desencolar(cola);
        printf("%s", aparicion);
        free(aparicion);
      }
    }
  }
  cola_destruir(cola, free);
  if (path != NULL) fclose(file);
  free(linea);
}

int main(int argc, char **argv) {
  if (!evaluar_comandos(argc, argv)) return -1;
  char* path = evaluar_path(argc, argv);
  buscar_coincidencias(argv[1], atoi(argv[2]), path);
  return 0;
}