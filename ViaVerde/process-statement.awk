BEGIN {
	RS = "<TRANSACCAO>"
	SEP = "--------------------------------------"
	total = total_parques = 0
}

# Accao a realizar para cada transaccao
/<\/TRANSACCAO/ {
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
		} else if(a[i] ~ /^VALOR_DESCONTO/) {
			importancia -= a[i+1]
		} else if(a[i] ~ /^TIPO/) {
			parque = (a[i+1] ~ "Parques de estacionamento")
		}
	}
	total += importancia
	if(parque)
		total_parques += importancia
}

END {
	n = asorti(entradas, d, "cmp_datas")
	print SEP "\na) Entradas em cada dia do mês\n" SEP
	for(i = 1; i <= n; ++i)
		print d[i] " -> " entradas[d[i]]

	n = asorti(saidas)
	print SEP "\nb) Lista dos locais de saida\n" SEP
	for(i = 1; i <= n; ++i)
		print saidas[i]

	print SEP "\nc) Total gasto = " total
	print "d) Total gasto em parques = " total_parques
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
