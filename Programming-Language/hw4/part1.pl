%knowledge base
flight(edirne,edremit).
flight(edremit,edirne).
flight(edremit,erzincan).
flight(erzincan,edremit).
flight(istanbul,izmir).
flight(izmir,istanbul).
flight(izmir,ısparta).
flight(ısparta,izmir).
flight(ısparta,burdur).
flight(burdur,ısparta).
flight(istanbul,antalya).
flight(antalya,istanbul).
flight(istanbul,gaziantep).
flight(istanbul,ankara).
flight(istanbul,van).
flight(istanbul,rize).
flight(antalya,konya).
flight(antalya,gaziantep).
flight(konya,antalya).
flight(konya,ankara).
flight(gaziantep,antalya).
flight(gaziantep,istanbul).
flight(ankara,istanbul).
flight(ankara,konya).
flight(ankara,van).
flight(van,istanbul).
flight(van,ankara).
flight(van,rize).
flight(rize,istanbul).
flight(rize,van).

%rules
% route base case
route(X, Y) :- 
	route(X, Y, [], X).
% route
route(X, Y, K, L) :-
	\+member(X, K),
	flight(X, Z),
	not(Z = L),
	route(Z, Y, [X|K], X),
	not(Y = L),
	not(X = Y).
% route

route(X, Y, _, _) :- 
	flight(X, Y).
