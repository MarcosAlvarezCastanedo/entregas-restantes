/* Ejemplo 3 (2.3, el del switch) - CODIGO ERRONEO DEL ENUNCIADO
 * Regla incumplida: DCL41-C (Do not declare variables inside a switch statement
 *                            before the first case label)
 * Anadido respecto al PDF: la definicion de f() y el main(), para poder ejecutarlo.
 * Uso:  ./ejemplo3_original        -> llama a func(0)
 *       ./ejemplo3_original 5      -> llama a func(5)
 */
#include <stdio.h>
#include <stdlib.h>           /* anadido: atoi para el main */

extern void f(int i);

void func(int expr) {
  switch (expr) {
    int i = 4;                /* ERROR: nunca se ejecuta, el switch salta por encima */
    f(i);                     /* ERROR: codigo muerto */
  case 0:
    i = 17;
  default:
    printf("%d\n", i);        /* si expr != 0, i esta SIN inicializar */
  }
}

/* --- anadido para poder ejecutar --- */
void f(int i) {
  printf("f() ha recibido %d\n", i);
}

int main(int argc, char *argv[]) {
  int expr = 0;
  if (argc > 1) {
    expr = atoi(argv[1]);
  }
  func(expr);
  return 0;
}
