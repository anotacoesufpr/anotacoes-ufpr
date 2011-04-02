import java.io.*;
import java.util.ArrayList;

/*
 * Os loops para preenchimento e leitura de vértices e arestas iniciam-se em 1 pois o primeiro vértice é 1, não 0
 */

public class Grafo
{
	public static final int MAX_VERTICES = 100;
	
	private int numVertices;
	private int numArestas;
	public Vertice[] arrVertices;
	public Aresta [][] matrizAdjacencia;
	
	
	/**
	 * Clona o objeto atual e o retorna.
	 * 
	 * Não é usado método clone() padrão pois ele não clona objetos.
	 * @return Retorna um objeto Grafo novo, igual ao da instãncia atual
	 */
	public Grafo clonaGrafo()
	{
		Grafo localG = new Grafo();
		localG.setNumArestas( this.getNumArestas() );
		localG.setNumVertices( this.getNumVertices() );
		
		localG.arrVertices = new Vertice[ this.arrVertices.length ];
		localG.matrizAdjacencia = new Aresta[ this.matrizAdjacencia.length ][ this.matrizAdjacencia.length ];
		
		for ( int i = 0; i < this.arrVertices.length; i++ )
		{
			localG.arrVertices[i] = (Vertice) this.arrVertices[i].clone();
		}
		
		for ( int i = 0; i < this.matrizAdjacencia.length; i++ )
		{
			for ( int j = 0; j < this.matrizAdjacencia.length; j++ )
			{
				localG.matrizAdjacencia[i][j] = (Aresta) this.matrizAdjacencia[i][j].clone();
			}
		}
		
		return localG;
	}
	/*------------------------------------*/
	
	public Grafo()
	{
		this.arrVertices = new Vertice[ Grafo.MAX_VERTICES ];
		this.matrizAdjacencia = new Aresta[ Grafo.MAX_VERTICES ][ Grafo.MAX_VERTICES ];
		
		for ( int i = 0; i < Grafo.MAX_VERTICES; i++ )
		{
			this.arrVertices[i] = new Vertice();
			for ( int j = 0; j < Grafo.MAX_VERTICES; j++ )
			{
				this.matrizAdjacencia[i][j] = new Aresta();
			}
		}
	}
	
	
	/**
	 * Lê um gafo de um arquivo
	 * @param FR Objeto FR com o ponteiro no início do grafo a ser lido
	 * @return TRUE se ler o grafo corretamete; FALSE caso contrário
	 */
	public boolean leGrafo( FileReader FR )
	{
		char charAnterior = ( char ) 0;
		int intChar, linha = 1, coluna = 1;
		char c;
		
		try
		{
			while ( ( intChar = FR.read() ) != -1 )
			{
				c = ( char ) intChar;
				
				if ( c == '\n' )
				{
					// se o caractere anteiror for \n também, para a leitura,
					// pois é onde começa o segundo grafo (para o exercício de isomorfismo)
					if ( charAnterior == '\n' )
					{
						break;
					}
					
					linha++;
					coluna = 1;
					this.numVertices++;
				}
				else
				{
					if ( c == '1' )
					{
						// evita que sejam contabilizadas as arestas (x,y) e (y,x)
						if ( ! this.matrizAdjacencia[linha][coluna].isAresta() && ! this.matrizAdjacencia[coluna][linha].isAresta() )
						{
							this.numArestas++;
						}
						
						this.matrizAdjacencia[linha][coluna].setAresta( true );
						this.matrizAdjacencia[linha][coluna].setV1( this.buscaVertice( linha ) );
						this.matrizAdjacencia[linha][coluna].setV2( this.buscaVertice( coluna ) );
						
						this.arrVertices[ linha ].setNome( linha );
						this.arrVertices[ linha ].setGrau( this.arrVertices[ linha ].getGrau() + 1 );
					}
					coluna++;
				}
				charAnterior = c;
			}
		}
		catch ( IOException IOE )
		{
			System.err.println( IOE.getMessage() );
			return false;
		}
		
		return true;
	}
	/*----------------------------------*/
	
	
	/** Busca por um vértice ainda não visitado e com grau maior que zero */
	public Vertice buscaVerticeNaoVisitado()
	{
		for ( int i = 1, total = this.getNumVertices(); i <= total; i++ )
		{
			if ( ! this.arrVertices[i].isVisitado() && this.arrVertices[i].getGrau() > 0 )
			{
				return this.arrVertices[i];
			}
		}
		
		return null;
	}
	/*--------------------------------------*/
	
	/** Busca um vértice pelo nome */
	public Vertice buscaVertice( int nome )
	{
		for ( int i = 1, total = this.getNumVertices(); i <= total; i++ )
		{
			if ( this.arrVertices[ i ].getNome() == nome )
			{
				return this.arrVertices[ i ];
			}
		}
		
		return null;
	}
	/*-------------------------------------------*/
	
	
	/** Busca os vizinhos do vértice v no grafo do objeto */
	public ArrayList<Vertice> buscaVizinhos( Vertice v )
	{
		ArrayList<Vertice> vizinhos = new ArrayList<Vertice>();
		
		for ( int i = 1, total = this.getNumVertices(); i <= total; i++ )
		{
			if ( this.matrizAdjacencia[ v.getNome() ][ i ].isAresta() )
			{
				Vertice vizinho = this.buscaVertice( i );
				
				if ( vizinho != null && ! vizinho.isVisitado() )
				{
					vizinhos.add( vizinho );
				}
			}
		}
		
		return vizinhos;
	}
	/*-------------------------------------*/
	
	
	/**
	 * Busca a quantidade de vértices que possui uma determinado grau
	 * Retorna o número de vértices de grau "grau".
	 */
	public static int buscaPorGrau( Grafo G, int grau )
	{
		int i;
		int total = 0;

		for ( i = 0; i < G.getNumVertices(); i++ )
		{
			if ( G.arrVertices[i].getGrau() == grau )
				total++;

		}

		return total;
	}
	/*----------------------------------*/
	
	
	public void removeVertice( int v )
	{
		Vertice objV = this.buscaVertice( v );
		Vertice objI;
		
		for ( int i = 1, total = this.getNumVertices(); i <= total; i++ )
		{
			if ( this.matrizAdjacencia[v][i].isAresta() )
			{
				objI = this.buscaVertice( i );
				this.matrizAdjacencia[v][i].setAresta( false );
				this.matrizAdjacencia[i][v].setAresta( false );
				this.numArestas--;
				objV.setGrau( objV.getGrau() - 1 );
				objI.setGrau( objI.getGrau() - 1 );
			}
		}
	}
	
	
	public void imprimeGrafo()
	{
		System.out.println( "|V(G)| = " + this.getNumVertices() + " | |E(G)| = " + this.getNumArestas() );
		for ( int i = 1, total = this.getNumVertices(); i <= total; i++ )
		{
			System.out.println( this.arrVertices[i].getNome() + " : visitado? " + this.arrVertices[i].isVisitado() );
		}
		for ( int i = 1, total = this.getNumVertices(); i <= total; i++ )
		{
			for ( int j = 1; j <= total; j++ )
			{
				System.out.print( ( this.matrizAdjacencia[i][j].isAresta() ? 1 : 0 ) + " " );
			}
			System.out.println();
		}
	}
	
	
	public int getNumVertices()
	{
		return this.numVertices;
	}
	/*-------------------------------------------*/
	
	
	public void setNumVertices( int numVertices )
	{
		this.numVertices = numVertices;
	}
	/*----------------------------------------*/
	
	
	public int getNumArestas()
	{
		return this.numArestas;
	}
	/*------------------------------------*/
	
	
	public void setNumArestas( int numArestas )
	{
		this.numArestas = numArestas;
	}
	/*------------------------------------------------*/
	
	
	
}
