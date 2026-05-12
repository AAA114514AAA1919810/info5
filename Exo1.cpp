#include <iostream>
#include <sstream>
#include <cmath>
#include <array>
#include <ctime>
#include <fstream>
// pour la présentation 
#include <iomanip>

using namespace std;

/// TRI SELECTION MINIMAL - ON recherche le plus petit et on le met à sa place
void tri_selection (int *tabI, int N, long *cpt) {
  int ind, position, i, tmp;
      (*cpt)++;
  for (ind=0; ind<N-1;ind++) { //E1
      (*cpt)++;
    position = ind; //E2
    for (i=ind+1;i<N;i++)  { //E3
      (*cpt)++;
      if (tabI[position] > tabI[i]) { //E4
      (*cpt)++;
	position = i; //E5
      }
    }
      (*cpt)++;
    if (position != ind)  { //E6
       (*cpt)++;
     tmp = tabI[position]; //E7
       (*cpt)++;
     tabI[position] = tabI[ind]; //E8
       (*cpt)++;
     tabI[ind] = tmp; //E9
    }
  }
}

/// TRI INSERTION
void tri_insertion (int *tabI, int N, long *cpt) {
  int  indice_elt, position, elt;
    (*cpt)++;
  for (indice_elt=1;indice_elt<N;indice_elt++) { //E1
     (*cpt)++;
   elt = tabI[indice_elt];
     (*cpt)++;
   position = indice_elt;
    (*cpt)++;
    while (position > 0 && tabI[position-1] > elt)  { //E2
      (*cpt)++;
      tabI[position] = tabI[position-1]; //E3
       (*cpt)++;
   position=position-1;
    }
      (*cpt)++;
  tabI[position] = elt;
  }
}

/// TRI FUSION
void fusion (int *tabI, int debut, int milieu,  int fin, long *cpt) {
  int  cptG, cptD,i=0,j;
  int *tmp = new int[fin-debut+1];
    (*cpt)++;
  cptG = debut;
     (*cpt)++;
 cptD = milieu+1;
    (*cpt)++;
  while ((cptG<=milieu) and (cptD<=fin)) { //E1 : 2 tableaux non vides
     (*cpt)++;
   if (tabI[cptG] < tabI[cptD])  {
     (*cpt)++;
     tmp[i] = tabI[cptG];
     (*cpt)++;
     cptG = cptG+1;
    }
    else {
    (*cpt)++;
      tmp[i] = tabI[cptD];
     (*cpt)++;
     cptD = cptD+1;
    }
    i = i+1;
    (*cpt)++;
      } //un des 2 tableaux (ou les 2) est vide
    (*cpt)++;
  while (cptD <= fin)  { //E2 : tableau gauche vide, on complete avec tableau droit trie
     (*cpt)++;
   tmp[i] = tabI[cptD];
    (*cpt)++;
    cptD = cptD+1;
    i = i+1;
    (*cpt)++;
  }
    (*cpt)++;
  while (cptG <= milieu) { //E3 : tableau droit vide, on complete avec tableau gauche trie
     (*cpt)++;
   tmp[i] = tabI[cptG];
     (*cpt)++;
   cptG = cptG+1;
    i = i+1;
    (*cpt)++;
  }
  
    (*cpt)++;
  for (j=0;j<i;j++) { //E4 : recopie du tableau temporaire dans
    (*cpt)++;
    tabI[debut+j] = tmp[j] ;
  }
}

void tri_fusion (int *tabI, int debut, int fin, long *cpt) {
      int  milieu;
    (*cpt)++;
      if (debut < fin)  {
     (*cpt)++;
       milieu = (fin+debut)/2;
     (*cpt)++;
       tri_fusion(tabI, debut, milieu, cpt); 
     (*cpt)++;
       tri_fusion(tabI, milieu+1, fin, cpt); 
    (*cpt)++;
        fusion(tabI, debut, milieu, fin, cpt); 
      }
    }

void lance_tri_fusion(int tab[], int N, long *cpt) {
  tri_fusion (tab, 0, N-1, cpt);
}
						
/// TRI RAPIDE (quick-sort)
void echanger(int T[], int a, int b) {
      if (a!=b) {
	int tmp = T[a];
	T[a] = T[b];
	T[b] = tmp;
      }
}  
  
int partitionnement (int tabI[], int debut, int fin, long *cpt) { 
  int pivot, ptr_Petit, ptr_courant;
    (*cpt)++;
  pivot = tabI[fin];
    (*cpt)++;
  ptr_Petit = debut - 1;
    (*cpt)++;
  for (ptr_courant=debut; ptr_courant<=fin-1; ptr_courant++)  { //on parcourt tous les élts~
     (*cpt)++;
   if (tabI[ptr_courant] < pivot) { //échange
     (*cpt)++;
     ptr_Petit = ptr_Petit + 1; //on pointe sur le 1er plus grand
     (*cpt)++;
     echanger(tabI,ptr_courant,ptr_Petit);
    }
  }
     (*cpt)++;
 ptr_Petit = ptr_Petit + 1;
    (*cpt)++;
  echanger(tabI,ptr_Petit,fin);
     (*cpt)++;
 return ptr_Petit;
}

void tri_rapide (int tabI[], int debut, int fin, long *cpt) { 
  int pivot;
     (*cpt)++;
 if (debut < fin)  {
    (*cpt)++;
    pivot = partitionnement(tabI, debut, fin, cpt); 
    (*cpt)++;
    tri_rapide(tabI, debut, pivot-1, cpt);
     (*cpt)++;
   tri_rapide(tabI, pivot+1, fin, cpt);
  }
}

void lance_tri_rapide(int tab[], int N, long *cpt) {
  tri_rapide (tab, 0, N-1, cpt);
}
						
// définition du tableau de fonctions de tris
void (*tab_tris[4]) (int tab[], int N, long *cpt) = {
  tri_selection, tri_insertion, lance_tri_fusion, lance_tri_rapide};


void initTab(int **Talea, int **Tdec, int **Ttrie, int N) {
  *Talea = new int[N];
  *Tdec = new int[N];
  *Ttrie = new int[N];
  for (int i=0;i<N;i++) {
    (*Talea)[i] = 1+rand()%N;
    (*Tdec)[i] = N-i;
    (*Ttrie)[i] = i+1;
  }
}

void afficher_tableau(int T[], int N) {
  for (int i=0;i<N;i++) {
    if (i%10==0) cout << endl;
    cout << setw(5) << T[i];
  }
}

int *recopier(int T[], int N) {
  int *rec = new int[N];
  for (int i=0;i<N;i++)
    rec[i] = T[i];
  return rec;
}


int main(int argc, char **argv)
{

  int * tab_init[3];
  int * tab_donnees[3];
  long cpt_etape = 0;
  int taille;
  string TTab[3] = {"aleatoire", "decroissant", "croissant"};
  string TTri[4] = {"selection", "insertion", "fusion", "rapide"};

  srand(time(NULL));

  ofstream monflux(argv[1]);

  if (monflux) {
    monflux << "type_tab, taille_tab, type_tri, temps, nb_etapes" << endl;
    
    for (taille = 10; taille <=10240; taille*=2) {
      initTab(&tab_init[0], &tab_init[1], &tab_init[2], taille);
      for (int typeTab = 0; typeTab<3 ; typeTab++) {
	for (int tri = 0 ; tri < 4; tri++) {
	  tab_donnees[typeTab] = recopier(tab_init[typeTab], taille);
	  cpt_etape = 0;
	  clock_t prec = clock() ;
	  tab_tris[tri](tab_donnees[typeTab], taille, &cpt_etape);
	  clock_t svt = clock();
	  double tmps = double(svt-prec)*1000/ CLOCKS_PER_SEC;
	  //remplissage
	  monflux << TTab[typeTab] << "," << taille << "," << TTri[tri] << "," << tmps << "," << cpt_etape << endl;
	}
      }
    }
  }
  else {
    cout << "ERREUR : impossible d'ouvrir le fichier" << endl;
  }


 return 0;
}
