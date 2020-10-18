#include "clases.h"

/**
 * Identifica la celda con la menor cantidad de posibilidades. 
 * @brief Recorre el vector de posibilidades para encontrar aquel con menor cantidad. 
 * @return Entero que indica la posición de la casilla con menos posibilidades.
 */
int Matriz::menor(){ //http://www2.lawrence.edu/fast/GREGGJ/CMSC270/iterators.html
    vector<vector<int>> _data = posibilidades;
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

/**
 * Imprime el contenido de una matriz de Sudoku
 * @param entrada Objeto de tipo Matriz.
 * @param bin Booleano que indica si imprimir el Sudoku en binario.
 * @param posi Booleano que indica si se debe imprimir la lista de posibilidades.
 */
void Sudoku::imprimir(Matriz entrada, bool bin, bool posi){
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

/**
 * Imprime el contenido de una matriz de Sudoku
 * @param entrada 
 */
// void Sudoku::imprimirDec(vector<vector<int>> contenido){
//     int n = 0;
//     cout << endl;
//     //cout << tamano << "matriz" << endl;
//     while(n<tamano){
//         cout << "l\t";
//         int m = 0;
//         while(m<tamano){
//             int punto = contenido[n][m];
//             for (int j = 0; j <tamano; j++){
//                 if((punto&1<<j)>0){ //es una posibilidad
//                     punto = j+1; //el 1 tiene una posicion 0
//                     cout << punto << " ";
//                     break;
//                 }
//             }
//             m++;
//         }
//         cout << endl;
//         n++;
//     }
// }

/**
 * Lee la entrada de consola e identifica el tipo de análisis que se desea llevar a cabo
 * @return Booleano, true para profundidad y false para anchura.
 */
bool Sudoku::leerTipo(){
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
 * Comprueba si el número enviado es una raiz entera.
 * @param _n Numero entero a verificar
 * @return Entero, valor de la raiz del numero ingresado.
 */
int Sudoku::esRaizEntera(int _n){  //https://www.johndcook.com/blog/2008/11/17/fast-way-to-test-whether-a-number-is-a-square/
    int base  = _n & 0xF;
    if (base > 9) return -1;
    if(base != 2 && base != 3 && base != 5 && base != 6 && base != 7 && base != 8){
        int raiz = (int) floor(sqrt((double)base));
        return raiz*raiz==base?raiz:-1;
    }
    return -1;
}

/**
 * Inserta evaluando reglas. 
 * Inserta un valor verificando que este cumpla con las 3 reglas
 * del sudoku. 
 * @param data Tipo Matriz con datos de entrada y posibilidades
 * @param numero Numero entero a insertar en bitmask
 * @param col Columna en el que va [x][col]
 * @param fil Fila en la que va [fil][x]
 */
bool Sudoku::insertarRegla(Matriz &data,int numero, int col, int fil){
    //anotar filas
    int size = tamano;
    int subsize = subtamano;
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

/**
 * Lee la entrada de consola e identifica el tipo de análisis que se desea llevar a cabo
 * @return Booleano, false en caso de que haya un error en la matriz de sudoku
 */
bool Sudoku::parseInput(){
    int input;
    vector<int> test;
    metodo = leerTipo(); // inserta un valor que indica el tipo de evaluacion
    string line;
    getline(cin, line); //lee la linea restante con n numeros
    istringstream iss(line);
    int contador = 0;
    while ( iss >> input) {  //la funcion >> lee hasta topar con un espacio, asi que está leyendo ints  
        test.push_back(input);
        contador ++; //cuenta la cantidad de digitos
    }
    int subMatriz = esRaizEntera(contador);
    DPRINT(subMatriz);
    DPRINTLN("Raiz");
    if (subMatriz>0){ // si es una entrada valida 
        tamano = contador; //actualiza campos
        subtamano = subMatriz;
        origen.restantes = contador*contador;
    }
    const int base0 = BLANK(tamano);
    vector <int> base1 (tamano,base0); // se prepara la base
    vector<vector <int>> base2 (tamano,base1);
    vector<int> posib0 (3,tamano);
    vector <vector<int>> posib1 (tamano*tamano,posib0);
    origen.contenido=base2;
    origen.posibilidades=posib1;
    vector <int> swap = test;
    int k  = 0;
    while(k < tamano){
        if(test[k]!=0){
            int buff = SET(base0,test[k]);
            if(!insertarRegla(origen,buff,k,0))return false;
        }
        k ++;
    }
    DPRINTLN("FLAG1");

    int fila = 1; //extrae las siguientes n-1 lineas
    while(fila<tamano){

        getline(cin, line); //lee la linea restante con n numeros
        istringstream iss2(line);
        int col = 0;
        while ( iss2 >> input) {  //la funcion >> lee hasta topar con un espacio, asi que está leyendo ints  
            if(input!=0){
                int buff = SET(base0,input);
                if(!insertarRegla(origen,buff,col,fila))return false;
            }
            col++;
        }
        fila++;
    }
    DPRINTLN("Finaliza lectura");
    return true;
}

/**
 * Inicia la lectura de la entrada de matriz
 * @return Booleano, false en caso de recibir una matriz vacía.
 */
bool Sudoku::leerMatriz(){
    parseInput();
    if(tamano==0)return false;
    return true;
}
/**
 * Evalua los casos disponibles y crea una nueva matriz solucion para cada caso
 * posteriormente coloca la nueva matriz en una pila o cola.
 * @param data Matriz a la cual se insertan los datos
 * @param punto Entero que referencia a una posicion en la matriz de 
 * probabilidades y en la matriz de datos
 * @return Booleano, false en caso de no ser capaz de crear una matriz con esa opcion.
 */
bool Sudoku::crearcasos(Matriz data, int punto){
    int col = punto-((punto/tamano)*tamano);
    int fil = (punto/tamano);
    punto = data.contenido[fil][col];
    bool posible = false;
    for (int j = 0; j < tamano; j++){
        if((punto&1<<j)>0){ //es una posibilidad
            Matriz dummy = data;//se copia la matriz original
            if(insertarRegla(dummy,punto&1<<j,col,fil)){
                DPRINT("Creando caso con:");
                DPRINTLN(j+1);
                if(metodo==0){ //anchura
                    cola.push(dummy);
                }else{
                    pila.push(dummy);
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

/**
 * @brief Funcion recurrente que ese encarga de evaluar los casos contenidos en las pilas
 * y generar nuevos casos.
 * @return Booleano, true al resolver el sudoku y false en caso de no poder resolverlo.
 */
bool Sudoku::recurrencia(){
    //primero, obtener la siguiente evaluacion
    Matriz caso;
    if(metodo==0){ //anchura
        caso = cola.front();
        cola.pop();
    }else{ //profundidad
        caso = pila.top();
        pila.pop();
    }

    //_sudoku.imprimir(caso,false,true);

    if (caso.restantes==0) { //lo resolvio!!
        solucion = caso;
        return true;
    }

    int sig = caso.menor();
    //cout << "siguiente" << caso.posibilidades[sig][0] << endl;
    if (sig == -1) return false; //fallo drasticamente, no deberia pasar
    crearcasos(caso,sig); //no puedo generar el caso que correspondia a esta
    //posibilidad

    return recurrencia();
}

/**
 * @brief Funcion que comienza el proceso de verificaciones del sudoku que se ha ingresado.
 * @return Booleano, true al resolver el sudoku, falso en caso contrario.
 */
bool Sudoku::resolver(){
    //primero, conocer el menor de posibilidades
    int sig = origen.menor();
    if (sig == -1) {//se insertó un sudoku ya resuelto
        solucion = origen;
        return true; 
    }
    //cout << "siguiente" << origen.posibilidades[sig][0] << endl;
 
    if(!crearcasos(origen,sig)){
        cout << "No se puede resolver, el menor era: " << sig << endl;
        return false;
    }
    if(!recurrencia()){
        cout << "No se puede resolver por backtracking"<< endl;
        return false;
    }
    return true;
}