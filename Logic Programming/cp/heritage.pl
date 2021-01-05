parent('******', '******').
...

sex('******', m).
sex('******', f).
...


% № 3
shurins_parent(GrandParent, X) :-
    parent(X, Child), parent(Wife, Child), sex(Wife, f), parent(GrandParent, Wife), parent(GrandParent, Shurin), sex(Shurin, m), !.

shurin(Shurin, X) :-
    shurins_parent(P, X), parent(P, Shurin), sex(Shurin, m).

% № 4
relation(father, F, X)          :- parent(F, X), sex(F, m).
relation(mother, M, X)          :- parent(M, X), sex(M, f).
relation(brother, B, X)         :- sex(B, m), parent(P, B), parent(P, X), B \= X, !.
relation(sister, S, X)          :- sex(S, f), parent(P, S), parent(P, X), S \= X, !.
relation(son, S, X)             :- sex(S, m), parent(X, S).
relation(dauther, D, X)         :- sex(D, f), parent(X, D).
relation(grand_father, G, X)    :- parent(F, X), relation(father, G, F).
relation(grand_mother, G, X)    :- parent(M, X), relation(mother, G, M).
relation(shurin, S, X)          :- shurin(S, X).

print_relation([]).
print_relation([H|T]) :- print_relation(T), write(H),  write(' - ').

step(Curr, Prev, Y, Rel) :- (relation(Rel, Curr, Y); relation(Rel, Y, Curr)), not(member(Y, Prev)).

dfs(X, X, _, _).
dfs(Curr, Last, T, [Rev|Tl]) :- step(Curr, T, Next, Rev), dfs(Next, Last, [Curr|T], Tl).

dpath(Way, First, Last) :- dfs(First, Last, [], RevWay), reverse(RevWay, Way), print_relation(Way).

relative(R, X, Y) :- relation(R, X, Y).
relative(Way, First, Last) :- dpath(Way, First, Last), !.
