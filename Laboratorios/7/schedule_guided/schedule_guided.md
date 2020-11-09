# Guided Schedule

Como se ha visto en clase, la cláusula **schedule** sirve para controlar la asignación de iteraciones en un bloque parallelo. El `schedule(static, chunk size)` agenda las iteraciones por orden, mientras que el `schedule(dynamic, chunk size)` asigna las iteraciones en tiempo de ejecución, casi como una fila. 
Como hemos visto, cada una de estas iteraciones o secciones de trabajo tiene un tamaño determinado, y ese tamaño es fijado por la variable **chunk size**, sin embargo con `schedule(guided, chunk size)` la asignación se comporta de manera diferente.

 ```c++
 #include  <omp.h>

#include  <bits/stdc++.h>

int  main()
{

	omp_set_num_threads(2);

	#pragma  omp  parallel  for  schedule(guided, 2)

	for(int  i  =  0; i  <  20; i++){

		#pragma  omp  critical

		{

			std :: cout  <<  "Thread num : "  <<  omp_get_thread_num() <<  " has iteration : "  <<  i  << std :: endl;

		}

	}
	return  0;
}
```

Al correr este ejemplo vemos que las asignaciones al principio no tienen mucho sentido, ya que no estan respetando la definición del **chunk size**, sin embargo, lo que ocurre es que lo que genera la cláusula **guided** es que para "tratar de hacer la repartición más eficiente" cada hilo agarra dinamicamente, en tiempo de ejecucion un chunk size mucho mas grande que el especificado. En la proxima iteración, el tamaño de su **chunk** va a ser mucho menor, y asi subsequentemente hasta tratar de llegar, a este caso, a un **chunk size** de 2 en la última iteración. El motivo de esto es para tratar de manejar imbalances en la asignación de iteraciones.  

[Referencia](https://docs.microsoft.com/en-us/cpp/parallel/openmp/d-using-the-schedule-clause?view=msvc-160)