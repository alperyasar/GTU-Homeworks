;;; Reading file to line and split it from space or brackets to end 
;;; assign splited numbers to new list and write it to file

(defun delimiterp (c) (position c " ()")) ;check is character is space or bracket

(defun my-split (string &key (delimiterp #'delimiterp))
  (loop :for beg = (position-if-not delimiterp string)	; begin if character is not space or bracket to them
    :then (position-if-not delimiterp string :start (1+ end)) ; so just take numbers as list
    :for end = (and beg (position-if delimiterp string :start beg))
    :when beg :collect (subseq string beg end)
    :while end))


(defun get-file ()
	;create list for hold 
	(let ((tempListe '()))
		(with-open-file (stream "nested_list.txt") ; open file for input
			(when stream
    	      (loop for line = (read-line stream nil)	;read line
   					;split line into list and assign to templist
    	      	while line do (setf tempListe (append  (my-split line) tempListe))
    	      )
    	   )	
		)
		
		(write-file tempListe)
	)
)


(defun write-file (str)
	; open and right new list
	(with-open-file (stream "flattened_list.txt" :direction :output)
	   (format stream "~A" str))
)


(get-file)