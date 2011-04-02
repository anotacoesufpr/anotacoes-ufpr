%% Usando o SWI-Prolog

% Vias terrestres:

vt(a,b,4).
vt(b,e,6).
vt(a,c,23).
vt(a,g,13).
vt(c,d,54).
vt(d,e,30).
vt(e,f,17).
vt(f,g,45).
vt(j,k,75).
vt(j,l,75).
vt(k,h,75).
vt(k,i,211).
vt(i,h,142).
vt(m,n,101).
vt(m,o,138).
vt(m,r,17).
vt(n,o,23).
vt(r,q,23).
vt(q,p,15).
vt(p,o,12).

% Vias aereas:

va(e, j, 3).
va(e, m, 87).
va(j, m, 9).

%%%%%%%%%%%%%%%%%%-----------------------------%%%%%%%%%%%%%%%%%%%

% uniao de duas listas que contem elementos distintos entre si.
une([],L,L).

% Este predicado faz a uniao das listas, desde que nao existam elementos em
% comum entre elas.
une([X|Cauda],L,[X|Resultado]):-
        not(pertence_a(X,L)),
        une(Cauda,L,Resultado).

% Este predicado proporciona diferentes opcoes de lista, caso a primeira solucao
% dada nao seja aceita. Aqui, podem existir elementos repetidos.
une([_|Cauda],L,Resultado):-
        une(Cauda,L,Resultado).


% insere um elemento presente numa lista, retornando a lista contendo o elemento
% adicionado. *Insere no final da lista.
% listas examinada
insercao(X,[],[X]).
insercao(X,[S|Cauda],Resultado) :-
        intersecao(X,S),
        une(X,S,Nova),
        insercao(Nova,Cauda,Resultado).
insercao(X,[S|Cauda],[S|Resultado]) :-
        insercao(X,Cauda,Resultado).


% concatena - Adivinha xD
concatena([], L, L).
concatena([X|Cauda1],L2,[X|Cauda3]):-
        concatena(Cauda1,L2,Cauda3).

% subculturas - encontram as cidades de um mesmo pais. Na verdade inverte a
% ordem dos elementos de uma lista, colocando essa lista invertida em outra
% lista.
subculturas([],[]).
subculturas([Cabeca|Cauda],Normal) :-
        subculturas(Cauda,SubC),
        insercao(Cabeca,SubC,Normal).

% pertence_a - verifica se um elemento pertence a uma lista
pertence_a(X, [X|_]).
pertence_a(X,[_|Cauda]):-
        pertence_a(X,Cauda).

% intersecao - Verifica duas listas possuem algum elemento em comum
intersecao([X|_],L):-
        pertence_a(X,L).
intersecao([_|Cauda],L):-
        intersecao(Cauda,L).


% Funcs auxiliares (economiza 1 chamada (pro usuario)):
vt_aux(X, Y, Z):-vt(X, Y, Z).
vt_aux(X, Y, Z):-vt(Y, X, Z).
va_aux(X, Y, Z):-va(X, Y, Z).
va_aux(X, Y, Z):-va(Y, X, Z).

%%%%%%%%%%%**********************************%%%%%%%%%%%%%%%%%%%
% Descobrindo os aerportos:
aeroporto(V, [Sub|_], A):-
		pertence_a(V,Sub),
		va_aux(A,_,_),
		pertence_a(A,Sub).
aeroporto(V,[_|Cauda],A):-
		aeroporto(V,Cauda,A).
aeroporto(_,[],_):- !,fail.


% caminho - Funcao principal do trabalho
caminho(Vert_inicial, Vert_final, Caminho):-
		dijkstra(Vert_inicial, Estruturas),
		member(e(Vert_final, _, Caminho), Estruturas), !.

caminho(Vert_inicial, Vert_final, Caminho):-
		findall(A,vt_aux(A,_,_),Lt),
		pertence_a(Vert_inicial, Lt),
		pertence_a(Vert_final,Lt),

		findall([C1,C2],vt(C1,C2,_),L1),
		subculturas(L1,L),
		caminho2(Vert_inicial, Vert_final, L, Aero_i, Aero),

		dijkstra(Vert_inicial, E1),
		member(e(Aero_i, _, Cam1), E1),

		dijkstra(Aero, E2),
		member(e(Vert_final, _, Cam2), E2),

		concatena(Cam1, Cam2, Caminho), !.

caminho2(Vert_inicial, Vert_final, Subculturas, Aeroporto_i, Aeroporto):-
		aeroporto(Vert_inicial, Subculturas, Aeroporto_i),
		aeroporto(Vert_final, Subculturas, Aeroporto).

% dijkstra(Vert_inicial, Estruturas) - Estruturas serao uma lista de estruturas
% e(Vert_final, Dist, Cam), contendo o menor caminho entre Vert_inicial e Vert_final
dijkstra(Vert_final, Estruturas):-
		criar_estruturas(Vert_final, [Vert_final], L),
		dijkstra_1(L, [e(Vert_final, 0, [Vert_final])], Estruturas).

dijkstra_1([], Estruturas, Estruturas).
dijkstra_1([D|L], Estruturas0, Estruturas):-
		escolhido(L, D, E),
		apagar([D|L], [E], L1),
		E = e(Vert_final, Distancia, Caminho),
		reverse([Vert_final|Caminho], Caminho1),
		unir_structs(Estruturas0, [e(Vert_final, Distancia, Caminho1)], Estruturas1),
		criar_estruturas(Vert_final, [Vert_final|Caminho], L2),
		apagar(L2, Estruturas1, L3),
		relaxacao(L3, Distancia, L4),
		unir_structs(L1, L4, L5),
		dijkstra_1(L5, Estruturas1, Estruturas).

% criar_estruturas(Inicial, Caminho, L)
% L sera uma lista de estruturas e(Vert, Dist, Cam), para cada vertice vizinho de Inicial
criar_estruturas(Inicial, Caminho, L):-
		setof(e(Vert,D,Caminho), vt_aux(Inicial,Vert,D), L),
		!.
criar_estruturas(_, _, []).

% escolhido(L, D0, D) - D sera a estrutura e(V, D, C) com a menor distancia
escolhido([], Melhor, Melhor).
escolhido([D|L], Melhor0, Melhor):-
		menor(D, Melhor0), !,
		escolhido(L, D, Melhor).
escolhido([_|L], Melhor0, Melhor):-
		escolhido(L, Melhor0, Melhor).

% menor
menor(e(_, X, _), e(_, Y, _)):-X < Y.

% apagar - L3 tera os elementos de L1 apagando os elementos iguais aos de L2
apagar([], _, []).
apagar([X|L1], [], [X|L1]):-!.
apagar([X|L1], [Y|L2], L3):-
		igual(X, Y), !,
		apagar(L1, L2, L3).
apagar([X|L1], [Y|L2], [X|L3]):-
		menor_que(X, Y), !, apagar(L1, [Y|L2], L3).
apagar([X|L1], [_|L2], L3):-
		apagar([X|L1], L2, L3).

% unir_structs - junta em L3 as estruturas de L1 com as de L2 se L1 e L2 tem
% estruturas do mesmo vertice, a que tiver menor distancia estara em L3
unir_structs([], L2, L2).
unir_structs([X|L1], [], [X|L1]):-!.
unir_structs([X|L1], [Y|L2], [X|L3]):-
		igual(X, Y), menor(X, Y), !,
		unir_structs(L1, L2, L3).
unir_structs([X|L1], [Y|L2], [Y|L3]):-
		igual(X, Y), !,
		unir_structs(L1, L2, L3).
unir_structs([X|L1], [Y|L2], [X|L3]):-
		menor_que(X, Y), !,
		unir_structs(L1, [Y|L2], L3).
unir_structs([X|L1], [Y|L2], [Y|L3]):-
		unir_structs([X|L1], L2, L3).

igual(e(X, _, _), e(X, _, _)).

menor_que(e(X, _, _), e(Y, _, _)):-X @< Y.

% relaxacao(L1, Incr, L2)
% promove uma rodada de relaxacao
relaxacao([], _, []).
relaxacao([e(V, D1, C)|L1], Incr, [e(V, D2, C)|L2]):-
		D2 is D1 + Incr,
		relaxacao(L1, Incr, L2).

