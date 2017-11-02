.PHONY: grammar_all generate compile clean

ANTLR=antlr3.2
GRAMMAR=rnbw.g

CC=gcc
FILES=rnbwLexer.c rnbwLexer.h rnbwParser.c rnbwParser.h

grammar_all: generate com

generate: $(GRAMMAR)
	$(ANTLR) $(GRAMMAR)

compile: $(FILES)
	$(CC) -c $(FILES)

clean:
	rm rnbwLexer.* rnbwParser.* rnbw.tokens *.h.gch *.o
