%% Usando o SWI-Prolog

%%%%%%%%%%%%%%%%%%%
% Base axiomatica %
%%%%%%%%%%%%%%%%%%%

% Vias terrestres
v_t(a,b,4).
v_t(b,e,6).
v_t(a,c,23).
v_t(a,g,13).
v_t(c,d,54).
v_t(d,e,30).
v_t(e,f,17).
v_t(f,g,45).
v_t(j,k,75).
v_t(j,l,75).
v_t(k,h,75).
v_t(k,i,211).
v_t(i,h,142).
v_t(m,n,101).
v_t(m,o,138).
v_t(m,r,17).
v_t(n,o,23).
v_t(r,q,23).
v_t(q,p,15).
v_t(p,o,12).

% Vias aereas.
v_a(e, j, 3).
v_a(e, m, 87).
v_a(j, m, 9).


%%%%%%%%%%%%%%%%%%%%%%
% Funcoes auxiliares %
%%%%%%%%%%%%%%%%%%%%%%

% inserindo um elemento no final da lista:
my_append(X,[],[X]).

my_append(X,[Cabeca|Cauda],Lista_Nova):-
    my_append(X,Cauda,Lista_Nova).

% Subculturas:
% vai usar o concatena.

subcultura(X,Y,[X,Y]):-
    v_t(X,Y,Custo).



% predicados para o dijkstra
minimo([],0,0).

minimo([X|Cauda],Menor,Resto):-
    X < Menor,
    minimo(Cauda,X,Resto),!;
    minimo(Cauda,Menor,Resto),
    Menor is X.

adjacente([],no,[]).

adjacente(Grafo,Node,Adj):-
%continua...


% Implementacao do algoritmo de dijkstra
dijkstra(Grafo,minDist,[],minDist).

dijkstra(Grafo,Fechado,Aberto,MinDist):-
    minimo(Open,V-D,ReducedOpen),
    adjacente(Grafo,V,NosAdjacentes),
    diff(NosAdjacentes,Fechado,PrunedNodes),
    addDist(PrunedNodes,D,UpdatedPrunedNodes),
    nodeMerge(UpdatedPrunedNodes,ReducedOpen,NextOpen),
    dijkstra(Grafo,[V-D|Fechado],NextOpen,MinDist).


% Novo daiXtra
% open_close_search(+Graph,+Open,+Closed,-Result)
open_close_search(Graph,[],Closed,Result):-
   tune_result(Graph,Closed,Result).
open_close_search(Graph,[Vertex|Open],Closed,Result):-
   explore(Vertex,Graph,Neighbourhood,ClosedVertex),
   diff(Neighbourhood,Closed,OpenNB), % remove closed vertices
   merge(OpenNB,Open,NewOpen),        % join with rest open vertices
   open_close_search(Graph,NewOpen,[ClosedVertex|Closed],Result).

% open_close_dijkstra(+Graph,+Start,-MinDist)
open_close_dijkstra(Graph,Start,MinDist):-
   open_close_search(Graph,[Start-0],[],MinDist).
   
   explore(V-D,Graph,Neigbourhood,V-D):-
   neighbourhood(Graph,V,NB),
   add_dist(NB,D,Neighbourhood).
   
add_dist([],_,[]).
add_dist([V-D1|Vs],D,[V-VD|Rest]):-
   VD is D+D1,
   add_dist(Vs,D,Rest).
   
   diff([],_,[]).
diff([V-D|VDs],Closed,NotClosed):-
   (member(V-_,Closed) -> NotClosed=[V-D|Rest] ; NotClosed=Rest),
   diff(VDs,Closed,Rest).
   
   merge([],Open,Open).
merge([V-D1|VDs],Open,NewOpen):-
   (del(V-D2,Open,RestOpen)
      -> min(D1,D2,D),ins(V-D,RestOpen,SOpen)
      ;  ins(V-D1,Open,SOpen),
   merge(VDs,SOpen,NewOpen).
   
del(X,[X|T],T).
del(X,[Y|T],Rest):-X\=Y,del(X,T,Rest).
   
ins(VD,[],[VD]).
ins(V-D,[U-D1|T],[V-D,U-D1|T]):-D<=D1.
ins(V-D,[U-D1|T],[U-D1|Rest]):-D>D1,ins(V-D,T,Rest).
   
   tune_result(_,Closed,Closed).
