% Sequencia de fibonacci: o valor passado para a fcao, representa o n-esimo
% elemento da sequencia.

fibo(1,1).

fibo(2,1).

fibo(X,S):-
    Y1 is X-1,
    Y2 is X-2,
    fibo(Y1,S1),
    fibo(Y2,S2),
    S is S1+S2.

fibo_foda(X,Y):-
    Raiz is 1/2,
    R5 is 5^Raiz,
    Multiplicador is 1/R5,
    Primeiro_termo is ((1+R5)/2)^X,
    Segundo_termo is ((1-R5)/2)^X,
    Y is Multiplicador*(Primeiro_termo-Segundo_termo).

