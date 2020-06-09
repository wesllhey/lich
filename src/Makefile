FLEX = flex
BISON = bison

CC = gcc -Wall -g

all: lich

lich: parser.tab.o lexer.lex.o
	$(CC) -o $@ $^ -ly -lfl

parser.tab.o: parser.tab.c

lexer.lex.o: lexer.lex.c

parser.tab.c: parser.y
	$(BISON) -d $^

lexer.lex.c: lexer.l
	$(FLEX) -o $@ $^

clean:
	rm *.o lich