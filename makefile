# Building
CC = g++
CFLAGS = -lGL -lGLU -lglut -O3
OUT = pacman
IN = pacman.cpp

# Formatting
CLANG_STYLE = {BasedOnStyle: google, IndentWidth: 4}


mainmake: $(IN)
	$(CC) $(IN) -o $(OUT) $(CFLAGS)

.PHONY: clean

clean: $(OUT)
	rm $(OUT)

.PHONY: format

format: $(IN)
	clang-format -i $(IN) -style="$(CLANG_STYLE)"	