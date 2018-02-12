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

    // getter-methodes gets attribute-values depending on ID (Reading-Iteration)
                    // anzahlAtt-counter is saved in parameter "id" and then delivered to the get-methode as a parameter
    char *getattValueID(int id) {return attValueID[id];}
    char *getattValueModel(int id) {return attValueModel[id];}
    char *getattValuePrice(int id) {return attValuePrice[id];}
    // get AnzahlAtt variable
    int  getAnzahlAtt() {return anzahlAtt;}






};

