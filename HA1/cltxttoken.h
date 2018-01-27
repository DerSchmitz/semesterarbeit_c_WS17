#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

class CltxtToken{
    private:

    int anzahlAtt;
    char *attValueID[100];
    char *attValueModel[100];
    char *attValuePrice[100];



    public:
    void ladeTXT(ifstream &txtdatei);

    // getter-methode holt attributwwerte je nach ID (Auslese-Iteration)
                    // counter wird in variable id gespeichert und dann innerhaalb der funktion weiterinterpretiert
    char *getattValueID(int id) {return attValueID[id];}
    char *getattValueModel(int id) {return attValueModel[id];}
    char *getattValuePrice(int id) {return attValuePrice[id];}
    // get Anzahl variable
    int  getAnzahlAtt() {return anzahlAtt;}

};
