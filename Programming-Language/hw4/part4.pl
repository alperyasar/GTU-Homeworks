%4.1 => element
% element(b,[a,b,c]). #true
% element(z,[a,b,c]). #false
%4.1 => element

element(X, [X|_]).
element(X, [_|T]) :-
    element(X,T). 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% union([a],[b],[a,b]). #true
% union([a],[b],[a]). #false
%4.2 => union

union([],S,Z):-
    union(S,Z).

union(L,[],Z):-
    union(L,Z).

% union([],T):-union([],[],_).   

union([],[],_).

union([X|L],[Y|S],Z) :-
    element(X,Z),
    element(Y,Z),!,
    union(L,S,Z).

union([Y|S],Z):-
    element(Y,Z),
    length(S,N1),
    ( N1 > 0 -> 
        union(S,Z);
        union([],[],_)
    ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% intersect([a,b],[c,d,e],[]). #true
% intersect([a,b],[a,b,c,d,e],[a,b]). #true
% intersect([a,b],[c,d,e],[a,b]). #false
%4.3 => intersect

delete(A, [A|B], B).
delete(A, [B, C|D], [B|E]) :-
    delete(A, [C|D], E).

intersect(_,[]).

intersect(L,[X|S]) :-
    not(element(X,L)),
    intersect(L,S).

intersect(L,S,[]):- intersect(L,S).

intersect(L,S,[X|Z]):-
    element(X,S),
    element(X,L),
    delete(X,L,L1),
    delete(X,S,S1),
    intersect(L1,S1,Z).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  equivalent([a,b],[c,d]). #true
%  equivalent([a,b],[a]). #false
%4.4 => equivalent size esit ise true..

size([],0).

size([_|T],N):-
    size(T,M),
    N is M+1.

equivalent(X,Y) :-
    size(X,S1),
    size(Y,S2),
    S1==S2.
