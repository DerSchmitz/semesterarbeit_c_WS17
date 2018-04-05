C++ Semesterarbeit - Jürgen Schmitz - Stand 18.2.2018


Programme Documentation:        
C++-Files:        
1. main.cpp: This file includes the cin and cout commands of the CLI as well as the launch-commands for the methods defined in txttokenlib.cpp and xmltokenlib.cpp.


2. txttokenlib.cpp: Here we find the parsing method for the txt-file, that saves the metadata of one product inside of a set of variables for each of the iterations of “anzahlAtt”. 


3. xmltokenlib.cpp: Here are the parsing methods for the xml-file defined, as well as the printing method needed to print out the stored XML- and TXT-data


Header-Files:
1. clxmltoken.h: Here you find the class-definition of the class designated for the XML-data, including all variables and functions that work with xml-data


2. cltxttoken.h: Here you find the class-definition of the class designated for the TXT-Data, including all txt-variables and a set of getter-methods, that enable the printing-method in xmltokenlib.cpp to also print out the txt-data


Datasources:
listProducts.xml: A list of products in XML-format 
products.txt: A list of additional products in TXT-format
allowed-tags.dtd: A DTD-File that defines allowed tags for stage 4 of this assignment


Repository Permalink: https://github.com/DerSchmitz/semesterarbeit_c_WS17 


Der Business Case: Ein Elektronikfachhandel erstellt für die Inventur einen XML-Datensatz mit allen Produkten und dazu gehörigen Produktbeschreibungen. Eine damit verbundene Dtd-Datei filtert veraltete oder nicht benötigte Metadaten heraus. 
Ein kürzlich assoziierter Franchisenehmer arbeitet mit einer veralteten Inventursoftware, die nur minimalistische Datensätze im txt-Format ausgibt, deren Datenwerte keine Leerstellen enthalten können. Die Datenexports dieser beiden Softwares müssen für die Inventur vereint werden.


Ziel des Programms: Die XML-Datei und die Txt-Datei in ein XML-Dokument konvertieren.


Verwendete Hilfestellungen: 
Hilfestellung zum Bau des XML-Parsers: https://gist.github.com/janwieners/a246cf84803bb7f2f2dd 
Hilfestellung zur Datenverarbeitung der Metadaten:
http://hki.uni-koeln.de/beispiel-10-rekursion-und-verknuepfte-listen-ii/ 





Vorgehensweise: 
1. Dateiverarbeitung TXT
   1. Öffne das txt-objekt
   2. parse die enthaltenen Datensätze
   3. speichere die einzelnen Metadaten eines Produkts in je einer Variable der Klasse Cltxttoken
   4. zähle mit integer-variable anzahlAtt für jeden Produktdatensatz iterativ herauf, um die Datensätze später nacheinander ausgeben zu können
   5. erstelle Getter für alle Variablen, um die TXT-Werte von der Print-Methode aus aufzurufen


2. Dateiverarbeitung XML
   1. Öffne das xml-objekt 
   2. parse die datensätze
   3. speichere einzelne Daten und Metadaten in Variablen der Klasse Clxmltoken 
   4. erzeuge rekursiv neue Chid- und Siblingobjekte, um die Datensätze voneinander zu unterscheiden


3. Implementierung der Printfunktion:
   1. Erzeuge ein fout-objekt zur Erzeugung einer Dateiausgabe
   2. Iteriere alle Child- und Siblingobjekte der XML-Datei durch und drucke die gespeicherten Daten jeweils im XML-Format ab
   3. Starte Abfrage, wann das letzte Vaterelement geschlossen wird und drucke vor dem Schließen die Produkte aus der TXT-Datei im XML-Format ab
