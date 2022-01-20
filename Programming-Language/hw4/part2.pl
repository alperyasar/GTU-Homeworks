distance(edirne,edremit,914).
distance(edremit,edirne,914).
distance(edremit,erzincan,736).
distance(erzincan,edremit,736).
distance(istanbul,izmir,328).
distance(istanbul,antalya,482).
distance(istanbul,gaziantep,847).
distance(istanbul,ankara,351).
distance(istanbul,van,1262).
distance(istanbul,rize,967).
distance(izmir,istanbul,328).
distance(izmir,ısparta,308).
distance(ısparta,izmir,308).
distance(ısparta,burdur,24).
distance(burdur,ısparta,24).
distance(antalya,istanbul,482).
distance(antalya,konya,192).
distance(antalya,gaziantep,592).
distance(konya,antalya,192).
distance(konya,ankara,227).
distance(gaziantep,antalya,592).
distance(gaziantep,istanbul,847).
distance(ankara,istanbul,351).
distance(ankara,konya,227).
distance(ankara,van,920).
distance(van,istanbul,1262).
distance(van,ankara,920).
distance(van,rize,373).
distance(rize,istanbul,967).
distance(rize,van,373).

% sroute base case
sroute(X, Y, D) :- 
	distance(X, Y, D),
	write(D),nl.
sroute(X, Y, D) :- sroute(X, Y, D, [], X).
% sroute
sroute(X, Y, D, P, L) :-
	\+member(X, P),
	distance(X, Z, D1),
	not(Z = L),
	sroute(Z, Y, D2, [X|P], X),
        write(P),nl,
	not(Y = L),
	not(X = Y),
	D is D1 + D2.	
% sroute

sroute(X, Y, D, _, _) :- 
	distance(X, Y, D).

