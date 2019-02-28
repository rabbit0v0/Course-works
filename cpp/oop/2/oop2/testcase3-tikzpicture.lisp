(define "unpaired" "usepackage")
(define "unpaired" "tableofcontents")
(define "unpaired" "maketitle")
(define "unpaired" "title")
(define "unpaired" "author")
(define "paired" "tikzpicture")
(define "unpaired" "draw")
(define "unpaired" "shade")
(define "unpaired" "filldraw")

(usepackage "tikz")
(title "Testcase 3 Tikz Graphics")
(author "OOP2")
(document
 (maketitle)
 (tableofcontents)
 (endpage)
 (section "Graph1")
 (tikzpicture
  (draw)
  "(0,0) circle [radius=1.5];"
  (draw)
  "(0,0) circle (2cm);"
  (draw)
  "(0,0) circle [x radius=1.5cm, y radius=10mm];"
  (draw)
  "(0,0) circle (1.2cm and 8mm);"
  (draw)
  "(0,0) circle [x radius=1cm, y radius=5mm, rotate=30];"
  (draw)
  "[rotate=30] (0,0) ellipse (20pt and 10pt);"
  )
 (section "Graph2")
 (tikzpicture
  (draw)
  "(0,0) rectangle (1,1);"
  (shade)
  "[top color=yellow, bottom color=black] (0,0) rectangle (2,-1);"
  (filldraw)
  "[fill=green!20!white, draw=green!40!black] (0,0) rectangle (2,1);"
  )
 (section "Graph3")
 (tikzpicture
  (draw) "[help lines] (-2,0) grid (2,4);" 
  (draw) "[->] (-2.2,0) -- (2.2,0);" 
  (draw) "[->] (0,0) -- (0,4.2);" 
  (draw) "[green, thick, domain=-2:2] plot (\\x, {4-\\x*\\x});"
  (draw) "[domain=-2:2, samples=50] plot (\\x, {1+cos(pi*\\x r)});"
  )
 )
