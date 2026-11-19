# Bloque Python, pregunta 1.
# En el PDF el 'return' aparece sin sangria; asi Python da IndentationError.
# Con la sangria correcta:


def greeting(name: str) -> str:
    return 'Hello ' + name


if __name__ == "__main__":
    print(greeting("Marcos"))
    # Las anotaciones NO se comprueban al ejecutar: solo son metadatos.
    print(greeting.__annotations__)
    # Esto lo detecta mypy, pero Python solo falla al llegar a la suma:
    # greeting(42)
