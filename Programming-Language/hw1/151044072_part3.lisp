;;; file read each line to string and this split it to integer
;;; then sending to write file list and 0 as parameters
;;; first parameter begining number and second parameter ending number
;;; when the number remaining is 0 if divided to 2 recurse the half number
;;; until 1 and pass the next number. At most 5 number doing this.
;;; if number remaining is not equal to 0 than Multiply by 3 add up by 1


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
		(with-open-file (stream "integer_inputs.txt"); open file for input
			(when stream
    	      (loop for line = (read-line stream nil)	;read line
   					;split line into list and assign to templist
    	      	while line do (setf tempListe (append  (split-str line) tempListe))
    	      )
    	      (close stream);close file
    	   )	
   		)
		(with-open-file (stream "collatz_outputs.txt" :direction :output);open file for write
		(write-file tempListe 0 stream))
	)
)

(defun write-file(list1 num1 stream)
	(if (not (null list1))
		(if (= num1 0)	;if number is not equal to 0 pass to new line in file for write
		(format stream "~A:" (parse-integer (car list1)))
		(format stream "~%~A:" (parse-integer (car list1)))))
	
	 
	(if (not (null list1))	;if list not end send first element as integer 
		(collatz (parse-integer (car list1)) stream))	
	(if (and (< num1 4) (not (null list1)))
		(write-file (cdr list1) (+ 1 num1) stream))
)

(defun collatz (num stream)	
	(format stream " ~A" num)	;write element to file
	(if (and (/= (rem num 2) 0) (/= num 1))		; if number is not divide 2 
		(collatz (+ 1 (* 3 num)) stream))		; recursive number *3 + 1
	(if (= (rem num 2) 0)						;divide number 2 and recursive it
		(collatz (/ num 2) stream)))

(get-file)