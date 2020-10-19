///////// 2020. GNU GENERAL PUBLIC LICENSE /////////////////////////
//
//  Project     : Solucionador de Sudoku
//  File        : sudoku.cpp
//  Description :
//      Funcion principal y punto de entrada del programa.
//
//  Authors     : E. Rodriguez
//                Keylor D. Muños Soto
//
//  Git repository: https://github.com/bejarane/sudoku
////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
#include <clases.h>
using namespace std;

//#define INTERNAL_TIME

int main(){
    int casos = 0;
    string buffer;

    DPRINTLN("Inicio");

    while(getline(cin,buffer)){
        if (buffer.empty())continue;
        casos = stoi(buffer);
        while(casos>0){
            casos --;
            #ifdef INTERNAL_TIME
            auto current_time = std::chrono::high_resolution_clock::now();
            auto start_time = std::chrono::high_resolution_clock::now();
            #endif
            Sudoku prueba;
            if(!prueba.leerMatriz()){
                cout << "Matriz inválida, número repetido" << endl;
                continue;
            }
            DPRINTLN("Imprime");
            DPRINTLN('\n');
            if(prueba.resolver()){
                #ifdef INTERNAL_TIME
                    current_time = std::chrono::high_resolution_clock::now();
                #endif
                prueba.imprimir(prueba.solucion,false,false);
                #ifdef INTERNAL_TIME
                    cout << "Tiempo de resolucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() << " ms" << std::endl;
                #endif
            }
        }
        break;
    }
    
    return 0;
}
