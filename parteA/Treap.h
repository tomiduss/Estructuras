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
		void insertar( string key, int element, BinNode* n );
		
		void sortedDump();
		void prettyPrint();
		
		void eliminar( BinNode* root, string key );
		void eliminar_root( BinNode* root );
		
		BinNode* getRoot();
		
	private:
        void imprimir( BinNode* raiz );
        void imprimirBonito( BinNode* raiz, int nivel, int* ramas, bool left);
        
        void rotate_right( BinNode* raiz );
        void rotate_left( BinNode* raiz );
        
        BinNode* buscarEn( BinNode* n, string llave);
        BinNode* _root;
        int _nodesCount; 
};

#endif // TREAP_H
