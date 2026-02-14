#include <iostream>
using namespace std;

const int MAX = 5;

struct pile{
    int* lst = new int [MAX];
    int taille;
};

bool est_vide(pile* p){
    return p->taille == 0;  
}

bool empiler(pile* p, int valeur){
    if(p->taille == MAX){
        return false; // pile pleine
    }

    p->lst[p->taille] = valeur;
    p->taille++;

    return true;
}

int depiler(pile* p){
    if(est_vide(p)){
        cout << "Pile vide !" << endl;
        return -1;
    }

    p->taille--;
    return p->lst[p->taille];
}

bool initPiles(pile P[3], int rayonMax){

    if(rayonMax > MAX){
        return false;
    }

    for(int i = 0; i < 3; i++){
        P[i].taille = 0;
    }

    for(int i = rayonMax; i >= 1; i--){
        empiler(&P[2], i);
    }

    return true;
}

void afficherDisque(int rayon){
    if(rayon == 0){
        // pile vide
        for(int i = 0; i < 2*MAX+1; i++)
            cout << " ";
    } else {
        int espaces = MAX + 1 - rayon;

        // espaces gauche
        for(int i = 0; i < espaces; i++)
            cout << " ";

        // etoiles disque
        for(int i = 0; i < 2*rayon-1; i++)
            cout << "*";

        // espaces droite
        for(int i = 0; i < espaces; i++)
            cout << " ";
    }
}

void afficher(pile P[3]){
    char noms[3] = {'D', 'I', 'A'};
    // nom disque
    for(int i = 0; i < 3; i++){
        for(int k = 0; k < MAX; k++) cout << " ";
        cout << noms[i];
        for(int k = 0; k < MAX; k++) cout << " ";
        if(i < 2) for(int k = 0; k < MAX; k++) cout << " ";
    }
    cout << endl;

    // affichage disque
    for(int niveau = 0; niveau < MAX; niveau++){
        for(int i = 0; i < 3; i++){
            int rayon = 0;
            if(niveau < P[i].taille)
                rayon = P[i].lst[P[i].taille - 1 - niveau];
            afficherDisque(rayon);

            if(i < 2) for(int k = 0; k < MAX; k++) cout << " ";
        }
        cout << endl;
    }
}

void deplacer(int N, int D, int A, int I, pile P[3]){
    if(N == 0) return;

    deplacer(N-1, D, I, A, P);

    int disque = depiler(&P[D]);
    empiler(&P[A], disque);

    afficher(P);
    cout << endl;

    deplacer(N-1, I, A, D, P);
}







int main(){
    pile P[3];

    for(int i=0; i<3; i++)
        P[i].taille = 0;

    int N;
    cout << "Combien de disques voulez-vous jouer ? (max " << MAX << ") : ";
    cin >> N;

    if(N > MAX || N <= 0){
        cout << "Nombre invalide !" << endl;
        return 0;
    }

    initPiles(P, N);

    cout << "Etat initial :" << endl;
    afficher(P);
    cout << endl;

    deplacer(N, 0, 2, 1, P);

    cout << "Tous les disques sont arrives sur le socle A !" << endl;
    return 0;
}