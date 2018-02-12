#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include "clxmltoken.h"
#include "print-check.h"

// definiere Regeln für das Erschaffen eines neuen Objekts der Klasse ClxmlToken
ClxmlToken::ClxmlToken()
{
*tokenTagname='\0'; // reset tokentagname
xmltokenChild=NULL; // reset child
xmltokenSibling=NULL;// reset sibling
tokenTaginhalt=new char[1];// reset taginhalt
*tokenTaginhalt='\0';
}

int ClxmlToken::ladeXML(ifstream &xmldatei) {

    //cout << endl << "Hallo, Ich bin die ladeXML Methode!" << endl;

        char zeichen;
        char puffer[100];
        int zaehler;
        // Kind-Objekt - Hilfsobjekt?
        ClxmlToken *child;


        enum zustand { zwischenTags, inNamen, erwarteAttributNamen,
                        erwarteAttributWert, verarbeiteAttributWert, istEndTag, erwarteTaginhalt} ;
        enum zustand zustand;

       cleanToken();


        cout << endl << endl;
        cout << "Parsing of the XML-Datafile " << endl;
        cout << "------------------------------"<< endl;

        // start for-loop
        for (zaehler=0, zustand=zwischenTags, anzahlAtt=0;;) {

            xmldatei.get(zeichen);

            // return function if file has come to an end
            if (xmldatei.eof()) {

                if (*tokenTagname == '\0' && tokenTaginhalt == NULL && xmltokenChild == NULL )  return fillToken(0);

                return fillToken(1);
               // break;
            }

            // start switch-case for parsing character by character
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
                            //cout << "Taginhalt: " << tokenTaginhalt << endl;
                        }
                   }
                else {
                  // IMPORTANT - HERE IS THE START TAG!
                    /* if tokenTagname is already filled, create new child-object and run it once more through the same methode */
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
                      }else{ // IF ELSE no xmlTokenchild exists

                            // iterate all possible tokenSiblings
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
                   // if we are in start-tag and tokentagname ist either filled or not filled, but there is NO Child yet
                   zustand=inNamen; // set enum to expect tokentagname
                   }
                    zaehler=0;
                    break;

                case '>':
                if (zustand==istEndTag)  return fillToken(1);
                 puffer[zaehler] = '\0';
                if (zustand == inNamen) {

                    // save tagname, expect taginhalt and reset counter
                    zustand = erwarteTaginhalt;
                    strcpy(tokenTagname,puffer);
                    // cout << endl << "Tag: " << tokenTagname << " and zustand is " << zustand <<  endl;
                    zaehler=0;
                }else {
                puffer[zaehler] = '\0';
                zaehler=0;
                zustand=erwarteTaginhalt;
                }
                    break;

                case ' ':
                if (zustand==istEndTag)  return fillToken(1);
                    if (zustand == inNamen)  {

                        zustand = erwarteAttributNamen;
                        puffer[zaehler] = '\0';
                        if (zaehler!=0) {
                            strcpy(tokenTagname,puffer);
                            //cout << endl << "Tag: " << tokenTagname << " and zustand is " << zustand <<  endl;
                        }else {
                            // we expect and endtag
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

                        zustand = erwarteAttributWert;
                        puffer[zaehler] = '\0';
                        attName[anzahlAtt] = new char[zaehler+1];
                        strcpy(attName[anzahlAtt],puffer);
                        zaehler=0;
                        //cout << "Name des Attributs: " << attName[anzahlAtt] << endl;

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
                    attValue[anzahlAtt] = new char[zaehler+1];
                    strcpy(attValue[anzahlAtt],puffer);
                    zaehler=0;
                    //cout << "Wert des Attributs: " << attValue[anzahlAtt] << endl;
                    anzahlAtt++; // count up, if there is more than one attribute

                    } else cout << "Fehlerhaftes Zeichen! '\"'" << endl;
                    break;
                case '\n':
                zustand=zwischenTags;
                   break;
                default:
                if (zustand!=zwischenTags) {
                    //cout << zeichen <<  " and the zustand is "<< zustand<<endl;
                     puffer[zaehler] = zeichen;
                     zaehler++;
                }
                    break;
            } // End switch
    }
}



void ClxmlToken::printXMLToken(CltxtToken &txttoken, ofstream &fout, bool &txtprinted)
{
// Form XML-Code

    // open tag
        fout << "<" << getname() ;
             // make room for attributes
            if (getanzahlAtt() > 0)
               {
               for (int i=0;i<getanzahlAtt();i++)
                   {
                   fout << " " << getattName(i) << "=" << '"' << getattValue(i) << '"';
                   }
               }
                    // close tag, insert Taginhalt
                    fout << ">" << getinhalt();


        // print all children completely
        if (xmltokenChild!=NULL) xmltokenChild->printXMLToken(txttoken, fout, txtprinted);

        // if we are before the closing of the last child-element (product-element)

        if (xmltokenSibling==NULL and xmltokenChild!=NULL ) {
            // close the last-product element from xml
            fout << "</" << getname() << ">" <<  endl;

            // then append the TXT-elements if not already printed
            if (txtprinted==false) {

                // for every TXT-record
                for (int i=0;i<txttoken.getAnzahlAtt();i++){

                    // print out txt-data in xml-form
                    fout << "<product xml:id=\""<<txttoken.getattValueID(i) << "\">" << endl;
                    fout << "<type>"<< txttoken.getattValueModel(i) << "</type>" << endl;
                    fout << "<price>"<< txttoken.getattValuePrice(i) << "</price>" << endl;
                    fout << "</product>" << endl;

                }
                txtprinted=true; // txt sucessfully printed
            }

        } else {
              // if its not the last child-element close the tag without printing txt
          fout << "</" << getname() << ">" <<  endl;
        }

         // after that print sibling elements if existing
        if (xmltokenSibling!=NULL) xmltokenSibling->printXMLToken(txttoken, fout, txtprinted);

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
// we need fillToken to unblock the print-methode, that complains if it gets to print an empty string
if (*tokenTagname=='\0')
   strcpy(tokenTagname,"Unbekanntes Element");
if (tokenTaginhalt==NULL)
   {
   tokenTaginhalt=new char[1];
   *tokenTaginhalt='\0';
   }

return mode;
}
