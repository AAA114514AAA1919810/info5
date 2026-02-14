#include <iostream>
#include <string>
using namespace std;

const int NB = 128 ;
struct PileNombres
{
int nombres [NB ] ;
int sommetPile ; /* i n d i c e p r o c h a i n é l é m e n t */
} ;

const int NBTERM = 256 ;
struct FileTermes
{
string termes [NBTERM] ;
int finDeFile ; /* i n d i c e p r o c h a i n é l é m e n t */
} ;

/* Les o p é r a t e u r s v a l i d e s */
const string MULT = "*" ;
const string DIV = "/" ;
const string MOD = "%" ;
const string ADD = "+" ;
const string SOUS = "-" ;
const int NBOPER = 5 ;
string Operateurs[NBOPER] = {MULT, DIV ,ADD, SOUS,MOD} ;


void viderPile(PileNombres &p) {
    p.sommetPile = 0;
}

bool empiler(PileNombres &p, int val) {
    if (p.sommetPile >= NB) return false;
    p.nombres[p.sommetPile++] = val;
    return true;
}

int depiler(PileNombres &p) {
    if (p.sommetPile == 0) return -1;
    return p.nombres[--p.sommetPile];
}

bool estPileVide(const PileNombres &p) {
    return p.sommetPile == 0;
}

bool estPilePleine(const PileNombres &p) {
    return p.sommetPile >= NB;
}

void viderFile(FileTermes &f) {
    f.finDeFile = -1;
}

bool enqueue(FileTermes &f, const string &terme) {
    if (f.finDeFile >= NBTERM - 1) return false;
    f.termes[++f.finDeFile] = terme;
    return true;
}

string dequeue(FileTermes &f) {
    if (f.finDeFile < 0) return "";
    string t = f.termes[0];

    for (int i = 0; i < f.finDeFile; i++)
        f.termes[i] = f.termes[i + 1];

    f.finDeFile--;
    return t;
}

bool estFileVide(const FileTermes &f) {
    return f.finDeFile < 0;
}

bool estFilePleine(const FileTermes &f) {
    return f.finDeFile >= NBTERM - 1;
}

void saisirChaine(string &ch) {
    cout << "Veuillez saisir une expression en notation polonaise inversee : ";
    getline(cin, ch, '\n');
}

void afficherChaine(const string &ch) {
    cout << "\"" << ch << "\"" << endl;
}

string sousChaine(const string &ch, int pos, bool aGauche) {
    if (pos <= 0 || ch.length() == 0) return ch;

    if (aGauche) {
        string reste = "";
        for (int i = 1; i < ch.length(); i++)
            reste = reste + ch[i];
        return sousChaine(reste, pos - 1, true);
    } else {

        string reste = "";
        for (int i = 0; i < ch.length() - 1; i++)
            reste = reste + ch[i];
        return sousChaine(reste, pos - 1, false);
    }
}

int compterEspaceGauche(const string &ch) {
    if (ch.length() == 0) return 0;
    if (ch[0] != ' ') return 0;

    string reste = sousChaine(ch, 1, true);
    return 1 + compterEspaceGauche(reste);
}

int compterEspaceDroite(const string &ch) {

    if (ch.length() == 0) return 0;
    if (ch[ch.length() - 1] != ' ') return 0;

    string reste = sousChaine(ch, 1, false);
    return 1 + compterEspaceDroite(reste);
}

string ltrim(const string &ch) {
    int nbEspaces = compterEspaceGauche(ch);
    return sousChaine(ch, nbEspaces, true);
}

string rtrim(const string &ch) {
    int nbEspaces = compterEspaceDroite(ch);
    return sousChaine(ch, nbEspaces, false);
}

string trim(const string &ch) {
    return rtrim(ltrim(ch));
}

string prochainTerme(const string &ch) {
    if (ch.length() == 0) return "";

    if (ch[0] == ' ') return "";

    return ch[0] + prochainTerme(sousChaine(ch, 1, true));
}

string termesRestants(const string &ch) {
    string s = ltrim(ch);

    if (s.length() == 0) return "";

    string terme = prochainTerme(s);

    string reste = sousChaine(s, terme.length(), true);
    reste = ltrim(reste);

    return reste;
}

bool aUnTerme(const string &ch) {
    string s = ltrim(ch);

    if (s.length() == 0) return false;

    return true;
}

void construireFileTermes(string ch, FileTermes &a) {
    ch = trim(ch);
    if (!aUnTerme(ch)) return;
    string terme = prochainTerme(ch);
    enqueue(a, terme);
    string reste = termesRestants(ch);
    construireFileTermes(reste, a);
}   

void afficherFileTermes(const FileTermes &a) {
    cout << "NPI : ";
    for (int i = 0; i <= a.finDeFile; i++) {
        cout << a.termes[i];
        if (i < a.finDeFile) cout << " ";
    }
    cout << endl;
}




int main() {
    string expr;
    FileTermes file;
    file.finDeFile = -1;

    saisirChaine(expr);
    expr = trim(expr);

    construireFileTermes(expr, file);

    afficherFileTermes(file);

    return 0;
}