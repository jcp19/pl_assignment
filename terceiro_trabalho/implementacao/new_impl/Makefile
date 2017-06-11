all: compiler

compiler: gramatica.fl gramatica.y
	flex intp.fl
	yacc intp.y
	gcc y.tab.c `pkg-config --cflags --libs glib-2.0` -o compilador

clean:
	rm -f y.tab.c lex.yy.c compilador
