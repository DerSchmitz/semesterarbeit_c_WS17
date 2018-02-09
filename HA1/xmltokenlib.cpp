#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include "clxmltoken.h"
#include "cltxttoken.h"


// definiere Regeln für das Erschaffen eines neuen Objekts der Klasse ClxmlToken
ClxmlToken::ClxmlToken()
{
*tokenTagname='\0'; // reset tokentagname
xmltokenChild=NULL; // reset
xmltokenSibling=NULL;
tokenTaginhalt=new char[1];
*tokenTaginhalt='\0';
}








int ClxmlToken::ladeXML(ifstream &xmldatei) {

    cout << endl << "Hallo, Ich bin die ladeXML Methode!" << endl;

        char zeichen;
        char puffer[100];
        int zaehler;
        int zeichentest =0;
        // Kind-Objekt - Hilfsobjekt?
        ClxmlToken *child;
        // KindObjekt

        enum zustand { zwischenTags, inNamen, erwarteAttributNamen,
                        erwarteAttributWert, verarbeiteAttributWert, istEndTag, erwarteTaginhalt} ;
        enum zustand zustand;

       cleanToken();

        cout << endl << endl;
        cout << "Parsing der XML Datei (listProducts.xml)" << endl;
        cout << "------------------------------"<< endl;

        for (zaehler=0, zustand=zwischenTags, anzahlAtt=0;;) {

            xmldatei.get(zeichen);
            if (xmldatei.eof()) {

                if (*tokenTagname == '\0' && tokenTaginhalt == NULL && xmltokenChild == NULL )  return fillToken(0);

                return fillToken(1);
               // break;
            }

            switch(zeichen) {

                case '<':

                xmldatei.get(zeichen);
                if (zeichen=='/')
                   {
                    zustand=istEndTag;
                        if (zaehler!=0){

                            puffer[zaehler]='\0';
                            tokenTaginhalt = new char[zaehler+1];
                            strcpy(tokenTaginhalt,puffer);
                            cout << "Taginhalt: " << tokenTaginhalt << endl;
                        }
                   }
                else {
                  // WICHTIG - HIER SIND WIR IM START TAG!
                    /* falls tokenTagname schon gefüllt ist ERSCHAFFE KIND-OBJEKT UND jage es erneut durch dieselbe Methode*/
                    xmldatei.putback(zeichen);
                    //cout << "*tokenTagname " << *tokenTagname << endl;
                   if (*tokenTagname!='\0')
                      {
                      xmldatei.putback('<');
                      //cout << "tokenTagname " << tokenTagname << " " << xmltokenChild << endl;
                  if (xmltokenChild==NULL)
                     {


                         xmltokenChild=new ClxmlToken; // cout << "erschaffe Kind" << endl;
                         xmltokenChild->ladeXML(xmldatei);
                      }else{ // IF ELSE kein xmlTokenchild existiert

                            // iteriere alle tokenSiblings durch!!!
                            for (child=xmltokenChild;;child=child->xmltokenSibling) { // durch iterative Bespielung des hilfsobjekts child werden objekte iteriert

                                if (child->xmltokenSibling==NULL)
                                     { //cout << "erschaffe Sibling" << endl;
                                     child->xmltokenSibling=new ClxmlToken;
                                     child->xmltokenSibling->ladeXML(xmldatei);
                                     break;
                                     }
                                }
                            }
                      }

                   // wenn wir im Start-tag sind, tokentagname gefüllt ist/nicht gefüllt ist
                                                   // es aber noch kein TOKENCHILD gibt
                   //xmldatei.putback(zeichen); // wird nicht gebraucht, da vorher schon behandelt? - ACTHUNG hier liegt evtl. Fehler vor!!!
                   zustand=inNamen;
                   //puffer[zaehler] = '\0';
                   }
                    zaehler=0;
                    break;

                case '>':
                if (zustand==istEndTag)  return fillToken(1);
                 puffer[zaehler] = '\0';
                if (zustand == inNamen) {
                   // ansonsten fahre fort wie gehabt
                    zustand = erwarteTaginhalt;

                    // puffer nicht einfach ausgeben
                    // cout << endl << "Tag: " << puffer << endl;
                    // stattdessen zwischenspeichern - ToDo
                     strcpy(tokenTagname,puffer);
                     cout << endl << "Tag: " << tokenTagname << " und zustand ist " << zustand <<  endl;

                    /*
                    *tokenTagname = new char[zaehler+1];
                    strcpy(tokenTagname[anzahlTagnamen],puffer);
                    cout << endl << "Tag: " << tokenTagname[anzahlTagnamen] << endl;
                    anzahlTagnamen++;*/

                     //cout << endl << "tokenTagname[" << anzahlTagnamen << "]: "<< tokenTagname[anzahlTagnamen] << endl;


                    zaehler=0;
                }else {
                puffer[zaehler] = '\0';
                zaehler=0;
                zustand=zwischenTags;
                }

                    break;

                case ' ':
                if (zustand==istEndTag)  return fillToken(1);
                    if (zustand == inNamen)  {

                        zustand = erwarteAttributNamen;
                        puffer[zaehler] = '\0';
                        //cout << endl << "Tag: " << puffer << endl;
                        if (zaehler!=0) {
                            strcpy(tokenTagname,puffer);
                            cout << endl << "Tag: " << tokenTagname << " und zustand ist " << zustand <<  endl;
                        }else {
                            zustand=istEndTag;
                        }

                        zaehler=0;

                    } else if (zustand == verarbeiteAttributWert or zustand==erwarteTaginhalt) {

                        puffer[zaehler] = zeichen;
                        zaehler++;
                    }
                    break;

                case '=':
                    if (zustand == erwarteAttributNamen) {
/*
                        zustand = erwarteAttributWert;
                        puffer[zaehler] = '\0';
                        cout << "Name des Attributs: " << puffer << endl;
                        zaehler=0; */

                        zustand = erwarteAttributWert;
                        puffer[zaehler] = '\0';
                        attName[anzahlAtt] = new char[zaehler+1];
                        strcpy(attName[anzahlAtt],puffer);
                        zaehler=0;
                        cout << "Name des Attributs: " << attName[anzahlAtt] << endl;



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
                       /* zustand = erwarteAttributNamen;
                        puffer[zaehler] = '\0';
                        cout << "Wert des Attributs: " << puffer << endl;
                        zaehler=0;*/



                    zustand = erwarteAttributNamen;
                    puffer[zaehler] = '\0';
                    attValue[anzahlAtt] = new char[zaehler+1];
                    strcpy(attValue[anzahlAtt],puffer);
                    zaehler=0;
                    cout << "Wert des Attributs: " << attValue[anzahlAtt] << endl;
                    anzahlAtt++; // zähle herauf, falls mehr als ein attribut existiert


                    } else cout << "Fehlerhaftes Zeichen! '\"'" << endl;
                    break;
                case '\n':
                zustand=zwischenTags;
                   break;
                default:
                if (zustand!=zwischenTags) {

                    if(zeichen=='\n') {
                     //    cout << "LINEBREAK" << " und zustand ist  "<<  zustand<< endl;

                    }else {

                     //  cout << zeichen <<" und zustand ist  "<<  zustand<< endl;
                    }


                     puffer[zaehler] = zeichen;
                     zaehler++;
                }

                    break;
            } // Ende switch
    }

}


void ClxmlToken::printXMLToken(
int                       ebene)
{
ClxmlToken *child;


        //druckeTokenEbene(ebene);
        cout << "TOKEN:            " << name() << " - " << inhalt() << endl;

 cout << "anzahlAtt " << anzahlAtt << endl;

        if (anzahlAtt > 0)
           {
           for (int i=0;i<anzahlAtt;i++)
               {
               //druckeTokenEbene(ebene);
               cout << "Attribut " << attName[i] << " hat den Wert "
                    << attValue[i] << endl;
               }
           }

     /*   if (child->xmltokenChild==NULL) break; // beende Schleife bei child==NULL
            child = child->xmltokenChild; */

        if (xmltokenChild!=NULL) xmltokenChild->printXMLToken(ebene+1);
        if (xmltokenSibling!=NULL) xmltokenSibling->printXMLToken(ebene);



}



void ClxmlToken::cleanToken(void)
{
*tokenTagname='\0';
if (xmltokenChild!=NULL)
   {
   delete xmltokenChild;
   xmltokenChild=NULL;
   }
if (tokenTaginhalt!=NULL)
   {
   delete tokenTaginhalt;
   tokenTaginhalt=NULL;
   }
}

int ClxmlToken::fillToken(
int                    mode)
{
    // wir brauchen fillToken um die Print-Methode nicht zu blockieren, wegen leeren strings

if (*tokenTagname=='\0')
   strcpy(tokenTagname,"Unbekanntes Element");
if (tokenTaginhalt==NULL)
   {
   tokenTaginhalt=new char[1];
   *tokenTaginhalt='\0';
   }

return mode;
}

