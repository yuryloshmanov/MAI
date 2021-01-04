:- op(12, xfx, =>).
:- op(11, xfy, &).
:- op(10, xfx, :).

determiner(K, L1, L2, all(K) : (L1 => L2)) --> [every].
determiner(K, L1, L2, exists(K) : (L1 & L2)) --> [a].

noun(K, man(K), [man|S], S).
noun(K, woman(K), [woman|S], S).

name(petya, [petya|S], S).

trans_verb(K, Y, loves(K, Y), [loves|S], S).

intrans_verb(K, lives(K), [lives|S], S).

relative_statement(K, L1, L1 & L2) --> [that], group_verb(K, L2).
relative_statement(_, L, L) --> [].

group_noun(K, L1, L) -->
    determiner(K, L2, L1, L), noun(K, L3), relative_statement(K, L3, L2).
group_noun(K, L, L) --> 
    name(K).

group_verb(K, L) --> 
    trans_verb(K, Y, L1),
    group_noun(Y, L1, L).
group_verb(K, L) --> 
    intrans_verb(K, L).

sentence(L) --> group_noun(K, L1, L), group_verb(K, L1), !.
