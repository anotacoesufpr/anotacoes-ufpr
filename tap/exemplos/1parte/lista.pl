% Swi-prolog
% Se nao comentar, o vim nao reconhece a sintaxe (pq pode ser perl).
n_elementos([],0).

n_elementos([X|Y],N):-
	n_elementos(Y,NY),
	N is 1+NY.

soma([],0).

soma([X|Y],S):-
	soma(Y,SY),
	S is X+SY.

media(Lista,Media):-
	n_elementos(Lista,Num_elem),
	soma(Lista,S),
	Media is S/Num_elem.

% Tem um append no prolog que usa somente listas, coloquei aqui um que faz o
% append de um elemento soh.
insere_fim(X,[],[X]).
insere_fim(Elem,[Cabeca|Cauda],[Cabeca|NovaLista]):-
    insere_fim(Elem,Cauda,NovaLista).


inverte([],[],[]).
inverte([C1|L1],[C2|L2],R):-
    
