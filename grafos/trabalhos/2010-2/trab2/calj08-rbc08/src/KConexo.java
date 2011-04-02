import java.io.*;
import java.util.ArrayList;

public class KConexo
{
	public static void main( String [] args )
	{
		Grafo G = new Grafo();
		int k = 0, intChar = 0;
		char kChar = (char)0;
		FileReader FR;
		String filename;
		
		
		if ( args.length != 1 )
		{
			System.err.println( "Erro. O primeiro parâmetro deve ser o nome do arquivo com o grafo." );
			System.exit( 1 );
		}

		filename = args[0];

		try
		{
			FR = new FileReader( filename );
			
			// Lê o valor de k
			intChar = FR.read();
			kChar = ( (char) intChar );
			k = Integer.parseInt( new String( kChar + "" ) );
			
			// Lê o \n para mover o ponteiro do arquivo para o início do grafo
			intChar = FR.read();
			
			G.leGrafo( FR );
			FR.close();
		}
		catch ( FileNotFoundException FNFE )
		{
			System.err.println( FNFE.getMessage() );
		}
		catch ( IOException IOE )
		{
			System.err.println( IOE.getMessage() );
		}
		
		System.out.println( ( KConexo.isKConexo( G, k ) ? 1 : 0 ) );
		
	}
	
	/*
	 * O algoritmo consiste em fazer uma busca em largura em grafos semelhantes ao grafo G, porém
	 * com conjuntos de vértices removidos. Esses conjuntos são todas as combinações simples dos
	 * vértices de G 1 a 1, 2 a 2... até (k-1) a (k-1)
	 * A remoção do vértice não é completa, noutras palavras, removem-se as arestas incidentes aos
	 * vértices que devem ser removidos, mas mantém-se os vértices no grafo. Foi decidido isso pois
	 * facilita a análise do resultado final, uma vez que nao é necessário remontar o grafo, com os
	 * vértices removidos.
	 * A Busca em Largura modifica o estado de visitado dos vértices. Logo, após cada busca, verifica-se
	 * se os vértices não visitados são somente os vértices removidos. Se houver algum não visitado
	 * que não seja um dos removidos. o grafo não é k-conexo
	 */
	public static boolean isKConexo( Grafo G, int k )
	{
		CombinationGenerator CG;
		int [] arr;
		Grafo localG;
		int i, j;
		
		// um grafo só pode ser k-conexo, se for conexo.
		// Logo, fazemos uma busca em largura e verificamos se o retorno é um ArrayList vazio
		localG = G.clonaGrafo();
		BuscaEmLargura.BuscaEmLargura( localG );
		
		// verifica se todos os vértices foram visitados
		for ( i = 1; i <= localG.getNumVertices(); i++ )
		{
			if ( ! localG.arrVertices[i].isVisitado() )
			{
				return false;
			}
		}
		
		// retira combinações de de 1 a (k-1) vértices, para verificar se o grafo
		// continua conexo      
		for ( i = 1; i < k; i++ )
		{       
			CG = new CombinationGenerator( G.getNumVertices(), i );
			
			while ( CG.hasMore() )
			{
				localG = (Grafo) G.clonaGrafo();
				arr = CG.getNext();
				
				for ( j = 0; j < i; j++ )
				{
					localG.removeVertice( localG.arrVertices[ arr[j] ].getNome() + 1 );
				}
				
				BuscaEmLargura.BuscaEmLargura( localG );
				
				// verifica os não visitados
				for ( j = 1; j < localG.getNumVertices(); j++ )
				{
					// se [j] não foi visitado, verifica se é um dos vértices removidos
					if ( ! localG.arrVertices[j].isVisitado() )
					{
						boolean foiRemovido = false;
						for ( int cont = 0; cont < i; cont++ )
						{
							if ( localG.arrVertices[j].getNome() == (localG.arrVertices[ arr[cont] ].getNome() + 1) )
							{
								foiRemovido = true;
							}
						}
						
						if ( ! foiRemovido )
						{
							return false;
						}
					}
				}
			}
		}

		return true;
	}
	
}
