SHELL=/bin/bash

relatorio.pdf: relatorio.tex
	pdflatex relatorio.tex
	bibtex relatorio.aux
	pdflatex relatorio.tex
	pdflatex relatorio.tex
	rm relatorio.{aux,log,out,toc,bbl,blg}
