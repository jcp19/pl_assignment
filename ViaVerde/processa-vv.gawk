BEGIN {
	RS = "<TRANSACCAO"
	SEP = "============================================="
	SEP_FICH = "#############################################"
	fmt_extracto = "EXTRACTO Nº: %s\nMES: %s\nNOME: %s\nID: %s\nNIF: %s\n"
	fmt_identificador = "IDENTIFICADOR: %s\nMATRICULA: %s\nREF. PAGAMENTO: %s\n"

	total = total_parques = 0
}

BEGINFILE {
	total_fich = total_parques_fich = 0
	print SEP_FICH
}

# Acção a realizar para cada novo extracto
/<EXTRACTO/ {
	id_extracto = ler_atributo_tag("EXTRACTO", "id", $0)
	mes_emissao = ler_valor_tag("MES_EMISSAO", $0)
	id_cliente = ler_atributo_tag("CLIENTE", "id", $0)
	nif = ler_valor_tag("NIF", $0)
	nome = ler_valor_tag("NOME", $0)

	# fmt_extracto está definido no bloco BEGIN
	printf fmt_extracto, id_extracto, mes_emissao, nome, id_cliente, nif
}

# Acção a realizar para cada transacção
/<\/TRANSACCAO/ {
	importancia = 0
	parque = 0
	split($0, a, /<|>/)
	
	# a[1] tem a string vazia, por isso começamos com i = 2
	for(i = 2; a[i] !~ "/TRANSACCAO"; ++i) {
		if(a[i] ~ /^DATA_ENTRADA/) {
			data = a[i+1]
			if(data != "null")
				++entradas[data]
		} else if(a[i] ~ /^SAIDA/) {
			++saidas[a[i+1]]
		} else if(a[i] ~ /^IMPORTANCIA/) {
			importancia = a[i+1]
			++n_viatura
		} else if(a[i] ~ /^VALOR_DESCONTO/) {
			importancia -= a[i+1]
		} else if(a[i] ~ /^TIPO/) {
			parque = (a[i+1] ~ "Parques de estacionamento")
		}
	}
	total_viatura += importancia
	if(parque)
		total_viatura_parques += importancia
}

/<\/IDENTIFICADOR/ {
	print SEP
	printf fmt_identificador, id, matricula, ref_pagamento
	printf "\nTotal gasto = %.2f EUR\n", total_viatura
	printf "Total gasto em parques = %.2f EUR\n", total_viatura_parques
	
	total_fich += total_viatura
	total_parques_fich += total_viatura_parques
}

# Acção a realizar para cada viatura encontrada
/<IDENTIFICADOR/ {
	id = ler_atributo_tag("IDENTIFICADOR", "id", $0)
	matricula = ler_valor_tag("MATRICULA", $0)
	ref_pagamento = ler_valor_tag("REF_PAGAMENTO", $0)

	total_viatura = total_viatura_parques = 0
}

ENDFILE {
	print SEP "\nRESULTADOS DO MÊS " mes_emissao "\n"

	n = asorti(entradas, d, "cmp_datas")
	print "+------------+-------------+"
	print "| Dia        | N. entradas |"
	print "+------------+-------------+"
	for(i = 1; i <= n; ++i) {
		printf "| %10s | %-11d |\n", d[i], entradas[d[i]]
	}
	print "+------------+-------------+"
	delete entradas

	n = asorti(saidas)
	print "\nLocais de saida:"
	for(i = 1; i <= n; ++i) {
		print "-> " saidas[i]
	}
	delete saidas

	printf "\nTotal gasto = %.2f EUR\n", total_fich
	printf "Total gasto em parques = %.2f EUR\n\n", total_parques_fich
	
	# Atualiza os totais globais
	total += total_fich
	total_parques += total_parques_fich
}

END {
	print SEP_FICH "\nRESULTADOS GLOBAIS\n" SEP_FICH
	printf "Total gasto = %.2f EUR\n", total
	printf "Total gasto em parques = %.2f EUR\n", total_parques
}

# Função que assume que os índices i1 e i2 são datas no formato dd-mm-yyyy
# e devolve -1 se i1 é mais antiga que i2, 0 se i1 == i2 ou 1 caso contrário.
function cmp_datas(i1, v1, i2, v2) {
	split(i1, d1, "-")
	split(i2, d2, "-")
	r = 0
	for(i = 3; !r && i >= 1; --i) {
		if(d1[i] < d2[i])
			r = -1
		else
			r = (d1[i] != d2[i])
	}
	return r
}

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
