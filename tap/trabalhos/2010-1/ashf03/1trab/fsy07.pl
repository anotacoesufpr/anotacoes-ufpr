% Usado SWI-prolog
% ta ae vlws

via_terrestre(a,b,4).
via_terrestre(b,e,6).
via_terrestre(a,c,23).
via_terrestre(a,g,13).
via_terrestre(c,d,54).
via_terrestre(d,e,30).
via_terrestre(e,f,17).
via_terrestre(f,g,45).
via_terrestre(j,k,75).
via_terrestre(j,l,75).
via_terrestre(k,h,75).
via_terrestre(k,i,211).
via_terrestre(i,h,142).
via_terrestre(m,n,101).
via_terrestre(m,o,138).
via_terrestre(m,r,17).
via_terrestre(n,o,23).
via_terrestre(r,q,23).
via_terrestre(q,p,15).
via_terrestre(p,o,12).
via_aerea(e,j,3).
via_aerea(e,m,87).
via_aerea(j,m,9).

% Caminho de A para B ou B para A
terra(A, B, Z):-via_terrestre(A, B, Z).
terra(A, B, Z):-via_terrestre(B, A, Z).

% Caminho de A para B ou B para A
ar(A, B, Z):-via_aerea(A, B, Z).
ar(A, B, Z):-via_aerea(B, A, Z).

% Cria uma lista de estruturas com caminho de A ate todos os outros pontos possiveis
dijkstra(A, ListaCaminhos):-
  create(A, [A], Ds),
  dijkstra_1(Ds, [s(A,0,[])], ListaCaminhos).

dijkstra_1([], ListaCaminhos, ListaCaminhos).
dijkstra_1([D|Ds], Ss0, ListaCaminhos):-
  best(Ds, D, S),
  delete([D|Ds], [S], Ds1),
  S=s(Vertex,Distance,Path),
  reverse([Vertex|Path], Path1),
  merge(Ss0, [s(Vertex,Distance,Path1)], Ss1),
  create(Vertex, [Vertex|Path], Ds2),
  delete(Ds2, Ss1, Ds3),
  incr(Ds3, Distance, Ds4),
  merge(Ds1, Ds4, Ds5),
  dijkstra_1(Ds5, Ss1, ListaCaminhos).

% Retorna A para o caminho se A = B						
path(A, B, [A]) :-				
  A = B.
 
% Procura menor caminho entre A e B,
% Cria caminho de A para todos os outros pontos possiveis e
% Procura na lista de caminhos de A se B se encontra no mesmo						
path(A, B, Caminho):-				
  dijkstra(A, Ss),   	                        
  member(s(B,_,Caminho), Ss), !.      	

% minha parte ------------------

% Concatena 2 caminhos entre paises
concatena([], L, L).
concatena([X|Cauda1], L2, [X|Cauda3]) :-
	concatena(Cauda1, L2, Cauda3).

caminho(A, B, Caminho) :-
	path(A, B, Caminho).	

% 1 ate 2

caminho(A, B, Caminho) :-
	path(A, e, Caminho1),
	path(m, B, Caminho2),
	concatena(Caminho1, Caminho2, Caminho).

% 2 ate 1

caminho(A, B, Caminho) :-
	path(A, m, Caminho1),
	path(e, B, Caminho2),
	concatena(Caminho1, Caminho2, Caminho).

% 1 ate 3

caminho(A, B, Caminho) :-
	path(A, e, Caminho1),
	path(j, B, Caminho2),
	concatena(Caminho1, Caminho2, Caminho).

% 3 ate 1

caminho(A, B, Caminho) :-
	path(A, j, Caminho1),
	path(e, B, Caminho2),
	concatena(Caminho1, Caminho2, Caminho).


% 2 ate 3

caminho(A, B, Caminho) :-
	path(A, j, Caminho1),
	path(m, B, Caminho2),
	concatena(Caminho1, Caminho2, Caminho).

% 3 ate 2

caminho(A, B, Caminho) :-
	path(A, m, Caminho1),
	path(j, B, Caminho2),
	concatena(Caminho1, Caminho2, Caminho).


% minha parte ------------------

% Cria a lista de Camihos de A
create(A, Caminho, Z):-
  setof(s(X,Y,Caminho), terra(A,X,Y), Z), !.
create(_, _, []).

best([], Best, Best).
best([Edge|Edges], Best0, Best):-
  shorter(Edge, Best0), !,
  best(Edges, Edge, Best).
best([_|Edges], Best0, Best):-
  best(Edges, Best0, Best).

shorter(s(_,X,_), s(_,Y,_)):-
   X < Y.

delete([], _, []). 
delete([X|Xs], [], [X|Xs]):-!. 
delete([X|Xs], [Y|Ys], Ds):-
  eq(X, Y), !, 
  delete(Xs, Ys, Ds). 
delete([X|Xs], [Y|Ys], [X|Ds]):-
  lt(X, Y), !, delete(Xs, [Y|Ys], Ds). 
delete([X|Xs], [_|Ys], Ds):-
  delete([X|Xs], Ys, Ds). 
  
merge([], Ys, Ys). 
merge([X|Xs], [], [X|Xs]):-!. 
merge([X|Xs], [Y|Ys], [X|Zs]):-
  eq(X, Y), shorter(X, Y), !, 
  merge(Xs, Ys, Zs).
merge([X|Xs], [Y|Ys], [Y|Zs]):-
  eq(X, Y), !, 
  merge(Xs, Ys, Zs).
merge([X|Xs], [Y|Ys], [X|Zs]):-
  lt(X, Y), !, 
  merge(Xs, [Y|Ys], Zs).
merge([X|Xs], [Y|Ys], [Y|Zs]):-
  merge([X|Xs], Ys, Zs).

eq(s(X,_,_), s(X,_,_)).  

lt(s(X,_,_), s(Y,_,_)):-
   X @< Y.

% Eh incrementado o valor da distancia
incr([], _, []).  
incr([s(V,D1,P)|Xs], Incr, [s(V,D2,P)|Ys]):-
  D2 is D1 + Incr,
  incr(Xs, Incr, Ys).

