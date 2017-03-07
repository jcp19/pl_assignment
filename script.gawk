BEGIN {FS = "/ e /|,"}
/<quem>.*<\/quem>/ {
                    #gensub("", "", 1) 
                    print gensub("Da esquerda para a direita:[[:space:]]*|[[:space:]]*<uem>[[:space:]]*", "", "G") 
                    #print $1 "||" $2
		    #FS = " "
		    #if($0 ~"Da esquerda para a direita:"){
                    #	print gensub("Da esquerda para a direita:", "", 1) " bla"
		    #}

}
