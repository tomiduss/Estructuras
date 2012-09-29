#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Avl.h"

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
    
    //bool a = aux->buscar( "Henry" );
    //cout << a << endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
