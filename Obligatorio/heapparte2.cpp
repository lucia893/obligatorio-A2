#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

struct Piedra{
    int peso;
};

typedef Piedra *Heap;

class MaxHeap{
private:
    Heap* array;
    int ultimoInsertado;
    int cap;
    
    int izq(int pos){
		return pos * 2;
	}

	int der(int pos){
		return (pos * 2) + 1;
	}

	int padre(int pos){
		return pos / 2;
	}

    void intercambiar(int pos1, int pos2){
		Heap aux = this->array[pos1];
		this->array[pos1] = this->array[pos2];
		this->array[pos2] = aux;
	}

    bool comparar(int dato1, int dato2){
        return (dato1<dato2);
    }

    void flotar(int pos){
		if (pos > 1){
			int posPadre = padre(pos);
			if (comparar(this->array[posPadre], this->array[pos]) == True){
				intercambiar(posPadre, pos);
				flotar(posPadre);
			}
		}
	}
    
    void hundir(int pos){
		int hizq = izq(pos);
		int hder = der(pos);
		if (hizq < ultimoInsertado && hder < ultimoInsertado){
            int posMayorHijo = hizq;
            if(hizq < hder){
                posMayorHijo = hder;
            }
			if (comparar(pos,posMayorHijo) == True){
				intercambiar(pos, posMayorHijo);
				hundir(posMayorHijo);
			}
		}
		else if (hizq < ultimoInsertado){
			if (comparar(pos,hizq) == True){
				intercambiar(pos, hizq);
				hundir(hizq);
			}
		}
	}

    void eliminar(){
		assert(!estaVacio());
		this->arr[1] = this->arr[ultimoInsertado - 1];
		this->ultimoInsertado--;
		hundir(1);
	}

public:
    MaxHeap(int capacidad){
        this->array = new Heap[capacidad+1];
        this->ultimoInsertado = 1;
        this->cap = capacidad;
    }

    int devolverTope(){
        assert(!estaVacio());
        return this->array[1];
    }

    void insertar(int dato){
		assert(!estaLleno());
		this->arr[ultimoInsertado++] = dato;
		flotar(ultimoInsertado - 1);
	}

    bool estaLleno(){
		return this->ultimoInsertado > this->cap;
	}

	bool estaVacio(){
		return this->ultimoInsertado == 1;
	}

    void eliminar(){
		assert(!estaVacio());
		this->array[1] = this->array[ultimoInsertado - 1];
		this->ultimoInsertado--;
		hundir(1);
	}

    void compararPeso(int dato){
        int raiz = this->array[1];
        int hizq = izq(raiz);
        int hder = der(raiz);
        int res;
        if(comparar(hizq,hder) == True){
            res = raiz - hder;
        }
        else{
            res = raiz - hizq;
        }
        if(res>0){
            this->eliminar();
            this->eliminar();
            insertar(dato);
        }
        else{
            this->eliminar();
            this->eliminar();
        }
    }
}