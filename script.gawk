#ideia: criar uma funcao que le um atributo de uma tag xml e outra que le o valor 
#devo tirar os spaces todos nas tags?
#ideia: usar css do museu da Pessoa
#ideia: ordenar por data
#falta: listar lugares sem repeticoes
#ideia: para cada local, fazer pagina com as fotos desse local

BEGIN             { RS = "<foto"
                    print "<!DOCTYPE html>\n<html>\n<head>\n<title>Catálogo</title>\n</head>\n<body>\n<ul>" > "catalogo.html"
                  }
#como se pretende mostrar as pessoas e as fotos onde aparecem, as linhas que não tiverem alguem nao sao processadas
/<[[:space:]]*quem[[:space:]]*>/          { 
                        # ler nome do ficheiro
                        f1 = gensub(".*ficheiro=", "", 1) 
                      	aspas = substr(f1,0,1)
                        split(f1, f2, aspas)
                        ficheiro = f2[2]

			#ler pessoas 
                        pessoas1 = gensub(".*<[[:space:]]*quem[[:space:]]*>[[:space:]]*", "", 1) 
                        pessoas = gensub("</[[:space:]]*quem[[:space:]]*>.*", "", 1, pessoas1) 
			#print pessoas
			print "<LI><b>" pessoas "</b></LI> <center> <img src=\"" ficheiro ".jpg\"/> </center>" > "catalogo.html"
                    }

END 		    { print "</ul></body>\n</html>" > "catalogo.html"}
