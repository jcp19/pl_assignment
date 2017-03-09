#ideia: criar uma funcao que le um atributo de uma tag xml e outra que le o valor X
#devo tirar os spaces todos nas tags?
#ideia: usar css do museu da Pessoa X (melhorar)
#ideia: ordenar por data X (processar melhor datas)
#falta: por prefixo das fotos
#falta: listar lugares sem repeticoes
#ideia: para cada local, fazer pagina com as fotos desse local
#fazer: no relatorio, identificar assumpcoes adotadas, principalmente aos locais, e atributos no onde, datas, ordenacoes
##simpflificar, agregar padroes repetidos
# ordenar locais alfabeticamente
# fazer relatorio

function lerValorTag(nome_tag, linha){
	if(linha == ""){linha = $0}
	temp = gensub(".*<[[:space:]]*" nome_tag "[[:space:]]*>[[:space:]]*", "", 1, linha) 
        ret = gensub("</[[:space:]]*" nome_tag "[[:space:]]*>.*", "", 1, temp) 
	if(ret != linha){
		return ret
	}else {return ""}
}


function lerAtributoTag(nome_tag, nome_atributo, linha){
	if(linha == ""){linha = $0}
        temp = gensub(".*<[[:space:]]*" nome_tag "[[:space:]]+" nome_atributo "[[:space:]]*=[[:space:]]*", "", 1, linha) 
        aspas = substr(temp,0,1)
        split(temp, temp2, aspas)
        ret = temp2[2]
	#se a tag com o atributo pretendido nao for encontrada, sera igual a linha original
	if(temp == linha){
		return ""
	} else { return ret}
}


BEGIN             { RS = "</[[:space:]]*foto"
                    print "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n <title>Catálogo</title>\n <link rel=\"stylesheet\" type=\"text/css\" href=\"museu.css\" /></head>\n<body>\n<h1> Fotografias </h1><ul>" > "catalogo.html"
 
                  }
#como se pretende mostrar as pessoas e as fotos onde aparecem, as linhas que não tiverem alguem nao sao processadas
/<[[:space:]]*quem[[:space:]]*>/          { 
                        # ler nome do ficheiro
                        ficheiro = lerAtributoTag("foto", "ficheiro")
			#ler pessoas 
			pessoas = lerValorTag("quem")
			#data
			data = lerAtributoTag("quando", "data") 
			if(data == ""){
				data = lerValorTag("quando")
				if(data==""){ data="Desconhecida" }
			}
			#print "<h3><LI><b>" pessoas "</b></LI></h3> <center> <img src=\"" ficheiro ".jpg\"/> </center>" > "catalogo.html"
			entrada = "<h3><LI><b>" pessoas "</b></LI></h3> <center> <img src=\"" ficheiro ".jpg\"/> </center>\n<p>Data: "data"</p>" 
			entradas[entrada] = data
			#ler local	
			local = lerValorTag("onde")
			#regista o local
              		locais[local]

                    }

END 		    { 
                      delete locais[""]
		      asorti(entradas, copia_entradas,"@val_str_asc")
		      for(i in copia_entradas){
			print copia_entradas[i] > "catalogo.html"
		      }
		      print "</ul>\n<h1> Locais Fotografados </h1>\n<ul>" > "catalogo.html"
		      for( i in locais){
                         print "<li> " i " </li>" > "catalogo.html"
		      }
		      print "</ul></body>\n</html>" > "catalogo.html"
 		    }
