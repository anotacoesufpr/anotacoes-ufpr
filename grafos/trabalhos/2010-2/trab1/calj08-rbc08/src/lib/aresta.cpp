#include "aresta.h"


Aresta::Aresta()
{
	// por padrão o construtor define a inexistência da aresta
	this->setAresta( false );
	this->setTipoArvore( false );
}
/*---------------------------------------*/


void Aresta::setVisitada( bool visitada )
{
	this->visitada = visitada;
}
/*------------------------------------*/


void Aresta::setAresta( bool aresta )
{
	this->aresta = aresta;
}
/*------------------------------------*/


void Aresta::setV1( Vertice v1 )
{
	this->v1 = v1;
}
/*-----------------------------------------*/



void Aresta::setV2( Vertice v2 )
{
	this->v2 = v2;
}
/*-----------------------------------------*/


void Aresta::setTipoArvore( bool tipoArvore )
{
	this->tipoArvore = tipoArvore;
}
/*-----------------------------------------*/

		
bool Aresta::isVisitada()
{
	return this->visitada;
}
/*----------------------------------*/


bool Aresta::isAresta()
{
	return this->aresta;
}
/*----------------------------------*/


Vertice Aresta::getV1()
{
	return this->v1;
}
/*------------------------------*/

Vertice Aresta::getV2()
{
	return this->v2;
}
/*--------------------------------*/


bool Aresta::isTipoArvore()
{
	return this->tipoArvore;
}
/*---------------------------------*/
