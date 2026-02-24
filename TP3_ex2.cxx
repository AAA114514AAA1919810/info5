#include <iostream>
#include <random>
using namespace std;

struct Place {
    int numero;   // num place
    bool occupe;  // false = libre, true = occupee
};

struct Wagon {
    int numero;      // num wagon
    int nb_places;   // nb places dans le wagon
    Place* places;   // tableau dynamique de places
    Wagon* suivant;  // pointeur sur le wagon suivant
};

struct Train {
    Wagon* locomotive;  // pointe sur le premier wagon
    int nb_wagons;      // nb total de wagons
};

int randomInt(int a, int b) {
    random_device dev; 
    mt19937 rng(dev());
    uniform_int_distribution<> dist(a, b);
    return dist(rng);
}


Place creerPlace(int N, bool* numeros_utilises, bool etat) {
    Place p;
    p.occupe = etat;

    int numero;
    do {
        numero = randomInt(1, 2*N); 
    } while(numeros_utilises[numero]);

    p.numero = numero;
    numeros_utilises[numero] = true;

    return p;
}

Wagon* creerWagon(int nb_places, int nb_places_occupees){
    Wagon* w = new Wagon;
    w->nb_places = nb_places;
    w->suivant = nullptr;
    w->places = new Place[nb_places];

    // si nb places occupees saisie plus nb total, on ajuste
    if(nb_places_occupees > nb_places) nb_places_occupees = nb_places;

    // on remplit les places
    for(int i = 0; i < nb_places; i++){
        bool etat;
        if(i < nb_places_occupees) etat = true;    // les premieres places occupees
        else etat = false;                           // autres libres
        w->places[i] = {i+1, etat};                 // num place = 1..nb_places
    }

    return w;
}

bool rechercherPlace(Wagon* wagon, int numero_place, bool& etat) {
    if (wagon == nullptr) return false;

    for (int i = 0; i < wagon->nb_places; i++) {
        if (wagon->places[i].numero == numero_place) {
            etat = wagon->places[i].occupe; // renvoyer l'etat
            return true;                    // place trouvée
        }
    }

    return false; // place non trouvee
}

int nbPlacesOccupees(const Wagon* wagon) {
    if (wagon == nullptr) return 0;

    int compteur = 0;
    for (int i = 0; i < wagon->nb_places; i++) {
        if (wagon->places[i].occupe) {
            compteur++;
        }
    }
    return compteur;
}

bool rechercherPlaceTrain(const Train& train, int numero_wagon, int numero_place, bool& etat) {
    Wagon* courant = train.locomotive;

    // parcourir les wagons
    while(courant != nullptr) {
        if(courant->numero == numero_wagon) {
            // wagon trouvé, chercher la place
            for(int i = 0; i < courant->nb_places; i++) {
                if(courant->places[i].numero == numero_place) {
                    etat = courant->places[i].occupe;
                    return true;
                }
            }
            return false; // wagon trouvé mais place non trouvée
        }
        courant = courant->suivant;
    }

    return false; // wagon non trouvé
}

void insererWagon(Train& train, Wagon* nouveau) {
    if (train.locomotive == nullptr || nouveau->numero < train.locomotive->numero) {
        // insérer au début
        nouveau->suivant = train.locomotive;
        train.locomotive = nouveau;
    } else {
        // parcourir la liste pour trouver l'emplacement
        Wagon* courant = train.locomotive;
        while (courant->suivant != nullptr && courant->suivant->numero < nouveau->numero) {
            courant = courant->suivant;
        }
        // insérer le wagon
        nouveau->suivant = courant->suivant;
        courant->suivant = nouveau;
    }
    train.nb_wagons++;
}

Train creerTrain(int N){
    Train train;
    train.locomotive = nullptr;
    train.nb_wagons = 0;

    for(int i = 0; i < N; i++){
        int num_wagon, nb_places_occupees;
        cout << "Entrez le num du wagon " << i+1 << " : ";
        cin >> num_wagon;
        cout << "Entrez le nb de places occupees : ";
        cin >> nb_places_occupees;

        Wagon* w = creerWagon(5, nb_places_occupees); // 5 places par wagon
        w->numero = num_wagon;

        insererWagon(train, w); // insertion triée
    }

    return train;
}   

void afficherTrain(const Train& train){
    Wagon* courant = train.locomotive;
    while(courant != nullptr){
        cout << "(" << courant->numero
             << ", " << courant->nb_places
             << ", " << nbPlacesOccupees(courant) << ")";
        if(courant->suivant != nullptr) cout << " -> ";
        courant = courant->suivant;
    }
    cout << endl;
}

int main(){
    int N;
    cout << "Combien de wagons dans le train ? ";
    cin >> N;

    Train train = creerTrain(N);

    cout << endl << "Recherche de places dans le train. Entrez 0 pour quitter." << endl;
    while(true){
        int num_wagon, num_place;
        cout << "Numero du wagon : ";
        cin >> num_wagon;
        if(num_wagon == 0) break;
        cout << "Numero de la place : ";
        cin >> num_place;
        if(num_place == 0) break;

        bool etat;
        if(rechercherPlaceTrain(train, num_wagon, num_place, etat)){
            cout << "Place " << num_place << " dans le wagon " << num_wagon
                 << " est " << (etat ? "occupee" : "libre") << endl;
        } else {
            cout << "Place " << num_place << " dans le wagon " << num_wagon << " n'existe pas." << endl;
        }
    }

    cout << "Fin du programme." << endl;

    return 0;
}
