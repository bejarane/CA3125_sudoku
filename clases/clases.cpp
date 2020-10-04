#include "clases.h"

/**
 * Crea un objeto de tipo Celda. 
 * Sobre cargado para agregar una celda cuando existe un valor 
 * pre existente. 
 * @constructor
 * @param _pCol Entero que indica la columna a la que pertenece.
 * @param _pRow Entero que indica la fila a la que pertenece.
 * @param _value Entero que indica el valor fijo de la celda.
 */
Celda::Celda(int _pCol, int _pRow, int _value){
    pCol = _pCol;
    pRow = _pRow;
    if (_value>0){
        fija = true;
        value = _value;
    }
}
