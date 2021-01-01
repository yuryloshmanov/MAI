% Первая часть задания - предикаты работы со списками
length1([], 0).
length1([_|Y], N) :- length1(Y, N1), N is N1 + 1.

member1(A, [A|_]).
member1(A, [_|Z]) :- member1(A, Z).

append1([], X, X).
append1([A|X], Y, [A|Z]) :- append1(X, Y, Z).

remove1(X, [X|T], T).
remove1(X, [Y|T], [Y|R]):- remove1(X, T, R).

permute1([],[]).
permute1(X, R):- remove1(Y, X, T), permute1(T, T1), R = [Y|T1].

sublist1(S, R):- append1(X, _, S), append1(_, R, X).


% Вариант 16
% Нахождение номера первого вхождения элемента со заданным значением

% Без использования стандартных предикатов:
first_entry1(A, [A|_], 0) :- !.
first_entry1(A, [_|Z], N) :- first_entry1(A, Z, N1), N is N1 + 1, !.

% С использованием стандарных предикатов:
first_entry2(A, [A|_], 0) :- !.
first_entry2(A, [_|Z], N) :- permute1(Z, X), first_entry2(A, X, N1), N is N1 + 1, !.


% Вариант 1
% Вычисление суммы элементов

% Без использования стандартных предикатов:
sum1([], 0).
sum1([X|Y], N) :- sum1(Y, N1), N is N1 + X.

% С использованием стандарных предикатов:
sum2([], 0) :- !.
sum2([X|Y], N) :- permute1(Y, Z), sum2(Z, N1), N is N1 + X, !.
