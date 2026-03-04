#include <iostream>
#include <cmath>
#include <cfloat>
using namespace std;

struct Maillon;

struct Point{
    float x, y;
};

struct Segment{
    Point deb, fin;
};

struct Maillon{
    Segment seg;
    Maillon *svt;
};

// Partie 1

void affichePoint(Point p){
    cout << p.x << ", " << p.y ;
}

void afficheSegment(Segment s){
    affichePoint(s.deb);
    cout << "; ";
    affichePoint(s.fin);
    cout << endl;
}


float calculeLongueur(Segment s){
    float n = sqrtf( (s.deb.x - s.fin.x)*(s.deb.x - s.fin.x) +  (s.deb.y - s.fin.y)*(s.deb.y - s.fin.y) );
    return n;
}

float calculeAngle(Segment s){
    float angle;
    if( (s.deb.x - s.fin.x) < FLT_EPSILON){
        if(s.fin.y > s.deb.y){
            angle = M_PI/2;
        }
        else
            angle = -M_PI/2;
    }
    else{
        if(s.fin.x > s.deb.x){
            angle = atan((s.fin.y - s.deb.y)/(s.fin.x-s.deb.x));
        }
        else
            angle = atan((s.fin.y - s.deb.y)/(s.fin.x-s.deb.x)) + M_PI;
    }
    return angle;
}

Point avancePoint(Point p, float dist, float angle){
    Point p2;
    p2.x = p.x + dist * cos(angle);
    p2.y = p.y + dist * sin(angle);
    return p2;
}

// Partie 2

void ajouteSegmentListe( Segment s, Maillon* *M){
    Maillon* M2 = new Maillon;
    M2->seg = s;
    M2->svt = *M;
    *M = M2;
}

void afficheListe(Maillon* M){
    afficheSegment(M->seg);
    if(M->svt != NULL){
        return afficheListe(M->svt);
    }
}

// Partie 3

void initialiseTriangleKoch(Maillon* Ma, float L){
    Point O;
    O.x = 0;
    O.y = 0;
    Point M = avancePoint(O, 3, M_PI/3);
    Segment OM;
    OM.deb = O;
    OM.fin = M;
    Point N = avancePoint(O, 3, 2*M_PI/3);
    Segment NO;
    NO.deb = N;
    NO.fin = O;
    Segment MN;
    MN.deb = M;
    MN.fin = N;
    ajouteSegmentListe(OM, &Ma);
    ajouteSegmentListe(MN, &Ma);
    ajouteSegmentListe(NO, &Ma);
}


int main(){
    Maillon *p;
    calculeKoch(&p,5);
    afficheListe(p);
    return 0;
}

