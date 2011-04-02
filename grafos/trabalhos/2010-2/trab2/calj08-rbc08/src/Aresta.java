public class Aresta implements Cloneable
{
	/* extremos da aresta */
	private Vertice v1;
	private Vertice v2;
	
	/* define se a aresta foi visitada a partir de v1 */
	private boolean visitada;
	
	/* define se existe a aresta */
	private boolean aresta;
	
	/* define se é aresta do tipo árvore */
	private boolean tipoArvore;
	
	
	public Aresta()
	{
		// se não definir v1 e v2, inicialmente a aresta não existe
		this.setAresta( false );
	}
	/*-----------------------------------*/
	
	public Aresta( Vertice v1, Vertice v2 )
	{
		this.setV1( v1 );
		this.setV2( v2 );
		this.setAresta( true ); // se existe v1 e v2, a aresta existe
		this.setTipoArvore( false );
	}
	/*----------------------------------------*/
	
	
	/**
	 * Sobrescreve o método clone(), de Object
	 */
	public Object clone()
	{
		try
		{
			return super.clone();
		}
		catch( CloneNotSupportedException e )
		{
			System.err.println( "Clonagem não suportada: " + e.getMessage() );
			return null;
		}
	}
	/*------------------------------------*/
	
	
	public Vertice getV1()
	{
		return this.v1;
	}
	/*-----------------------------------*/

	
	public void setV1( Vertice v1 )
	{
		this.v1 = v1;
	}
	/*---------------------------------------*/
	

	public Vertice getV2()
	{
		return this.v2;
	}
	/*------------------------------------*/
	

	public void setV2( Vertice v2 )
	{
		this.v2 = v2;
	}
	/*-------------------------------------*/
	

	public boolean isVisitada()
	{
		return this.visitada;
	}
	/*-----------------------------------------*/
	

	public void setVisitada( boolean visitada )
	{
		this.visitada = visitada;
	}
	/*-----------------------------------------*/
	

	public boolean isAresta()
	{
		return this.aresta;
	}
	/*---------------------------------------*/
	

	public void setAresta( boolean aresta )
	{
		this.aresta = aresta;
	}
	/*------------------------------------------*/
	

	public boolean isTipoArvore()
	{
		return this.tipoArvore;
	}
	/*----------------------------------------*/
	

	public void setTipoArvore( boolean tipoArvore )
	{
		this.tipoArvore = tipoArvore;
	}
	/*---------------------------------------------*/
	
	
}
