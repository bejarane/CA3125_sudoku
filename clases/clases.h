///////// 2020. GNU GENERAL PUBLIC LICENSE /////////////////////////
//
//  Project     : Solucionador de Sudoku
//  File        : clases.h
//  Description :
//      Definición de clases.
//
//  Authors     : E. Rodriguez
//                Keylor D. Muños Soto
//
//  Git repository: https://github.com/bejarane/sudoku
////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

/* 
 * Macro para activacion de prints de debug
 */
//#define DEBUG

#ifdef DEBUG
    #define DPRINT(a) cout<<(a);
    #define DPRINTLN(a) cout<<(a)<<endl;
#else
    #define DPRINT(a)
    #define DPRINTLN(a)
#endif


/* 
 * Macros para mapear entradas y generar blancos
 */
#define SET(a,i) (i==0?(a):(a)&(1<<(i-1))) //asigna posiciones de bit a partir del 1
#define BLANK(a) (1<<((a)+1))-1 //crea un binario de posibilidades en "blanco"

/**
 *Clase utilizada para almacenar las matrices de sudoku junto con su par  
 */
class Matriz {
    public: //esta public para pruebas, pero deberia ser private
        vector <vector <int>> contenido; //un vector multidimensional para guardar las celdas
        vector <vector <int>> posibilidades;
        int restantes = 0;

    /**
         * Encuentra, por fuerza bruta, la casilla con menos posibilidades.
         */
    int menor();

};

class Sudoku{
    public: //mismo caso del public anterior
        Matriz origen;
        Matriz solucion;
        bool metodo = true; //Método de solución. True es profundidad y false es anchura
        int tamano = 0;
        int subtamano = 0;
        queue <Matriz> cola;
        stack <Matriz> pila;

        /**
         * Identifica el tipo de análisis requerido
         */
        bool leerTipo();

        /**
         * Evalua si el numero ingresado es el cuadrado de un entero
         */
        int esRaizEntera(int _n);

        /**
         * Inserta un valor dado en la matriz Sudoku
         */
        bool insertarRegla(Matriz &data,int numero, int col, int fil);

        /**
         * Lee la entrada de datos y los acomoda para su uso
         */
        bool parseInput();

        /**
         * Lee un Sudoku
         */
        bool leerMatriz();

        /**
         * Genera los Sudoku posibilidad y los inserta en la pila/cola
         */
        bool crearcasos(Matriz data, int punto);

        /**
         * Revisa cada posibilidad listada en la pila/cola y genera más posibilidades a
         * partir de ella.
         */
        bool recurrencia();

        /**
         * Utiliza a recurrencia() para resolver el Sudoku
         */
        bool resolver();

        /**
         * Imprime los datos contenidos en la matriz enviada para impresión. Permite varios formatos
         */
        void imprimir(Matriz entrada, bool bin, bool posi);
};