# PHILOSOPHERS

## ¿Qué es un hilo?

Un hilo es una unidad de ejecución dentro de un proceso. Comparte el mismo espacio de memoria con otros hilos del mismo proceso, lo que permite la comunicación eficiente, pero también genera problemas de sincronización (race conditions y deadlocks).

### 🔧 Creación y Manejo de Hilos en C

Para trabajar con hilos en C, usaremos la biblioteca **pthread**. Las funciones principales son:

| Función                                         | Descripción                                      |
| ----------------------------------------------- | ------------------------------------------------ |
| `pthread_create(&thread, NULL, function, args)` | Crea un hilo                                     |
| `pthread_join(thread, NULL)`                    | Espera a que el hilo termine                     |
| `pthread_detach(thread)`                        | Deja que el hilo se ejecute sin bloquear el main |

---

## Problemas de sincronización

### Race Condition

Si dos hilos modifican la misma variable simultáneamente, el resultado es impredecible.

#### 🔴 Ejemplo :

```c
int counter = 0;

void *increment(void *arg)
{
	for (int i = 0; i < 10; i++)
		counter++;
	return NULL;
}
```

Al ejecutar dos hilos con esta función, el resultado podría no ser 20.

#### 🟢 Solución :

```c
int counter = 0;
pthread_mutex_t lock;
pthread_mutex_init(&lock, NULL);

void *increment(void *arg)
{
	for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}
```

Crear un mutex e inciarlo. Dentro de las funciones, bloquear el mutex, lo que iniciará la protección, ejecutar la función y desbloquear el mutex, finaliza la protección y da acceso a otros hilos.

Con esto, el valor de i incrementará hasta llegar al tope y dará acceso a la variable a otros hilos, haciendo que un segundo hilo aumente el valor de la variable ya modificada. Finalmente, tras ejecutar dos hilos con esta función, i tendrá un valor final de 20.

### ⛔ Deadlock

Un deadlock (bloqueo mutuo) ocurre cuando dos o más hilos quedan bloqueados esperando recursos que nunca se liberan, haciendo que el programa se quede atascado indefinidamente.

#### 🔴 Ejemplo con Philosophers:

Filósofo 1 toma el tenedor izquierdo.
Filósofo 2 toma el tenedor izquierdo (del siguiente).
Ambos esperan el otro tenedor… y nunca lo obtienen. 🚫

#### 🟢 Solución :

- Usar orden de adquisición de recursos (Ej: el filósofo con ID impar toma el derecho primero, los pares el izquierdo primero).
- Limitar el número de procesos (si hay N filósofos, comerán N-1 a la vez).
- Usar un monitor o semáforo en vez de mutex.
- Implementar un "tiemout" para detectar hilos bloqueados (Si un filósofo espera demasiado tiempo, puede soltar su tenedor y reintentar).

---

## Herramientas

### 🔒 MUTEX

Un mutex (mutual exclusion) es una herramienta para evitar que múltiples hilos accedan simultáneamente a una sección crítica del código. Asegura que sólo un hilo pueda modificar una variable a la vez.

#### 🛠 Modo de uso

1. Declarar el mutex

```c
   pthread_mutex_t lock;
```

2. Iniciarlizar el mutex

```c
   pthread_mutex_init(&lock, NULL);
```

La función recibe como parámetro el mutex a inicializar y la personalización del mutex:

- PTHREAD_MUTEX_NORMAL
  - Si un hilo intenta hacer pthread_mutex_unlock() sin haber hecho pthread_mutex_lock(), el comportamiento es indefinido.
  - Si un hilo intenta bloquearlo dos veces, se queda bloqueado (deadlock).
- PTHREAD_MUTEX_ERRORCHECK
  - Detecta errores como:
    • Intentar desbloquear un mutex no bloqueado.
    • Intentar bloquear el mismo mutex dos veces en el mismo hilo.
  - Devuelve un error en lugar de desbloquearse.
- PTHREAD_MUTEX_RECURSIVE
  - Un mismo hilo puede bloquear el mutex múltiples veces sin bloquearse.
  - Debe desbloquearlo el mismo número de veces.
  - Útil cuando una función llama a otra función que ya tiene el mutex bloqueado.
  - Puede ocultar problemas de diseño si se usa mal.
- PTHREAD_MUTEX_DEFAULT
  - Comportamiento definido por el sistema operativo.
  - Similar a PTHREAD_MUTEX_NORMAL, pero su comportamiento puede variar.
  - En general, no se recomienda usarlo explícitamente porque su funcionamiento puede ser diferente según la implementación de pthreads.

3. Bloquear el mutex

```c
   pthread_mutex_lock(&lock);
```

4. Ejecutar el código.

5. Desbloquear el mutex

```c
   pthread_mutex_unlock(&lock);
```

6. Destruir el mutex

```c
   pthread_mutex_destroy(&mutex);
```

#### ❌ Problemas comunes con Mutex

1. Olvidar pthread_mutex_unlock → Bloqueo total
2. Olvidar pthread_mutex_init → Comportamiento indefinido
3. Destruir un mutex antes de terminar (pthread_mutex_destroy)
4. Usar un mutex en memoria compartida incorrectamente (casos avanzados)

#### 🏆 Resumen

✔ **pthread_mutex_t** → Declara un mutex.  
✔ **pthread_mutex_init(&mutex, NULL)** → Lo inicializa.  
✔ **pthread_mutex_lock(&mutex)** → Bloquea el acceso.  
✔ **pthread_mutex_unlock(&mutex)** → Libera el acceso.  
✔ **pthread_mutex_destroy(&mutex)** → Lo destruye cuando ya no se usa.

#### 💡 ¿Cuál podría ser útil para Philosophers?

- **Para sincronizar tenedores**: PTHREAD_MUTEX_NORMAL o PTHREAD_MUTEX_ERRORCHECK
- **Si hay posibilidad de bloqueo dentro de funciones anidadas**: PTHREAD_MUTEX_RECURSIVE
- **Para debugging y detección de errores**: PTHREAD_MUTEX_ERRORCHECK

### 🚦 SEMÁFOROS

Los semáforos son mecanismos de sincronización que controlan el acceso a recursos compartidos en entornos concurrentes. A diferencia de MUTEX, los semáforos son para procesos (fork).

#### 📌 Tipos de Semáforos

Existen dos tipos principales:

**1️⃣ Semáforos Binarios (Mutexes)**

- Solo pueden tener los valores 0 (bloqueado) y 1 (libre).
- Son equivalentes a pthread_mutex_t.

**2️⃣ Semáforos Contadores**

- Pueden tener valores mayores a 1.
- Se usan para controlar múltiples recursos compartidos (ej. tenedores en Philosophers).

#### 🛠 Uso de Semáforos

En sistemas Unix/Linux, los semáforos se manejan con sem_t y las funciones de la librería POSIX como:

- **sem_init** : inicializa el semáforo previamente declarado, similar al mutex_init.

  ```c
  sem_init(&sem, 0, 1)
  ```

  En este caso, se inicializa un semáforo contador donde los argumentos son:

  - &sem : variable semáforo declarada.
  - 0 : indica que el semáforo no está compartido entre procesos ('1' si lo está).
  - 1 : indica el valor inicial como libre o disponible ('0' si no lo está).

- **sem_wait** : Espera el recurso. Cronológicamente es similar al mutex_lock.
- **sem_post** : Libera el recurso, como lo hace mutex_unlock.
- **sem_destroy** : destruye el semáforo.

#### 🍽 Semáforos en Philosophers

```c

    sem_t forks; // Un solo semáforo para todos los tenedores

    void philosopher(int id)
    {
    	while (1)
    	{
    		printf("Filósofo %d está pensando\n", id);
    		sem_wait(&forks); // 🚦 Toma un tenedor
    		sem_wait(&forks); // 🚦 Toma el otro tenedor
    		printf("Filósofo %d está comiendo\n", id);
    		sleep(1);
    		sem_post(&forks); // 🚦 Suelta un tenedor
    		sem_post(&forks); // 🚦 Suelta el otro tenedor
    	}
    }
```
