#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <iostream>
#include <sstream>
#include <cstdio>
#include <list>

using namespace std;

#include "vertice.h"
#include "aresta.h"

class Grafo
{
	private:
		/** Número de vértices do grafo */
		unsigned int numVertices;
		
		/** Número de arestas do grafo */
		unsigned int numArestas;

	public:
		/** Array com os vértices do grafo */
		Vertice * arrVertice;

		/** Matriz de adjacência. */
		Aresta ** matrizAdjacencia;

		/** Lë o grafo passado pela entrada padrão */
		bool leGrafo();
		
		/** Busca um vértice no array de vértices pelo nome */
		Vertice * busca( unsigned int );

		/** Busca por um vértice visitado ou não */
		Vertice * busca( bool );

		list<Vertice*> buscaVizinhos( Grafo *, Vertice );

		void setNumVertices( unsigned int );
		void setNumArestas( unsigned int );
		unsigned int getNumVertices();
		unsigned int getNumArestas();
};

#endif
