% Fatorial

fatorial(1,1).

fatorial(X,Y):-
    X > 0,
    X2 is X-1,
    fatorial(X2,Y2),
    Y is X*Y2.

