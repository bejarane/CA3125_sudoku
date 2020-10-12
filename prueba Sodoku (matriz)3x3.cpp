/*#include <bits/stdc++.h>
using namespace std;

int main () {
	
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
}*/
//*****************************************************************
// VARIANTE PARA LA PRUEBA abajo QUE SE QUIERE HACER DE METER MATRICES MAS GRANDES(arriba es para recorrer y rellenar la matriz)
//*****************************************************************
#include <bits/stdc++.h>
using namespace std;

int main () {
	
	int matriz [4][4],f,c;
	cout << "digite el numero de filas: ";
	cin >>f; 
	cout << "digite el numero de  columnas: ";
	cin >>c;
	
	for(int i=0;i<f;i++){
		for(int j=0;j<c;j++){
		cout << "introduzca los valores del sodoku ["<<i<<"]["<<j<<"]: ";
		cin>> matriz[i][j];
		}
	}
	for(int i=0;i<f;i++){
		for(int j=0;j<c;j++){
			cout << matriz[i][j];
			cout<<" ";
		}
		cout<<"\n";
	}
	
	
	return 0;
}
