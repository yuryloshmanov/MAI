% Task 2: Relational Data

% The line below imports the data
:- ['four.pl'].

% Вариант 1

% Получить таблицу групп и средний балл по каждой из групп

find_grade([grade(Student, Grade)|_], Student, Grade) :- !.
find_grade([_|Grades], Student, Grade) :- find_grade(Grades, Student, Grade).


sum_for_subj([], _, 0) :- !.
sum_for_subj([Student|Students], Grades, Sum) :-
    find_grade(Grades, Student, Grade),
    sum_for_subj(Students, Grades, Sum1),
    Sum is Sum1 + Grade.

evaluate_sum(_, [], 0) :- !.
evaluate_sum(Students, [Subject|Subjects], Sum) :- 
    subject(Subject, Grades),
    sum_for_subj(Students, Grades, Sum1),
    evaluate_sum(Students, Subjects, Sum2),
    Sum is Sum1 + Sum2.


group_data([]) :- !.
group_data([Group|Groups]) :- 
    write('Группа: '), write(Group), nl,
    group(Group, Students),
    findall(Subject, subject(Subject, _), Subjects),
    evaluate_sum(Students, Subjects, Sum),
    findall(_, subject(_, _), Subjects),
    length(Subjects, X),
    length(Students, Y),
    Avg is Sum / X / Y,
    write('Средний балл: '), write(Avg), nl, nl,
    group_data(Groups).


task1() :-
    findall(Group, group(Group, _), Groups),
    group_data(Groups).



% Для каждого предмета получить список студентов, не сдавших экзамен (grade=2)

evaluate_grade(grade(_, Grade), Value) :-
    Grade = 2, Value is 1, !;
    Grade \= 2, Value is 0, !.

sum_fail_grades([], 0) :- !.
sum_fail_grades([Grade|Grades], Sum) :-
    sum_fail_grades(Grades, Sum1),
    evaluate_grade(Grade, Value),
    Sum is Sum1 + Value.

fails_for_subject([]) :- !.
fails_for_subject([Subject|Subjects]) :-
    write(Subject), nl,
    subject(Subject, Grades),
    sum_fail_grades(Grades, Sum),
    write('Не сдали экзамен: '), write(Sum), nl, nl,
    fails_for_subject(Subjects).

task2() :-
    findall(Subject, subject(Subject, _), Subjects),
    fails_for_subject(Subjects).


% Найти количество не сдавших студентов в каждой из групп

remove_duplicates([],[]).
remove_duplicates([H | T], List) :- member(H, T), remove_duplicates( T, List).
remove_duplicates([H | T], [H|T1]) :- \+member(H, T), remove_duplicates( T, T1).


is_grade_fail(Grade, Student, Res) :-
    Grade = 2, append([], [Student], Res), !;
    Grade \= 2, !.

append_for_subj([], _, []) :- !.
append_for_subj([Student|Students], Grades, List) :-
    find_grade(Grades, Student, Grade),
    append_for_subj(Students, Grades, Res1),
    is_grade_fail(Grade, Student, Res2),
    append(Res2, Res1, List).

evaluate_list(_, [], []) :- !.
evaluate_list(Students, [Subject|Subjects], Res) :- 
    subject(Subject, Grades),
    append_for_subj(Students, Grades, Res1),
    evaluate_list(Students, Subjects, Res2),
    append(Res1, Res2, Res).


group__data([]) :- !.
group__data([Group|Groups]) :- 
    write('Количество не сдавших: '), write(Group), nl,
    group(Group, Students),
    findall(Subject, subject(Subject, _), Subjects),
    evaluate_list(Students, Subjects, Res),
    remove_duplicates(Res, Failed_students),
    length(Failed_students, Cuont),
    write('Не сдало: '), write(Cuont), nl, nl,
    group__data(Groups).


task3() :-
    findall(Group, group(Group, _), Groups),
    group__data(Groups), !.
