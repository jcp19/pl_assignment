v=inline_templates
$v: $v.fl
	flex --noyywrap $v.fl
	cc lex.yy.c -o $v
	rm lex.yy.c

install: $v
	 mkdir -p ~/bin/
	 mv $v ~/bin/
