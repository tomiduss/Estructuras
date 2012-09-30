
#ifndef TREAP_H
#define TREAP_H
#include "BinNode.h"


class Treap
{
	public:
		// class constructor
		Treap();
		// class destructor
		~Treap();
		
		bool buscar( string llave );
		
		void insertar( string key, int priority, int element, BinNode* n );
		void insertar( int element );
		
		void sortedDump();
		void prettyPrint();
		
		BinNode* getRoot();
		
	private:
        void imprimir( BinNode* raiz );
        void imprimirBonito( BinNode* raiz);
        
        void rotate_right( BinNode* raiz );
        void rotate_left( BinNode* raiz );
        
        BinNode* buscarEn( BinNode* n, string llave);
        BinNode* _root;
        int _nodesCount; 
};

#endif // TREAP_H
