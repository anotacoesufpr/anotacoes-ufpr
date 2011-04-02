% Construir um predicado que inverta uma lista de elementos

concatena([],L,L).
concatena([X|L1],L2,[X|L3]):-
    concatena(L1,L2,L3).

invertida([],[]).

invertida([X|L],L2):-
    invertida(L,L3),
    concatena(L3,[X],L2).
