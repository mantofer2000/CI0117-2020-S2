
##  Pruebas

  

###  n = 10000000

  

Las pruebas del tiempo de ejecución fueron calculadas

con la herramienta de profiling *perf* de linux.

Estas pruebas fueron realizadas en una máquina

virtual de Ubuntu 14.04 con una maquina host de

2 cores. Por esta razon, las pruebas con *scheduling*

siguen este orden:

  

```

type, 1

type, 2 (Cantidad total de hilos)

type, 1 (Mitad del total de hilos)

type, 5000000 (Mitad del total de iteraciones)

```

  
  

| | type | chunksize | time elapsed |
|-----------------|---------|-----------|---------------|
| Serial | - | - | 14,258888146s |
| Paralelo | - | - | 13,944362885s |
| Schedule | static | 1 | 13,941795662s |
| Schedule | static | 2 | 13,982923198s |
| Schedule | static | 1 | 13,980834833s |
| Schedule | static | 5000000 | 14,675612909s |
| Schedule | dynamic | 1 | 14,404273926s |
| Schedule | dynamic | 2 | 14,179012868s |
| Schedule | dynamic | 1 | 14,369498565s |
| Schedule | dynamic | 5000000 | 14,097824792s |
| **Schedule** | **guided** | **1** | **13,897028766**s |
| **Schedule** | **guided** | **2** | **14,087485208**s |
| **Schedule** | **guided** | **1** | **14,172110385**s |
| **Schedule** | **guided** | **5000000** | **14,161198757**s |

 -**Speed Up :** T_Serial / T_Paralelo = 14,258888146 / 13,944362885 =  1,022555728
 
 Se contabiliza un **Speed Up** o un incremento de velocidad de 1,022555728 s del tiempo Serial con respecto al Paralelo.


#### Resalte cuál tipo de _scheduling_ obtuvo mejor rendimiento y escriba un comentario que explique por qué considera que se obtuvo el resultado.
Como se puede ver en la tabla, al sumar los tiempos de **guided** podemos ver que es el schedule que obtuvo el mejor rendimiento. Al ver la teoría y entender como **guided** funciona para repartir tareas, creemos que se obtuvo mejor rendimiento debido a su asignación dinamica y donde los **chunk sizes** van reduciendo su tamaño. Por ejemplo, para calcular los numeros primos de los números mas pequeños se hace más rapido que los números primos más grandes, por lo tanto si tiene logica ir reduciendo el tamaño de los chunk sizes. 
