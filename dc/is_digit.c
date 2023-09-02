#include <stdbool.h>

bool is_digit(char* cadena) {
  for (int i = 0; cadena[i] != '\0'; i++) {
    if ('0' > cadena[i] || cadena[i] > '9') return false;
  }
  return true;
}