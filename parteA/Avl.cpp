#include "Avl.h" 
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
    //Si se encuentra el nodo exacto actualizamos su informaci�n
    else
        n->setElement( element );
    
    //Por �ltimo balanceamos
    balancear( n );
}

void Avl::eliminar( string key )
{
    //encuentro el nodo que se quiere eliminar
    BinNode* raiz = buscarEn( _root, key );
    
    //si es centinela, nada que borrar
    if( raiz->getCentinel() == true)
        return;
    
    //si el nodo no tiene hijos, simplemente se borra
    else if( (raiz->getLeft()->getCentinel() == true) && (raiz->getRight()->getCentinel() == true) )
    {
        raiz->setCentinel( true );
        raiz->setAltura( 0 );
        delete raiz->getLeft();
        delete raiz->getRight();
        balancear( raiz->getFather() );
    }
    
    //si tiene hijo izquierdo
    else if( (raiz->getLeft()->getCentinel() == false) && (raiz->getRight()->getCentinel() == true) )
    {
        BinNode* left = raiz->getLeft();
        BinNode* padre = raiz->getFather();
        
        //reemplazo el nodo por su hijo
        if( padre->getLeft() == raiz)
            padre->setLeft( left );
        else
            padre->setRight( left );
        left->setFather( padre );
        
        //destruyo el nodo y su centinela
        delete raiz->getRight();
        delete raiz;
        
         balancear( left->getFather() );
    }
    
    //si tiene hijo derecho
    else if( (raiz->getLeft()->getCentinel() == true) && (raiz->getRight()->getCentinel() == false) )
    {
        BinNode* right = raiz->getRight();
        BinNode* padre = raiz->getFather();
        
        //reemplazo el nodo por su hijo
        if( padre->getLeft() == raiz)
            padre->setLeft( right );
        else
            padre->setRight( right );
        right->setFather( padre );
        
        //destruyo el nodo y su centinela
        delete raiz->getLeft();
        delete raiz;
        
         balancear( right->getFather() );
    }
    
    //Si tiene dos hijos
    else
    {
        //Busco el proximo inorden
        BinNode* aux = raiz->getRight();
        while( aux->getLeft()->getCentinel() == false )
        {
            aux = aux->getLeft();
        } 
        
        //si existe guardo el hijo del nodo encontrado
        BinNode* hijo = new BinNode();
        if( aux->getLeft()->getCentinel() == false )
            hijo = aux->getLeft();
        else if( aux->getRight()->getCentinel() == false )
            hijo = aux->getRight();
            
        //reemplazo el nodo por el encontrado
        raiz->setAltura( aux->getAltura());
        raiz->setElement( aux->getElement());
        raiz->setKey( aux->getKey());
        //raiz->setCentinel( aux->getKey());
            
        //destruyo el nodo encontrado
        BinNode* padre = aux->getFather();
        if( padre->getLeft() == aux)
            padre->setLeft( hijo );
        else
            padre->setRight( hijo );
        hijo->setFather( padre );
        
        //libero memoria
        delete aux;
        
        balancear( hijo->getFather() );
    }
    
}

void Avl::sortedDump( )
{
    //caso en que el arbol este vac�o
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
        //Caso 1 rotaci�n simple
        if( left->getLeft()->getAltura() > left->getRight()->getAltura())
        {
            //Guardo el padre del nodo y un aux
            BinNode* aux = left->getRight();
            BinNode* padre = nodo->getFather();
            
            //Hago la rotaci�n 
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
            
            //Hago la rotaci�n 
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
        //Caso 3 Rotaci�n doble
        if( right->getLeft()->getAltura() > right->getRight()->getAltura())
        {
            //Variables necesarias
            BinNode* nieto = right->getLeft();
            BinNode* padre = nodo->getFather();
            BinNode* aux_left = nieto->getLeft();
            BinNode* aux_right = nieto->getRight();
            
            //Hago la rotaci�n 
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


void Avl::prettyPrint()
{
    //caso en que el arbol este vac�o
	if( _root->getCentinel() == true)
	{
		cout << "arbol vacio" <<endl;
	}
	else
	{
        imprimirBonito(_root, 0, new int[100], true);    
    }
}


void Avl::imprimirBonito( BinNode* raiz, int nivel, int* ramas, bool left)
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

