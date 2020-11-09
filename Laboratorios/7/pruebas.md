## Pruebas

### n = 10000000

Las pruebas del tiempo de ejecucion fueron calculadas
con la herramienta de profiling *perf* de linux.
Estas pruebas fueron realizadas en una maquina
virtual de Ubuntu 14.04 con una maquina host de
2 cores. Por esta razon, las pruebas con *scheduling*
siguen este orden:

```
type, 1
type, 2 (Cantidad total de hilos)
type, 1 (Mitad del total de hilos)
type, 5000000 (Mitad del total de iteraciones)
```


|                 | type    | chunksize | time elapsed  |
|-----------------|---------|-----------|---------------|
| Serial          | -       | -         | 14,258888146s |
| Paralelo        | -       | -         | 13,944362885s |
| Schedule        | static  | 1         | 13,941795662s |
| Schedule        | static  | 2         | 13,982923198s |
| Schedule        | static  | 1         | 13,980834833s |
| Schedule        | static  | 5000000   | 14,675612909s |
| Schedule        | dynamic | 1         | 14,404273926s |
| Schedule        | dynamic | 2         | 14,179012868s |
| Schedule        | dynamic | 1         | 14,369498565s |
| Schedule        | dynamic | 5000000   | 14,097824792s |
| Schedule        | guided  | 1         | 13,897028766s |
| Schedule        | guided  | 2         | 14,087485208s |
| Schedule        | guided  | 1         | 14,172110385s |
| Schedule        | guided  | 5000000   | 14,161198757s |