.PHONY: all grammar grammar_gen grammar_com com app build run clean

CC=g++
NAME=rnbw
LIBS=-lantlr3c
FLAGS=-std=c++11 -Wall
FILES=main.cpp \
      clrs.cpp clrs.h \
      core.cpp core.h \
      arg_parser.cpp arg_parser.h
OBJS=main.o clrs.o core.o arg_parser.o

GRAMMAR_FILES=grammar/rnbwParser.c grammar/rnbwParser.h \
              grammar/rnbwLexer.c grammar/rnbwLexer.h
GRAMMAR_OBJS=grammar/rnbwParser.o grammar/rnbwLexer.o

all: grammar app

# grammar
grammar: grammar_gen grammar_com
grammar_gen:
	$(MAKE) -C $(shell pwd)/grammar generate
grammar_com:
	$(MAKE) -C $(shell pwd)/grammar compile

# app
com: $(FILES)
	$(CC) $(FLAGS) -c $(FILES)
build: $(FILES)
	$(CC) $(FLAGS) $(OBJS) $(GRAMMAR_OBJS) -o $(NAME) $(LIBS)
app: com build
run: all
	./rnbw

# files
arg_parser.o: arg_parser.h arg_parser.cpp
	$(CC) $(FLAGS) -c arg_parser.h arg_parser.cpp
core.o: core.h core.cpp
	$(CC) $(FLAGS) -c core.h core.cpp

# asm:
# 	g++ -S -g main.cpp -o main.s
# 	as -alhnd main.s > main.lst

clean:
	rm rnbw *~ main.lst main.s a.out *.o *.gch
