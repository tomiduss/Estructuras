#include "BinNode.h" // class's header file

// class constructor
BinNode::BinNode()
{
	_centinel = true;
}

// class destructor
BinNode::~BinNode()
{
	// insert your code here
}

BinNode::BinNode( string key, int element)
{
    _key = key;
    _element = element;
    _left = new BinNode();
    _right = new BinNode();
}

//getters y setters

bool BinNode::getCentinel()
{
    return _centinel;   
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


