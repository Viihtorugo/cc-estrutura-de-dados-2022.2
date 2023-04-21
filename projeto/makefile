APP = ./app
BIN = ./bin
DOC = ./doc
OBJ = ./obj
SRC = ./src
FLAG = -lglut -lGLU -lGL

all: clean folders build myapp run

clean:
	rm -rf bin/ obj/

folders:
	mkdir bin/ obj/

build: \
	$(OBJ)/room.o 

myapp: $(BIN)/main

$(OBJ)/%.o: $(SRC)/%.c $(DOC)/%.h
	gcc -c $< -I $(DOC) -o $@

$(BIN)/%: $(APP)/%.c
	gcc $< $(OBJ)/*.o -I $(DOC) -o $@

run: 
	$(BIN)/main