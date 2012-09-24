#include "Avl.h" // class's header file

// class constructor
Avl::Avl()
{
	_root = new BinNode();
	_nodesCount = 0;
}

// class destructor
Avl::~Avl()
{
	// insert your code here
}

bool Avl::buscar( string llave )
{
    return buscarEn( _root, llave);
}


bool Avl::buscarEn( BinNode* n, string llave )
{
    //Caso en que le arbol no tiene nodos
    if ( _root == 0 )
    {
        return false;
    }
    
    //Caso en que la llave sea menor que la del nodo
    else if ( llave < n->getKey())
    {
        return buscarEn( n->getLeft(), llave);
    }
    
    //Caso en que la llave es mayor que el nodo
    else if ( llave > n->getKey())
    {
        return buscarEn( n->getRight(), llave );
    }
    
    //Caso en que hayamos encontrado el nodo
    else
    {
        return true;
    }
    
}


void Avl::insertar( string key, int element)
{
    //Caso 1 nodo encontrado es un centinela
    if( _root->getCentinel() == true )
    {
        _root->setKey(key);
        _root->setElement(element);
        _root->setLeft( new BinNode);
        _root->setRight( new BinNode);
    }
    //Caso 2 nodo es mayor que el valor a incertar
    //else if()
    //{
    //}
        
}
