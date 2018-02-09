#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include "clxmltoken.h"
#include "cltxttoken.h"

/* Bereiten Sie Parser für Ihre Datenquellen vor.
Laden Sie die Inhalte Ihrer Datenquellen und speichern Sie diese als Objekt innerhalb Ihres Programms.
Bereiten Sie dazu eine geeignete Klasse vor.*/

int main()
{
    // erstelle Objekte zur Arbeit mit Datafiles
    ifstream eingabe_xml, eingabe_txt;

    //erstelle Objekt für einen Datensatz der XML-Daten
    ClxmlToken xmltoken;
    CltxtToken txttoken;

    // öffne Dateien
    eingabe_xml.open("listProducts.xml");
    eingabe_txt.open("products.txt");

    // übergebe ifstreamobjekt an funktion den Parsing-Methoden
            // diese Methode gibt direkt die geparsten Daten aus
    xmltoken.ladeXML(eingabe_xml);

    // Drucke XML durch eigene MEthode
    cout << "DRUCKE XML AB" << endl;
    xmltoken.printXMLToken(1);





            // diese Methode speichert die daten innerhalb der Klasse CltxtToken zwischen, sodass sie anschließend über eine Print-Anweisung ausgedruckt werden kann
   /* txttoken.ladeTXT(eingabe_txt);

    // Print out TXT
    for (int i=0;i<txttoken.getAnzahlAtt();i++){
    cout << "ValueID: " << txttoken.getattValueID(i) << endl;
    cout << "ValueModel: " << txttoken.getattValueModel(i) << endl;
    cout << "ValuePrice: " << txttoken.getattValuePrice(i) << endl;
    }*/

    // Close ifstreamobjekts
    eingabe_xml.close();
    eingabe_txt.close();

    // end main-function
    return 0;
}
