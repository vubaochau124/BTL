all:
	g++ -Isrc/include -Lsrc/lib -o main.exe main.cpp Board.cpp Button.cpp Game.cpp Snake.cpp Texture.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image 