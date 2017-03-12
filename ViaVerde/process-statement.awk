BEGIN {
	RS = "<TRANSACCAO>"
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

# Accao a realizar para cada novo extracto
/<EXTRACTO/ {
	id_extracto = ler_atributo_tag("EXTRACTO", "id", $0)
	mes_emissao = ler_valor_tag("MES_EMISSAO", $0)
	id_cliente = ler_atributo_tag("CLIENTE", "id", $0)
	nif = ler_valor_tag("NIF", $0)
	nome = ler_valor_tag("NOME", $0)

	# fmt_extracto esta definido no bloco BEGIN
	printf fmt_extracto, id_extracto, mes_emissao, nome, id_cliente, nif
}

# Accao a realizar para cada transaccao
/<\/TRANSACCAO>/ {
	importancia = 0
	parque = 0
	split($0, a, /<|>/)
	
	# a[1] tem a string vazia, por isso comecamos com i = 2
	for(i = 2; a[i] != "/TRANSACCAO"; ++i) {
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
	printf "\nTotal gasto = %.2f\n", total_viatura
	printf "Total gasto em parques = %.2f\n", total_viatura_parques
	
	total_fich += total_viatura
	total_parques_fich += total_viatura_parques
}

# Accao a realizar para cada viatura encontrada
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

	printf "\nTotal gasto = %.2f\n", total_fich
	printf "Total gasto em parques = %.2f\n", total_parques_fich
	
	# Atualiza os totais globais
	total += total_fich
	total_parques += total_parques_fich
}

END {
	print SEP_FICH "\nRESULTADOS GLOBAIS\n" SEP_FICH
	printf "Total gasto = %.2f\n", total
	printf "Total gasto em parques = %.2f\n", total_parques
}

# Funcao que assume que os indices i1 e i2 sao datas no formato dd-mm-yyyy
# e devolve -1 se i1 é mais antiga que i2, 0 se i1 == i2 ou 1 caso contrario.
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
	if(linha == "")
		linha = $0

	match(linha, "<" nome_tag "(\\s+.*)*>(.*)</" nome_tag "\\s*>", arr)
	return arr[2]
}

function ler_atributo_tag(nome_tag, nome_atributo, linha){
	if(linha == "")
		linha = $0

	# 0 ou mais atributos
	regex_atribs = "(\\s+\\w+\\s*=\\s*[\"'][^<\"]*[\"'])*"
	match(linha, "<" nome_tag regex_atribs "\\s+" nome_atributo "\\s*=\\s*[\"']([^<\"]*)[\"']" regex_atribs "\\s*>", arr)

	# o valor do atributo é capturado pelo segundo grupo (o primeiro grupo é regex_atribs)
	return arr[2]
}

# de - data de entrada (dd-mm-yyyy)
# he - hora de entrada (hh:mm)
# ds - data de saída   (dd-mm-yyyy)
# hs - hora de saída   (hh:mm)
function duracao(de, he, ds, hs) {
	split(de, de_arr, "-")
	split(ds, ds_arr, "-")
	split(he, he_arr, ":")
	split(hs, hs_arr, ":")

	# A especificacao da data tem de estar na forma YYYY MM DD HH MM SS, para ser passada para a funcao mktime
	spec_de = sprintf("%s %s %s %s %s %s", de[$3], de[$2], de[$1], he[$1], he[$2], "00")
	spec_ds = sprintf("%s %s %s %s %s %s", ds[$3], ds[$2], ds[$1], hs[$1], hs[$2], "00")

	return mktime(spec_ds) - mktime(spec_de)
}
