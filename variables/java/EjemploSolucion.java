// Bloque Java (3.1) - SOLUCION conforme a DCL02-J
// La variable del for se declara 'final': si alguien intenta asignarle algo,
// el compilador lo rechaza. El valor que se quiere procesar va en otra variable.
// (Integer.valueOf sustituye a 'new Integer', obsoleto desde Java 9.)
import java.util.Arrays;
import java.util.List;

public class EjemploSolucion {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(13, 14, 15);
        boolean first = true;

        System.out.println("Processing list...");
        for (final Integer i : list) {
            Integer item = i;                 // copia explicita con la que si se trabaja
            if (first) {
                first = false;
                item = Integer.valueOf(99);
            }
            System.out.println(" New item: " + item);
            // Process item
        }

        System.out.println("Modified list?");
        for (final Integer i : list) {
            System.out.println("List item: " + i);
        }
    }
}
