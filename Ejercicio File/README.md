# Apertura/cierre de fichero: análisis de seguridad de `inseguro.py`

## Enunciado

Proponer un ejemplo de apertura/cierre de fichero en el lenguaje que se prefiera y
analizar sus problemas de ciberseguridad (CERT, apertura/cierre, tests, concurrencia
con threads, etc.). El código se ha generado con IA y después se ha revisado.

## Prompt utilizado

> Escribe en Python 3 una función que mantenga un contador en un fichero de texto
> (abrir, leer el valor, incrementarlo, escribirlo y cerrar) y un programa que la
> llame desde 4 hilos, 100 veces cada uno.

## Código generado (`inseguro.py`)

```python
RUTA = "/tmp/contador.txt"

def incrementar(ruta):
    if not os.path.exists(ruta):          # línea 8
        f = open(ruta, "w")
        f.write("0")
        f.close()
    f = open(ruta, "r")                   # línea 12
    valor = int(f.read())                 # línea 13
    f.close()
    f = open(ruta, "w")                   # línea 15
    f.write(str(valor + 1))
    f.close()

# main: 4 hilos x 100 llamadas a incrementar(RUTA)
print("Valor final:", open(RUTA).read())  # línea 31
```

Con un solo hilo funciona y parece correcto. Con 4 hilos, el resultado esperado es
**400**, pero en 5 ejecuciones se obtuvo **101–102**, y varios hilos abortaron con
`ValueError: invalid literal for int() with base 10: ''`.

## Errores encontrados

### 1. Apertura y cierre no garantizados (fuga de recursos)

**Líneas:** 9–17 y 31.

- Se usa `open()` / `close()` a mano: si `int()` o `write()` lanzan una excepción,
  el `close()` no se ejecuta y el descriptor queda abierto.
- En la línea 31, el fichero nunca se cierra.
- Repetido muchas veces, el proceso agota sus descriptores (denegación de servicio).
- **Solución:** usar `with open(...) as f:` para que el cierre ocurra siempre.

**CERT:** FIO42-C, FIO04-J · **CWE:** CWE-772

### 2. Condición de carrera entre hilos (concurrencia)

**Líneas:** 12–17.

- La secuencia leer → incrementar → escribir no es atómica: dos hilos leen el mismo
  valor y uno de los incrementos se pierde.
- Además, `open(ruta, "w")` vacía el fichero antes de escribir, así que otro hilo
  puede leerlo vacío y fallar. Esto explica los resultados de 101 en vez de 400.
- **Solución:** proteger toda la sección con `threading.Lock()` (y `fcntl.flock()`
  si puede haber varios procesos), abriendo el fichero una sola vez en modo `r+`.

**CERT:** CON43-C, VNA02-J · **CWE:** CWE-362

### 3. TOCTOU, ruta insegura y permisos

**Líneas:** 4, 8–9 y 12.

- **TOCTOU:** se comprueba con `os.path.exists()` y se abre después. Entre ambas
  operaciones, otro proceso puede crear o sustituir el fichero.
- **Ruta predecible en `/tmp`:** el directorio es compartido y `open()` sigue enlaces
  simbólicos. Otro usuario puede crear `/tmp/contador.txt` como symlink a un fichero
  de la víctima y hacer que el programa lo sobrescriba.
- **Permisos:** el fichero se crea con los permisos por defecto (normalmente `0644`),
  así que cualquier usuario local puede leerlo.
- **Solución:** abrir en una sola llamada con
  `os.open(ruta, O_RDWR | O_CREAT | O_NOFOLLOW, 0o600)` dentro de un directorio
  privado (`0700`).

**CERT:** FIO45-C, FIO21-C, FIO06-C · **CWE:** CWE-367, CWE-59, CWE-732

### 4. Entrada del fichero no validada ni controlada

**Línea:** 13.

- `int(f.read())` confía ciegamente en el contenido del fichero:
  - si contiene texto o está vacío, el programa lanza una excepción no controlada;
  - si es enorme, `read()` lo carga entero en memoria.
- **Solución:** leer un tamaño máximo, comprobar que el contenido son dígitos y
  gestionar el error.

**CERT:** ERR33-C, IDS (validación de entrada) · **CWE:** CWE-20, CWE-400

### 5. Ausencia de tests

- No hay ninguna prueba. El fallo de concurrencia solo aparece con varios hilos, así
  que una prueba manual con un hilo da el código por bueno.
- Este es el principal riesgo de usar código generado por IA sin revisarlo: hace lo
  pedido en el caso simple y falla justo en lo que no se probó.
- **Solución:** escribir tests unitarios que cubran:
  - la concurrencia (N hilos × M llamadas = N·M);
  - el rechazo de symlinks;
  - los permisos `0600`;
  - un contenido corrupto;
  - que no haya fuga de descriptores.

## Resumen

| # | Problema | Aspecto del enunciado | CERT |
|---|---|---|---|
| 1 | Cierre no garantizado | Apertura/cierre | FIO42-C |
| 2 | Condición de carrera | Concurrencia con threads | CON43-C |
| 3 | TOCTOU, `/tmp`, symlinks y permisos | Apertura segura | FIO45-C, FIO21-C, FIO06-C |
| 4 | Contenido no validado | Gestión de errores | ERR33-C |
| 5 | Sin tests | Tests | — |

La versión corregida está en `seguro.py` y sus pruebas en `test_seguro.py`
(7 tests, todos superados).
