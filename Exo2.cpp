#include <iostream>
#include <sstream>
#include <cmath>
#include <array>
#include <ctime>
#include <fstream>
/* pour la présentation */
#include <iomanip>

using namespace std;

struct personne {
  string nom ;
  int SS[15] ;
};

struct population {
  personne *pers;
  int N;
};
  
int compter(population hab, int sexe) {
  int i, cpt=0;
  for (i=0;i<hab.N;i++) {
    if (hab.pers[i].SS[0] == sexe)  cpt = cpt+1;
  }
  return cpt ;
}

int partageSexe(population *hab) {
  int F=compter(*hab, 2);
  //parcourir le sous-tableaux des femmes
  int fem=0;
  int hom=hab->N-1;
  while (fem < F && hom>=F) {
    while (hab->pers[fem].SS[0]==2) fem++;
    while (hab->pers[hom].SS[0]==1) hom--;
    //ici on est sur une personne cote femme qui est un homme
    //et une personne cote homme qui est une femme
    // => on les echange
    personne tmp = hab->pers[fem];
    hab->pers[fem] = hab->pers[hom];
    hab->pers[hom] = tmp;
    //puis on continue sur la personne suivante
    fem++;
    hom--;
  }
  return F;
}

int codeLieu(int SS[15])
{
  return SS[5]*10000+SS[6]*1000+SS[7]*100+SS[8]*10+SS[9];
}

void triLieuSexe(population *hab, int deb, int fin) {
  int ind, position, i;
  personne tmp;
  for (ind=fin; ind>=deb+1;ind--) { 
    position = deb; 
    for (i=deb+1;i<=ind;i++)  { 
      if (codeLieu(hab->pers[position].SS) < codeLieu(hab->pers[i].SS)) { //tri sur les departements
	position = i; //E5
      }
    }
    if (position != ind)  { //E6
      tmp = hab->pers[position]; //E7
      hab->pers[position] = hab->pers[ind]; //E8
      hab->pers[ind] = tmp; //E9
    }
  }
}

void triLieu(population *hab, int nbF)
{
  triLieuSexe(hab, 0, nbF-1);
  triLieuSexe(hab, nbF, hab->N-1);
}

int codeAge( int SS[15])
{
  return SS[1]*10+SS[2] + 100*(19+((99-SS[1]*10-SS[2])/79));
}

void triAgeSexe(population *hab, int deb, int fin) {
  int  indice_elt, position;
  personne elt;
  for (indice_elt=deb+1;indice_elt<fin;indice_elt++) { 
    elt = hab->pers[indice_elt];
    position = indice_elt;
    while (position > deb && codeAge(hab->pers[position-1].SS) < codeAge(elt.SS))  { 
      hab->pers[position] = hab->pers[position-1]; 
      position=position-1;
    }
    hab->pers[position] = elt;
  }
}
void triAge(population *hab, int nbF)
{
  triAgeSexe(hab, 0, nbF);
  triAgeSexe(hab, nbF, hab->N);
}

string rechercheDichoNom(population *hab, int sexe, int annee, int deb, int fin)
{
  if (deb<=fin) {
    int milieu = (deb+fin)/2;
    //cout << milieu << " " << hab->pers[milieu].SS[0] << " " << codeAge(hab->pers[milieu].SS) << ">> " << sexe << " " << annee << endl;
    if (hab->pers[milieu].SS[0] == sexe) {
      if (codeAge(hab->pers[milieu].SS)==annee) return hab->pers[milieu].nom;
      if (codeAge(hab->pers[milieu].SS)<annee) return rechercheDichoNom(hab, sexe, annee, deb, milieu-1);
      return rechercheDichoNom(hab, sexe, annee, milieu+1, fin);
    }
    if (hab->pers[milieu].SS[0] < sexe) 
      return rechercheDichoNom(hab, sexe, annee, deb, milieu-1);
    return rechercheDichoNom(hab, sexe, annee, milieu+1, fin);
  }
  return "";
}

void initSS(int tab[15]) {
  tab[0] = 1+rand()%2;
  for (int i=1; i<15; i++) tab[i]=rand()%10;
  int mois = rand()%12+1;
  tab[3] = mois/10;
  tab[4] = mois%10;
}

void afficherSS(int tab[15]) {
  for (int i=0; i<15; i++) cout << tab[i];
}

string initString(int nb)
{
  string s;
  for (int i=0;i<nb;i++) {
    char c = 'a';
    c = (char) ((int)c+rand()%26);
    s = s+c;
  }
  return s;
}

void afficherHab(population P)
{
  cout << "il y a : " << P.N << "personnes" << endl;
  for (int i=0;i<P.N;i++) {
    cout << P.pers[i].nom << "\t";
    afficherSS(P.pers[i].SS);
    cout << endl;
  }
}

/* main */
int main(int argc, char **argv)
{

  population Habitants;
  
  ifstream fic(argv[1]);
  fic >> Habitants.N;
  Habitants.pers = new personne[Habitants.N];
  //cout << endl << "//////////////////////" << endl;
  int nb_Pers = 0;
  if (fic) {
    while (!fic.eof())//tant qu'on acquière des lignes...
      {
	fic >> Habitants.pers[nb_Pers].nom;
	//cout << Habitants.pers[nb_Pers].nom << "\t";
	for (int j=0;j<15;j++) {
	  fic >>  Habitants.pers[nb_Pers].SS[j];
	  //cout << Habitants.pers[nb_Pers].SS[j] << " ";
	}
	nb_Pers++;
	//cout <<nb_Pers<<endl; 
      }
    //Habitants.N = nb_Pers-1;
    cout << "Hab : " << Habitants.N << " et nb pers : " << nb_Pers-1<<endl;
    //cout << "nbPers " << Habitants.N << endl;
  }
  else {
    cout << "ERREUR : impossible d'ouvrir le fichier" << endl;
  }
  
  cout << endl << "//////AFFICHAGE////////" << endl;

  //population TEMP = Habitants;
  int NbFemmes = partageSexe(&Habitants);
  cout << "Nb femmes " << NbFemmes << endl;
  //afficherHab(Habitants);

  population TEMP = Habitants;
  triLieu(&Habitants, NbFemmes);
  //afficherHab(Habitants);

   Habitants = TEMP;
   triAge(&Habitants, NbFemmes);
   afficherHab(Habitants);

   int annee, sexe;
   cout << "Annee desiree <aaaa> : "; cin >> annee;
   cout << "Sexe de la personne <1:homme ; 2:femme> : "; cin >> sexe;

   string pimprenelle = rechercheDichoNom(&Habitants, sexe, annee, 0, Habitants.N-1);
   if (pimprenelle!="") cout << "on a trouve une personne du nom de : " << pimprenelle << endl;
   else {
     cout << "on n'a trouve personne de sexe ";
     if (sexe==1) cout << "masculin ne en ";
     else cout << "feminin nee en ";
     cout << annee << endl;
     }
  return 0;
}
