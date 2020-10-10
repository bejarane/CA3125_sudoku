#include <bits/stdc++.h>
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
}
