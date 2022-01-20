;;; Reading file to line and split it from space to end
;;; then sending 2 numbers as parameters
;;; first number is begining number and second number is ending number
;;; if number is prime or semi-prime then write it to file
;;; increment the first number until equal less than second number
;;; and recurse it



;file read each line to string and this split it to 2 integer
(defun split-str (string &optional (separator " ") (r nil))

  (let ((n (position separator string
		     :from-end t 	;find string from seperator
		     :test #'(lambda (x y)
			       (find y x :test #'string=)))))
    (if n 	;recursive until string
	(split-str (subseq string 0 n) separator (cons (subseq string (1+ n)) r))
      (cons string r))
  )
)
(defun get-file ()
	;create list for hold 
	(let ((tempListe '()))
		(with-open-file (stream "boundries.txt"); open file for input
			(when stream
    	      (loop for line = (read-line stream nil)	;read line
   					;split line into list and assign to templist
    	      	while line do (setf tempListe (append  (split-str line) tempListe))
    	      )
    	      (close stream);close file
    	   )	
		)
		(with-open-file (stream "primedistribution.txt" :direction :output) ;open file for write
			;send numbers as a integer for write to file
		(write-file (parse-integer (car tempListe)) (parse-integer(second tempListe)) stream))
	)
)

(defun write-file(num1 num2 stream) 

		(cond ((is-prime num1)	;if prime write
		(format stream "~A is prime~%" num1))
		((is-semi-prime num1)	;if semi-prime write
		(format stream "~A is Semi-prime~%" num1))
	)
	(if (<= num1 num2)	;recursive until the last number 
		(write-file (+ num1 1) num2 stream)
	   )	
	

)
;check number is prime
(defun is-prime (num &optional (div (- num 1))) 
  (or (= div 1)	(and (/= (rem num div) 0)
           (is-prime  num (- div 1)))))
;check number is semi-prime
(defun is-semi-prime (num &optional (div 2))
  
  (cond ((> div (isqrt num)) nil)
        ((zerop (rem num div)) (and (is-prime div) (is-prime (/ num div))))
        (t (is-semi-prime num (+ div 1)))))

(get-file)