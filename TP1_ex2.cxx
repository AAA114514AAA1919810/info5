#include <iostream>
using namespace std;

struct Ville {
    string nom;
    double latitude;
    double longitude;
};

struct TabVilles {
    Ville* villes;
    int nbVilles;
};

struct Tournee {
    int* villesVisitees;
    int nbVillesVisitees;
};

Ville saisirUneVille() {
    Ville v;
    cout << "Nom ville : ";
    cin >> v.nom;
    cout << "Latitude : ";
    cin >> v.latitude;
    cout << "Longitude : ";
    cin >> v.longitude;
    return v;
}

void saisirLesVilles(int nbVilles, Ville* villes, int indice) {
    if (indice >= nbVilles) {
        return;
    }

    cout << endl <<"Ville numero " << indice << endl;
    villes[indice] = saisirUneVille();

    saisirLesVilles(nbVilles, villes, indice + 1);
}

void saisirEnsembleVilles(TabVilles& tv) {
    cout << "Combien de villes voulez-vous saisir ? " << endl;
    cin >> tv.nbVilles;

    tv.villes = new Ville[tv.nbVilles];

    saisirLesVilles(tv.nbVilles, tv.villes, 0);
}

bool villeDeja(int* villes, int villeRecherchee, int indice, int nbVilles) {
    if (indice >= nbVilles) {
        return false;
    }

    if (villes[indice] == villeRecherchee) {
        return true;
    }

    return villeDeja(villes, villeRecherchee, indice + 1, nbVilles);
}

void saisirVilleTournee(int* tournee, int nbVillesTournee, int nbVillesExistantes, int indice) {
    if (indice >= nbVillesTournee) {
        return;
    }

    int numVille;
    cout << "Numero de la ville pour l'etape " << indice << " : " << endl;
    cin >> numVille;

    if (numVille < 0 || numVille >= nbVillesExistantes) {
        cout << "Ville inexistante. Reessayez." << endl;
        saisirVilleTournee(tournee, nbVillesTournee, nbVillesExistantes, indice);
        return;
    }

    if (villeDeja(tournee, numVille, 0, indice)) {
        cout << "Ville deja utilisee. Reessayez." << endl;
        saisirVilleTournee(tournee, nbVillesTournee, nbVillesExistantes, indice);
        return;
    }

    //cas final ou la saisie est valide
    tournee[indice] = numVille;

    saisirVilleTournee(tournee, nbVillesTournee, nbVillesExistantes, indice + 1);
}

Tournee saisirTournee(const TabVilles& tv) {
    Tournee t;

    cout << "Combien de villes seront visitees dans la tournee ? " << endl;
    cin >> t.nbVillesVisitees;

    t.villesVisitees = new int[t.nbVillesVisitees];

    // appel fonction rec pour saisir les num des ville
    saisirVilleTournee(t.villesVisitees, t.nbVillesVisitees, tv.nbVilles, 0);

    return t;
}



int main() {
    TabVilles tv;

    saisirEnsembleVilles(tv);

    cout << endl << "--- Villes saisies ---" << endl;
    for (int i = 0; i < tv.nbVilles; i++) {
        cout << "Ville " << i << " : "
             << tv.villes[i].nom << " ("
             << tv.villes[i].latitude << ", "
             << tv.villes[i].longitude << ")"
             << endl;
    }

    delete[] tv.villes;

    return 0;
}

