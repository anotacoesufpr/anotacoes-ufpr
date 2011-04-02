/*
	Autor: Roberto Beraldo Chaiben - GRR20084213 - rbc08

	Compilador Prolog: SWI-Prolog
	
total_de_ordens([[h,e],[h,d],[f,e],[g,d],[g,c],[e,a],[e,b],[e,c],[d,b]], T).
*/



/*===========================*/
/*   Estruturas de dados     */
/*===========================*/

/* Vértices */
:- dynamic vertice/1.

/* Arestas */
:- dynamic aresta/2.

/* Vértices que só têm arestas de saída (zero ancestrais) */
:- dynamic verticesSaida/1.



/*=============================*/
/*        Predicados           */
/*=============================*/


/* verifica o total de Ordens Topológicas */
/* \+ buscaSaida(_) força retorno de TRUE */
total_de_ordens( Grafo, T ):-
	percorre( Grafo ),
	\+ buscaVerticesDeSaida(_),
	T is 1.
/*-------------------------------------*/


/* Adiciona vértices à estrutura de dados, evitando repetições */
/* 
	\+ => not
	; => OR
*/
addVertice( X ):-
	(\+ vertice( X ),
	assert( vertice( X ) ));
	vertice(X).
/*-------------------------------------------*/



/* Percorre o grafo do parâmetro e define os vértices e as arestas */
percorre([]).

percorre( [X | Y] ):-
	percorre2( X ),
	percorre( Y ).

percorre2([X, Y]):-
	addVertice( X ),
	addVertice( Y ),
	assert(aresta( X, Y )).
/*------------------------------------------*/


/* Busca vértices que só tenham arestas de sáida */
/* O "fail" do final força o backtracking, a fim de encontrar todas as possibilidades */
buscaVerticesDeSaida( X ):-
	aresta( X, _ ),
	\+ aresta( _, X ),
	\+ verticesSaida( X ),
	assert( verticesSaida( X ) ),
	fail.
/*------------------------------------------------*/


/* Busca as adjacencias de um vértice */
adjacencias( V, W ):-
	aresta( V, V2 ),
	W = V2.


/* Verifica se X é ancestral de Y */
ancestral( X, Y ) :-
	aresta( X, Y ).

ancestral( X, Y ) :-
	aresta( Z, Y ),
	ancestral( X, Z ).



/* Limpa a base de dados do Prolog usada no programa */
limpa(_):-
	retractall( vertice(_) ),
	retractall( aresta(_,_) ),
	retractall( verticesSaida(_) ).
	
	
