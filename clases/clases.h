#include <bits/stdc++.h>
using namespace std;

//#define DEBUG

#ifdef DEBUG
    #define DPRINT(a) cout<<(a);
    #define DPRINTLN(a) cout<<(a)<<endl;
#else
    #define DPRINT(a)
    #define DPRINTLN(a)
#endif

#define SET(a,i) (i==0?(a):(a)&(1<<(i-1)))
#define BLANK(a) (1<<((a)+1))-1

class Matriz {
    public: //esta public para pruebas, pero deberia ser private
        vector <vector <int>> contenido; //un vector multidimensional para guardar las celdas
        vector <vector <int>> posibilidades;
        int restantes = 0;

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

        bool leerTipo();

        int esRaizEntera(int _n);

        bool insertarRegla(Matriz &data,int numero, int col, int fil);

        bool parseInput();

        bool leerMatriz();

        void imprimir(Matriz entrada, bool bin, bool posi);

        bool crearcasos(Matriz data, int punto);

        bool recurrencia();

        bool resolver();
};