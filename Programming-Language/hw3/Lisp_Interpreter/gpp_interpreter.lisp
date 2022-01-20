;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;																 ;;
;;							ALPER YASAR							 ;;
;;																 ;;
;;							 151044072							 ;;
;;																 ;;			
;;						    ASSIGNMENT 3						 ;;
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
; Expression list. This list makes sense of the commands in the list that come as input.
(defvar expi '("VALUES" ("while" "EXPB" "EXPLISTI") ("/" "EXPI" "EXPI") 
						("*" "EXPI" "EXPI") ("+" "EXPI" "EXPI") 
						("-" "EXPI" "EXPI") "ID" "integer" 	
						("if" "EXPB" "EXPLISTI" "EXPLISTI") ("if" "EXPB" "EXPLISTI") 
						("deffun" "ID" "IDLIST" "EXPLISTI") ("and" "EXPB" "EXPB") 
						("or" "EXPB" "EXPB") ("not" "EXPB") ("equal" "EXPI" "EXPI") 
						("equal" "EXPB" "EXPB") "BinaryValue" ("concat" "EXPLISTI" "EXPLISTI") 
						("append" "EXPI" "EXPLISTI") "null" "keyword" ("for" "ID" "EXPI" "EXPI" "EXPLISTI") 
						("defvar" "ID" "EXPI") ("set" "ID" "EXPI")))

(defun gppinterpreter (&optional filename)   (or #+CLISP *args* #+SBCL *posix-argv* 
							   #+LISPWORKS system:*line-arguments-list*
							   #+CMU extensions:*command-line-words* nil)

	(let ((tempListe '()))
		(if (= (length *args*) 1)	;this take file as argument from terminal
			(setf tempListe (lexer (car *args*))) ; send the lexer with filename

			(progn (setf lexerList (readLine))
				

			(setf tempListe (result (tokenization lexerList )))))

	)

	(parser tempListe) 

	(write-to-output-file "(defun tempFunc () " )
	(call-func tempListe) 
	(write-to-output-file ") (write (tempFunc ) ) ")
	(load "../Lisp_Interpreter/temp.lisp") 
	(delete-file "temp.lisp")
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
	(tokenization lexerList )
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
			      ((isKeyword (car lexerList) keywords) (append (cons (cons (strCat "KW_" lexerList) (cons (car lexerList) list2))  returnList) (tokenization (cdr lexerList))))
			      ((isOperator (car lexerList) operators) (append (cons (cons (strCat "OP_" lexerList) (cons (car lexerList) list2)) returnList) (tokenization (cdr lexerList))))
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
; dosyayı doldur..
(defun write-to-output-file(outputString)
    (with-open-file (str "temp.lisp"
                    :direction :output
                    :if-exists :append
                    :if-does-not-exist :create)
    (format str outputString))
)
;; dosyaya yazdır bunları lisp formatında
(defun call-func (param )
    (if (null param)
        nil 
        (progn
            (cond
                ;;OPERATIONS
                ( (string-equal (car (car param))  "OP_OP") (write-to-output-file "( ") )
                ( (string-equal (car (car param))  "OP_CP") (write-to-output-file " ) ") )
                ( (string-equal (car (car param) ) "OP_PLUS")  (write-to-output-file "+ "))
                ( (string-equal (car (car param) ) "OP_MINUS")  (write-to-output-file "- "))
                ( (string-equal (car (car param) ) "OP_DIV")  (write-to-output-file "/ "))
                ( (string-equal (car (car param) ) "OP_MULT")  (write-to-output-file "* "))
                ( (string-equal (car (car param) ) "OP_OC")  (write-to-output-file "\" "))
                ( (string-equal (car (car param) ) "OP_CC")  (write-to-output-file "\" "))
                ;( (string-equal (car (car param) ) "OP_COMMA")  (write-to-output-file "\" "))
                ;( (string-equal (car (car param) ) "OP_DBLMULT")  (write-to-output-file "*"))
                ;;; KEYS                
                ( (string-equal (car (car param) ) "KW_OR")  (write-to-output-file "or "))
                ( (string-equal (car (car param) ) "KW_AND") (write-to-output-file "and "))
                ( (string-equal (car (car param) ) "KW_NOT") (write-to-output-file "not "))
                ( (string-equal (car (car param) ) "KW_EQUAL") (write-to-output-file "equal "))
                ( (string-equal (car (car param) ) "KW_LESS") (write-to-output-file "< "))
                ( (string-equal (car (car param) ) "KW_NIL") (write-to-output-file "nil "))
                ( (string-equal (car (car param) ) "KW_LIST") (write-to-output-file "list "))
                ( (string-equal (car (car param) ) "KW_APPEND") (write-to-output-file "append "))
                ( (string-equal (car (car param) ) "KW_CONCAT") (write-to-output-file "concatenate "))
                ( (string-equal (car (car param) ) "KW_SET") (write-to-output-file "set "))
                ( (string-equal (car (car param) ) "KW_FOR") (write-to-output-file "for "))
                ( (string-equal (car (car param) ) "KW_DEFFUN") (write-to-output-file "defun "))
                ( (string-equal (car (car param) ) "KW_IF") (write-to-output-file "if "))
                ( (string-equal (car (car param) ) "KW_EXIT") (write-to-output-file "quit "))
                ( (string-equal (car (car param) ) "KW_LOAD") (write-to-output-file "load "))
               ; ( (string-equal (car (car param) ) "KW_DISP") (write-to-output-file "load "))
                ( (string-equal (car (car param) ) "KW_TRUE") (write-to-output-file "t "))
                ( (string-equal (car (car param) ) "KW_FALSE") (write-to-output-file "nil "))
                ;;SPECIAL
                ( (string-equal (car (car param))  "VALUE") (write-to-output-file (car (cdr (car param)) ) ) 
                                                            (write-to-output-file " " ))
                ( (string-equal (car (car param))  "IDENTIFIER") (write-to-output-file (car (cdr (car param)) ) )
                                                                 (write-to-output-file " " ))
                ( (string-equal (car (car param))  "COMMENT") (write-to-output-file "(write \"Syntax OK.\" )(write-line \"\")" ))

                ( t (write-to-output-file "write-line \"\")(write \"SYNTAX_ERROR Expression not recognized.\")")
                    (write-to-output-file "(quit") ) ;yoksa error yazdır.
            )
            (call-func (cdr param) )
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


; It creates an empty file and adds the required comment line.
(defun create-file()
	(with-open-file (str "parse_tree.tree"
		             :direction :output
		             :if-exists :supersede
		             :if-does-not-exist :create)
	(format str "; DIRECTIVE: parse tree"))
)

; adding the string received as input to the relevant file.
(defun write_parserTree(outputString)
	(with-open-file (str "parse_tree.tree"
					 :direction :output
		             :if-exists :append
		             :if-does-not-exist :create)
	(format str outputString))

)

; hiding the necessary indentation, bottom line, keywords that should not be in the output.
(defun print-tree (tree &optional (stringx ""))
	(if (null tree)
		nil
		(progn
			
			(if (listp (car tree))
				(progn
					(if (string= (car (car tree)) "operator")
						(if (or (string= (car (cdr (car tree))) "(") (string= (car (cdr (car tree))) ")"))
							(print-tree (cdr (car tree)) stringx)
						)
						(if (string= (car (car tree)) "keyword")
							(print-tree (cdr (car tree)) stringx)
							(print-tree (car tree) stringx)
						)
					)
				)
				(progn
					(write_parserTree "~%")
					(write_parserTree stringx)
					(if (string= "identifier" (car tree))
						(write_parserTree "ID")
						(if (string= "integer" (car tree))
							(write_parserTree "integerValue")
							(write_parserTree (car tree))
						)
					)

					;(write-string (car tree))
					(setq stringx (concatenate 'string stringx "  "))
				)
			)
			(print-tree (cdr tree) stringx)
		)
	)
)
; take a count when it seen opened brackets it will increase
; when closed brackets it will decrease
; hold new element as last element when fuction done.
(defun errorCheck (lexerList)
	
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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Bu fonksiyon input olarak gelen liste icerisinde en distaki parantezin icerigini kontrol etmektedir.
; Karsilasilan ilk acma parantezi nerede kapandi ise kapandigi indexi return etmektedir.
(defun closeBrackets(param param-check)
	(if (not (car param))
		0
		(if (string= (car (cdr (car param))) "(")
			(+ 1 (closeBrackets (cdr param) (+ 1 param-check)))
			(if (string= (car (cdr (car param))) ")")
				(if (= (- param-check 1) 0)
					1
					(+ 1 (closeBrackets (cdr param) (- param-check 1)))
				)
				(+ 1 (closeBrackets (cdr param) param-check))
			)
		)
	)
)


; match-exp-list'te kullanicidan gelen kodlar bulunmaktadir.
; expList ile karsilastirilip tokenlari belirlenmektedir.
; closeBrackets isimli fonkisyon ile istenilen parantez icerisindeki kodlar alinip
; hangi pattern'e ait olduklari belirlenir.
; expi = expressionlari tutan liste checklist;(+ x 5) olan liste
(defun match-exp(match-exp-list expList) 
	(if (not (car expList))
		nil
		(if (listp (car expList))
			(if (equal (car (car expList)) (car (cdr (car match-exp-list))))
				(car expList)
				(match-exp match-exp-list (cdr expList))
			)
			(if (string= (car expList) (car (cdr (car match-exp-list))))
				(car expList)
				(match-exp match-exp-list (cdr expList))
			)

		)
	)	
)

; Bu method bir liste ve string almaktadir.
; string , listenin en icteki elemani ile eslesir ise true
; eslesmez ise nil return etmektedir.
(defun checkList(cnlliste cnlstring)
	(if (not (car cnlliste))
		nil
		(if (listp (car cnlliste))
			(checkList (cdr cnlliste) cnlstring)
			(if (string= (car cnlliste) cnlstring)
				t
				(checkList (cdr cnlliste) cnlstring)
			)
		)
	)
)

; Create parseTree list
; incoming codes (parser List) create a list according to the expression list.
; parserList:sublist , parserResult;return of match-exp (+ expi expi)	
(defun createList(parserList parserResult &optional (rResult '())) 
	(if (or (string= (car (cdr (car parserList))) "(" ) (string= (car (cdr (car parserList))) "'" ) )
		(progn
			(if (string= "IDLIST" (car parserResult))
				(progn
					(setq mouse '("IDLIST"))
					(append rResult (createList (subseq parserList (closeBrackets parserList 0) (length parserList)) (cdr parserResult) (list (basic parserList mouse))))
				)
				(if (string= "EXPLISTI" (car parserResult))
					(progn
						(setq mouse '("EXPLISTI"))	
						(append rResult (createList (subseq parserList (closeBrackets parserList 0) (length parserList)) (cdr parserResult) (list (basic  parserList mouse))))
					)
					(if (string= "EXPB" (car parserResult))
						(progn
							(setq mouse '("EXPB"))
							(append rResult (createList (subseq parserList (closeBrackets parserList 0) (length parserList)) (cdr parserResult) (list (basic  parserList mouse))))
						)
						(if (and (string= "VALUES" (car parserResult)) (string= (car (cdr (car parserList))) "'" ))
							(progn
								(setq mouse '("VALUES"))
								(append rResult (createList (subseq parserList (closeBrackets parserList 0) (length parserList)) (cdr parserResult) (list (basic  parserList  mouse))))
							)
							(progn
								(append rResult (createList (cdr parserList) parserResult (list (car parserList))))
							)
						)

					)
				)
			)
		)
		(if (not (car parserList))
			rResult
			(if (checkList expi (car (car parserList)))
				(progn
					(if (string= "EXPLISTI" (car parserResult))
						(progn
							(if (string= "integer" (car (car parserList)))
(append rResult (createList (cdr parserList) (cdr parserResult) (list (reverse (append (list (append (list "EXPI" (append '("VALUES")(list (car parserList))))) "EXPLISTI")))) ))
								(append rResult (createList (cdr parserList) (cdr parserResult) (list (reverse (append (list (car parserList)) '("EXPLISTI"))))))
							)
						)
						;BinaryValue
						(if (string= "EXPB" (car parserResult))
							(append rResult (createList (cdr parserList) (cdr parserResult) (list (reverse (append (list (car parserList)) '("EXPB"))))))
							(if (string= "VALUES" (car parserResult))
								(append rResult (createList (cdr parserList) parserResult (list (reverse (append (list (car parserList)) '("VALUES"))))))
								(if (string= (car parserResult) "EXPI")
									(if (string= "integer" (car (car parserList)))
										(append rResult (createList (cdr parserList) (cdr parserResult) (list (reverse (append (list  (append  '("VALUES")(list (car parserList))) "EXPI"))))))
										(append rResult (createList (cdr parserList) (cdr parserResult) (list (reverse (append (list (car parserList)) '("EXPI"))))))
									)
									;(append rResult (createList (cdr parserList) (cdr parserResult) (list (reverse (append (list (car parserList)) '("expi"))))))
									(append rResult (createList (cdr parserList) (cdr parserResult) (list (car parserList))))
								)
							)
						)
					)
				)
				(progn
					(append rResult (createList (cdr parserList) (cdr parserResult) (append (list (car parserList)) )))
					

				)
			)
		)
	)
)

; This function is sent to the createList function to determine which structure the code 
; in the desired coin has, and then extract the parserTree list of this code.
; returns the list of the result parserTree.
(defun basic(token &optional (parserTree '("EXPI")))
	(setq bound (closeBrackets token 0))
	
	(if (and (string= (car parserTree) "EXPLISTI") (string= (car (cdr (car token))) "'"))
		(progn
			(setq parserTree (append parserTree '(("operator" "'"))))
			(setq parserTree (append parserTree '(("operator" "("))))			
			(setq setexp '("VALUES"))
			(setq parserTree (append parserTree (createList (subseq token 0 bound) setexp)))
			(setq parserTree (append parserTree '(("operator" ")"))))
		)
		(if (string= (car parserTree) "VALUES")
			(progn
				(setq setexp '("VALUES"))
				; eger token lenght 2 ye esit ve büyükse
				(setq parserTree (append parserTree (createList (subseq token 2 (- bound 1)) setexp)))
				
			)
			(progn
				(setq parserTree (append parserTree (createList (subseq token 0 bound) (match-exp (subseq token 1 (- bound 1)) expi))))
			)
		)
	)
)


(defun parser(inputList)
	(defvar outputList '("START" "INPUT" "EXPI"))
	(defvar output (basic inputList outputList))
	
	(create-file)
	(print-tree output)
)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(gppinterpreter "grammar.txt")
;(write-file (gppinterpreter))
