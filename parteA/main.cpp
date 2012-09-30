#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

#include "Avl.h"
#include "Treap.h"

using namespace std;

int main(int argc, char *argv[])
{
    string input;
    string output;
    
    cout << "indique el nombre del archivo de entrada" << endl;
    cin >> input;
    
    cout << "indique el nombre del archivo de salida" << endl;
    cin >> output;
    
    //AVL
    
    Avl* aux = new Avl();
    
    string line;
    /*      
    ifstream myfile(input.c_str());
    
    if (myfile.is_open())
    {   
        while ( myfile.good() )
        {
            getline (myfile,line);
            istringstream iss(line);
            string key;
            string instruccion;
            iss >> instruccion;
            iss >> key;
            if( instruccion == "insert")
                aux->insertar( key, 1);
            else if ( instruccion == "delete")
                aux->eliminar( key );
            aux->prettyPrint();
            cout << endl;
            cout << endl;
        }
        myfile.close();
    }
    cout << "avl" << endl;
    aux->prettyPrint();
    */

    //Treap
    
    Treap* arbol = new Treap();
    line = "";
    
    ifstream myfile_2(input.c_str());
    
    if (myfile_2.is_open())
    {   
        while ( myfile_2.good() )
        {
            getline (myfile_2,line);
            istringstream iss(line);
            string instruccion;
            string key;
            int priority;
            string aux;
            iss >> instruccion;
            iss >> key;
            iss >> aux;
            priority = atoi(aux.c_str());
            
            if( instruccion == "insert")
                arbol->insertar( key, priority, 1, arbol->getRoot());
            else if( instruccion == "delete" )
            { 
                 arbol->eliminar( arbol->getRoot(), key );
            }
        }
        myfile_2.close();
    }
    cout << endl;
    cout << endl;
    
    cout << "Treap" << endl;
    arbol->prettyPrint();
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
