;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;																 ;;
;;							ALPER YASAR							 ;;
;;																 ;;
;;							 151044072							 ;;
;;																 ;;			
;;						    ASSIGNMENT 1						 ;;
;;																 ;;
;; if there is a undefined or too much parantesis write error    ;;
;; message. or code will tokenized given code and write it.      ;;
;;																 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defvar operators '("+" "-" "/" "*" "(" ")" "**" "\"" ","))
(defvar comment '(";;")) ;; "" da olcak.. (,)

(defvar keywords '("and" "or" "not" "equal" "less" "nil" "list" "append" "concat" "set" "deffun" "for" "if" "exit" "load"))
(defvar globalList '()) ;global variables are hold as a list
(defvar localList '())	;local variables are hold as a list
(defvar openparenthesis 0)	;hold number of paranthesis for error
(defvar closeparenthesis 0)
(defvar lastElmInList nil) ;last element in list
(defvar seenDefun 0) ; when a function is opened it will true
(defvar errorStr '())

(defun gppinterpreter (&optional filename)   (or #+CLISP *args* #+SBCL *posix-argv* 
							   #+LISPWORKS system:*line-arguments-list*
							   #+CMU extensions:*command-line-words* nil)

	(let ((tempListe '()))
		(if (= (length *args*) 1)	;this take file as argument from terminal
			(setf tempListe (lexer (car *args*))) ; send the lexer with filename

			(progn (setf lexerList (readLine))
				

			(setf tempListe (result (tokenization lexerList ))))
				)
		(with-open-file (stream "parsed_lisp.txt" :direction :output)
		(write-file tempListe stream))

	)
)

(defun readLine ()
	(setq  lexerList'())
	(setf lexerList (append lexerList (read-line lexerList) ) )

	(setf lexerList (cleanEmptyString (splitToList (splitToList (splitToList (reverse
	(StoLSplit lexerList " ")) "(" ) ")" ) "\"")))

	(setf lexerList (doubleQuotes lexerList))
	(if (car lexerList)
			(append lexerlist (readLine))
			lexerlist)

)
; get file to list and clean it as list and sperate
; after that tokenize them in tokenazation function
(defun lexer(fileName)

	(setq lexerList (cleanEmptyString (splitToList (splitToList (splitToList (reverse (get-file fileName)) "(" ) ")" ) "\"")))

	(setf lexerList (doubleQuotes lexerList))
	(result (tokenization lexerList ) )
)
; check errors if not find what it is keywords, operator, integer.. etc.
; ad it to new list and return it
; if there is a parantesis or undefined identifier add to new list and return it 
(defun tokenization(lexerList)
	(setq returnList '())
	(setq list2 '())


	(if (not (car lexerList))
		list2
		(if (errorCheck (car lexerList))		
			(progn (setf list2 (append list2 (list errorStr))))
			(cond
			      ((isKeyword (car lexerList) keywords) (append (cons (cons (strCat "KW_" lexerList) list2)  returnList) (tokenization (cdr lexerList))) )
			      ((isOperator (car lexerList) operators) (append (cons (cons (strCat "OP_" lexerList) list2) returnList) (tokenization (cdr lexerList))) )
			      ((isBinary (car lexerList)) (append (cons (cons "BINARY" (cons (car lexerList) list2)) returnList) (tokenization (cdr lexerList))))
			      ((isInteger (car lexerList)) (append (cons (cons "VALUE" (cons (car lexerList) list2)) returnList) (tokenization (cdr lexerList))))
			      ((isIdentifier (car lexerList)) (append (cons (cons "IDENTIFIER" (cons (car lexerList) list2)) returnList) (tokenization (cdr lexerList))))
	                ;; comment'ten sonrasını atla..
	              ((isComment (car lexerList)) (append (cons (cons "COMMENT" (cons (car lexerList) list2)) returnList) (tokenization (cdr (cdr lexerList)))))
			      ((isQuotes (car lexerList))
				  	   (append (append (cons (cons "OP_OC" (cons (car lexerList) list2)) returnList)
						 			   (cons (cons "OP_CC" (cons (car lexerList) list2)) returnList) ) (tokenization (cdr lexerList)) ))
				  (t (append (cons (cons "SYNTAX_ERROR" (cons (car lexerList) list2)) returnList) (tokenization (cdr (cdr lexerList)))) )
			)
		)
	)
)
; verilmiş stringi istenilen karaktöre göre ayırıp liste return ediyor.
(defun StoLSplit(str id &optional (emptyList '()))
	(if (not (position (char id 0) str ))
		(cons str emptyList)
		(if (string= id (subseq str 0 1))
			(StoLSplit (subseq str 1) id (cons id emptyList))
			(StoLSplit (subseq str (+ 1 (position (char id 0) str ))) id (cons id (cons (subseq str 0 (position (char id 0) str )) emptyList)))
		)
	)
)

; verilen listeyi gezip belirtilen karaktere göre bölüp liste return ediyor
(defun splitToList(paramliste1 ch)
	(setq list2 '())
	(if (not (car paramliste1))
		list2
		(append (reverse (StoLSplit (car paramliste1) ch list2)) (splitToList (cdr paramliste1) ch))
	)
)


(defun tempSubString (string1 string2 &optional (index 0) )
    (if (>= index (length string2))
        nil
        (if (string-equal (subseq string2 index (+ 1 index) ) string1)
			t
            (tempSubString string1 string2 (+ 1 index) )
        )
    )
)

;"" ve içindekileri birleştiriyor. " list " => "list"
(defun deleteSpaces (dliste check)
    (if (tempSubString "\"" (car dliste))
        (if (= check 0)
            (concatenate 'string (car dliste) (deleteSpaces (cdr dliste) 1))
            (car dliste)
        )
        (concatenate 'string (car dliste) (deleteSpaces (cdr dliste) 1))
    )
)

; "" varsa içindekilerle birlikte onlar birleştirilmiş hali ile yeni list oluşturuyor.
(defun doubleQuotes(dliste &optional (check 0))
    (setq rliste'())
    (if (null dliste)
        nil
        (if (tempSubString "\"" (car dliste))
            (if (= check 0)
                (append (cons (deleteSpaces dliste 0) rliste) (doubleQuotes (cdr dliste) 1) )
                (append rliste (doubleQuotes (cdr dliste) 0))
            )
            (if (= check 1)
                (append  rliste (doubleQuotes (cdr dliste) 1) )
                (append (cons (car dliste) rliste) (doubleQuotes (cdr dliste) 0))
            )
        )
    )
)

; return operator or keyword name
(defun strCat (token value)
	(setq name (car value))
	(cond
		((string-equal name "(") (setf name "OP"))
		((string-equal name ")") (setf name "CP"))
		((string-equal name ",") (setf name "COMMA"))
		((string-equal name "+") (setf name "PLUS"))
		((string-equal name "-") (setf name "MINUS"))
		((string-equal name "/") (setf name "DIV"))
		((string-equal name "**") (setf name "DBLMULT"))
		((string-equal name "*") (setf name "MULT"))
    )
	(concatenate 'string token (string-upcase name))
)
; read file
(defun get-file(fileName)
	(defvar tempListe '())
	(defvar splitList '())
	(let ((in (open fileName :if-does-not-exist nil)))
	   (when in
	      (loop for line = (read-line in nil)

	      	while line do (setq tempListe (append  (StoLSplit line " " splitList) tempListe))
	      )
	      (close in)
	   )
	)
	tempListe
)

(defun isKeyword(paramKeyword keywordList)
	(if (not (car keywordList))
		nil
		(if (string= (car keywordList) paramKeyword)
			t
			(isKeyword paramKeyword (cdr keywordList))
		)
	)
)

(defun isOperator(paramOperator operatorList)
	(if (not (car operatorList))
		nil
		(if (string= (car operatorList) paramOperator)
			t
			(isOperator paramOperator (cdr operatorList))
		)
	)
)

(defun isBinary(paramBinaryValue)
	(if (string-equal "true" paramBinaryValue)
		t
		(if (string-equal "false" paramBinaryValue)
			t
			nil
		)
	)
)

(defun isComment(paramComment)
	(if (string= ";;" paramComment)
		t
		nil
	)
)

(defun isQuotes (paramQuates)
    (if (tempSubString "\""  paramQuates)
		t
		nil
    )
)
(defun isInteger(numbers &optional (index 0) (negative 0))
	(if (and (= (length numbers) 1))
		(isPosInt numbers index negative)
		(if (> (length numbers) 1)
			(isNegInt numbers index negative)
			nil
		)
	)
)

; Negative integer value control
(defun isNegInt (numbers index negative)
	(if (and (string= (subseq numbers 0 1) "-") (= index 0))
		(isInteger (subseq numbers 1 (length numbers)) (+ index 1) 1)
		(if (and (string<= (subseq numbers 0 1) "9") (string>= (subseq numbers 0 1) "1") (= index 1) (= negative 1))
			(isInteger (subseq numbers 1 (length numbers)) (+ index 1) 1)
			(if (and (string<= (subseq numbers 0 1) "9") (string>= (subseq numbers 0 1) "0") (> index 1) (= negative 1))
				(isInteger (subseq numbers 1 (length numbers)) (+ index 1) 1)
				(if (and (string<= (subseq numbers 0 1) "9") (string>= (subseq numbers 0 1) "1") (= index 0) (= negative 0))
					(isInteger (subseq numbers 1 (length numbers)) (+ index 1) 0)
					(if (and (string<= (subseq numbers 0 1) "9") (string>= (subseq numbers 0 1) "0") (> index 0) (= negative 0))
						(isInteger (subseq numbers 1 (length numbers)) (+ index 1) 0)
						nil
					)
				)
			)
		)
	)
)
; Pozitive integer value control
(defun isPosInt (numbers index negative)
	(if (and (string<= numbers "9") (string>= numbers "0") (>= index 0) (= negative 0))
		t
		(if (and (string<= numbers "9") (string>= numbers "0") (> index 1) (= negative 1))
			t
			(if (and (string<= numbers "9") (string>= numbers "1"))
				t
				nil))
	)
)

(defun isIdentifier(id)
	(if (> (length id) 1)
		(if (or (and (string<= (subseq id 0 1) "z")(string>= (subseq id 0 1) "a"))
			(and (string<= (subseq id 0 1) "Z")(string>= (subseq id 0 1) "A")))
			(isIdentifier (subseq id 1 (length id)))
			nil
		)
		(if (= (length id) 1)
			(if (or (and (string<= (subseq id 0 1) "z")(string>= (subseq id 0 1) "a"))
				(and (string<= (subseq id 0 1) "Z")(string>= (subseq id 0 1) "A")))
				t
				nil
			)
			nil
		)
	)
)
;sadece tokenları yazdırması için son düzenleme (Identifier a) -- Identifier
(defun result (lexerList )
	(defvar returnList '())
    (if (null lexerList)
        nil
		(append  (cons (car (car lexerList)) returnList) (result (cdr lexerList)))
	)
)



(defun cleanEmptyString(mySpaceList)
	(defvar emptyList '())
	(if (not (car mySpaceList))
		emptyList
		(if (or (string= "" (string-trim " " (car mySpaceList))) (string= "" (string-trim "	" (car mySpaceList)))  (string= "	" (string-trim "	" (car mySpaceList))))
			(cleanEmptyString (cdr mySpaceList))
			(append (cons (string-trim "	" (car mySpaceList)) emptyList) (cleanEmptyString (cdr mySpaceList)))
		)
	)

)

(defun write-file(lexerList stream)
	(if (not (car lexerList))
		nil
		(progn
			(format stream "~A~%" (car lexerList))
			(write-file (cdr lexerList) stream)
		)
	)
)
; take a count when it seen opened brackets it will increase
; when closed brackets it will decrease
; hold new element as last element when fuction done.
(defun errorCheck (lexerList)
	(write lexerlist)
	(cond
		((string-equal lexerList "(") (progn 
			(setq openparenthesis (+ 1 openparenthesis)) (setq lastElmInList lexerList) nil))
		((string-equal lexerList ")") (checkCloseparenthesisError lexerList))
		((isKeyword lexerList keywords) (checkKeywordsError lexerList))
		((isOperator lexerList operators) (checkOperatorsError lexerList))
		((isInteger lexerList) (setq lastElmInList lexerList) nil)
		((isIdentifier lexerList) (checkIdentifiersError lexerList))
		(t (progn	(setq lastElmInList lexerList) nil))
	)
)
; if there is too much closed paranthesis it will give error.
(defun checkCloseparenthesisError (str)
	(if (equal openparenthesis 0)
		(progn
			(setf errorStr (list "SYNTAX_ERROR too much closed parenthesis")) t)
		
		(progn
			(setq openparenthesis (- openparenthesis 1)) (setq lastElmInList str)
			(if (equal openparenthesis 0)
				(progn (setq seenDefun 0)
					(setf localList '())))
			nil))

)
; if before keywords there is no open brackets it will be give error 
; if seen deffun hold it because check local variables
(defun checkKeywordsError (str)
	(cond
		((string-equal str "deffun") (progn
			(if (not (string-equal lastElmInList "("))
				(progn (setf errorStr (list "SYNTAX_ERROR missing parenthesis for keywords")) t)
			(progn (setq seenDefun 1)
			(setq lastElmInList str) nil))))
		((string-equal lastElmInList "(") nil)
		((not (string-equal lastElmInList "(")) (progn
			(setf errorStr (list "SYNTAX_ERROR missing parenthesis for keywords")) t))
	)
)
; if before operator there is no open brackets it will be give error
; if 1 + 2 will give error

(defun checkOperatorsError (str)
	(if (string-equal lastElmInList "(")
		(progn (setq lastElmInList str) nil)
		(progn (setf errorStr (list "SYNTAX_ERROR missing parenthesis for operator")) t)

	)
)
; check identifier as global or local variables
; if it is undefiend give error
(defun checkIdentifiersError (str)
	(if (equal seenDefun 1)
		(if (checkLocalVaribals str)
			t
			(progn (setq lastElmInList str) nil))
		(if (checkglobalVaribals str)
			t
			(progn (setq lastElmInList str) nil)))
)

(defun checkglobalVaribals (str)
	(if (not (car globalList))
		(progn (if (or (string-equal lastElmInList "list") (string-equal lastElmInList "set"))
			(progn (setf globalList (list str)) nil) 
			(progn (setf errorStr (list "SYNTAX_ERROR missing Identifier")) t)))
		(if (returnGlobalVariables str globalList)
			nil
			(progn (setf errorStr (list "SYNTAX_ERROR missing Identifier")) t))
	)
)
(defun returnGlobalVariables (str var)

	(if (not (car var))
		nil
		(if (string= str (car var))
			t
			(returnGlobalVariables str (cdr var))))
)

(defun checkLocalVaribals (str)
	
	(cond
		((string-equal lastElmInList "deffun") (progn (setf localList (list str)) nil))
		((equal openparenthesis 2) (progn (setf localList (append localList (list str))) nil))
		((or (returnGlobalVariables str localList) (returnGlobalVariables str localList)) nil)
		((or (isKeyword str keywords) (isOperator str operators)) (progn (setf localList (append localList (list str))) nil))
		(t (progn (setf errorStr (list "SYNTAX_ERROR missing Identifier")) t))
	)
)

(gppinterpreter "grammar.txt")
;(write-file (gppinterpreter))
