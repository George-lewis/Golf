; Y-Combinator and recursion with anonynmous functions
; My head hurts.

#lang racket

; (define _factorial
;     (lambda (f)
;             (lambda (n)
;                 (if (equal? n 0)
;                     1
;                     (* n (f (- n 1)))))))

; (define Y
;     (lambda (f)
;         ((lambda (x) (f (lambda (a) ((x x)a))))
;          (lambda (x) (f (lambda (a) ((x x)a)))))))

; (define factorial (Y _factorial))

; (factorial 5)


(
    ((lambda (f)
        ((lambda (q) (q q))
             (lambda (x) (f (lambda (a) ((x x)a))))))
    (lambda (f)
            (lambda (n)
                (if (equal? n 0)
                    1
                    (* n (f (- n 1)))))))
    5
)