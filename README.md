# Anguja-ha-Mbarakaja
Mini Juego en C++ utilizando un algoritmo en el que los personajes toman desicion de sus movientos por si mismos.

El juego consiste en un tablero del estilo de tateti en donde se deben ubicar los personajes: Anguja (A) y Mbarakaja (M), luego los jugadores van moviendose por el tablero un turno a la vez, 
donde el personaje Mbarakaja busca cazar a Anguja y Anguja busca escapar de Mbarakaja

Sus movimientos estan basados en un algoritmo de toma de decisiones en donde cada jugador analiza el tablero antes de elegir su jugada y realizan la jugada basandose en su condicion de victoria en este caso, la distancia.

Inicialmente el usuario elige la dimensiones del tablero y tambien las posiciones iniciales de los personajes 
El juego termina una vez que el tablero se llene ,o sea, cuando ambos jugadores jueguen todos sus turnos 

Como se define el ganador? 
Una vez que el tablero este lleno (los personajes ya recorrieron todo el tablero) se calcula la distancia entre las ultimas posiciones de ambos jugadores 
Si los personajes estan separados a mas de 1 casilla de distancia ---> Gana Anguja (Mbarakaja no puede casarle al no estar cerca)
Si los personajes estan a 1 casilla de distancia (o sea, uno al lado del otro) ---> Gana Mbarakaja (al estar al lado puede cazar a Anguja) 


## Instrucciones de Uso
1. Para ejecutarlo primeramente se debe installar las siguientes extensiones en visual:
     1. C/C++
     2. C/C++ Compile Run
  Para ejecutar el codigo:
    se puede hacer con una de las siguientes maneras:
    1. Usar F6
    2. Usar el atajo Ctrl + 6
    3. ejecutar en la terminal: ./"Game"
2. Una vez ejecutado, se iniciara el juego y le pedira al usuario que eliga las dimensiones del tablero dandote 3 opciones
   a. 3x3
   b. 4x4
   c. 5x5 
3. El usuario debe elegir las posiciones iniciales de ambos personajes eligiendo numeros enteros a partir del 1 que representan las posiciones del tablero (De izquierda a derecha y de arriba a abajo)

4. Finalmente, luego de que se terminen los turnos, el juego mostrara el el tablero final y quien es el Ganador. 


