#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include "clxmltoken.h"
#include "cltxttoken.h"


void CltxtToken::ladeTXT(ifstream &txtdatei) {

    cout << endl << "Hallo, ich bin die ladeTXT-Methode" << endl;

    char zeichen;
    char puffer[100];
    int counter;
    enum zustandsmeldung {
        nachID, nachZweitemSpace,zwischendenZeilen    };

    zustandsmeldung zustandsmeldung;
    //reset enum
    zustandsmeldung = zwischendenZeilen;

    cout << endl << endl;
    cout << "Parsing der TXT Datei (products.txt)" << endl;
    cout << "------------------------------"<< endl;
    for (counter=0, zustandsmeldung=zwischendenZeilen, anzahlAtt=0;;){
    txtdatei.get(zeichen);
    if (txtdatei.eof()) return; // ERGÄNZE ANDERE OBJEKTE.EOF !!!!


        switch(zeichen){

        case ' ':
            // was passiert bei space
            // wir bearbeiten gerade eine xml:id
        if (zustandsmeldung==zwischendenZeilen){

            puffer[counter] = '\0';
            attValueID[anzahlAtt] = new char[counter+1];
            strcpy(attValueID[anzahlAtt],puffer);
            counter=0;

            zustandsmeldung=nachID;
        }
        else if (zustandsmeldung==nachID)  {
                puffer[counter] = '\0';
                attValueModel[anzahlAtt] = new char[counter+1];
                strcpy(attValueModel[anzahlAtt],puffer);
                counter=0;

            zustandsmeldung=nachZweitemSpace;
        }
        else  {
           // fülle das array mit den datenwerten auf und zähle einen weiter
           puffer[counter]=zeichen;
           counter++;
        }
        break;

        case '\n':
        // ich erreiche das ende einerZeile - der nächste Punkt dient also wieder der Abgrenzung zwischen Attributwerten

        // PREIS AUSLESEN
        puffer[counter] = '\0';
        attValuePrice[anzahlAtt] = new char[counter+1];
        strcpy(attValuePrice[anzahlAtt],puffer);
        counter=0;
        //Wichtig!!! Zähle attribut aanschließnd langsam herauf - ABER NUR EINMAL PRO WIEDERHOLENDE LINE
        anzahlAtt++;

        // reset zustand
        zustandsmeldung=zwischendenZeilen;
        break;

        default:
        // was passiert normalerweise: fülle das array mit den datenwerten auf und zähle einen weiter
        puffer[counter]=zeichen;
        counter++;
        break;
        }
    }
}
