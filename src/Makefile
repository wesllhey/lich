FLEX = flex
BISON = bison

CC = gcc -Wall -g

all: lich

lich: alloc.o hash_table.o symbol_table.o ast.o parser.tab.o lexer.lex.o
	$(CC) -o $@ $^ -lfl

alloc.o: alloc.c
	$(CC) -c $^

hash_table.o: hash_table.c
	$(CC) -c $^

symbol_table.o: symbol_table.c
	$(CC) -c $^

ast.o: ast.c
	$(CC) -c $^

parser.tab.o: parser.tab.c

lexer.lex.o: lexer.lex.c

parser.tab.c: parser.y
	$(BISON) -d $^

lexer.lex.c: lexer.l
	$(FLEX) -o $@ $^

clean:
	rm *.o

# all: tests

# tests: tests.o  alloc.o hash_table.o symbol_table.o ast.o
# 	$(CC) -o $@ $^

# %.o: %.c
# 	$(CC) -c $^

# clean:
# 	rm *.o tests