all:
	g++ *.cpp -w -lSDL2 -lSDL2_image -lSDL2_ttf -o snake
	./snake
