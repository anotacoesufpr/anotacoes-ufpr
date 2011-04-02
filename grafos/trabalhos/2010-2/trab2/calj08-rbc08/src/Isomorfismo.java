import java.io.*;

public class Isomorfismo
{
	public static void main( String args [] )
	{
		FileReader FR;
		Grafo G1 = new Grafo();
		Grafo G2 = new Grafo();
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
			G1.leGrafo( FR );
			G2.leGrafo( FR );
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
		
		// verifica se G1 e G2 são isomorfos
		System.out.println( ( Isomorfismo.isIsomorfo( G1, G2 ) ? 1 : 0 ) );
	}
	
	
	
	/**
	 * Método que verifica se G1 e G2 são isomorfos
	 */
	public static boolean isIsomorfo( Grafo G1, Grafo G2 )
	{
		int maiorGrau = 0; /* Maior grau dos dois grafos */
		int [] relacao = new int[ G1.getNumVertices() + 1 ]; /* Array que armazena a relação entre vértices dos dois grafos, se forem isomorfos */
		int totalRelacoes = 0;
		
		/* Verifica se os dois grafos possuem os mesmos números de arestas e vértices */
		if ( G1.getNumVertices() != G2.getNumVertices() || G1.getNumVertices() != G2.getNumVertices() )
		{
			return false;
		}
		
		/* busca o maior grau dos grafos G1 e G2 */
		for ( int i = 1, total = G1.getNumVertices(); i <= total; i++ )
		{
			/* OBS: G1->vertices == G2->vertices  */

			if ( G1.arrVertices[ i ].getGrau() > maiorGrau )
				maiorGrau = G1.arrVertices[ i ].getGrau();

			if ( G2.arrVertices[ i ].getGrau() > maiorGrau )
				maiorGrau = G2.arrVertices[ i ].getGrau();
		}
		
		/* Compara os números de vértices de cada grau */
		for ( int i = 0; i <= maiorGrau; i++ )
		{
			if ( Grafo.buscaPorGrau( G1, i ) != Grafo.buscaPorGrau( G2, i ) )
			{
				return false;
			}
		}
		
		/* percorre cada vértice de G1 a fim de encontrar simétrico em G2 */
		for ( int i = 1, total = G1.getNumVertices(); i <= total; i++ )
		{
			/* Busca em G2 um vértice simétrico ao vértice i de G1 */
			/* O simétrico de "vertice" em G2 deve ter o mesmo grau de "vertice" */
			for ( int j = 1, total2 = G2.getNumVertices(); j <= total2; j++ )
			{
				if ( G2.arrVertices[j].getGrau() == G1.arrVertices[i].getGrau() )
				{
					if ( ! Isomorfismo.inArray( j, relacao ) )
					{
						relacao[i] = j;
						totalRelacoes++;
						break;
					}
				}
			}
		}
		
		return ( totalRelacoes == G1.getNumVertices() );
	}
	
	
	public static boolean inArray( int x, int [] arr )
	{
		for ( int i = 0; i < arr.length; i++ )
		{
			if ( arr[i] == x )
			{
				return true;
			}
		}

		return false;
	}
	
	
	
}
