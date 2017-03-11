# TODO
# Funcao generica que dada a indentacao, nome e conteudo de uma tab, imprime-a

# As funcoes estao no final do ficheiro

BEGIN {
	FS = ";"
}

# So funciona a partir da versao 4 do gawk
BEGINFILE {
	id_viatura = ""
	total = total_iva = total_viatura = 0
	print "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
}

/DOCUMENTO N\./ { id_extracto = $2 }
/DATA DE/ { mes_emissao = $2 }
/NIF/ { nif = $2 }
/CONTRATO N\./ { id_cliente = $2 }
/NOME/ { nome = $2 }
/MORADA/ { morada = $2 }

/IDENTIFICADOR/ {
	imprime_cabecalho(id_extracto, mes_emissao, id_cliente, nif, nome, morada)
}

# Linha que começa com o identificador do veiculo (indica uma transaccao)
/[0-9]+;/ {
	# Testa se passamos para as transaccoes de outra viatura
	if($1 != id_viatura) {
		# se nao e a primeira viatura, imprime o total gasto na viatura
		# anterior, fecha a tag <IDENTIFICADOR> dessa viatura, atualiza
		# o total global e repoe total_viatura a 0
		if(id_viatura != "") {
			fecha_transaccoes_id()
		}
		id_viatura = $1
		imprime_dados_viatura($1, $2, $3)
	}

	print "\t\t<TRANSACCAO>"
	if($4 != "") {
		printf "\t\t\t<DATA_ENTRADA>%s</DATA_ENTRADA>\n", $4
		printf "\t\t\t<HORA_ENTRADA>%s</HORA_ENTRADA>\n", $5
		printf "\t\t\t<ENTRADA>%s</ENTRADA>\n", $6
	} else {
		print "\t\t\t<DATA_ENTRADA>null</DATA_ENTRADA>"
		print "\t\t\t<HORA_ENTRADA />"
		print "\t\t\t<ENTRADA />"
	}
	printf "\t\t\t<DATA_SAIDA>%s</DATA_SAIDA>\n", $7
	printf "\t\t\t<HORA_SAIDA>%s</HORA_SAIDA>\n", $8
	printf "\t\t\t<ENTRADA>%s</ENTRADA>\n", $9
	
	printf "\t\t\t<VALOR>%s</VALOR>\n", $10
	printf "\t\t\t<VALOR_DESCONTO>%s</VALOR_DESCONTO>\n", $11
	printf "\t\t\t<TAXA_IVA>%s</TAXA_IVA>\n", $12
	printf "\t\t\t<OPERADOR>%s</OPERADOR>\n", $13
	printf "\t\t\t<TIPO>%s</TIPO>\n", $14
	printf "\t\t\t<DATA_DEBITO>%s</DATA_DEBITO>\n", $15
	printf "\t\t\t<CARTAO>%s</CARTAO>\n", $16
	
	print "\t\t</TRANSACCAO>"
	total_viatura += ($10 - $11)
	total_iva += ($10 * $12 / 100)
}

ENDFILE {
	if(id_viatura != "") {
		fecha_transaccoes_id()
	}
	printf "\t<TOTAL>%.2f</TOTAL>\n", total
	printf "\t<TOTAL_IVA>%.2f</TOTAL_IVA>\n", total_iva
	print "</EXTRACTO>"
}

function imprime_cabecalho(id_extracto, mes_emissao, id_cliente, nif, nome, morada) {
	printf "<EXTRACTO id=\"%s\">\n", id_extracto
	printf "\t<MES_EMISSAO>%s</MES_EMISSAO>\n", mes_emissao
	printf "\t<CLIENTE id=\"%s\">\n", id_cliente
	printf "\t\t<NIF>%s</NIF>\n", nif
	printf "\t\t<NOME>%s</NOME>\n", nome
	printf "\t\t<MORADA>%s</MORADA>\n", morada
	print "\t</CLIENTE>"
}

function imprime_dados_viatura(id_viatura, matricula, ref_pagamento) {
	printf "\t<IDENTIFICADOR id=\"%s\">\n", id_viatura
	printf "\t\t<MATRICULA>%s</MATRICULA>\n", matricula
	printf "\t\t<REF_PAGAMENTO>%s</REF_PAGAMENTO>\n", ref_pagamento
}

function fecha_transaccoes_id() {
	printf "\t\t<TOTAL>%.2f</TOTAL>\n", total_viatura
	print "\t</IDENTIFICADOR>"
	total += total_viatura
	total_viatura = 0
}
