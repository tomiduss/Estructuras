#include "Avl.h" // class's header file
#include <iostream>

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

BinNode* Avl::getRoot()
{
    return _root;
}

bool Avl::buscar( string llave )
{   
    //Si el nodo encontrado es centinela retorno false.
    //Si no, retorno true
    return !buscarEn( _root, llave )->getCentinel();
}


BinNode* Avl::buscarEn( BinNode* n, string llave )
{
    //Caso en que el nodo es un centinela 
    if ( n->getCentinel()== true )
    {
        return n;
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
    //Caso en que se encuentre exactamente el nodo
    else
    {
        return n;
    }
}


void Avl::insertar( string key, int element)
{
    BinNode* n = buscarEn( _root, key);
    
    //si el nodo encontrado es un centinela
    if( n->getCentinel() )
    {
        n->setCentinel(false);
        n->setKey( key );
        n->setElement(element);
        n->setRight( new BinNode() );
        n->setLeft( new BinNode() );
    }
    //si se encuentra el nodo exacto lo insertamos a la derecha de este
    else
    {
        BinNode* aux = n->getRight();
        n->setRight( new BinNode( key, element ) );
        aux->setFather( n->getRight() );
    }    
}

void Avl::sortedDump( )
{
    //caso en que el arbol este vacío
	if( _root->getCentinel() == true)
	{
		cout << "arbol vacio" <<endl;
	}
	else
	{
        imprimir(_root);    
    }
}

void Avl::imprimir( BinNode* raiz )
{
    //Si el hijo izquierdo no es centinela recorro ese primero
    if( raiz->getLeft()->getCentinel() == false)
    {
        imprimir( raiz->getLeft());
    }
    
    //Imprimo el nodo actual
    cout << raiz->getKey() << " " << raiz->getElement() << endl;
    
    //Si el hijo derecho no es centinela recorro ese sub-arbol
    if( raiz->getRight()->getCentinel() == false)
    {
        imprimir( raiz->getRight());
    }
}
