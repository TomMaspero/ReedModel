Algoritmo que aplica el Modelo de Reed-Frost a una red. 
https://en.wikipedia.org/wiki/Reed%E2%80%93Frost_model

Comienza creando una red compleja a partir de ciertos parámetros elegidos dentro del .bat de antemano. 
!!! Este programa se ejecuta desde el run.bat dentro de bin\Debug\run.bat!!!
---Esta es la version de W general, tambien esta la version de W dependiente de cada vecino---

Con el bat, el programa se ejecuta 10 veces, en cada ejecucion se crea una red y esta, a su vez se utiliza 10 veces (dependiendo del n_steps) para desarrollar una nueva infeccion. 
---Luego hay que usar el programa de "Redes promedio" para promediar los datos finales---


Variables en el .bat:
max_vecinos y min_vecinos: numero maximo/minimo de vecinos que puede llegar a tener un nodo.
n_nodos: numero total de nodos a generar
beta: probabilidad de contagiar, cada vez que un nodo intenta contagiar a otro se rolea una probabilidad p. Si p es mayor que beta entonces el nodo se contagia
n_steps: cantidad de veces que se ejecuta la propagacion usando la misma red
W: medida de mitigacion
tr: tiempo de recuperacion de un nodo, luego del cual no puede volver a infectar (se vuelve inmune)

Luego de que se conecta la red en connect_network esta se guarda en un txt (datos_red.txt), donde queda como 
NODO0	VECINO1 VECINO2 VECINO3 ...
NODO1	VECINO1 VECINO2 VECINO3 ...
...



