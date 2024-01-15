#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>  // Incluir la biblioteca para obtener INT_MAX
#include <tuple>
#include <set>
using namespace std;


char JUGADOR_1 = 'A';
char JUGADOR_2 = 'M';

// Definir el conjunto con el comparador personalizado



// Función para inicializar el tablero con valores vacíos y dimensión dimension x dimension
vector<vector<char>> inicializar_tablero(int dimension) {
    return vector<vector<char>>(dimension, vector<char>(dimension, ' '));
}



// Función que verifica si una jugada es válida
bool es_jugada_valida(const vector<vector<char>>& tablero, int fila, int columna, int dimension) {
    return (0 <= fila && fila < dimension && 0 <= columna && columna < dimension &&
            tablero[fila][columna] == ' ');
}


// Función que imprime el tablero con el diseño
void imprimir_tablero(const vector<vector<char>>& tablero, int dimension) {
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            cout << " " << (tablero[i][j] != ' ' ? tablero[i][j] : ' ') << " ";
            if (j < dimension - 1) {
                cout << "|";
            }
        }
        cout << endl;

        if (i < dimension - 1) {
            for (int k = 0; k < 4 * dimension - 1; ++k) {
                cout << "-";
            }
            cout << endl;
        }
    }
}




// Función que verifica si el tablero está lleno
bool tablero_lleno(const vector<vector<char>>& tablero) {
    for (const auto& fila : tablero) {
        for (char celda : fila) {
            if (celda == ' ') {
                return false;  // Si hay al menos una celda vacía, el tablero no está lleno
            }
        }
    }
    return true;  // Todas las celdas están ocupadas
}


// Función que hace la jugada
void hacer_jugada(vector<vector<char>>& tablero, int fila, int columna, char jugador) {
    tablero[fila][columna] = jugador;


}


// Función que retorna la última jugada de cada jugador
pair<int, int> buscar_ultima_posicion(const vector<vector<char>>& tablero, char jugador) {
    int dimension = tablero.size();  // Se obtiene la dimensión del tablero

    for (int fila = 0; fila < dimension; ++fila) {
        for (int columna = 0; columna < dimension; ++columna) {
            if (tablero[fila][columna] == jugador) {
                return make_pair(fila, columna);
            }
        }
    }

    // Si no se encuentra ninguna posición para el jugador, se retorna (-1, -1) u otro valor que indique que no se encontró
    return make_pair(-1, -1);
}



// Función que calcula la distancia entre dos posiciones
int calcular_distancia(const pair<int, int>& posicion_1, const pair<int, int>& posicion_2) {
    if (posicion_1 == make_pair(-1, -1) || posicion_2 == make_pair(-1, -1)) {
        return INT_MAX;  // Utilizamos INT_MAX para representar infinito
    }

    int fila_1 = posicion_1.first;
    int columna_1 = posicion_1.second;
    int fila_2 = posicion_2.first;
    int columna_2 = posicion_2.second;

    // Resto el valor absoluto para obtener la distancia en términos de filas y columnas
    int distancia = abs(fila_1 - fila_2) + abs(columna_1 - columna_2);

    return distancia;
}



// Función que calcula la distancia entre dos personajes en el tablero
int calcular_distancia_entre_personajes(const vector<vector<char>>& tablero, char jugador_1, char jugador_2) {
    // Buscamos las últimas posiciones de los jugadores en el tablero
    pair<int, int> posicion_jugador_1 = buscar_ultima_posicion(tablero, jugador_1);
    pair<int, int> posicion_jugador_2 = buscar_ultima_posicion(tablero, jugador_2);

    // Calculamos la distancia entre las posiciones de los jugadores
    return calcular_distancia(posicion_jugador_1, posicion_jugador_2);
}




// Función que verifica si hay un ganador
char hay_ganador(const vector<vector<char>>& tablero) {
    if (!tablero_lleno(tablero)) {
        return '\0';  // No hay ganador si el tablero no está lleno
    }

    pair<int, int> ultima_posicion_jugador_1 = buscar_ultima_posicion(tablero, JUGADOR_1);
    pair<int, int> ultima_posicion_jugador_2 = buscar_ultima_posicion(tablero, JUGADOR_2);

    int distancia = calcular_distancia(ultima_posicion_jugador_1, ultima_posicion_jugador_2);

    if (distancia > 1) {
        return JUGADOR_1;
    } else if (distancia <= 1) {
        return JUGADOR_2;
    } else {
        return '\0';  // No hay ganador en caso de empate o error
    }
}






// Función que obtiene las posiciones con la mínima distancia desde la ubicación de referencia
vector<pair<int, int>> obtener_posiciones_minima_distancia(const vector<vector<char>>& tablero, const pair<int, int>& ubicacion_referencia,  int dimensiones) {
    // Calcula la distancia mínima desde la ubicación de referencia hasta cada posición vacía en el tablero.

    vector<pair<int, int>> posiciones_disponibles;

    for (int fila = 0; fila < dimensiones; ++fila) {
        for (int columna = 0; columna < dimensiones; ++columna) {
            if (tablero[fila][columna] == ' ') {
                posiciones_disponibles.emplace_back(fila, columna);
            }
        }
    }

    int minima_distancia = INT_MAX;

    for (const auto& posicion : posiciones_disponibles) {
        int distancia = calcular_distancia(ubicacion_referencia, posicion);
        minima_distancia = min(minima_distancia, distancia);
    }

    vector<pair<int, int>> posiciones_minima_distancia;

    for (const auto& posicion : posiciones_disponibles) {
        int distancia = calcular_distancia(ubicacion_referencia, posicion);
        if (distancia == minima_distancia) {
            posiciones_minima_distancia.emplace_back(posicion);
        }
    }

    return posiciones_minima_distancia;
}



// Función que obtiene las posiciones con la máxima distancia desde la ubicación de referencia
vector<pair<int, int>> obtener_posiciones_maxima_distancia(const vector<vector<char>>& tablero, const pair<int, int>& ubicacion_referencia, int dimensiones) {
    // Calcula la distancia máxima desde la ubicación de referencia hasta cada posición vacía en el tablero.

    vector<pair<int, int>> posiciones_disponibles;

    for (int fila = 0; fila < dimensiones; ++fila) {
        for (int columna = 0; columna < dimensiones; ++columna) {
            if (tablero[fila][columna] == ' ') {
                posiciones_disponibles.emplace_back(fila, columna);
            }
        }
    }

    int maxima_distancia = INT_MIN;

    for (const auto& posicion : posiciones_disponibles) {
        int distancia = calcular_distancia(ubicacion_referencia, posicion);
        maxima_distancia = max(maxima_distancia, distancia);
    }

    vector<pair<int, int>> posiciones_maxima_distancia;

    for (const auto& posicion : posiciones_disponibles) {
        int distancia = calcular_distancia(ubicacion_referencia, posicion);
        if (distancia == maxima_distancia) {
            posiciones_maxima_distancia.emplace_back(posicion);
        }
    }

    return posiciones_maxima_distancia;
}



// Función de comparación para vector<vector<char>> en un conjunto
struct ComparadorTablero {

    bool operator()(const vector<vector<char>>& a, const vector<vector<char>>& b) const {
        return a < b;
    }
};


set<vector<vector<char>>, ComparadorTablero> estados_visitados;



pair<int, int> minimax(vector<vector<char>>& tablero, char jugador, int dimensiones, set<vector<vector<char>>, ComparadorTablero>& estados_visitados) {

    while (true) {
        pair<int, int> ultima_posicion_gato = buscar_ultima_posicion(tablero, JUGADOR_2);
        pair<int, int> ultima_posicion_raton = buscar_ultima_posicion(tablero, JUGADOR_1);
        vector<pair<int, int>> maxima_distancias = obtener_posiciones_maxima_distancia(tablero, ultima_posicion_gato, dimensiones);
        vector<pair<int, int>> minima_distancias = obtener_posiciones_minima_distancia(tablero, ultima_posicion_raton, dimensiones);

        if (jugador == JUGADOR_1) {
            if (!maxima_distancias.empty()) {
                for (const auto& posicion : maxima_distancias) {
                    int fila_jugada = posicion.first;
                    int columna_jugada = posicion.second;
                    if (es_jugada_valida(tablero, fila_jugada, columna_jugada, dimensiones)) {
                        if (estados_visitados.find(tablero) == estados_visitados.end()) {
                            return make_pair(fila_jugada, columna_jugada);
                        }
                    }
                }
            } else {
                cout << "Anguja y Mbarakaja se hicieron amigos, el juego terminó :p" << endl;
                break;
            }
        } else if (jugador == JUGADOR_2) {
            if (!minima_distancias.empty()) {
                for (const auto& posicion : minima_distancias) {
                    int fila_jugada2 = posicion.first;
                    int columna_jugada2 = posicion.second;
                    if (es_jugada_valida(tablero, fila_jugada2, columna_jugada2, dimensiones)) {
                        if (estados_visitados.find(tablero) == estados_visitados.end()) {
                            return make_pair(fila_jugada2, columna_jugada2);
                        }
                    }
                }
            } else {
                cout << "Anguja y Mbarakaja se hicieron amigos, el juego terminó :p" << endl;
                break;
            }
        } else {
            cout << "Se acabó, jefe" << endl;
            break;
        }
    }
    return make_pair(-1, -1);
}


int main() {


    cout << "BIENVENIDO A ANGUJA HA MBARAKAJA\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Iniciando...\n";
    this_thread::sleep_for(chrono::seconds(3));


    string DIMENSIONES;

    cout << "Escoge las dimensiones del tablero:\n";
    cout << "A. 3x3\nB. 4x4\nC. 5x5\n:";
    cin >> DIMENSIONES;

    transform(DIMENSIONES.begin(), DIMENSIONES.end(), DIMENSIONES.begin(), ::tolower);

    int dimension;

    while (DIMENSIONES != "a" && DIMENSIONES != "b" && DIMENSIONES != "c") {
        cout << "Escoge solo una de las opciones del tablero:\n";
        cout << "A. 3x3\nB. 4x4\nC. 5x5\n:";
        cin >> DIMENSIONES;
        transform(DIMENSIONES.begin(), DIMENSIONES.end(), DIMENSIONES.begin(), ::tolower);
    }

    if (DIMENSIONES == "a") {
        dimension = 3;
    } else if (DIMENSIONES == "b") {
        dimension = 4;
    } else {
        dimension = 5;
    }


    // Creamos el tablero y lo llamamos tablero
    vector<vector<char>> tablero = inicializar_tablero(dimension);
    

    // Solicitar posición inicial del ratón
    int primera_posicion_raton;
    do {
        cout << "Ingrese la posición de Anguja 🐭 del 1 al " << dimension * dimension << ": ";
        cin >> primera_posicion_raton;

        if (!(1 <= primera_posicion_raton && primera_posicion_raton <= dimension * dimension)) {
            cout << "Número incorrecto. ";
        }
    } while (!(1 <= primera_posicion_raton && primera_posicion_raton <= dimension * dimension));

    int fila_elegida = (primera_posicion_raton - 1) / dimension;
    int columna_elegida = (primera_posicion_raton - 1) % dimension;

    // Solicitar posición inicial del gato
    int primera_posicion_gato;
    do {
        cout << "Ingrese la posición de Mbarakaja 😺 del 1 al " << dimension * dimension << ": ";
        cin >> primera_posicion_gato;

        if (!(1 <= primera_posicion_gato && primera_posicion_gato <= dimension * dimension) || primera_posicion_gato == primera_posicion_raton) {
            cout << "Número incorrecto. ";
        }
    } while (!(1 <= primera_posicion_gato && primera_posicion_gato <= dimension * dimension) || primera_posicion_gato == primera_posicion_raton);

    int fila_elegida2 = (primera_posicion_gato - 1) / dimension;
    int columna_elegida2 = (primera_posicion_gato - 1) % dimension;

    int jugadas_realizadas = 0;

    // Llamamos a la función para realizar la jugada
    hacer_jugada(tablero,fila_elegida,columna_elegida,JUGADOR_1);
    hacer_jugada(tablero,fila_elegida2,columna_elegida2,JUGADOR_2);


    // imprimimos para ver la nueva jugada 
    cout << "Posiciones iniciales" << endl;
    cout << endl;

   
    imprimir_tablero(tablero,dimension);
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Ahora es el turno de Anguja " << JUGADOR_1 << endl;
    this_thread::sleep_for(chrono::seconds(1));


    pair<int, int> posicion_anterior = make_pair(fila_elegida, columna_elegida);
    pair<int, int> posicion_anterior2 = make_pair(fila_elegida2, columna_elegida2);

    

    // BUCLE DEL JUEGO
    while (!tablero_lleno(tablero)) {

        
       // Obtener el estado actual del tablero
        vector<vector<char>> estado_actual = tablero;

        // Verificar si el estado actual ya ha sido visitado después de que los jugadores hicieron al menos una jugada
        if (jugadas_realizadas > 1 && estados_visitados.find(estado_actual) != estados_visitados.end()) {
        cout << "¡El juego ha caído en un bucle infinito!" << endl;
            break;
        }

        estados_visitados.insert(estado_actual);
        jugadas_realizadas += 1;


        // JUGADOR 1 HACE SU JUGADA 
        hacer_jugada(tablero, posicion_anterior.first, posicion_anterior.second, 'x');
        pair<int, int> posicion_jugada1 = minimax(tablero, JUGADOR_1, dimension, estados_visitados);
        hacer_jugada(tablero, posicion_jugada1.first, posicion_jugada1.second, JUGADOR_1);
        posicion_anterior = {posicion_jugada1.first, posicion_jugada1.second};
                
        
        // Imprime el tablero
        this_thread::sleep_for(chrono::seconds(1));
        cout << endl;
        imprimir_tablero(tablero,dimension);
        cout << endl;

        // Comprueba si hay ganador

        if (hay_ganador(tablero)) {
            if (hay_ganador(tablero) == JUGADOR_1) {
                cout << "El ganador es Anguja " << JUGADOR_1 << endl;
                break;
            } else {
                cout << "El ganador es Mbarakaja " << JUGADOR_2 << endl;
                break;
            }
        }

        // Imprime el turno del otro jugador
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Ahora es el turno de Mbarakaja " << JUGADOR_2 << endl;
        this_thread::sleep_for(chrono::seconds(1));

        // JUGADOR 2 HACE SU JUGADA
        hacer_jugada(tablero,posicion_anterior2.first,posicion_anterior2.second,'x');
        pair<int, int> posicion_jugada2 = minimax(tablero,JUGADOR_2,dimension, estados_visitados);
        hacer_jugada(tablero,posicion_jugada2.first,posicion_jugada2.second, JUGADOR_2);
        posicion_anterior2 = {posicion_jugada2.first, posicion_jugada2.second};

        // Imprime el tablero
        this_thread::sleep_for(chrono::seconds(1));
        cout << endl;
        imprimir_tablero(tablero,dimension);
        cout << endl;


        if (hay_ganador(tablero)) {
            if (hay_ganador(tablero) == JUGADOR_1) {
                cout << "El ganador es Anguja " << JUGADOR_1 << endl;
                break;
            } else {
                cout << "El ganador es Mbarakaja " << JUGADOR_2 << endl;
                break;
            }
        }

        // Imprime el turno del otro jugador
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Ahora es el turno de Anguja " << JUGADOR_1 << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }




    return 0;
}  
