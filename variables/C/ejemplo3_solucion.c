/* Ejemplo 3 (2.3, el del switch) - SOLUCION conforme a DCL41-C
 * La declaracion (y la llamada a f) salen fuera del switch, antes de el,
 * para que se ejecuten SIEMPRE. Asi 'i' nunca se usa sin inicializar.
 * Los 'break' y el comentario de fall-through hacen explicito el flujo (MSC17-C).
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static void f(int i) {
  printf("f() ha recibido %d\n", i);
}

static void func(int expr) {
  int i = 4;                  /* declarada e inicializada ANTES del switch */
  f(i);

  switch (expr) {
  case 0:
    i = 17;
    /* Igual que el original, el caso 0 continua hasta el printf: */
    /* fall through */
  default:
    printf("%d\n", i);
    break;
  }
}

int main(int argc, char *argv[]) {
  long expr = 0;

  if (argc > 1) {
    char *fin = NULL;
    errno = 0;
    expr = strtol(argv[1], &fin, 10);       /* ERR34-C: strtol en vez de atoi */
    if (errno != 0 || fin == argv[1] || *fin != '\0'
        || expr < INT_MIN || expr > INT_MAX) {
      fprintf(stderr, "Uso: %s [entero]\n", argv[0]);
      return EXIT_FAILURE;
    }
  }

  func((int)expr);
  return EXIT_SUCCESS;
}
