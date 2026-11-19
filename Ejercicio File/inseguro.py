import os
import threading

RUTA = "/tmp/contador.txt"


def incrementar(ruta):
    if not os.path.exists(ruta):
        f = open(ruta, "w")
        f.write("0")
        f.close()
    f = open(ruta, "r")
    valor = int(f.read())
    f.close()
    f = open(ruta, "w")
    f.write(str(valor + 1))
    f.close()


def trabajador():
    for _ in range(100):
        incrementar(RUTA)


if __name__ == "__main__":
    hilos = [threading.Thread(target=trabajador) for _ in range(4)]
    for h in hilos:
        h.start()
    for h in hilos:
        h.join()
    print("Valor final:", open(RUTA).read())
