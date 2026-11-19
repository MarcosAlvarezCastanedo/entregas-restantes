/* Ejercicio extra (5.1) - VERSION CORREGIDA (no la pide el enunciado, es de apoyo)
 * Arregla lo comentado en el guion: include que faltaba, %llu, strtoul en vez de
 * atoi, una variable por declaracion, constantes con nombre, tipos sin signo
 * coherentes, funcion static, y limite para que el factorial no desborde.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

enum {
    N_POR_DEFECTO = 12,
    N_MAXIMO = 20             /* 21! ya no cabe en 64 bits sin signo */
};

static unsigned long long factorial(unsigned int n) {
    unsigned long long resultado = 1ULL;

    for (unsigned int k = 2U; k <= n; ++k) {   /* iterativo: sin recursion */
        resultado *= k;
    }
    return resultado;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Factorial of %d is %llu\n", N_POR_DEFECTO,
               factorial((unsigned int)N_POR_DEFECTO));
        return EXIT_SUCCESS;
    }

    char *fin = NULL;
    errno = 0;
    const unsigned long limite = strtoul(argv[1], &fin, 10);
    if (errno != 0 || fin == argv[1] || *fin != '\0' || argv[1][0] == '-'
        || limite > (unsigned long)N_MAXIMO + 1UL) {
        fprintf(stderr, "Uso: %s [n entre 0 y %d]\n", argv[0], N_MAXIMO + 1);
        return EXIT_FAILURE;
    }

    for (unsigned int n = 0U; n < (unsigned int)limite; ++n) {
        printf("Factorial of %u is %llu\n", n, factorial(n));
    }

    return EXIT_SUCCESS;
}
