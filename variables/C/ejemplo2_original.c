/* Ejemplo 2 (2.2) - CODIGO ERRONEO DEL ENUNCIADO
 * Regla incumplida: DCL38-C (Use the correct syntax when declaring a flexible array member)
 * Anadido respecto al PDF: solo el main() del final, para poder ejecutarlo.
 */
#include <stdlib.h>

struct flexArrayStruct {
  int num;
  int data[1];                /* ERROR: "struct hack"; array de 1 usado como si fuera de N */
};

void func(size_t array_size) {
  /* Space is allocated for the struct */
  struct flexArrayStruct *structP
    = (struct flexArrayStruct *)
      malloc(sizeof(struct flexArrayStruct)
             + sizeof(int) * (array_size - 1));
  if (structP == NULL) {
    /* Handle malloc failure */
  }

  structP->num = array_size;

  /*
   * Access data[] as if it had been allocated
   * as data[array_size].
   */
  for (size_t i = 0; i < array_size; ++i) {
    structP->data[i] = 1;     /* ERROR: para i >= 1 se sale del array declarado (UB) */
  }
}

/* --- anadido para poder ejecutar --- */
int main(void) {
  func(10);
  return 0;
}
