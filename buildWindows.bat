echo "compiling bezier.c"
gcc -c bezier.c -o bin/bezier.o -Wall
echo "compiling surface.c"
gcc -c surface.c -o bin/surface.o -Wall
echo "compiling transformation.c"
gcc -c transformations.c -o bin/trans.o -Wall
echo "compiling items.c"
gcc -c items.c -o bin/items.o -Wall

echo "compiling main.c"
gcc -c main.c -o bin/main.o -Wall

echo "compiling project"
gcc bin/main.o bin/surface.o bin/items.o bin/bezier.o bin/trans.o -o surface.exe -Wall -lm