% Tem ordem trocada:
% Verifica se os elementos numericos de uma lista estao em ordem decrescente.

pertence_a([],[]).
pertence_a(X,[X|L]).
pertence_a(X,[_|L]):-
    pertence_a(X,L).

tem_ordem_trocada([X|L]):-
    integer(X),
    pertence_a(Z,L),
    integer(Z),
    X > Z.

tem_ordem_trocada([_|L]):-
    tem_ordem_trocada(L).

