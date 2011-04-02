#include "vertice.h"

Vertice::Vertice() {}
/*-----------------------------------------*/


Vertice::Vertice( unsigned int nome )
{
	this->setNome( nome );
}
/*--------------------------------------------------*/


Vertice::Vertice( unsigned int nome, bool visitado )
{
	this->setNome( nome );
	this->setVisitado( visitado );
}
/*--------------------------------------------------*/

/* fp é opcional */
void Vertice::exibir( FILE *fp )
{
	fprintf( fp, "%d", this->getNome() );
}
/*--------------------------------------*/


void Vertice::setVisitado( bool visitado )
{
	this->visitado = visitado;
}
/*--------------------------------------*/



void Vertice::setNome( unsigned int nome )
{
	this->nome = nome;
}
/*-------------------------------*/




bool Vertice::isVisitado()
{
	return this->visitado;
}
/*---------------------------------------------*/



unsigned int Vertice::getNome()
{
	return this->nome;
}
/*---------------------------------------*/


