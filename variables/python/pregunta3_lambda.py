# Bloque Python, pregunta 3.

# Enunciado: lambda asignada a un nombre (PEP 8 lo desaconseja, aviso E731)
f = lambda x: 2*x


# Forma recomendada por PEP 8: una funcion normal, con nombre y anotaciones
def doble(x: float) -> float:
    return 2 * x


if __name__ == "__main__":
    print(f(21), f.__name__)          # 42 <lambda>   <- nombre inutil en trazas de error
    print(doble(21), doble.__name__)  # 42 doble
