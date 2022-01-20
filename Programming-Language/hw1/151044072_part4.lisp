; read file into list 
(defun get-file ()
	(let ((tempListe '()))
		(with-open-file (stream "paragraph.txt")
			(when stream
    	      (loop for line = (read-char stream nil)

    	      	while line 
    	      	do (setf tempListe (cons line tempListe)) ;read to list all characters
    	      )
    	   )	
		)
    ;when read last element adding to first 
    ;reverse it like in txt
		(reverse tempListe) 
    (with-open-file (stream "huffman_codes.txt" :direction :output)
    (format stream "~A" (make-huffman-tree tempListe)))


	)
)
; make new list and take them freqeuncy in paragraph
(defun make-freqlist (chars freqlist)
  (cond ;return new list ending of paragraphlist
    ((endp chars) freqlist)
	(t (make-freqlist (rest chars) (freqlist-inc-chars freqlist (first chars))))))

;increments the current char in the frequency list, or adds it if not present
(defun freqlist-inc-chars (freqlist chars)
  (cond
    ((endp freqlist) ; if char is not found in frequency list its adding and make it 1 ("char" 1)
     (list (freqlist-make-entry chars 1))) 
    ((equal (freqlist-chars (first freqlist)) chars) ;if char found in frequecy list increnebt number and add it to first list
     (cons (freqlist-make-entry chars (1+ (freqlist-count (first freqlist)))) (rest freqlist)))
    ;recursive until find character or ending of frequency list
    (t (cons (first freqlist) (freqlist-inc-chars (rest freqlist) chars)))))  

(defun freqlist-make-entry (chars freq) 
  (list (list chars) freq))    ; add to list as (("char" 1))

(defun freqlist-count (freqlist-entry)
  (second  freqlist-entry))   ;take number of char frequency number

(defun freqlist-chars (freqlist-entry)
  (first ( first freqlist-entry)))  ;take character in frequency list

;Return t if weight htree1 is less than weight of htree2
(defun htree-less (htree1 htree2) 
   (<  (htree-weight htree1)  (htree-weight htree2)))

;Return a list of symbols contained in the Huffman tree
(defun htree-symbols (htree)
  (first (htree-root htree)))

;Return the weight of the Huffman tree
(defun htree-weight (htree)
  (second (htree-root htree)))

;Return the root node of a Huffman tree
(defun htree-root (htree)
  (first htree))

;Sorts a list of htrees by weight in ascending order
(defun htree-sort (htrees)
  (sort htrees #'htree-less))

;Returns a Huffman tree constructed from a paragraph.
(defun make-huffman-tree (text)
  (make-huffman-tree-iter (htree-sort (map 'list #'list (make-freqlist text ())))))

(defun make-huffman-tree-iter (htrees)
  (if (equal (length htrees) 1) 
      (first htrees) 
      (make-huffman-tree-iter 
       (htree-sort (cons 
		    (htree-merge (first htrees) (second htrees))
		    (rest (rest htrees)))))))
;A recursive function to construct a single Huffman tree from a list of Huffman trees.
(defun htree-merge (htree1 htree2)
  (list ;The list contains only one htree, return that htree.
   (list (append (htree-symbols htree1) (htree-symbols htree2))
	 (+ (htree-weight htree1) (htree-weight htree2)))  ;Two or more htrees remain. Sort the list of 
   htree1 htree2 )) ;htrees and merge the first two elements.


(get-file)
