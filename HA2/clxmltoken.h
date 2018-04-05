#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "cltxttoken.h"

using namespace std;

class ClxmlToken{
    public:
    // funktion for initialisation of ClxmlToken-objects
    ClxmlToken();

    // parsing-methode for xml-file
    int ladeXML(ifstream &xmldatei);

    // print-methode to print out XML-data AND TXT-data in one XML-document
    void printXMLToken(CltxtToken &txttoken, ofstream &fout, bool &txtprinted);

    // GETTER
    char *getname() { return tokenTagname; }
    char *getinhalt() { return tokenTaginhalt; }
    char *getattName(int id) { return attName[id]; }
    char *getattValue(int id) { return attValue[id]; }
    int getanzahlAtt(void) { return anzahlAtt; }

    private:
    // variables to save XML-Data
    int anzahlTagnamen;
    char tokenTagname[100];
    char *tokenTaginhalt;
    int anzahlAtt;
    char *attName[10];
    char *attValue[10];

    // pointer to child-object - we use this to connect the father elements (e.g. product) to child elements (e.g. type/model/descr/price)
    ClxmlToken *xmltokenChild;
    // pointer to sibling-object - we use this to connect data from elements that are next to each other
    ClxmlToken *xmltokenSibling;

    // we clean objects after creation to make sure they are not filled yet
    void cleanToken();

    // we fill Objects to avoid bugs with printing
    int fillToken(int mode);
};





