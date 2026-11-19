/* Ejemplo 2 (2.2) - SOLUCION conforme a DCL38-C
 * Cambios:
 *  - 'int data[];' -> miembro de array flexible de verdad (C99).
 *  - sizeof(struct) ya NO incluye data, asi que se reserva array_size (no array_size-1).
 *    De paso desaparece el desbordamiento de (array_size - 1) cuando array_size es 0.
 *  - Se trata de verdad el fallo de malloc y se libera la memoria.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct flexArrayStruct {
  size_t num;
  int data[];                 /* flexible array member: siempre el ultimo campo */
};

static int func(size_t array_size) {
  /* Evita que sizeof(int) * array_size desborde (INT30-C) */
  if (array_size > (SIZE_MAX - sizeof(struct flexArrayStruct)) / sizeof(int)) {
    return -1;
  }

  struct flexArrayStruct *structP
    = malloc(sizeof(struct flexArrayStruct) + sizeof(int) * array_size);
  if (structP == NULL) {
    return -1;                /* fallo de malloc tratado */
  }

  structP->num = array_size;

  for (size_t i = 0; i < array_size; ++i) {
    structP->data[i] = 1;     /* ahora si: data tiene array_size elementos */
  }

  printf("Reservados %zu elementos, el ultimo vale %d\n",
         structP->num, array_size > 0 ? structP->data[array_size - 1] : 0);

  free(structP);              /* MEM31-C: liberar lo reservado */
  return 0;
}

int main(void) {
  if (func(10) != 0) {
    fprintf(stderr, "Error reservando memoria\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
