# Ejercicio 1 [thread_creation_time]

## Estime el tiempo que toma el sistema en crear y destruir un thread. Escriba un programa en C que reciba un número entero T en los argumentos de línea de comandos, el cual indica la cantidad de pruebas a realizar. Si el usuario no especifica este número, asuma T = 1. Seguidamente su programa realiza T pruebas secuenciales. En cada prueba, el thread principal crea un thread secundario, espera a que este termine, y mide la duración que tardan estas dos acciones juntas con resolución de nanosegundos. El thread secundario simplemente ejecuta una función cuyo cuerpo es vacío. Note que las pruebas no se realizan concurrente si no secuencialmente. El thread principal debe reportar una estadística en la salida estándar, que es la duración en segundos de la prueba que tardó menos tiempo. Este dato permite a un programador tener un estimado del tiempo en que tarda el sistema en crear y destruir un hilo de ejecución. La salida podría tener el formato:

## Minimum thread creation and destruction time was 0.123456789s among 12345 trials

## Sugerencia: Utilice la función clock_gettime para obtener el tiempo inicial y final y calcular la duración.