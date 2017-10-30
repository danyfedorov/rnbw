.PHONY: grammar_all

ANTLR=antlr3.2
GRAMMAR=rnbw.g

grammar_all: generate com

generate: $(GRAMMAR)
	$(ANTLR) $(GRAMMAR)

com: main.c rnbwLexer.c rnbwLexer.h rnbwParser.c rnbwParser.h
	gcc -g main.c rnbwLexer.c rnbwParser.c -lantlr3c

clean:
	rm rnbwLexer.* rnbwParser.* rnbw.tokens
