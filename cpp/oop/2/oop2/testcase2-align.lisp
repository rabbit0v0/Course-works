(define "unpaired" "tableofcontents")
(define "unpaired" "maketitle")
(define "unpaired" "title")
(define "unpaired" "author")
(define "unpaired" "frac")

(title "Testcase 2")
(author "OOP2")
(document
 (maketitle)
 (tableofcontents)
 (endpage)
 (section "Section 1")
 (subsection "Subsection 1.1")
 (align
    "S_n &= (n + 1)(n + 2)T_n \\\\"
    "&=(n + 1)(n + 2)H_{n + 2} + 2(n + 1) - \\frac{5}{2}(n + 1)(n + 2) \\\\"
    "&=(n + 1)(n + 2)H_{n + 1} + 3(n + 1) - \\frac{5}{2}(n + 1)(n + 2) \\\\"
    "S_{n - 1} &= (n + 1)nH_n + 3n - \\frac{5}{2}(n + 1)n \\\\"
    "S_n &= (n + 1)(n + 2)H_n + (4n + 5) - \\frac{5}{2}(n + 1)(n + 2) \\\\"
    "(5)-(4):"
    "E_n &= 2(n + 1)H_n +n + 5 - 5(n + 1) \\\\"
    "&=2(n + 1)H_n -4n"
  )
 )
 
