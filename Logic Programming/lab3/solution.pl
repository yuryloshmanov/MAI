member1(X, [X|_]).
member1(X,[_|Y]) :- member1(X,Y).

append1([],X,X).
append1([A|X],Y,[A|Z]) :- append1(X,Y,Z).

integer1(1).
integer1(M) :- integer1(N), M is N+1.

buf([],Result,Result).
buf([X|Y],Result,Z) :- buf(Y,[X|Result],Z).
reverse1(L,Z) :- buf(L,[],Z).

move(X,Y) :- append1(S,["w","r"|L],X), append1(S,["r","w"|L],Y).
move(X,Y) :- append1(S,["b","r"|L],X), append1(S,["r","b"|L],Y).
move(X,Y) :- append1(S,["b","w"|L],X), append1(S,["w","b"|L],Y).

prolong([X|P],[C,X|P]) :- move(X,C), not(member1(C,[X|P])).

% поиск в глубину

path1([T|P],T,[T|P]).
path1(X,T,H) :- prolong(X,Y), path1(Y,T,H).

path_dfs(X,T,H) :- path1([X],T,L), reverse1(L,H).


% поиск в ширину

path2([[T|P]|_],T,[T|P]).
path2([X|P],T,G) :- findall(P1,prolong(X,P1),L), append1(P,L,Y), !, path2(Y,T,G).
path2([_|P],T,G) :- path2(P,T,G).

path_bfs(X,T,G):- path2([[X]],T,L), reverse1(L,G).


% поиск в глубину с итеративным погружением для нахождения кратчайшего пути

path3([T|P],T,[T|P],0).
path3(X,T,H,N) :- N > 0, prolong(X,Y), N1 is N-1, path3(Y,T,H,N1).

search_id(S,F,P,DL) :- path3([S],F,P,DL).
search_id(S,F,P) :- integer1(Level), search_id(S,F,P,Level).

path_id(S,F,P) :- search_id(S,F,K), reverse1(K,P).
