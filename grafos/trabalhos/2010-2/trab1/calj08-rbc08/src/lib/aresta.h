#ifndef _ARESTA_H_
#define _ARESTA_H_

/**
 * Classe que define uma aresta de p1 a p2
*/

#include "vertice.h"

class Aresta
{
	private:
		/** Define se foi visitasa a partir de p1 */
		bool visitada;
		
		/** Define se existe aresta entre v1 e v2 */
		bool aresta;

		/** Extremos da aresta */
		Vertice v1;
		Vertice v2;

		/** Define se é do tipo árvore */
		bool tipoArvore;
	
	public:
		Aresta();

		void setVisitada( bool );
		void setAresta( bool );
		void setV1( Vertice );
		void setV2( Vertice );
		void setTipoArvore( bool );
		bool isVisitada();
		bool isAresta();
		Vertice getV1();
		Vertice getV2();
		bool isTipoArvore();
		
};



#endif
