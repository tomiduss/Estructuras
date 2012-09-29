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

void Avl::insertar( string key, int element)
{
    BinNode* n = buscarEn( _root, key);
    
    //si el nodo encontrado es un centinela
    if( n->getCentinel() )
    {
        //Reemplazo el centinela por los valores a insertar
        n->setCentinel(false);
        n->setKey( key );
        n->setElement(element);
        
        //Agrego nuevos Centinelas
        n->setRight( new BinNode() );
        n->getRight()->setFather( n );
        
        n->setLeft( new BinNode() );
        n->getLeft()->setFather( n );
    }
    //Si se encuentra el nodo exacto actualizamos su información
    else
        n->setElement( element );
    
    //Por último balanceamos
    balancear( n );
    
}

void Avl::sortedDump( )
{
    //caso en que el arbol este vacío
	if( _root->getCentinel() == true)
		cout << "arbol vacio" <<endl;
	else
        imprimir(_root);    
}

void Avl::imprimir( BinNode* raiz )
{
    //Si el hijo izquierdo no es centinela recorro ese primero
    if( raiz->getLeft()->getCentinel() == false)
        imprimir( raiz->getLeft());
    
    //Imprimo el nodo actual
    cout << raiz->getKey() << " " << raiz->getElement()<< " "<< raiz->getAltura() << endl;
    
    //Si el hijo derecho no es centinela recorro ese sub-arbol
    if( raiz->getRight()->getCentinel() == false)
        imprimir( raiz->getRight());
}

void Avl::balancear( BinNode* nodo )
{
    BinNode* left = nodo->getLeft();
    BinNode* right = nodo->getRight();
    
    int left_h = left->getAltura();
    int right_h = right->getAltura();
    
    //Primero, actualizo la altura del padre
    if( left_h > right_h)
        nodo->setAltura( left_h+1 );
    else
        nodo->setAltura( right_h+1 );
        
    //Caso 1 o 2    
    if( left_h - right_h > 1 )
    {
        //Caso 1 rotación simple
        if( left->getLeft()->getAltura() > left->getRight()->getAltura())
        {
            //Guardo el padre del nodo y un aux
            BinNode* aux = left->getRight();
            BinNode* padre = nodo->getFather();
            
            //Hago la rotación 
            left->setRight( nodo );
            nodo->setFather( left );
            nodo->setLeft( aux );
            aux->setFather( nodo );
            
            //Si el nodo era la raiz, simplemente hacemos que left sea la raiz del arbol
            if( nodo == _root)
                _root = left;
                
            //De lo contrario debemos averiguar donde iba el nodo y poner a left ahi
            else
            {
                if( padre->getLeft() == nodo)
                    padre->setLeft( left );
                else
                    padre->setRight( left );
                left->setFather( padre );
            } 
            nodo->setAltura( nodo->getRight()->getAltura()+1);
        }
        
        //Caso 2 rotacion doble
        else
        {
            //Variables necesarias
            BinNode* nieto = left->getRight();
            BinNode* padre = nodo->getFather();
            BinNode* aux_left = nieto->getLeft();
            BinNode* aux_right = nieto->getRight();
            
            //Hago la rotación 
            nieto->setLeft( left );
            left->setFather( nieto );
            
            nieto->setRight( nodo );
            nodo->setFather( nieto );
            
            left->setRight( aux_left );
            aux_left->setFather( left );
            
            nodo->setLeft( aux_right );
            aux_right->setFather( nodo );
            
            //Si el nodo era la raiz, simplemente hacemos que el nieto sea la raiz del arbol
            if( nodo == _root)
                _root = nieto;
                
            //De lo contrario debemos averiguar donde iba el nodo y poner a left ahi
            else
            {
                if( padre->getLeft() == nodo)
                    padre->setLeft( nieto );
                else
                    padre->setRight( nieto );
                nieto->setFather( padre );
            } 
            
            //actualizo las alturas
            nodo->setAltura( nieto->getAltura());
            nieto->setAltura( nodo->getAltura() +1 );
            left->setAltura( nodo->getAltura() );
        }
    }   
    
    //Caso 3 o 4
    else if( right_h - left_h > 1)
    {
        //Caso 3 Rotación doble
        if( right->getLeft()->getAltura() > right->getRight()->getAltura())
        {
            //Variables necesarias
            BinNode* nieto = right->getLeft();
            BinNode* padre = nodo->getFather();
            BinNode* aux_left = nieto->getLeft();
            BinNode* aux_right = nieto->getRight();
            
            //Hago la rotación 
            nieto->setLeft( nodo );
            nodo->setFather( nieto );
            
            nieto->setRight( right );
            right->setFather( nieto );
            
            nodo->setRight( aux_left );
            aux_left->setFather( nodo );
            
            right->setLeft( aux_right );
            aux_right->setFather( right );
            
            //Si el nodo era la raiz, simplemente hacemos que el nieto sea la raiz del arbol
            if( nodo == _root)
                _root = nieto;
                
            //De lo contrario debemos averiguar donde iba el nodo y poner a left ahi
            else
            {
                if( padre->getLeft() == nodo)
                    padre->setLeft( nieto );
                else
                    padre->setRight( nieto );
                nieto->setFather( padre );
            } 
            
            //actualizo las alturas
            nodo->setAltura( nieto->getAltura());
            nieto->setAltura( nodo->getAltura() +1 );
            right->setAltura( nodo->getAltura() );
        }
        //Caso 4 rotacion simple
        else
        {
            BinNode* aux = right->getLeft();
            BinNode* padre = nodo->getFather();
            
            right->setLeft( nodo );
            nodo->setFather( right );
            
            nodo->setRight( aux );
            aux->setFather( nodo );
            
            //Si el nodo era la raiz, simplemente cambiamos hacemos que right sea la raiz del arbol
            if( nodo == _root)
                _root = right;
            //De lo contrario debemos averiguar donde iba el nodo y poner a left ahi
            else
            {
                if( padre->getLeft() == nodo)
                    padre->setLeft( right );
                else
                    padre->setRight( right );
                right->setFather( padre );
            } 
            nodo->setAltura( nodo->getRight()->getAltura()+1);
        }
    }
    
    //Si el nodo no es la raiz del arbol, repito para el padre
    if( nodo != _root )
        balancear( nodo->getFather() ); 
}

//incompleto
void Avl::prettyPrint()
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

//incompleto no pescar
void Avl::imprimirBonito( BinNode* raiz)
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

