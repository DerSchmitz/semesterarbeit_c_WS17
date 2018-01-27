#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include "clxmltoken.h"
#include "cltxttoken.h"

void ClxmlToken::ladeXML(ifstream &xmldatei) {

    cout << endl << "Hello, Iam the ladeXML MEthode!" << endl;

        char zeichen;
        char puffer[100];
        int zaehler;
        enum zustand { zwischenTags, inNamen, erwarteAttributNamen,
                        erwarteAttributWert, verarbeiteAttributWert, istEndTag, erwarteTaginhalt} ;
        enum zustand zustand;

        cout << endl << endl;
        cout << "Parsing der XML Datei (listProducts.xml)" << endl;
        cout << "------------------------------"<< endl;

        for (zaehler=0, zustand=zwischenTags;;) {

            xmldatei.get(zeichen);
            if (xmldatei.eof()) break;

            switch(zeichen) {

                case '<':
                xmldatei.get(zeichen);
                if (zeichen=='/')
                   {
                    zustand=istEndTag;
                        if (zaehler!=0){
                            puffer[zaehler] = '\0';
                            cout << "Taginhalt: " << puffer << endl;
                        }
                   }
                else {
                   xmldatei.putback(zeichen);
                   zustand=inNamen;
                   puffer[zaehler] = '\0';
                   }
                    zaehler=0;
                    break;

                case '>':
                if (zustand == inNamen) {
                    zustand = erwarteTaginhalt;
                    puffer[zaehler] = '\0';
                    cout << endl << "Tag: " << puffer << endl;
                    zaehler=0;
                }else {
                puffer[zaehler] = '\0';
                zaehler=0;
                zustand=zwischenTags;
                }

                    break;

                case ' ':
                    if (zustand == inNamen) {

                        zustand = erwarteAttributNamen;
                        puffer[zaehler] = '\0';
                        cout << endl << "Tag: " << puffer << endl;
                        zaehler=0;

                    } else if (zustand == verarbeiteAttributWert or zustand==erwarteTaginhalt) {

                        puffer[zaehler] = zeichen;
                        zaehler++;
                    }
                    break;

                case '=':
                    if (zustand == erwarteAttributNamen) {

                        zustand = erwarteAttributWert;
                        puffer[zaehler] = '\0';
                        cout << "Name des Attributs: " << puffer << endl;
                        zaehler=0;
                    } else if (zustand == verarbeiteAttributWert) {

                        puffer[zaehler] = zeichen;
                        zaehler++;
                    } else cout << "Fehlerhaftes Zeichen! '='" << endl;
                    break;


                case '\'':
                case '"':
                    if (zustand == erwarteAttributWert)  {
                        zustand = verarbeiteAttributWert;
                        zaehler = 0;
                    } else if (zustand == verarbeiteAttributWert) {
                        zustand = erwarteAttributNamen;
                        puffer[zaehler] = '\0';
                        cout << "Wert des Attributs: " << puffer << endl;
                        zaehler=0;
                    } else cout << "Fehlerhaftes Zeichen! '\"'" << endl;
                    break;

                default:
                if (zustand!=zwischenTags) {
                    puffer[zaehler] = zeichen;
                     zaehler++;
                }

                    break;
            } // Ende switch
    }



}
