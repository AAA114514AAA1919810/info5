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
    return L;
}

maillon* createListeChaine(int N){
    if (N <= 0) return NULL;

    maillon* tete = new maillon;
    tete->val = 0;
    tete->svt = NULL;

    maillon* courant = tete;

    for(int i = 1; i < N; i++){
        maillon* nouveau = new maillon;
        nouveau->val = i;
        nouveau->svt = NULL;

        courant->svt = nouveau; 
        courant = nouveau;
    }

    return tete;
}

// Les tableau dynamique

void afficheListeTab(listeTab L){
    for(int i = 0; i < L.taille; i++){
        cout << L.tab[i];
        if(i < L.taille - 1)
            cout << " -> ";
    }
    cout << endl;
}

bool rechercheValeurTab(listeTab L, int valeur, int& position){

    for(int i = 0; i < L.taille; i++){
        if(L.tab[i] == valeur){
            position = i + 1;
            return true;
        }
    }

    position = -1;
    return false;
}

bool supprimePositionTab(listeTab& L, int P, int& valeurSupprimee){

    if(P < 1 || P > L.taille)
        return false;

    int index = P - 1;
    valeurSupprimee = L.tab[index];

    // décalage vers la gauche
    for(int i = index; i < L.taille - 1; i++){
        L.tab[i] = L.tab[i+1];
    }

    L.taille--;
    return true;
}

bool inserePositionTab(listeTab& L, int val, int P){

    if(P < 0 || P > L.taille)
        return false;

    int* nouveauTab = new int[L.taille + 1];

    // avant insertion
    for(int i = 0; i < P; i++)
        nouveauTab[i] = L.tab[i];

    // insertion
    nouveauTab[P] = val;

    // après insertion
    for(int i = P; i < L.taille; i++)
        nouveauTab[i+1] = L.tab[i];

    delete[] L.tab;
    L.tab = nouveauTab;
    L.taille++;

    return true;
}

void recopieListeTab(listeTab L, listeTab& Lrecopie){

    Lrecopie.taille = L.taille;
    Lrecopie.tab = new int[L.taille];

    for(int i = 0; i < L.taille; i++)
        Lrecopie.tab[i] = L.tab[i];
}

void concateneListeTab(listeTab L1, listeTab L2, listeTab& Lfusion){

    Lfusion.taille = L1.taille + L2.taille;
    Lfusion.tab = new int[Lfusion.taille];

    for(int i = 0; i < L1.taille; i++)
        Lfusion.tab[i] = L1.tab[i];

    for(int i = 0; i < L2.taille; i++)
        Lfusion.tab[L1.taille + i] = L2.tab[i];
}

int supprimeTouteValTab(listeTab& L, int valeur){

    int compteur = 0;

    for(int i = 0; i < L.taille; i++){
        if(L.tab[i] == valeur){
            compteur++;

            for(int j = i; j < L.taille - 1; j++)
                L.tab[j] = L.tab[j+1];

            L.taille--;
            i--; 
        }
    }

    return compteur;
}



// Les liste chainees

void afficheListeChaine(maillon* L){
    maillon* courant = L;

    while(courant != NULL){
        cout << courant->val;

        // on affiche la fleche seulement si suivant existe
        if(courant->svt != NULL){
            cout << " -> ";
        }

        courant = courant->svt;
    }

    cout << endl;
}

bool rechercheValeurChaine(maillon* L, int valeur, int& position){
    position = 1;              // on commence avec pos = 1
    maillon* courant = L;

    while(courant != NULL){
        if(courant->val == valeur){
            return true;       
        }

        courant = courant->svt;
        position++;
    }

    position = -1;             // pos -1 pour val non trouvee   
    return false;
}

bool supprimePositionChaine(maillon*& L, int P, int& valeurSupprimee){

    if(L == NULL || P <= 0)
        return false;

    // cas spe lorsqu'on supprime la tete
    if(P == 1){
        maillon* aSupprimer = L;
        valeurSupprimee = aSupprimer->val;

        L = L->svt;        // nouvelle tête
        delete aSupprimer;

        return true;
    }

    // chercher elt juste avant pos recherchee
    maillon* courant = L;
    int position = 1;

    while(courant != NULL && position < P-1){
        courant = courant->svt;
        position++;
    }

    // pos P n'existe pas
    if(courant == NULL || courant->svt == NULL)
        return false;

    // suppression
    maillon* aSupprimer = courant->svt;
    valeurSupprimee = aSupprimer->val;

    courant->svt = aSupprimer->svt;
    delete aSupprimer;

    return true;
}

bool inserePositionChaine(maillon*& L, int val, int P){

    if(P < 0)
        return false;

    //  insert tete
    if(P == 0){
        maillon* nouveau = new maillon;
        nouveau->val = val;
        nouveau->svt = L;
        L = nouveau;
        return true;
    }

    // chercher elt juste avant pos P
    maillon* courant = L;
    int position = 0;

    while(courant != NULL && position < P-1){
        courant = courant->svt;
        position++;
    }

    // pos impossible
    if(courant == NULL)
        return false;

    // insert
    maillon* nouveau = new maillon;
    nouveau->val = val;

    nouveau->svt = courant->svt;
    courant->svt = nouveau;

    return true;
}

void recopieListeChaine(maillon* L, maillon*& Lrecopie){

    Lrecopie = NULL;

    if(L == NULL)
        return;

    // cree 1er elt
    Lrecopie = new maillon;
    Lrecopie->val = L->val;
    Lrecopie->svt = NULL;

    maillon* courantSource = L->svt;
    maillon* courantCopie = Lrecopie;

    // copie du reste
    while(courantSource != NULL){
        maillon* nouveau = new maillon;
        nouveau->val = courantSource->val;
        nouveau->svt = NULL;

        courantCopie->svt = nouveau;

        courantCopie = nouveau;
        courantSource = courantSource->svt;
    }
}

void concateneListeChaine(maillon* L1, maillon* L2, maillon*& Lfusion){

    Lfusion = NULL;
    maillon* fin = NULL; // dernier élément de la fusion

    // copier L1 
    maillon* courant = L1;
    while(courant != NULL){
        maillon* nouveau = new maillon;
        nouveau->val = courant->val;
        nouveau->svt = NULL;

        if(Lfusion == NULL){
            Lfusion = nouveau;
            fin = nouveau;
        }else{
            fin->svt = nouveau;
            fin = nouveau;
        }

        courant = courant->svt;
    }

    // copier L2
    courant = L2;
    while(courant != NULL){
        maillon* nouveau = new maillon;
        nouveau->val = courant->val;
        nouveau->svt = NULL;

        if(Lfusion == NULL){
            Lfusion = nouveau;
            fin = nouveau;
        }else{
            fin->svt = nouveau;
            fin = nouveau;
        }

        courant = courant->svt;
    }
}

int supprimeTouteValChaine(maillon*& L, int valeur){

    int compteur = 0;

    // supprimer tete si necessaire
    while(L != NULL && L->val == valeur){
        maillon* aSupprimer = L;
        L = L->svt;
        delete aSupprimer;
        compteur++;
    }

    // si liste devient vide apres boucle
    if(L == NULL)
        return compteur;

    // suppression reste
    maillon* courant = L;

    while(courant->svt != NULL){
        if(courant->svt->val == valeur){
            maillon* aSupprimer = courant->svt;
            courant->svt = aSupprimer->svt;
            delete aSupprimer;
            compteur++;
        }else{
            courant = courant->svt;
        }
    }

    return compteur;
}


int main() {
    int tailles[] = {10, 50, 100, 1000, 10000};

    for(int t = 0; t < 5; t++){
        int N = tailles[t];

        cout << "Taille de la liste ? " << N << endl;

        // creation tableau
        clock_t prec = clock();
        listeTab Ltab = createListeTab(N);
        clock_t svt = clock();
        double temps_tab = double(svt - prec) * 1000 / CLOCKS_PER_SEC;
        cout << "Representation en tableau : " << temps_tab << " ms" << endl;

        // creation liste chainee
        prec = clock();
        maillon* Lchaine = createListeChaine(N);
        svt = clock();
        double temps_chaine = double(svt - prec) * 1000 / CLOCKS_PER_SEC;
        cout << "Liste chainie : " << temps_chaine << " ms" << endl;

        cout << endl;
    }
    return 0;
}


// Les liste chainees sont plus lentes que les tableaux pour creer la liste, car elles dois allouer un emplacement pour chaque elts 
// en revenche lorqu'on modifie un elt, les tableaux sont moins efficaces car il faut deplacer toutes les elts apres l'elt modifie
// donc plus la liste est grande, plus les liste chainees sont efficace, et pour les petites listes, les tableaux sont plus efficaces 