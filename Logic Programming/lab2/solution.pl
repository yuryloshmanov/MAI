remove1(X, [X|T], T).
remove1(X, [Y|T], [Y|R]):- remove1(X, T, R).

permute1([],[]).
permute1(X, R):- remove1(Y, X, T), permute1(T, T1), R = [Y|T1].

neighbours('Корнеев', _, 'Докшин', _).

rides('Корнеев', _).
rides('Докшин', _).

walks(_, пекарь).

older('Докшин', _, 'Мареев', _).
older(_, милиционер, _, врач).
older(_, милиционер, _, инженер).

metManyTimes('Корнеев', _, 'Докшин', _).
metManyTimes('Корнеев', _, 'Скобелев', _).

metOnce(_, инженер, _, милиционер).

solve :-
    permute1([K, D, M, S], [пекарь, врач, инженер, милиционер]),
    permute1([Baker, Doctor, Engineer, Policeman], ['Корнеев', 'Докшин', 'Мареев', 'Скобелев']),

    not(walks('Корнеев', K)),
    not(walks('Докшин', D)),
    
    not(rides(Baker, пекарь)),
    
    not(older('Мареев', M, 'Докшин', D)),
    not(older(Doctor, врач, Policeman, милиционер)),
    not(older(Engineer, инженер, Policeman, милиционер)),

    not(neighbours(Policeman, милиционер, Doctor, врач)),

    not(metManyTimes(Engineer, инженер, Policeman, милиционер)),

    not(metOnce('Корнеев', K, 'Скобелев', S)),
    not(metOnce('Корнеев', K, 'Докшин', D)),

    write('Корнеев - '), write(K), nl,
    write('Докшин - '), write(D), nl,
    write('Мареев - '), write(M), nl,
    write('Скобелев - '), write(S), nl, !.
