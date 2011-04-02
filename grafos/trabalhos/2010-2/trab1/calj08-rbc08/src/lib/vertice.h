#ifndef _VERTICE_H
#define _VERTICE_H

/**
 * Classe que representa um vértice
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>

// define os caracteres que serão exibidos para informar se o vértice é de árvore ou não-árovore
#define CHAR_ARVORE 'a'
#define CHAR_NAOARVORE 'n'

class Vertice
{
	private:
		/** Define se o vértice foi visitado ou não */
		bool visitado;
		
		/** Nome do vértice (tratado como inteiro) */
		unsigned int nome;
		

	public:
		Vertice();
		Vertice( unsigned int );
		Vertice( unsigned int, bool );

		/**
		 * Exibe o nome do vértice
		 * @param arquivo (Opcional) Arquivo onde deve ser impresso (stdout por padrão)
		*/
		void exibir( FILE *fp = stdout );

		void setVisitado( bool );
		void setNome( unsigned int );
		bool isVisitado();
		unsigned int getNome();
		
};

#endif
