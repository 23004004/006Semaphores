# 006 Semaphores

## Descripción

Este proyecto simula un parqueo usando hilos (`pthread`) y semáforos en C.
Varios carros intentan estacionarse en un espacio limitado si no hay lugar a esperar.

---

## Tecnologías

* C
* pthreads
* semáforos (`semaphore.h`)
* mutex

---

## Funcionamiento

* Se crean varios carros (hilos).
* El parqueo tiene espacios limitados.
* Cada carro:

  * Llega
  * Espera si está lleno (`sem_wait`)
  * Se estaciona (1–5 segundos)
  * Sale y libera espacio (`sem_post`)
* Se calcula el tiempo promedio de espera.

---

## Sincronización

* **Semáforo:** controla espacios disponibles
* **Mutex:** evita conflictos al imprimir en consola

---

## Compilación y ejecución

```bash
gcc main.c semaphores.c -o a -lpthread
./a
```

---

## Configuración

```c
#define NUM_CARS   10
#define NUM_SPACES  2
```
