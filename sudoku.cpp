#include <bits/stdc++.h>
#include <clases.h>
using namespace std;

bool leerTipo(){
    string buffer;
    cin >> buffer;
    
    //las siguientes lineas son solo para debug
    cout << "Tipo de analisis es " << buffer << endl;
    bool resultado = buffer=="profundidad";
    cout << resultado << endl; 
    //terminan lineas de debug
    return buffer=="profundidad";
}


void leerMatriz(Sudoku &_sudoku){
    Matriz buffer;
    int entrada=0;
    for (int j = 0; j<9; j++){
        vector <int> columna;
        for (int k = 0; k<9; k++){
            cin >> entrada;
            columna.push_back(entrada);
        }
        buffer.contenido.push_back(columna);
    }
    _sudoku.origen = buffer;
}



int main(){
    int casos = 0;

    cout << "Inicio" << endl;

    while(scanf("%i",&casos)==1){
        while(casos>0){
            Sudoku prueba;
            prueba.metodo = leerTipo();
            leerMatriz(prueba);
            prueba.imprimirOrigen();

            casos --;
        }
    }
    int matriz[3][3]; 
	int f,c;
	
	for(f=0; f<3; f++){
		for(c=0; c<3; c++){
			matriz[f][c] = 1 + rand() %  9;
		}
	}
	for(f=0; f<3; f++){
		for(c=0; c<3; c++){
			cout << matriz[f][c] <<" ";
		}cout << endl;
	}
    return 0;
}
