#ifndef BINNODE_H
#define BINNODE_H
#include <string>

using namespace std;

class BinNode
{
	public:
		// constructores
		BinNode();
		
		BinNode( string key, int element);
		
        // class destructor
		~BinNode();
		
		//getters y setters
		bool getCentinel();
		void setCentinel( bool valor );
		
		int getElement();
		void setElement( int element );
		
		string getKey();
		void setKey( string key);
		
		BinNode* getLeft();
		void setLeft( BinNode* nodo );
		
		BinNode* getRight();
		void setRight( BinNode* nodo);
		
		BinNode* getFather();
		BinNode* setFather( BinNode* nodo);
		
	private:
        BinNode* _left;
        BinNode* _right;
        BinNode* _father;
            
        int _element;
        string _key;
        bool _centinel;
};

#endif // BINNODE_H
