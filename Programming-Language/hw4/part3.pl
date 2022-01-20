% facts
class(102,10,z23).
class(108,12,z11).
class(341,14,z06).
class(455,16,207).
class(452,17,207).


enrollment(a,102).
enrollment(a,108).
enrollment(b,102).
enrollment(c,108).
enrollment(d,341).
enrollment(e,455).

% query

when(X,Y) :- 
    class(X,Y,_).


where(X,Y) :- 
    class(X,_,Y).

enroll(X,Y) :-
    enrollment(X,Y).


schedule(S,P,T) :- % student-place-time
    enrollment(S,P),
    when(P,T).

% bu sınıftaki dersleri yaz.
usage(P,T) :- %place - class
    class(_, T, P).

% class girdiğinde place veya time çakışıyor mu?
conflict(C1,C2) :-
    %room için..
    class(C1, _, P1),
    class(C2, _, P2),

    %time için
    class(C1, T1, _),
    class(C2, T2, _),

    ((T1==T2);(P1==P2)).

% student girdiğinde place ve time aynı mi? 
meet(S1,S2) :- 
    %öğrencinin aldığı classı bul.
    enrollment(S1,C1),   
    enrollment(S2,C2),  
    
    C1==C2.
