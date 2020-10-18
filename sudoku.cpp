
#include <bits/stdc++.h>
#include <clases.h>
using namespace std;

int main(){
    int casos = 0;
    string buffer;

    DPRINTLN("Inicio");

    while(getline(cin,buffer)){
        //DPRINTLN(buffer);
        if (buffer.empty())continue;
        casos = stoi(buffer);
        while(casos>0){
            casos --;
            auto current_time = std::chrono::high_resolution_clock::now();
            auto start_time = std::chrono::high_resolution_clock::now();
            Sudoku prueba;
            if(!prueba.leerMatriz()){
                cout << "Entrada erronea" << endl;
                continue;
            }
            DPRINTLN("Imprime");
            DPRINTLN('\n');
            if(prueba.resolver()){
                current_time = std::chrono::high_resolution_clock::now();
                prueba.imprimir(prueba.solucion,false,false);
                cout << "Tiempo de resolucion: " << std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() << " ms" << std::endl;
            }
        }
        break;
    }
    
    return 0;
}
