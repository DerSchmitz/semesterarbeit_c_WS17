#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include "clxmltoken.h"


int main()
{
    // make two ifstream objects to work with the two diffrent datafiles
    ifstream eingabe_xml, eingabe_txt;
    // make ofstream-object
    ofstream fout;

    // make 2 objects to store information of the the diffrent datafiles
    ClxmlToken xmltoken;
    CltxtToken txttoken;

    //set variables for while-loop and cli
    int active = 0;
    // set variables for cin-userinputs
    char userinput;
    char txtfilename[50];
    char xmlfilename[50];
    char outputfilename[50];
    // set variable for printing methode
    bool txtprinted;

    /* Start Command Line Interface*/
    cout << endl << endl;
    cout  << "Command line interface" << endl;
    cout << "------------------------------"<< endl;
while (active==0){



    //Display menu-options
     cout << "Menu:"<< endl;
     cout << "1. [C]onvert"<< endl;
     cout << "2. [H]elp"<< endl;

     cin >> userinput;

     switch (userinput) {
     case 'C':
     case 'c':
        cout << "You want to convert metadata from a  TXT-File into a XML-productlist and your into one XML-file containign all metadata." << endl;
        cout << "Please enter the name of your TXT-file (e.g. metainformation.txt)" << endl;
        cin >> txtfilename;
        cout << "Now enter the name of your XML-file (e.g. listProducts.xml)" << endl;
        cin >> xmlfilename;
        cout << "Lastly please enter the name of the ouput-file you want to create (e.g. ouput.xml)" << endl;
        cin >> outputfilename;

        // open datafiles
        eingabe_txt.open(txtfilename);
        eingabe_xml.open(xmlfilename);

        // define output-file
        fout.open(outputfilename);

        // break off programme if, input-files do not exist or output-file can not be generated
        if( !eingabe_txt.is_open() or !eingabe_xml.is_open() or !fout.is_open() ) {
            cout << "One or more of the named files do not seem to exist, please restart the programme." << endl;
            return 0;
        }

        // deliver ifstreamobject to their respective parsing-methodes
            // this methode parses the TXT-file and saves the data inside of the class CltxtToken to be later printed by the print-methode
            txttoken.ladeTXT(eingabe_txt);

            // this methode parses the XML-file and saves the data inside of the class ClxmlToken
            xmltoken.ladeXML(eingabe_xml);


        // Print XML in designated file
        cout << endl << "Print XML in output-file: " << outputfilename << endl;

        // set boolean on false (txt NOT printed yet)
        txtprinted=false;
                            // deliver the txttoken-object to be printed out in between the xml-objects
                                        // deliver the fout-object to the print function to find the file where the XML should be printed
                                                //deliver a boolean to prevent multiple printouts
        xmltoken.printXMLToken(txttoken, fout, txtprinted);
        cout << "Print successful!" << endl;

        // close off ifstream-, and ofstream-objekts
        fout.close();
        eingabe_xml.close();
        eingabe_txt.close();

         break;

     case 'H':
     case 'h':
        cout << endl << "To navigate the menue, please enter the first letter of the action you want to start. "<< endl;
                cout << "When you are asked for an inputfilename please make sure the file exists and is placed in the build-directory of this programme." << endl;
                cout << "Please make also sure to type in the correct and complete name of the files you want to read or create." << endl;
                cout << "If you encounter any issues please contact the administrator." << endl;

         break;
     default:
          cout << "Your input was invalid, please type in 'h' and press enter for input instructions." << endl;
         break;
     }



}

















    // end main-function
    return 0;
}






