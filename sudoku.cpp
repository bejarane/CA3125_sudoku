#include <clases.h>
bool leerTipo(){
    string buffer;
    cin >> buffer;
    cout << "Tipo de analisis es " << buffer << endl;
    return buffer=="profundidad";
}


void leerMatriz(Sudoku &_sudoku){
    Matriz buffer;
    int entrada=0;
    for (int j = 0; j<9; j++){
        vector <Celda> columna;
        for (int k = 0; k<9; k++){
            cin >> entrada;
            Celda celda(j,k,entrada);
            columna.push_back(celda);
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
    return 0;
}