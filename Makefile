prog:main.o enigme2.o
	gcc main.o enigme2.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx
enigme2.o:enigme2.c
	gcc -c enigme2.c -g
main.o:main.c
	gcc -c main.c -g
emoji: emoji.c
	gcc -o emoji emoji.c


