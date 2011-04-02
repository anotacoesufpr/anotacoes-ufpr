% Intersecao entre 2 listas

pertence_a([],[]).
pertence_a(X,[X|L]).
pertence_a(X,[_|L]):-
    pertence_a(X,L).

tem_intersecao([],[]).
tem_intersecao([X|T],L):-
    pertence_a(X,L).
tem_intersecao([_|T],L):-
    tem_intersecao(T,L).
