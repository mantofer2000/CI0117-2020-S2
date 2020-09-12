## hello_ordered_semaphore

### ¿Permite este mecanismo de control de concurrencia resolver este problema de manera predecible? 

### Explique las diferencias entre usar exclusión mutua y semáforos para resolver este problema en un archivo rationale.md dentro de su carpeta hello_ordered_semaphore.

#### El semaforo es un mecanismo que permite resolver este problema. Se soluciona serializando el comportamiento de los hilos. 

#### El semaforo se puede decir que se diferenciaentre exclusion mutua porque tiene una variable que permite dar valor cuando empezar la exclusion mutua. En esta solucion, se esta inicializando con 0, pero la variable se puede cambiar. En metodologia de solucion, se sigue utilizando un arreglo.