#include <iostream>
using namespace std;

struct joueur{
    string nom;
    bool titulaire;
    int numero, point;
};

joueur saisirJoueur(){
    joueur j;
    cout << "nom : " << endl;
    cin >> j.nom;
    cout << endl << "titulaire ? (saisir 0 pour non, 1 pour oui) : " << endl;
    cin >> j.titulaire;
    cout << endl << "numero : " << endl;
    cin >> j.numero;
    cout << endl << "point: " << endl;
    cin >> j.point;
    cout << endl;
    return j;
}

struct equipe {
    joueur* membre;
    int nbJoueurs;
    int nbTit;
};

int compterTit(equipe e) {
    int nb = 0;
    for (int i = 0; i < e.nbJoueurs; i++) {
        if (e.membre[i].titulaire) {
            nb++;
        }
    }
    return nb;
}

void initEquipe(equipe* E) {

    cout << "Combien de joueurs dans l'equipe ? ";
    cin >> (*E).nbJoueurs;

    (*E).membre = new joueur[(*E).nbJoueurs];

    (*E).nbTit = 0;

    for (int i = 0; i < (*E).nbJoueurs; i++) {
        cout << endl << "Joueur " << i + 1 << endl;
        (*E).membre[i] = saisirJoueur();

        if ((*E).membre[i].titulaire) {
            (*E).nbTit++;
        }
    }

    cout << endl << "Equipe initialisee avec " << (*E).nbJoueurs
         << " joueurs dont " << (*E).nbTit << " titulaires" << endl;
}

void compterPoints(equipe* E, int* total, int* tit, int* remp) {
    *total = 0;
    *tit = 0;
    *remp = 0;

    for (int i = 0; i < (*E).nbJoueurs; i++) {
        *total += (*E).membre[i].point;

        if ((*E).membre[i].titulaire) {
            *tit += (*E).membre[i].point;
        } else {
            *remp += (*E).membre[i].point;
        }
    }
}

void augmentationTaille(joueur** Membre, int taille, int newTaille) {
    joueur* nouveau = new joueur[newTaille];

    for (int i = 0; i < taille; i++) {
        nouveau[i] = (*Membre)[i];
    }

    delete[] *Membre;

    *Membre = nouveau;
}

void rajouterJoueur(equipe* E) {
    int nbAjout;
    cout << "Combien de nouveaux joueurs a ajouter ? " << endl;
    cin >> nbAjout;

    if (nbAjout <= 0) {
        cout << "pas de joueur ajout" << endl;
        return;
    }

    int tailleAvant = (*E).nbJoueurs;

    // agrandir le tableau pour pouvoir mettre les nouveaux joueurs
    augmentationTaille(&(*E).membre, (*E).nbJoueurs, (*E).nbJoueurs + nbAjout);

    // saisir les nouveaux joueurs
    for (int i = tailleAvant; i < (*E).nbJoueurs + nbAjout; i++) {
        cout << endl << "Nouveau joueur " << i + 1 << endl;
        (*E).membre[i] = saisirJoueur();

        if ((*E).membre[i].titulaire) {
            (*E).nbTit++;
        }
    }

    // Mettre à jour le nb total joueurs
    (*E).nbJoueurs += nbAjout;

    cout << endl << nbAjout << " joueurs ajoutes" << endl;
    cout << "nouvelle taille de l'equipe : " << (*E).nbJoueurs << " joueurs" << endl;
}

int main(){
    equipe monEquipe;
    initEquipe(&monEquipe);

    cout << endl << "Liste des joueurs :" << endl;
    for (int i = 0; i < (*(&monEquipe)).nbJoueurs; i++) {
        cout << "Nom : " << (*(&monEquipe)).membre[i].nom
             << ", Titulaire : " << ((*(&monEquipe)).membre[i].titulaire ? "O" : "N")
             << ", Numero : " << (*(&monEquipe)).membre[i].numero
             << ", Points : " << (*(&monEquipe)).membre[i].point << endl;
    }

    int total, titulaires, remplaçants;
    compterPoints(&monEquipe, &total, &titulaires, &remplaçants);

    cout << endl <<"Points totaux : " << total << endl;
    cout << "Points des titulaires : " << titulaires << endl;
    cout << "Points des remplacants : " << remplaçants << endl;

    delete[] (*(&monEquipe)).membre;
    return 0;
}
