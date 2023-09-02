#define _POSIX_C_SOURCE 200809L
#include "cadenas.h"
#include <stdlib.h>
#include <string.h>

void rstrip(char* cadena, char caracter) {
  size_t tam = strlen(cadena);
    if (cadena[tam - 1] == caracter) cadena[tam - 1] = '\0';
}

bool is_digit(char* cadena) {
  if (cadena[0] == '\0') return false;
  for (int i = 0; cadena[i] != '\0'; i++) {
    if ('0' > cadena[i] || cadena[i] > '9') return false;
  }
  return true;
}

char **split(const char *str, char sep) {
  size_t cont = 0;
  for (int i = 0; str[i] != '\0'; i++) if (str[i] == sep) cont++; // O(n)
  char** vector = malloc(sizeof(char*) * (cont + 2));
  if (vector == NULL) return NULL;
  size_t pos = 0; // Posición en el vector.
  size_t inicio = 0; // Donde inicia lo que va en vector[pos] en str.
  for (size_t n = 0; str[n] != '\0'; n++) {
    if (str[n] == sep) {
      vector[pos] = strndup(str + inicio, n - inicio);
      inicio = n + 1;
      pos++;
    }
  }
  vector[pos] = strdup(str + inicio);
  vector[pos+1] = NULL;
  return vector;
}

void free_strv(char *strv[]) {
  for (int i = 0; strv[i] != NULL; i++) {
    free(strv[i]);
  }
  free(strv);
}