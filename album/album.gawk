function ler_valor_tag(nome_tag, linha) {
    if(linha == "") {
        linha = $0
    }
    match(linha, "<" nome_tag "(\\s+.*)*>(.*)</" nome_tag "\\s*>", arr)
    return arr[2]
}

function ler_atributo_tag(nome_tag, nome_atributo, linha){
    if(linha == "") {
        linha = $0
    }
    regex_atributos = "\\w+\\s*=\\s*(\"[^<\"]*\")|(\\'[^<\\']*\\')"
    temp = gensub(".*<" nome_tag "(\\s+" regex_atributos ")*\\s+" nome_atributo "\\s*=\\s*", "", 1, linha) 
    aspas = substr(temp,0,1)
    split(temp, temp2, aspas)
    ret = temp2[2]
    # se a tag com o atributo pretendido nao for encontrada, temp sera igual a linha 
    if(temp == linha) {
        ret = ""
    } 
    return ret
}

# funcao simplificada que poe uma string num formato simplificado do url encode 
function url_encode(linha) {
    ret = gensub("\\s", "+", "G", linha)
    ret = gensub("!", "%21", "G", ret)
    ret = gensub(":", "%3A", "G", ret)
    ret = gensub("'", "%27", "G", ret)
    ret = gensub(",", "%2C", "G", ret)
    return ret
}

BEGIN {
    RS = "</foto"
    output = "album.html"
    html_doctype = "<!DOCTYPE html>"
    html_css = "<link rel=\"stylesheet\" type=\"text/css\" href=\"museu.css\" />"
    html_head = "<head><meta charset=\"UTF-8\"><title> Album Fotográfico </title>" html_css "</head>"
    
    print html_doctype html_head "<html><body>\n<h1> Fotografias </h1><ul>" > output
}

# como se pretende mostrar as pessoas e as fotos onde aparecem, 
# as linhas que não tiverem a tag "quem" nao sao processadas

/<quem(\s+.*)*/  { 
 
    ficheiro = ler_atributo_tag("foto", "ficheiro")
    pessoas = ler_valor_tag("quem")
    data = ler_atributo_tag("quando", "data") 
    if(data=="") {
        data = ler_valor_tag("quando")
    }
    facto = ler_valor_tag("facto")
    local = ler_valor_tag("onde")
                    
    # regista o local
    locais[local]
                    
    # campos formatados para html
    local_formatado = (local == "")? "" : "<center><p> Local: " local "</p></center>" 
    data_formatada = (data=="")? "" : "<center><p>Data: " data "</p></center> "
    facto_formatado = (facto == "")? "" : "<center><h5>" facto "</h5></center>"
    pessoas_formatado = "<h3><LI><b>" pessoas "</b></LI></h3>" 
    imagem_formatada = "<img src=\"" ficheiro "\"/>"

    entrada = pessoas_formatado "<center>" imagem_formatada "</center>\n" facto_formatado data_formatada local_formatado
    entradas[entrada] = data
}

END { 
    delete locais[""]
    asorti(entradas, copia_entradas,"@val_str_asc")
    for(i in copia_entradas) {
        print copia_entradas[i] > output 
    }
    print "</ul>\n<h1> Locais Fotografados </h1>" > output 
    # ordena locais alfabeticamente
    asorti(locais)
    # gera mapa
    url = "https://maps.googleapis.com/maps/api/staticmap?key=AIzaSyAGDCGp6aTCV7_JQC3KNW2X3pmkOJxgMyw&size=640x480&markers="
    for(i in locais) {
        url = url "|" url_encode(locais[i])  
    }
    print "<ul>" > output
    for(i in locais) {
        print "<li> " locais[i] " </li>" > output 
    }
    print "</ul>  <center><img src=\"" url "\"/></center> <hr width=800> <center><p>  Feito por João Pereira(A75273), João Martins(A68646), Manuel Freitas(A71646) </p><img src=\"logoUM.jpg\"  width=\"100\" height=\"50\"></center></body>\n</html>" > output 
}
