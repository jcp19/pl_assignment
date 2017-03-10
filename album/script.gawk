function lerValorTag(nome_tag, linha){
	if(linha == ""){linha = $0}
	temp = gensub(".*<" nome_tag "([[:space:]]+.*)*" "[[:space:]]*>[[:space:]]*", "", 1, linha) 
        ret = gensub("</" nome_tag "[[:space:]]*>.*", "", 1, temp) 
	if(ret == linha){
		ret = ""
	}
	return ret
}

function lerAtributoTag(nome_tag, nome_atributo, linha){
	if(linha == ""){linha = $0}
        temp = gensub(".*<" nome_tag "[[:space:]]+" nome_atributo "[[:space:]]*=[[:space:]]*", "", 1, linha) 
        aspas = substr(temp,0,1)
        split(temp, temp2, aspas)
        ret = temp2[2]
	#se a tag com o atributo pretendido nao for encontrada, temp sera igual a linha 
	if(temp == linha){
		ret = ""
	} 
	return ret
}

BEGIN             { RS = "</foto"
		    output = "album.html"
		    html_doctype = "<!DOCTYPE html>"
		    html_css = "<link rel=\"stylesheet\" type=\"text/css\" href=\"museu.css\" />"
		    html_head = "<head><meta charset=\"UTF-8\"><title> Album Fotográfico </title>" html_css "</head>"
                    print html_doctype html_head "<html><body>\n<h1> Fotografias </h1><ul>" > output
		  }
#como se pretende mostrar as pessoas e as fotos onde aparecem, as linhas que não tiverem a tag "quem" nao sao processadas
/<quem(\s+.*)*/   { 
                        ficheiro = lerAtributoTag("foto", "ficheiro")
			pessoas = lerValorTag("quem")
			data = lerAtributoTag("quando", "data") 
			if(data==""){
				data = lerValorTag("quando")
			}
			facto = lerValorTag("facto")
			local = lerValorTag("onde")
			
			#regista o local
              		locais[local]

			#campos formatados para html
			local_formatado = (local == "")? "" : "<p> Local: " local "</p>" 
			data_formatada = (data=="")? "" : "<p>Data: " data "</p> "
			facto_formatado = (facto == "")? "" : "<h5>" facto "</h5>"
			pessoas_formatado = "<h3><LI><b>" pessoas "</b></LI></h3>" 
			imagem_formatada = "<img src=\"" ficheiro ".jpg\"/>"
			
			entrada = pessoas_formatado "<center>" imagem_formatada "</center>\n" facto_formatado data_formatada local_formatado
			entradas[entrada] = data
                    }

END 		    { 
                      delete locais[""]
		      asorti(entradas, copia_entradas,"@val_str_asc")
		      for(i in copia_entradas){
			print copia_entradas[i] > output 
		      }
		      print "</ul>\n<h1> Locais Fotografados </h1>\n<ul>" > output 
		      #ordena locais alfabeticamente
                      asorti(locais)
		      for(i in locais){
                         print "<li> " locais[i] " </li>" > output 
		      }
		      print "</ul></body>\n</html>" > output 
 		    }
