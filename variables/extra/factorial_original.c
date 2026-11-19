/* Ejercicio extra (5.1) - CODIGO DEL ENUNCIADO, sin tocar.
 * Ojo: falta #include <stdlib.h> para atoi(). Con gcc 13 (Ubuntu 24.04) es un
 * warning; con gcc 14 o superior es un error y hay que compilar con -std=gnu89
 * o anadir el include.
 */
#include <stdio.h>

unsigned long long int factorial(unsigned int i) {

    if (i <= 1) {
        return 1;
    }
    return i * factorial(i - 1);
}

int main(int argc, char *argv[]) {
    int i = 12, j=3, f = 0;

    if (argc==1) {
        printf("Factorial of %d is %lld\n", i, factorial(i));
    }
    else{
        j = atoi(argv[1]);
        for (f = 0; f<j; f++) {
            printf("Factorial of %d is %lld\n", f, factorial(f));
        }
    }

    return 0;
}
