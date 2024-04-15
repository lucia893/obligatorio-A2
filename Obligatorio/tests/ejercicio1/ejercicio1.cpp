#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "hashparte1.cpp"

using namespace std;


int main(){
    int oper;
    cin >> oper;
    string tipoOper;
    int id;
    string elem;
    string e = "Entregado";
    TablaHashAbierta_Ordenes* tabla = new TablaHashAbierta_Ordenes(oper);
    for(int i=0; i<oper;i++){
        cin >> tipoOper;
        cin >> id;
        if(tipoOper == "A"){
            getline(cin,elem);
            elem.erase(0,1);
            tabla->insertarOrden(id,elem);
        }
        else if(tipoOper == "E"){
            tabla->insertarOrden(id,e);
        }
        else if(tipoOper == "Q"){
            tabla->imprimir(id);
        }  
    }
}
