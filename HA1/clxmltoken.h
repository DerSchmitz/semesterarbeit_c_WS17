#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

class ClxmlToken{
    public:
    ClxmlToken();
    int ladeXML(ifstream &xmldatei);
   // char *getTagname() { return "sss"; }


    void printXMLToken(int ebene);


    // GETTER
    char *name() { return tokenTagname; }
    char *inhalt() { return tokenTaginhalt; }
  //  char *attName(int id) { return attName[id]; }
  //  char *attValue(int id) { return attValue[id]; }

    private:
    int anzahlTagnamen;
    char tokenTagname[100];
    char *tokenTaginhalt;
    int anzahlAtt;
    char *attName[10];
    char *attValue[10];

    // erschaffe eigenes Objekt für Kindelemente - stellt Beziehung zwischen product und model/descr/price her
    ClxmlToken *xmltokenChild;
    // erschaffe eigenes Objekt für Geschwisterlemente - stellt Beziehung zu dem nächstgelegenen Geschwisterelement her
    ClxmlToken *xmltokenSibling;

    void cleanToken();
    int fillToken(int mode);
};
