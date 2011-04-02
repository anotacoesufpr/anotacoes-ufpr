somatorio(0,0).

somatorio(X,SomaX):-
	X > 0,
	Y is X-1,
	somatorio(Y,SomaY),
	SomaX is X + SomaY.

somatorio([],0).

somatorio([C|L],Total):-
    Total > 0,
    somatorio
