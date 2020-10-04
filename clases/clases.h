#include <bits/stdc++.h>
using namespace std;

class Celda {
    private:
        vector<int> conjunto = {1,1,1,1,1,1,1,1,1,1};//lleva 10 campos del 0 al 9, el 0 no será usado
        int posibilidades = 9;
        int pCol = 0;
        int pRow = 0;
        int value = 0;
        bool fija = false;
    public:

        /**
         * Crea un objeto de tipo Celda. 
         * Sobre cargado para agregar una celda cuando existe un valor 
         * pre existente. 
         * @constructor
         * @param _pCol Entero que indica la columna a la que pertenece.
         * @param _pRow Entero que indica la fila a la que pertenece.
         * @param _value Entero que indica el valor fijo de la celda.
         */
        Celda(int _pCol, int _pRow, int _value);

        /**
         * Elimina una posibilidad del conjunto. 
         *
         * Elimina una posibilidad del conjunto de posibilidades guardado 
         * en la casilla, en caso de que la posibilidad eliminada fuera la 
         * última disponible, el método devuelve false para indicar que no 
         * es una celda válida. 
         * 
         * Tomar en cuenta que el programa está desarrollado para eliminar 
         * posibilidades, pero no para agregar una posiblidad nueva excepto 
         * al iniciarlizar la celda, cuando e posible precargar un valor 
         * constante.
         *
         * @param _posicion Entero que indica el número a eliminar.
         * @return Booleano, True si queda al menos una posibilidad y False 
         * si las posibilidades se han agotado.
         */
        bool remove(int _posicion);

        int read(){
            return value;
        }
        

};

class Matriz {
    public: //esta public para pruebas, pero deberia ser private
        vector <vector <Celda>> contenido; //un vector multidimensional para guardar las celdas

};

class Sudoku{
    public: //mismo caso del public anterior
        Matriz origen;
        vector <Matriz> soluciones; //vector que se usará como pila o cola, la pila seria la más eficiente.
        bool metodo = true; //Método de solución. True es profundidad y false es anchura

        void imprimirOrigen(){
            for (int j = 0; j<9; j++){
                for (int k = 0; k<9; k++){
                    cout << origen.contenido[j][k].read() << " ";
                }
                cout << endl;
            }
        }
};