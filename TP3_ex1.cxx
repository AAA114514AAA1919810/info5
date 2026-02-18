#include <iostream>
using namespace std;

struct listeTab{
    int* tab;
    int taille;
};

struct maillon{
    int val;
    maillon* svt = NULL;
};

listeTab createListeTab(int N){
    listeTab L;
    L.taille = N;
    L.tab = new int[N];
}

maillon* createListeChaine(int N, maillon** m){
    maillon* C = new maillon;
    C->val = N;

    *m = C;
    while (N>0){
        
    }
}
















int main(){






    return 0;
}