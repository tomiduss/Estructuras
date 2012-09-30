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
    Avl* aux = new Avl();
    
    string line;
    string nombre_archivo = "";
    cout << "indique nombre del archivo" << endl;
    cin >> nombre_archivo;
          
    ifstream myfile(nombre_archivo.c_str());
    
    if (myfile.is_open())
    {   
        while ( myfile.good() )
        {
            getline (myfile,line);
            istringstream iss(line);
            string key;
            int value;
            iss >> key;
            iss >> value;
            aux->insertar( key, value);
        }
        myfile.close();
    }
    aux->sortedDump();
    aux->prettyPrint(); 
    
    /*
    Treap* arbol = new Treap();
    line = "";
    nombre_archivo = "prueba.txt";
    
    ifstream myfile_2(nombre_archivo.c_str());
    
    if (myfile_2.is_open())
    {   
        // initialize random seed: 
        srand ( time(NULL) );
        
        while ( myfile_2.good() )
        {
            getline (myfile_2,line);
            istringstream iss(line);
            string key;
            int value;
            iss >> key;
            iss >> value;
            
            //genero la prioridad entre 1 y 100
            int priority = rand() % 100 + 1;
            
            arbol->insertar( key, priority, value, arbol->getRoot());
        }
        myfile_2.close();
    }
    
    arbol->sortedDump();
    */
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
