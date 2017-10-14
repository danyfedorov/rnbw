default: build

build: main.cpp clrs.cpp clrs.h
	@g++ -std=c++11 -Wall main.cpp clrs.cpp -o rnbw -lncurses

run: build
	@./rnbw

# asm:
# 	@g++ -S -g main.cpp -o main.s
# 	@as -alhnd main.s > main.lst

clean:
	@-rm rnbw *~ main.lst main.s a.out || true
