.PHONY: all clean

# Targets
all: codegen
 
codegen: lex.yy.c y.tab.c function.c
	gcc -o codegen lex.yy.c y.tab.c function.c -lfl

lex.yy.c :scanner.l
	flex scanner.l

y.tab.c: parser.y
	byacc -d parser.y

clean:
	rm -f lex.yy.c y.tab.c y.tab.h  codegen