#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "heapparte2.cpp"
using namespace std;

int main(){
    int cant;
    cin >> cant;
    MaxHeap* heap = new MaxHeap(cant);
    int dato;
    for(int i=0; i<cant;i++){
        heap->compararPeso(cin>>dato);
    }
}