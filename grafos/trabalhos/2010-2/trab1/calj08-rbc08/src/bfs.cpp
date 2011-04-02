/*
	bfs (Breadth-first Search - busca em largura)
*/

#include "bfs.h"


int main()
{
	Grafo *G = new Grafo();
	queue<Vertice*> FilaVertices;
	Vertice *v;
	register unsigned int i, j;
	
	G->leGrafo();
	
	// busca por vértices não visitados
	while ( ( v = G->busca( false ) ) != NULL )
	{
		// enfila v
		FilaVertices.push( v );

		while ( ! FilaVertices.empty() )
		{
			v = FilaVertices.front();
			FilaVertices.pop();

			// exibe visita ao vértice
			v->exibir();
			cout << " ";

			v->setVisitado( true );

			list<Vertice*> vizinhos = G->buscaVizinhos( G, *v );

			if ( vizinhos.size() > 0 )
			{
				while ( ! vizinhos.empty() )
				{
					Vertice *w = vizinhos.front();

					vizinhos.pop_front();

					if ( ! w->isVisitado() )
					{
						w->setVisitado( true );
						FilaVertices.push( w );
						/*
						 * As duas linahs abaixo foram adicinoadas a fim de corrigir a primeira versão
						 * do trabalho. Mais informações no comentário da linha 117 do arquivo lib/grafo.cpp
						*/
						G->matrizAdjacencia[ v->getNome() ][ w->getNome() ].setTipoArvore( true );
						G->matrizAdjacencia[ w->getNome() ][ v->getNome() ].setTipoArvore( true );
					}
				}
			}
		}
	}

	cout << endl;

	for ( i = 1; i <= G->getNumVertices(); i++ )
	{
		for ( j = 1; j < i; j++ )
		{
			if ( G->matrizAdjacencia[i][j].isAresta() )
			{
				if ( G->matrizAdjacencia[i][j].isTipoArvore() )
				{
					cout << CHAR_ARVORE;
				}
				else
				{
					cout << CHAR_NAOARVORE;
				}

				cout << " " << i << " " << j << endl;
			}
		}
	}

	return 0;
}
