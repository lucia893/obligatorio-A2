#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

struct Orden{
    int id;
    string elem;
    Orden* sig;
};

typedef Orden *Lista;

class TablaHashAbierta_Ordenes{
private:
    //Atributos
    Lista *arrayElem;
    Lista *arrayElem2;
    Lista* aux;
    int tamTabla;
    int cantOrdenes;
    
    float factorDeCarga(){
		return (float)this->cantOrdenes / this->tamTabla;
	}

    void insertarRecusrivo(int identificador, string elementos, Orden *&auxiliar){
		if (auxiliar == NULL){
			auxiliar = new Orden;
            auxiliar->id = identificador;
            auxiliar->elem = elementos;
            auxiliar->sig = NULL;
            this->cantOrdenes++;
		}
		else{
			if (auxiliar->id == identificador){
				auxiliar->elem = elementos;
			}
			else{
                insertarRecusrivo(identificador, elementos, auxiliar->sig);
            } 
		}
	}

    //Retorna true si la orden existe
    bool estaOrden (int identificador, Orden *auxiliar){
        if(auxiliar == NULL){
            return false;
        }
        else{
            if(auxiliar->id == identificador){
                return true;
            }
            else{
                return estaOrden(identificador,auxiliar->sig);
            }
        }
    }

    string devolverOrden(int id, Orden* auxiliar){
        int pos = abs(this->funHash(id)) % this->tamTabla;
        if(arrayElem[pos]->id == id){
            return arrayElem[pos]->elem;
        }
        else{
            return devolverOrden(id,auxiliar->sig);
        }
    }

    void rehash(int id){
        int auxTam = tamTabla;
		this->tamTabla = this->tamTabla*2;
        for (int i = 0; i < auxTam; i++){
            this->aux[i] = this->arrayElem[i];
            while(this->aux != NULL){
                int pos = abs(this->funHash(id)) % this->tamTabla;
                arrayElem2[pos]->elem = aux[i]->elem;
                arrayElem2[pos]->id = aux[i]->id;
                arrayElem2[pos]->sig = aux[i]->sig;
            }
        }
        this->arrayElem = this->arrayElem2;
        //delete[]arrayElem2;
	}

public:
    //Constructor
    TablaHashAbierta_Ordenes(int tamaTabla){
		this->tamTabla = tamaTabla;
		this->cantOrdenes = 0;
		arrayElem = new Lista[this->tamTabla]();
	}

    //Funcion hash
    int funHash(int id){
		return abs(id%this->tamTabla);
	}

    //Funcion insertar orden
    void insertarOrden(int identificador, string elementos){
		int pos = (this->funHash(identificador));
        this->insertarRecusrivo(identificador, elementos,arrayElem[pos]);
		if (this->factorDeCarga() > 0.7){
            this->rehash(identificador);
        }
	}

    void imprimir(int id){
        int pos = abs(this->funHash(id)) % this->tamTabla;
		if(this->estaOrden(id,arrayElem[pos]) == false){
            cout << "Pedido no encontrado";
        }
        else{
            cout << this->devolverOrden(id,arrayElem[pos]);
        }
        cout << endl;
	}
};