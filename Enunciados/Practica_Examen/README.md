# CI0117 - Práctica OpenMP y MPI

## Ejercicio 1 [pi_omp]

Una manera de aproximar el valor del número pi (π) es utilizando la siguiente fórmula:

![Pi approx formla](http://jocan3.com/misc_images/pi.png)

En dicha sumatoria, conforme más grande sea el valor de *n*, mejor es la aproximación calculada. La fórmula anterior también puede verse en código de la siguiente manera:

```c

double factor = 1.0;
double sum = 0.0;
for (k = 0; k < n; ++k) {
  sum += factor/(2*k+1);
  factor = -factor;
}

pi = 4.0 * sum;

```
Escriba un programa en C o en C++ que paralelice el código anterior utilizando directivas de *OpenMP*, de forma que varios hilos puedan ejecutar cálculos de la sumatoria de forma concurrente. Su programa debe recibir como parámetro el valor de *n* (número de iteraciones). Utilice el número de hilos por defecto. Note que en el código anterior la manera en la que el *factor* es calculado implica una dependencia de valores entre iteraciones, por lo que debe cambiar la forma en la que éste se calcula. Utilice la directiva *default(none)* para especificar el *scope* de todas las variables involucradas. El programa debe imprimir el valor aproximado de pi (muestre al menos 16 decimales). Por ejemplo:

```c
printf("pi is approximately %.16f\n", pi);
```

Ejemplo de entrada/salida:

```
$ ./pi_omp 99999
pi is approximately 3.1416026536897879
```

Ver [ejemplo de solución](https://github.com/jocan3/CI9117-2020-S2/tree/master/Ejemplos%20de%20clase/17_MPI/pi_omp).

## Ejercicio 2 [pi_mpi]

Escriba un programa en C o en C++ que de igual manera resuelva el problema del cálculo de la aproximación del número pi de forma concurrente, pero utilizando concurrencia distribuida con funciones de MPI. Su programa no debe recibir el número *n* como argumento, sino que el proceso 0 se encarga de pedírselo al usuario en la entrada estándar. Una vez ingresado el valor de *n*, su programa debe calcular la aproximación y luego solicitar otro valor al usuario. El programa termina si el usuario digita 0.

Para el cálculo de la aproximación, el proceso 0 debe enviar el valor de *n* a los demás procesos y cada proceso ejecuta una parte de las iteraciones totales. Puede seguir una estrategia similar al *scheduling static* de OpenMP para distribuir las iteraciones. Una vez que cada proceso calcula localmente la sumatoria de las iteraciones que le corresponden, se calculará la sumatoria global en el proceso 0 y éste imprimirá el valor de la aproximación obtenida (muestre al meos 16 decimales).

Ejemplo de entrada/salida:

```
mpiexec -n 4 ./pi_mpi
Enter the value of n: (0 quits) 1000
pi is approximately 3.1405926538397937
Enter the value of n: (0 quits) 25000
pi is approximately 3.1415526535898044
Enter the value of n: (0 quits) 5000000
pi is approximately 3.1415924535909800
Enter the value of n: (0 quits) 0
```
Ver [ejemplo de solución](https://github.com/jocan3/CI9117-2020-S2/tree/master/Ejemplos%20de%20clase/17_MPI/pi_mpi).
