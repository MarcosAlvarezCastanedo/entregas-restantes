/* Ejemplo 1 (2.1) - CODIGO ERRONEO DEL ENUNCIADO
 * Regla incumplida: DCL30-C (Declare objects with appropriate storage durations)
 * Unico cambio respecto al PDF: el ';' que faltaba en la linea marcada,
 * sin el cual el programa ni siquiera compila.
 */
#include <stdio.h>
#include <stddef.h>

const char *p;

char *funcion1(void) {
  char array[10] = "Mi Cadena";
  /* Initialize array */
  return array;               /* ERROR: devuelve la direccion de una variable local */
}

void funcion2(void) {
  const char c_str[] = "Todo va bien";
  p = c_str;                  /* ERROR: guarda en una global la direccion de una local */
}

void funcion3(void) {
  printf("%s\n", p);          /* ERROR: p apunta a la pila de funcion2, que ya no existe */
}

int main(void) {

  p = funcion1();
  printf("%s\n", p);          /* <- en el PDF falta este ';' */
  funcion2();
  funcion3();
  printf("%s\n", p);

  return 0;
}
