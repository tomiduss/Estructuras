#include "Treap.h" 
#include <iostream>
#include <time.h>

// class constructor
Treap::Treap()
{
	_root = new BinNode();
	_nodesCount = 0;
}

// class destructor
Treap::~Treap()
{
	
}

BinNode* Treap::getRoot()
{
    return _root;
}

void Treap::insertar( string key, int priority, int element, BinNode* n)
{
    //Si el nodo encontrado es un centinela
    if( n->getCentinel() == true)
    {       
        //Agrego los nuevos valores    
        n->setKey( key );
        n->setPriority( priority );
        n->setElement( element );
        n->setCentinel( false );
        
        //Agrego nuevos centinelas
        n->setRight( new BinNode() );
        n->getRight()->setFather( n );
        
        n->setLeft( new BinNode() );
        n->getLeft()->setFather( n );
    }
    
    else if( key < n->getKey() )
    {
        insertar( key, priority, element, n->getLeft());
        if( n->getLeft()->getPriority() > n->getPriority() )
            rotate_right( n );
    }   
    else if ( key > n->getKey() )
    {
        insertar( key, priority, element, n->getRight());
        if( n->getRight()->getPriority() > n->getPriority() )
            rotate_left( n );
    }
}

void Treap::insertar( string key, int element, BinNode* n)
{
    //Si el nodo encontrado es un centinela
    if( n->getCentinel() == true)
    {   
        srand ( time(NULL) );
        int priority = rand() % 10000 + 1;
            
        //Agrego los nuevos valores    
        n->setKey( key );
        n->setPriority( priority );
        n->setElement( element );
        n->setCentinel( false );
        
        //Agrego nuevos centinelas
        n->setRight( new BinNode() );
        n->getRight()->setFather( n );
        
        n->setLeft( new BinNode() );
        n->getLeft()->setFather( n );
    }
    
    else if( key < n->getKey() )
    {
        insertar( key, element, n->getLeft());
        if( n->getLeft()->getPriority() > n->getPriority() )
            rotate_right( n );
    }   
    else if ( key > n->getKey() )
    {
        insertar( key, element, n->getRight());
        if( n->getRight()->getPriority() > n->getPriority() )
            rotate_left( n );
    }
}

void Treap::eliminar( BinNode* root, string key)
{
    if( key < root->getKey())
        eliminar( root->getLeft(), key);
    else if( key > root->getKey() )
        eliminar( root->getRight(), key);
    else
        eliminar_root(root);
}

void Treap::eliminar_root( BinNode* root )
{
    if( root->getCentinel() == true )
    {
        //Nada   
    }
    else if( (root->getLeft()->getCentinel() == true) && (root->getRight()->getCentinel() == true) )
        root->setCentinel( true );
    else if( root->getLeft()->getCentinel() == true )
    {
        rotate_left(root);
        eliminar_root(root);
    }
    else if( root->getRight()->getCentinel() == true )
    {
        rotate_right(root);
        eliminar_root(root);
    }
    else if( root->getLeft()->getPriority()> root->getRight()->getPriority())
    {
        rotate_right(root);
        eliminar_root(root);
    }
    else
    {
        rotate_left(root);
        eliminar_root(root);
    }
}


void Treap::rotate_left( BinNode* raiz )
{
    BinNode* left = raiz->getLeft();
    BinNode* right = raiz->getRight();
    
    //Guardo el padre del nodo y un aux
    BinNode* aux = right->getLeft();
    BinNode* padre = raiz->getFather();
            
    //Hago la rotación 
    right->setLeft( raiz );
    raiz->setFather( right );
    raiz->setRight( aux );
    aux->setFather( raiz );
            
    //Si el nodo era la raiz, simplemente hacemos que right sea la raiz del arbol
    if( raiz == _root )
        _root = right;
                
    //De lo contrario debemos averiguar donde iba el nodo y poner a right ahi
    else
    {
        if( padre->getLeft() == raiz)
            padre->setLeft( right );
        else
            padre->setRight( right );
        right->setFather( padre );
    }   
}

void Treap::rotate_right( BinNode* raiz )
{
    BinNode* left = raiz->getLeft();
    BinNode* right = raiz->getRight();
    
    //Guardo el padre del nodo y un aux
    BinNode* aux = left->getRight();
    BinNode* padre = raiz->getFather();
            
    //Hago la rotación 
    left->setRight( raiz );
    raiz->setFather( left );
    raiz->setLeft( aux );
    aux->setFather( raiz );
            
    //Si el nodo era la raiz, simplemente hacemos que left sea la raiz del arbol
    if( raiz == _root)
    _root = left;
                
    //De lo contrario debemos averiguar donde iba el nodo y poner a left ahi
    else
    {
        if( padre->getLeft() == raiz)
            padre->setLeft( left );
        else
            padre->setRight( left );
        left->setFather( padre );
    }          
}

void Treap::sortedDump( )
{
    //caso en que el arbol este vacío
	if( _root->getCentinel() == true)
		cout << "arbol vacio" <<endl;
	else
        imprimir(_root);    
}

void Treap::imprimir( BinNode* raiz )
{
    //Si el hijo izquierdo no es centinela recorro ese primero
    if( raiz->getLeft()->getCentinel() == false)
        imprimir( raiz->getLeft());
    
    //Imprimo el nodo actual
    cout << raiz->getKey() << " " << raiz->getElement()<< " "<< raiz->getPriority() << endl;
    
    //Si el hijo derecho no es centinela recorro ese sub-arbol
    if( raiz->getRight()->getCentinel() == false)
        imprimir( raiz->getRight());
}

void Treap::prettyPrint()
{
    //caso en que el arbol este vacío
	if( _root->getCentinel() == true)
	{
		cout << "arbol vacio" <<endl;
	}
	else
	{
        imprimirBonito(_root, 0, new int[100], true);    
    }
}

//incompleto no pescar
void Treap::imprimirBonito( BinNode* raiz, int nivel, int* ramas, bool left)
{
    //Si el hijo izquierdo no es centinela recorro ese primero
    if( raiz->getLeft()->getCentinel() == false)
    {
        if ( left )
            ramas[ nivel ] = 0;
        else 
            ramas[ nivel ] = 1;
        imprimirBonito( raiz->getLeft(), nivel + 1, ramas, true);
    }
    
    //Imprimo las ramas y los espacios
    for( int i = 0; i < nivel; i++)
    {
        if( ramas[i] == 1 && i != 0)
            cout << "|   ";
        else
            cout << "    ";
    }
    
    //imprimo el nodo
    cout << "|-- " << raiz->getKey() << endl;
    
    //Si el hijo derecho no es centinela recorro ese sub-arbol
    if( raiz->getRight()->getCentinel() == false)
    {
        if ( left )
            ramas[ nivel ] = 1;
        else 
            ramas[ nivel ] = 0;
        imprimirBonito( raiz->getRight(), nivel + 1, ramas, false);
    }   
}

bool Treap::buscar( string llave )
{   
    //Si el nodo encontrado es centinela retorno false.
    //Si no, retorno true
    return !buscarEn( _root, llave )->getCentinel();
}

BinNode* Treap::buscarEn( BinNode* n, string llave )
{
    //Caso en que el nodo es un centinela 
    if ( n->getCentinel()== true )
        return n;
    
    //Caso en que la llave sea menor que la del nodo
    else if ( llave < n->getKey())
        return buscarEn( n->getLeft(), llave);
    
    //Caso en que la llave es mayor que el nodo
    else if ( llave > n->getKey())
        return buscarEn( n->getRight(), llave );
        
    //Caso en que se encuentre exactamente el nodo
    else
        return n;
}




