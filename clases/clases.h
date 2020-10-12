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
        vector <vector <int>> contenido; //un vector multidimensional para guardar las celdas
        vector <vector <int>> posibilidades;
        int restantes = 0;

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

        void imprimir(Matriz entrada, bool bin, bool posi){
            int n = 0;
            //cout << tamano << "matriz" << endl;
            while(n<tamano){
                cout << "l\t";
                int m = 0;
                while(m<tamano){
                    if (bin){
                        cout << bitset<10>(entrada.contenido[n][m]) << "\t";
                    }else{
                        int punto = entrada.contenido[n][m];
                        for (int j = 0; j <tamano; j++){
                            if(punto>>9){
                                cout << 0 << " ";
                                break;
                            }
                            if((punto&1<<j)>0){ //es una posibilidad
                                punto = j+1; //el 1 tiene una posicion 0
                                cout << punto << " ";
                                break;
                            }
                        }
                    }
                    m++;
                }
                cout << endl;
                n++;
            }
            if(posi){
                n =0;
                for (int j = 0; j< tamano;j++){
                    for (int k = 0; k<tamano; k++){
                        cout << entrada.posibilidades[j*tamano+k][0] << " ";
                    }
                    cout << endl;
                }
            }
        }

        void imprimirDec(vector<vector<int>> contenido){
            int n = 0;
            cout << endl;
            //cout << tamano << "matriz" << endl;
            while(n<tamano){
                cout << "l\t";
                int m = 0;
                while(m<tamano){
                    int punto = contenido[n][m];
                    for (int j = 0; j <tamano; j++){
                        if((punto&1<<j)>0){ //es una posibilidad
                            punto = j+1; //el 1 tiene una posicion 0
                            cout << punto << " ";
                            break;
                        }
                    }
                    m++;
                }
                cout << endl;
                n++;
            }
        }
};