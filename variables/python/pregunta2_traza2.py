# Bloque Python, pregunta 2 - Traza 2: el mismo tipo escrito entero cada vez
from typing import TypeVar, Iterable, Tuple

T = TypeVar('T', int, float, complex)


def inproduct(v: Iterable[Tuple[T, T]]) -> T:
    return sum(x*y for x, y in v)


def dilate(v: Iterable[Tuple[T, T]], scale: T) -> Iterable[Tuple[T, T]]:
    return ((x * scale, y * scale) for x, y in v)


vec = []

if __name__ == "__main__":
    datos = [(1, 2), (3, 4)]
    print(inproduct(datos))          # 14
    print(list(dilate(datos, 10)))   # [(10, 20), (30, 40)]
