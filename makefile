.PHONY: all grammar run clean

CC=g++
NAME=rnbw
LIBS=-lantlr3c
FLAGS=-std=c++11 -Wall -g
FILES=main.cpp \
      clrs.cpp clrs.h \
      core.cpp core.h \
      arg_parser.cpp arg_parser.h \
      grammar/rnbwParser.c grammar/rnbwParser.h \
      grammar/rnbwLexer.c grammar/rnbwLexer.h \



all: grammar app

grammar:
	$(MAKE) -C $(shell pwd)/grammar generate

app: $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $(NAME) $(LIBS)

run: all
	./rnbw

# asm:
# 	@g++ -S -g main.cpp -o main.s
# 	@as -alhnd main.s > main.lst

clean:
	rm rnbw *~ main.lst main.s a.out
