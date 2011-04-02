#include "grafo.h"


bool Grafo::leGrafo()
{
	FILE *fp = stdin; // ponteiro para o arquivo de entrada
	unsigned int numVertices;
	unsigned int v1, v2;
	unsigned int cont = 0;
	
	if ( fscanf( fp, "%d", &numVertices ) == 0 )
	{
		cerr << "Erro ao ler o número de vértices do grafo" << endl;
		exit( 1 );
	}
	this->setNumVertices( numVertices );
	
	this->arrVertice = new Vertice[ numVertices ];

	// aloca espaço na matriz de adjacencia
	// aloca uma posição a mais pois os vértices começam em 1, não em 0
	this->matrizAdjacencia = new Aresta*[ numVertices + 1 ];
	for ( cont = 0; cont <= numVertices; cont++ )
	{
		this->matrizAdjacencia[ cont ] = new Aresta[ numVertices + 1 ];
	}

	// lê as arestas
	cont = 0;
	while ( fscanf( fp, "%d %d", &v1, &v2 ) == 2 )
	{
		// insere no array de vértices somente se já não tiver sido inserido
		if ( this->busca( v1 ) == NULL )
		{
			this->arrVertice[ cont ].setNome( v1);
			this->arrVertice[ cont ].setVisitado( false );
			cont++;
		}

		if ( this->busca( v2 ) == NULL )
		{
			this->arrVertice[ cont ].setNome( v2 );
			this->arrVertice[ cont ].setVisitado( false );
			cont++;
		}


		// coloca na matriz de adjacência
		this->matrizAdjacencia[v1][v2].setV1( v1 );
		this->matrizAdjacencia[v1][v2].setV2( v2 );
		this->matrizAdjacencia[v1][v2].setAresta( 1 );
		this->matrizAdjacencia[v1][v2].setTipoArvore( false );

		this->matrizAdjacencia[v2][v1].setV1( v2 );
		this->matrizAdjacencia[v2][v1].setV2( v1 );
		this->matrizAdjacencia[v2][v1].setAresta( 1 );
		this->matrizAdjacencia[v2][v1].setTipoArvore( false );
	}

	return true;
}
/*-------------------------------*/



Vertice * Grafo::busca( unsigned int nome )
{
	register unsigned int i;

	for ( i = 0; i < this->numVertices; i++ )
	{
		if ( this->arrVertice[i].getNome() == nome )
		{
			return &(this->arrVertice[i]);
		}
	}

	return NULL;
}
/*------------------------------------------*/



Vertice * Grafo::busca( bool visitado )
{
	register unsigned int i;

	for ( i = 0; i < this->numVertices; i++ )
	{
		if ( this->arrVertice[i].isVisitado() == visitado )
		{
			return &(this->arrVertice[i]);
		}
	}

	return NULL;
}
/*------------------------------------------*/



list<Vertice*> Grafo::buscaVizinhos( Grafo *G, Vertice v )
{
	list<Vertice*> vizinhos;
	register unsigned int i;

	for ( i = 1; i <= this->getNumVertices(); i++ )
	{
		if ( this->matrizAdjacencia[v.getNome()][i].isAresta() )
		{
			Vertice *w = this->busca( i );

			if ( w != NULL && !w->isVisitado() )
			{
				vizinhos.push_front( w );
				
				/*
				 * A primeira versão do trabalho continha a parte abaxo descomentada, o que gerou
				 * o erro na busca em profundidade. O problema era que ele setava todos os vizinhos
				 * não visitados de um vértice como visitado. Isso pode ocorrer na busca em largura,
				 * mas não na busca em profundidade.
				 * O trecho abaixo foi transferido para os arquivos bfs.cpp e dfs.cpp, que contém as
				 * funções main(). O trcho está presenta dentro do loop que verifica a vizinhança dos
				 * vértices.
				*/
				/*if ( ! w->isVisitado() )
				{
					cout << "\nSetando aresta " << i << "-" << v.getNome() << " como aresta-árvore\n";
					this->matrizAdjacencia[v.getNome()][i].setTipoArvore( true );
					this->matrizAdjacencia[i][v.getNome()].setTipoArvore( true );
				}*/
			}
		}
	}

	return vizinhos;
}


void Grafo::setNumVertices( unsigned int numVertices )
{
	this->numVertices = numVertices;
}
/*----------------------------------------------*/


void Grafo::setNumArestas( unsigned int numArestas )
{
	this->numArestas = numArestas;
}
/*------------------------------------------------*/


unsigned int Grafo::getNumVertices()
{
	return this->numVertices;
}
/*-----------------------------------------------------*/



unsigned int Grafo::getNumArestas()
{
	return this->numArestas;
}
