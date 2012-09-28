#include "BinNode.h" // class's header file

// constructores
BinNode::BinNode()
{
	_centinel = true;
}

BinNode::BinNode( string key, int element)
{
    _key = key;
    _element = element;
    _left = new BinNode();
    _right = new BinNode();
    _centinel = false;
}

// class destructor
BinNode::~BinNode()
{
	// insert your code here
}


//getters y setters

bool BinNode::getCentinel()
{
    return _centinel;   
}

void BinNode::setCentinel( bool valor)
{
    _centinel = valor;
}

int BinNode::getElement()
{
    return _element;
}

void BinNode::setElement( int element )
{
    _element = element;
}
		
string BinNode::getKey()
{
    return _key;
}

void BinNode::setKey( string key )
{
    _key = key;
}

BinNode* BinNode::getLeft()
{
    return _left;   
}

void BinNode::setLeft( BinNode* nodo )
{
    _left = nodo;
}
		
BinNode* BinNode::getRight()
{
    return _right;
}

void BinNode::setRight( BinNode* nodo)
{
    _right = nodo;
}

BinNode* BinNode::getFather()
{
    return _father;
}

BinNode* BinNode::setFather( BinNode* nodo)
{
    _father = nodo;
}


