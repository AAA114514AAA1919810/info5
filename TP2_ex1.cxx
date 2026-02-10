#include <iostream>
using namespace std;

const int MAX = 5;

struct pile{
    int* lst = new int [MAX];
    int taille;
};

bool est_vide(pile* p){
    return p->lst == [];
}
/*
bool empiler(pile* p, int val){
    if ();
}
*/











int main(){
    pile *p;
    p->lst[0]= 0;
    p->lst[1]= 1;
    p->lst[2]= 2;
    p->taille=3;
    cout<< est_vide(p);


    return 0;
}