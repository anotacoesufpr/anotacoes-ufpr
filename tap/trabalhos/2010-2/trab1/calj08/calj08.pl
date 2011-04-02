/*
	Autor: Carlos Augusto Ligmanowski Junior - GRR20081238 - calj08

	Compilador Prolog: SWI-Prolog
	
	Programa que retorna o número de ordens topológicas possíveis a partir de um grafo G.
	
	Ex: total_de_ordens([[a,b],[a,c],[a,d],[a,e],[a,f],[a,g],[a,h]], T).
	    T = 5040 .

	Obs: Sou iniciante em programação em lógica , então certamente existem algoritmos MUITO mais eficazes =D. Para executar o programa ,
só passar um Grafo de acordo com o exemplo e ele retornará em T o numero de ordens topológicas possíveis. Para ver todas as ordens , 
execute total_de_ordens_mantendo, ao invés de total_ordens e faça : 

listing(lista).


*/

/*
	
	
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

/* Listas Ordem Topologica */
:- dynamic lista/1.



/*=============================*/
/*        Predicados           */
/*=============================*/


/* verifica o total de Ordens Topológicas */
/* \+ buscaSaida(_) força retorno de TRUE */
total_de_ordens( Grafo, T ):-
	percorre( Grafo ),
	\+ buscaVerticesDeSaida(_),
	(fazLista(_);
	contaOrdens(T,0)),
	limpa(_),!.
/*-------------------------------------*/

/* Esse mantem o grafo , com todas as informações: vertices, arestas, listas de ordem topológica.*/
total_de_ordens_mantendo( Grafo, T ):-
	percorre( Grafo ),
	\+ buscaVerticesDeSaida(_),
	\+fazLista(_),!.

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


/* Busca vértices que só tenham arestas de saida */
/* O "fail" do final força o backtracking, a fim de encontrar todas as possibilidades */
buscaVerticesDeSaida( X ):-
	aresta( X, _ ),
	\+ aresta( _, X ),
	\+ verticesSaida( X ),
	assert( verticesSaida( X ) ),
	fail.
/*------------------------------------------------*/

/* Retorna em T o numero de vértices.
   Modo de funcionamento: Vai jogando os vertices em uma lista para forçar o backtrack com o "jafoi" e vai incrementando o 
contador para retornar no final o numero de vertices.*/

tam(T,I,L):-
	vertice(Z),
	\+jafoi(Z,L),
	cons(Z,L,L1),
	T1 is I+1,
	tam(T,T1,L1),!;
	T = I.
/*-------------------------------------------*/

/*Adiciona X na lista Y, retorna a lista resultante.*/		
cons(X, Y, [X|Y]).

/*-------------------------------------------*/

/*Monta uma lista inicial com um dos vertices de saida */

listaInicial(L):-
	verticesSaida(X),
	cons(X,[],L).
/*-------------------------------------------*/


/*A partir da lista inicial , chama o predicado comeca que monta as listas de ordem.*/	
fazLista(_) :-
	tam(S,0,[]),
	listaInicial(L),
	comeca(L,L1,S).

/*-------------------------------------------*/
	
/*A partir de uma lista inicial L , adiciona um vértice que "podemir" na lista e faz isso novamente , até todos os vertices terem ido.
  O parâmetro S é o numero de vertices . Foi necessário ele para que o backtracking pegasse somente as listas completas, ou seja, com todos os 
vertices. Ao termino do "começa" , junto ao "fazLista" , forma-se atomos com todas as listas de ordem possiveis. Nome de é lista. Verifica-se as listas 
fazendo : listing(lista).
Obs: inverte a lista porque o cons controi uma lista ao contrario */
comeca(L,L1,S) :-
	podemir(X,L),
	cons(X,L,L1),
	comeca(L1,Z,S);(length(L,S),inverte(L,R,[]),assert(lista(R)),fail).

/*-------------------------------------------*/

/*Aqui conta quantas listas tem. Fiz o retract para o backtracking não entrar em loop na recursão. Com certeza tem um jeito melhor de contar o numero de listas, 
mas aqui eu só consegui ter essa idéia =D . 

Obs: Após a execução dele , perde-se os atomos com as listas. Para recuperá-los , só fazer fazLista(_) denovo . */
contaOrdens(T,I):-
	lista(L),
	T2 is I+1,
	retract(lista(X)),
	contaOrdens(T,T2),!;T is I.

/*-------------------------------------------*/
	
/*Passa um vertice em X e uma lista vazia em Z , então em L retorna uma lista com as adjacencias do vertice X*/	

foianc(X,L,Z):-
	(aresta(Y,X),
	\+jafoi(Y,Z),
	cons(Y,Z,T),
	foianc(X,L,T)),!;
	L = Z.

/*-------------------------------------------*/

/*Verifica se os elementos de uma lista estão contidos em outra lista*/
verifica([],_).

verifica([H|C],L):-
	jafoi(H,L),
	verifica(C,L).

/*-------------------------------------------*/

/*A partir de uma lista L , retorna em X um vértice que pode ir , seguindo a ordem topológica do grafo. Com backtracking, retorna todos 
os vértices que podem ir a partir da lista L */
podemir(X,L) :-
	(vertice(X),
	foianc(X,L1,[]),
	\+ L1 = [],
	verifica(L1,L),
	\+jafoi(X,L));
	(verticesSaida(X),
	\+ jafoi(X,L)). 

/*-------------------------------------------*/

/*Verifica se X "jafoi" na lista*/
jafoi(X, [X | Cauda]).

jafoi(X, [Cabeca | Cauda]) :- 
	jafoi(X, Cauda).

/*-------------------------------------------*/

/*inverte uma lista*/
inverte([],L,L).
inverte([H|C],Z,L1) :-
	cons(H,L1,R),
	inverte(C,Z,R),!;
	Z = L1.

/*-------------------------------------------*/

/* Limpa a base de dados do Prolog usada no programa */
limpa(_):-
	retractall( vertice(_) ),
	retractall( aresta(_,_) ),
	retractall( verticesSaida(_) ),
	retractall( lista(_) ).
	
	
