# Bloque Python, pregunta 2 - Traza 1: usa un ALIAS de tipo generico (Vector)
from typing import TypeVar, Iterable, Tuple

T = TypeVar('T', int, float, complex)
Vector = Iterable[Tuple[T, T]]


def inproduct(v: Vector[T]) -> T:
    return sum(x*y for x, y in v)


def dilate(v: Vector[T], scale: T) -> Vector[T]:
    return ((x * scale, y * scale) for x, y in v)


vec = []

if __name__ == "__main__":
    datos = [(1, 2), (3, 4)]
    print(inproduct(datos))          # 1*2 + 3*4 = 14
    print(list(dilate(datos, 10)))   # [(10, 20), (30, 40)]
