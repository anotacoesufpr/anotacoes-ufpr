listificada([],[]).

listificada([X|L1],[[X]|L2]):-
    listificada(L1,L2).

lista_dobro([],[]).

lista_dobro([X|L1],[Y,L2]):-
    Y is X*2,
    lista_dobro(L1,L2).

no(Palavra,[],0).

no(Palavra,[Palavra|L1],Y):-
    no(Palavra,L1,Num_o),
    Y is Num_o + 1.

no(Palavra,[Cabeca,Cauda],Num_ocorrencias):-
    no(Palavra,Cauda,Num_ocorrencias).

todas_antes(Palavra,[],[]).

todas_antes(Palavra,[Palavra|_],[]).

