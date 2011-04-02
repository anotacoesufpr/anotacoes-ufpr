public class Vertice implements Cloneable
{
	private boolean visitado;
	private int nome;
	private int grau;
	
	
	public Vertice() {}
	/*---------------------------------*/
	
	
	public Vertice( int nome )
	{
		this.setNome( nome );
	}
	/*------------------------------------------*/
	
	
	public Vertice( int nome, boolean visitado )
	{
		this.setNome( nome );
		this.setVisitado( visitado );
	}
	/*--------------------------------*/
	
	
	public Vertice( int nome, int grau, boolean visitado )
	{
		this.setNome( nome );
		this.setGrau( grau );
		this.setVisitado( visitado );
	}
	
	
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
	
	
	public boolean isVisitado()
	{
		return this.visitado;
	}
	/*------------------------------------------*/
	
	
	
	public void setVisitado( boolean visitado )
	{
		this.visitado = visitado;
	}
	/*------------------------------------------*/
	
	
	public int getNome()
	{
		return this.nome;
	}
	/*--------------------------------------*/
	
	
	public void setNome( int nome )
	{
		this.nome = nome;
	}
	/*-------------------------------------------*/
	
	
	public int getGrau()
	{
		return this.grau;
	}
	/*---------------------------------------------*/
	
	
	public void setGrau( int grau )
	{
		this.grau = grau;
	}
}
