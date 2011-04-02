import java.util.*;

public class BuscaEmLargura
{
	/**
	 * Faz busca largura em um grafo
	 * @param G Grafo em que a busca será feita
	 */
	public static boolean BuscaEmLargura( Grafo G )
	{
		Queue<Vertice> FilaVertices = new LinkedList<Vertice>();
		Vertice v;
		
		v = G.buscaVerticeNaoVisitado();
		
		if ( v == null )
		{
			return false;
		}
		
		FilaVertices.add( v );
		
		while ( ! FilaVertices.isEmpty() )
		{
			v = FilaVertices.remove();
			v.setVisitado( true );
			ArrayList<Vertice> vizinhos = G.buscaVizinhos( v );
			
			for ( int i = 0, total = vizinhos.size(); i < total; i++ )
			{
				Vertice w = vizinhos.get( i );

				if ( ! w.isVisitado() )
				{
					w.setVisitado( true );
					FilaVertices.add( w );
				}
			}
		}
		
		return true;
	}
}