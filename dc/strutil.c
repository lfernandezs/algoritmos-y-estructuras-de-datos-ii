#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include <string.h>
#include <stdlib.h>

char *substr(const char *str, size_t n) {
  char* str_copia = (char*)malloc(sizeof(char) * (n+1));
  if (str_copia == NULL) return NULL;
  size_t i = 0;
  while (i < n) {
    if (str[i] == '\0') break;
    str_copia[i] = str[i];
    i++;
  }
  str_copia[i] = '\0';
  return str_copia;
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

char *join(char **strv, char sep) {
  size_t cont = 0;
  for (int i = 0; strv[i] != NULL; i++) {
    cont += strlen(strv[i]);
    if (sep != '\0') cont++; // Si sep es \0 no lo considero.
  }
  if (sep == '\0' || strv[0] == NULL) cont++; // Agrego espacio para el \0 final obligatorio de la cadena.
  char* str = malloc(sizeof(char) * cont);
  int i = 0; // Posición del vector.
  int j = 0; // Posición de la cadena del vector.
  for (int k = 0; k < cont-1; k++) { // Posición en str.
    if (strv[i] == NULL) break;
    if (strv[i][j] == '\0') {
      if (sep == '\0') k--; // Si sep es \0 no agrego nada.
      else str[k] = sep;
      i++;
      j = 0;
      continue;
    }
    str[k] = strv[i][j];
    j++;
  }
  str[cont-1] = '\0';
  return str;
}

void free_strv(char *strv[]) {
  for (int i = 0; strv[i] != NULL; i++) {
    free(strv[i]);
  }
  free(strv);
}
