(defun fib (x) (if (< x 2) x (+ (fib (- x 1))(fib (- x 2)))))

(loop for x from 1 to 10 do (print (fib x))) 
