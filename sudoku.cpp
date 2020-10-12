/**
 * Todo list
 * [ ] Buscar una manera más optima de pasar el vector
 *      de resultado de la funcion pasrse que no sea pasar por
 *      referencia.
*/


#include <bits/stdc++.h>
#include <clases.h>
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

bool leerTipo(){
    string buffer;
    getline(cin,buffer);
    while(buffer.empty()){
        getline(cin,buffer);
    }
    
    //las siguientes lineas son solo para debug
    DPRINT("Tipo de analisis es ");
    DPRINTLN(buffer);

    #ifdef DEBUG
    bool resultado = buffer=="profundidad";
    DPRINTLN(resultado);
    #endif

    //terminan lineas de debug
    return buffer=="profundidad";
}

/**
 * Inserta evaluando reglas. 
 * Inserta un valor verificando que este cumpla con las 3 reglas
 * del sudoku. 
 * @param data Matriz con datos de entrada y posibilidades
 * @param size Tamaño del sudoku
 * @param subsize Tamaño de submatriz
 * @param numero Numero a insertar en bitmask
 * @param col Columna en el que va [x][col]
 * @param fil Fila en la que va [fil][x]
 */
bool insertarRegla(Matriz &data, Sudoku _sudoku,int numero, int col, int fil){
    //anotar filas
    int size = _sudoku.tamano;
    int subsize = _sudoku.subtamano;
    for (int j = 0; j < size;j++){
        if (j == col) continue; //no verificar la casilla misma
        if ((data.contenido[fil][j]&numero)==0) continue; //el numero evaluado no lo tenia como opcion
        if (data.posibilidades[fil*size+j][0] == 1) return false; //si paso la prueba anterior es porque contiene el numero, si lo
        //restara de aqui, se daria un 0 posibilidades y eso no puede pasar.
        data.contenido[fil][j]=data.contenido[fil][j] ^ numero; //se elimina la posibilidad
        data.posibilidades[fil*size+j][0]--; //se resta una posibilidad
    }
    //anotar columnas
    for (int j = 0; j < size;j++){
        if (j == fil) continue; //no verificar la casilla misma
        if ((data.contenido[j][col]&numero)==0) continue; //el numero evaluado no lo tenia como opcion
        if (data.posibilidades[j*size+col][0] == 1) return false; //si paso la prueba anterior es porque contiene el numero, si lo
        //restara de aqui, se daria un 0 posibilidades y eso no puede pasar.
         data.contenido[j][col]=data.contenido[j][col] ^ numero; //se elimina la posibilidad
        data.posibilidades[j*size+col][0]--; //se resta una posibilidad
    }
    //anotar sub seccion
    int icol = col/subsize*subsize, ifil = fil/subsize*subsize; //define los inicios del subcuadrante
    for (int j = ifil; j< ifil + subsize;j++){
        for (int k = icol; k<icol + subsize; k++){
            if (j == fil || k == col) continue; //no verificar la casilla misma ni las que estan en la misma fila o col
            if ((data.contenido[j][k]&numero)==0) continue; //el numero evaluado no lo tenia como opcion
            if (data.posibilidades[j*size+k][0] == 1) return false; //si paso la prueba anterior es porque contiene el numero, si lo
            //restara de aqui, se daria un 0 posibilidades y eso no puede pasar.
            data.contenido[j][k]=data.contenido[j][k] ^ numero; //se elimina la posibilidad
            data.posibilidades[j*size+k][0]--; //se resta una posibilidad
        }
    }
    data.contenido[fil][col]=(numero);
    data.posibilidades[fil*size+col][0]=-1; //le deja un flag para no volverlo a llamar
    data.restantes --;
    //DPRINT("Restantes: ");
    //DPRINTLN(data.restantes);
    return true;
}

int esRaizEntera(int _n){  //https://www.johndcook.com/blog/2008/11/17/fast-way-to-test-whether-a-number-is-a-square/
    int base  = _n & 0xF;
    if (base > 9) return -1;
    if(base != 2 && base != 3 && base != 5 && base != 6 && base != 7 && base != 8){
        int raiz = (int) floor(sqrt((double)base));
        return raiz*raiz==base?raiz:-1;
    }
    return -1;
}

bool parseInput(Sudoku &_sudoku){

    int input;
    //int tipo = 0;
    //int size = 0;
    //int subsize = 0;
    vector<int> test;
    _sudoku.metodo = leerTipo(); // inserta un valor que indica el tipo de evaluacion
    string line;
    getline(cin, line); //lee la linea restante con n numeros
    istringstream iss(line);
    int contador = 0;
    
    //DPRINT("INPUT");
    //DPRINTLN(contador);
    while ( iss >> input) {  //la funcion >> lee hasta topar con un espacio, asi que está leyendo ints  
        //DPRINTLN(input);
        test.push_back(input);
        contador ++; //cuenta la cantidad de digitos
    }
    int subMatriz = esRaizEntera(contador);
    DPRINT(subMatriz);
    DPRINTLN("Raiz");
    if (subMatriz>0){ // si es una entrada valida 
        _sudoku.tamano = contador; //actualiza campos
        _sudoku.subtamano = subMatriz;
        _sudoku.origen.restantes = contador*contador;
    }

    
    const int base0 = BLANK(_sudoku.tamano);
    vector <int> base1 (_sudoku.tamano,base0); // se prepara la base
    //fill(base.begin(),base.end(),inicial); //se llena
    //for (int j = 0; j < size; j++){ //se guarda en buffer
    //    buffer.push_back(base); 
    //}
    vector<vector <int>> base2 (_sudoku.tamano,base1);

    vector<int> posib0 (3,_sudoku.tamano);
    vector <vector<int>> posib1 (_sudoku.tamano*_sudoku.tamano,posib0);


    _sudoku.origen.contenido=base2;
    _sudoku.origen.posibilidades=posib1;

    vector <int> swap = test;
    //test.clear();
    int k  = 0;
    while(k < _sudoku.tamano){
        if(test[k]!=0){
            int buff = SET(base0,test[k]);
            //cout<< bitset<9>(buff)<< "bin" << endl;
            if(!insertarRegla(_sudoku.origen,_sudoku,buff,k,0))return false;
            //test.push_back(SET(inicial,swap[k])); //size +1 para mantener un bit de informacion arriba
        }
        k ++;
    }
    DPRINTLN("FLAG1");
    //buffer.push_back(test);
    //test.clear();
    
    //DPRINT(contador);
    //DPRINTLN("Nuevo");
    int fila = 1; //extrae las siguientes n-1 lineas
    while(fila<_sudoku.tamano){
        //DPRINT("INPUT");
        //DPRINTLN(contador);
        getline(cin, line); //lee la linea restante con n numeros
        istringstream iss2(line);
        int col = 0;
        while ( iss2 >> input) {  //la funcion >> lee hasta topar con un espacio, asi que está leyendo ints  
            if(input!=0){
                int buff = SET(base0,input);
                //cout<< bitset<9>(buff)<< "bin" << endl;
                if(!insertarRegla(_sudoku.origen,_sudoku,buff,col,fila))return false;
                //test.push_back(SET(inicial,swap[k])); //size +1 para mantener un bit de informacion arriba
            }
            col++;
        }
        //buffer.push_back(test);
        //test.clear();
        fila++;
    }
    DPRINTLN("Finaliza lectura");
    return true;
}

bool leerMatriz(Sudoku &_sudoku){
    parseInput(_sudoku);
    if(_sudoku.tamano==0)return false;
    return true;
}

int menor(vector<vector<int>> _data){ //http://www2.lawrence.edu/fast/GREGGJ/CMSC270/iterators.html
    int min = 2000, contador = 0, posi = -1;
    for (auto j = begin(_data);j!=end(_data);++j,++contador){ //no esta ordenada y ordenarla seria perder la llave de acceso
        //cout << j->operator[](0) << endl;
        if(j->operator[](0)<min && j->operator[](0)!=-1){ //el minimo no puede ser uno de los fijos
            min = j->operator[](0);
            posi = contador;
        }
    }
    DPRINT("|Menor fue: ");
    DPRINT(posi);
    return posi;
}

bool crearcasos(Sudoku &_sudoku, Matriz data, int punto){
    int col = punto-((punto/_sudoku.tamano)*_sudoku.tamano);
    int fil = (punto/_sudoku.tamano);
    punto = data.contenido[fil][col];
    bool posible = false;
    for (int j = 0; j < _sudoku.tamano; j++){
        if((punto&1<<j)>0){ //es una posibilidad
            Matriz dummy = data;//se copia la matriz original
            if(insertarRegla(dummy,_sudoku,punto&1<<j,col,fil)){
                DPRINT("Creando caso con:");
                DPRINTLN(j+1);
                if(_sudoku.metodo==0){ //anchura
                    _sudoku.cola.push(dummy);
                }else{
                    _sudoku.pila.push(dummy);
                }
                posible = true;
            }else{
                //cout << "No pudo "<< j+1 << endl;
            }
        }
    }
    DPRINT("crear caso fue ");
    DPRINTLN(posible);
    return posible;
}

bool recurrencia(Sudoku &_sudoku){
    //primero, obtener la siguiente evaluacion
    Matriz caso;
    if(_sudoku.metodo==0){ //anchura
        caso = _sudoku.cola.front();
        _sudoku.cola.pop();
    }else{
        caso = _sudoku.pila.top();
        _sudoku.pila.pop();
    }

    //_sudoku.imprimir(caso,false,true);

    if (caso.restantes==0) { //lo resolvio!!
        _sudoku.solucion = caso;
        return true;
    }

    int sig = menor(caso.posibilidades);
    //cout << "siguiente" << caso.posibilidades[sig][0] << endl;
    if (sig == -1) return false; //fallo drasticamente, no deberia pasar
    crearcasos(_sudoku,caso,sig); //no puedo generar el caso que correspondia a esta
    //posibilidad

    return recurrencia(_sudoku);
}

bool resolver(Sudoku &_sudoku){
    //primero, conocer el menor de posibilidades
    int sig = menor(_sudoku.origen.posibilidades);
    if (sig == -1) {//se insertó un sudoku ya resuelto
        _sudoku.solucion = _sudoku.origen;
        return true; 
    }
    //cout << "siguiente" << _sudoku.origen.posibilidades[sig][0] << endl;
 
    if(!crearcasos(_sudoku,_sudoku.origen,sig)){
        cout << "No se puede resolver, el menor era: " << sig << endl;
        return false;
    }
    if(!recurrencia(_sudoku)){
        cout << "No se puede resolver por backtracking"<< endl;
        return false;
    }
    return true;
}

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
            Sudoku prueba;
            if(!leerMatriz(prueba)){
                cout << "Entrada erronea" << endl;
                continue;
            }
            DPRINTLN("Imprime");
            //prueba.imprimir(prueba.origen,true,true);
            DPRINTLN('\n');
            if(resolver(prueba)){
                prueba.imprimir(prueba.solucion,false,false);
            }
        }
        break;
    }
    
    return 0;
}
