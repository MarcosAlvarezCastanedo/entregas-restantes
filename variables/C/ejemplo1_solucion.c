/* Ejemplo 1 (2.1) - SOLUCION conforme a DCL30-C
 * Idea: ningun puntero sobrevive al objeto al que apunta.
 *  - Los arrays pasan a tener duracion de almacenamiento estatica ('static'),
 *    asi que existen durante todo el programa y es seguro devolver su direccion.
 *  - Los arrays se declaran sin tamano explicito (STR11-C): el compilador
 *    reserva exactamente la cadena mas su terminador '\0'.
 *  - Desaparece la variable global: la cadena se pasa por parametro
 *    (DCL15-C / DCL19-C: ambito minimo).
 */
#include <stdio.h>

static const char *funcion1(void) {
  static const char array[] = "Mi Cadena";
  return array;
}

static const char *funcion2(void) {
  static const char c_str[] = "Todo va bien";
  return c_str;
}

static void funcion3(const char *cadena) {
  printf("%s\n", cadena);
}

int main(void) {
  const char *p = funcion1();
  printf("%s\n", p);

  p = funcion2();
  funcion3(p);
  printf("%s\n", p);

  return 0;
}
