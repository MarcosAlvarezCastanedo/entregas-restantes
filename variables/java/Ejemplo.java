// Bloque Java (3.1) - CODIGO ERRONEO DEL ENUNCIADO adaptado a un fichero con main
// Regla incumplida: DCL02-J (Do not modify the collection's elements during an
//                            enhanced for statement)
// Anadido respecto al PDF: los import, la clase y el main.
import java.util.Arrays;
import java.util.List;

public class Ejemplo {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(new Integer[] {13, 14, 15});
        boolean first = true;

        System.out.println("Processing list...");
        for (Integer i : list) {
            if (first) {
                first = false;
                i = new Integer(99);   // ERROR: solo cambia la copia local 'i', no la lista
            }
            System.out.println(" New item: " + i);
            // Process i
        }

        System.out.println("Modified list?");
        for (Integer i : list) {
            System.out.println("List item: " + i);
        }
    }
}
