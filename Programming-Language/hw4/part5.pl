operators('+').
operators('-').
operators('*').

getLines(Line):-
    open('input.txt', read, In),
    readData(In, Line),
    new_list(Line,NewList),
    last(NewList,Result),        % takes last element
    list_delete(Result,NewList,NumbersList),
    list_length(NumbersList,Len),
    count_to_3(0,Len,OpList,NumbersList,Result),     % make opList for permutation
    close(In).

readData(In, L):-
  read_term(In, H, []),
  (   H == end_of_file
  ->  L = []
  ;   L = [H|T],
      readData(In,T)
  ).

%file read file into nested list [[]]
%it takes into new list []
new_list([],[]).
new_list([A], A) :- new_list(L, P).

%delete last elemenet from list
list_delete(X, [X], []).
list_delete(X,[X|L1], L1).
list_delete(X, [Y|L2], [Y|L1]) :- list_delete(X,L2,L1).

list_length([],0).
list_length([_|TAIL],N) :- list_length(TAIL,N1), N is N1 + 1.

count_to_3(X,Len,OpList,NumbersList,Result) :- X == 3,
  Len1 is Len - 1,
  take_ops(0,Len1,OpList,NewList,NumbersList,Result).
count_to_3(X,Len,OpList,NumbersList,Result) :-
   count_for_make_operator(0,Len,X,OpList,NumbersList,Result).
   

count_for_make_operator(X,Len,Z,Ops,NumbersList,Result) :- X == Len,
      Y is Z + 1,
      count_to_3(Y,Len,Ops,NumbersList,Result).
count_for_make_operator(X,Len,Z,Ops,NumbersList,Result) :-
   chooseOps(Z,Ops,NewOps),
   Y is X + 1,
   count_for_make_operator(Y,Len,Z,NewOps,NumbersList,Result).

list_insert(X,L,R) :- list_delete(X,R,L).

chooseOps(X,Ops,NewOps) :- X == 0, list_insert('+',Ops,NewOps).
chooseOps(X,Ops,NewOps) :- X == 1, list_insert('-',Ops,NewOps).
chooseOps(X,Ops,NewOps) :- X == 2, list_insert('*',Ops,NewOps).

chooseRandom([], []).
chooseRandom(List, Elt) :-
        length(List, Length),
        random(0, Length, Index),
        nth0(Index, List, Elt).

take_ops(X,Len,OpList,NewList,NumbersList,Result) :- X == Len,
  length(NumbersList, Length),
  L is Length - 1,  
  take_num(0,Length,OpList,NewList,NumbersList,[],Result).
take_ops(X,Len,OpList,NewList,NumbersList,Result) :-
    chooseRandom(OpList,Op),
    list_insert(Op,NewList,SecondNew),
    Y is X + 1,
   take_ops(Y,Len,OpList,SecondNew,NumbersList,Result).

calc(OpList,WriteOp,NewOpList,NewNumberList,NumbersList,Len,Calc,Result) :- Len == 1, Calc == Result,
    list_rev(NumbersList,X),
    list_rev(WriteOp,Y),
    last(X,Num),
    list_insert(Num,[],L),
    list_butlast(X,N),
    length(Y,Length),
    makeWrite(N,Y,L,Length,Result).
 %write file.
calc(OpList,WriteOp,NewOpList,NewNumberList,NumbersList,Len,Calc,Result) :- Len == 1, 
    not(Calc = Result),
    length(NumbersList, Length),
    L is Length - 1,
   take_ops(0,L,OpList,[],NumbersList,Result).
calc(OpList,WriteOp,NewOpList,NewNumberList,NumbersList,Len,Calc,Result) :- 
  last(NewOpList,Op),
  list_delete(Op,NewOpList,NewOpList2),
  last(NewNumberList,Number1),
  list_delete(Number1,NewNumberList,NewList),
  last(NewList,Number2),
  list_delete(Number2,NewList,NewList2),
  list_insert(Number2,NumbersList,Y),
  chooseCalc(Op,Number1,Number2,Result1),
  add(Result1,NewList2,NewList3),
  Len1 is Len - 1,
  calc(OpList,WriteOp,NewOpList2,NewList3,Y,Len1,Result1,Result).

chooseCalc(X,Num1,Num2,Result) :- X == '+', Result is Num1 + Num2.
chooseCalc(X,Num1,Num2,Result) :- X == '-', Result is Num1 - Num2.
chooseCalc(X,Num1,Num2,Result) :- X == '*', Result is Num1 * Num2.

take_num(X,Len,OpList,SubOp,NumbersList,NewNumberList,Result) :- 
    X == Len,
    length(NewNumberList, Length),
      last(NewNumberList,Number1),
    list_insert(Number1,K,Y),
    calc(OpList,SubOp,SubOp,NewNumberList,Y,Length,Calc,Result). 


take_num(X,Len,OpList,SubOp,NumbersList,NewNumberList,Result) :-
    
    chooseRandom(NumbersList,Op),
    list_delete(Op,NumbersList,K),
    list_insert(Op,NewNumberList,SecondNew),
    Y is X + 1,
   take_num(Y,Len,OpList,SubOp,K,SecondNew,Result).

add(X,[],[X]).

add(X,[Y|Tail],[Y|Tail1]):-
    add(X,Tail,Tail1).
list_butlast([X|Xs], Ys) :-                 % use auxiliary predicate ...
   list_butlast_prev(Xs, Ys, X).            % ... which lags behind by one item

list_butlast_prev([], [], _).
list_butlast_prev([X1|Xs], [X0|Ys], X0) :-  
   list_butlast_prev(Xs, Ys, X1).           % lag behind by one

list_concat([],L,L).
list_concat([X1|L1],L2,[X1|L3]) :- list_concat(L1,L2,L3).

list_rev([],[]).
list_rev([Head|Tail],Reversed) :-
   list_rev(Tail, RevTail),list_concat(RevTail, [Head],Reversed).

makeWrite(Numbers,Ops,L,Length,Result) :- Length == 0, open("output.txt", write, File),
    write(File,"("),
    loop_through_list(File, L),
    write(File,")= "),
    write(File,Result),
    close(File).
makeWrite(Numbers,Ops,L,Length,Result) :-
    last(Ops,Op),
    list_insert(Op,L,M),
    list_butlast(Ops,O),
    last(Numbers,Num),
    list_insert(Num,M,X),
    list_butlast(Numbers,N),

    Y is Length - 1,
    makeWrite(N,O,X,Y,Result).
loop_through_list(_File, []) :- !.
loop_through_list(File, [Head|Tail]) :-
    write(File, Head),
    loop_through_list(File, Tail).

write_list_to_file(Filename,List) :-
    open(Filename, write, File),
    loop_through_list(File, List),
    close(File).