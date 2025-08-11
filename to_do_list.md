# Corrección 01

## Prueba fallida

la prueba:

```bash
./philo 4 410 200 200
```

En esta prueba no debería morir nadie, no obstante Philo 01 lo hace

## Forma de entrega correcta

- El proyecto deberá estar en un directorio **Philo**
- el ejecutable debe llamarse **"./philo"**

## Valgrind

- Existen errores:

"Condictional jump or move depends on unitialised value(s)"

Hay que revisar la inicialización de los valores, quizás incluir un NULL al inicializarlo.
