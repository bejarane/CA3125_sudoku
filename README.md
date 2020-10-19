# Solucionador para Sudoku
*Solución presentada para el curso de Análisis de Algoritmos.*

## Descripción
Este proyecto consiste en un programa capaz de leer matrices de Sudoku para encontrar su solución a través de un algoritmo de backtracking.

Se ha implementado la posiblidad de seleccionar un método de resolución por profunidad o por anchura como parte de los requerimientos con fines educativos con el fin de demostrar la diferencia de rendimiento entre ambos algoritmos.

## Uso
Primeramente es necesario compilar un binario para su posterior ejecución. El archivo *makefile* contiene un macro que permite ejecutar la compilación del proyecto. Ejecutar con el comando **make** dentro de esta carpeta. El archivo ejecutable será guardado en el directorio *bin*.

Una vez se dispone del archivo ejecutable, basta con cargar un archivo de prueba con el comando `ejecutable.o < caso_de_prueba.txt`.

En la carpeta *inputs* se adjuntan casos de prueba que pueden ser utilizados como template para generar nuevos casos de prueba.

## Funcionamiento
El funcionamiento del programa se describe a grandes razgos en la siguiente imagen: ![proceso](/results/proceso.png)

## Resultados
Se ha encontrado que estadísticamente el método de resolución por profundidad requiere menos recursos para encontrar la solución, en la siguiente imagen se observa el resumen de los casos evaluados.
![resultados](/results/resultados.png)

También se ha incluido un archivo de datos que incluye los resultados puntuales de las mediciones que fueron llevadas a cabo. Este se denomina *test_results.odt* dentro del directorio *results*

## Notas extra
Hacer un solucionador de Sudoku es una tarea entretenida en realidad. Toma algo de tiempo para aquellos que somos iniciados en la programación, pero es un ejercicio mental e investigativo bastante fructífero.