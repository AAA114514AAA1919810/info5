#include <iostream>
#include <random>
using namespace std;

int alea(int a, int b){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> dist(a,b);
    
    int val;
    val = dist(rng);

    return val;
}

int* initTablter(int N){
    int* T = new int[N];
    for (int i = 0; i < N; i++){
        T[i] = alea(0, N);
    }
    return T;
}

void afficherRec(int* T, int N){
    if (N > 0){
        afficherRec(T, N-1);
        cout << T[N-1] << " ";
    }
}

int* initTabRec(int* T, int N){
    if (N > 0){
        T[N-1] = alea(0,N);
        initTabRec(T, N-1);
    }
    return T;
}

int additionnerRec(int a, int b){
    if (b == 0){
        return a;
    }
    if (b > 0){
        return 1 + additionnerRec(a, b-1);
    }
    if (b < 0){
        return -1 + additionnerRec(a, b+1);
    }   
}

int sommeTabRec(int* T, int N, int* nb0){
    if ((*T == 0)and(N != 0)){
        (*nb0)++ ;
    }
    if (N > 0){
        return *T + sommeTabRec(T+1,N-1, nb0);
    }
    return 0;
}

int main(){
    int N = 5;
    int* T = initTablter(N);
    cout << "tab 1 : ";
    afficherRec(T, N);
    cout << endl;

    int* nb0_1 = new int;
    int somme = sommeTabRec(T, N, nb0_1);
    cout << "somme = " << somme << endl;
    cout << "nb de 0 : " << *nb0_1 << endl;

    int* T2 = new int[N];
    T2 = initTabRec(T2, N);
    cout << "tab 2 : ";
    afficherRec(T2, N);
    cout << endl;

    int nb0_2 = 0;
    int somme2 = sommeTabRec(T2, N, &nb0_2);
    cout << "somme = " << somme2 << endl;
    cout << "nb de 0 : " << nb0_2 << endl;


    return 0;
}