#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include "clxmltoken.h"

void CltxtToken::ladeTXT(ifstream &txtdatei) {

    //cout << endl << "Hallo, ich bin die ladeTXT-Methode" << endl;

    char zeichen;
    char puffer[100];
    int counter;
    enum zustandsmeldung {
        nachID, nachZweitemSpace , zwischendenZeilen    };

    zustandsmeldung zustandsmeldung;
    //reset enum
    zustandsmeldung = zwischendenZeilen;

    cout << endl << endl;
    cout << "Parsing of the TXT-file" << endl;
    cout << "------------------------------"<< endl;
    for (counter=0, zustandsmeldung=zwischendenZeilen, anzahlAtt=0;;){
    txtdatei.get(zeichen);
    if (txtdatei.eof()) return; // andere objekte abprüfen?


        switch(zeichen){

        case ' ':
            // what happens if we read space?
            // we are currently reading a xml:id
        if (zustandsmeldung==zwischendenZeilen){

            puffer[counter] = '\0';
            attValueID[anzahlAtt] = new char[counter+1];
            strcpy(attValueID[anzahlAtt],puffer);
            counter=0;

            // set enum to signify that we already read ID
            zustandsmeldung=nachID;
        }
        else if (zustandsmeldung==nachID)  {

                puffer[counter] = '\0';
                attPlace[anzahlAtt] = new char[counter+1];
                strcpy(attPlace[anzahlAtt],puffer);
                counter=0;
            // set enum to signify that we already read the type-information
            zustandsmeldung=nachZweitemSpace;
        }
        else  {
           // fill the array with the datavalues and slowly count up
           puffer[counter]=zeichen;
           counter++;
        }
        break;

        case '\n':
        // we come to the end of a line - we can read the priceValue
        puffer[counter] = '\0';
        attPackagecontent[anzahlAtt] = new char[counter+1];
        strcpy(attPackagecontent[anzahlAtt],puffer);
        counter=0;
        //Important!!! We count the attribute-amount slowly up - ONLY ONE TIME FOR EVERY LINE (and therefore every seperate product)
        anzahlAtt++;

        // reset enum
        zustandsmeldung=zwischendenZeilen;
        break;

        default:
        // what happens on default?: fill the array with the datavalues and slowly count up
        puffer[counter]=zeichen;
        counter++;
        break;
        }
    }

}
