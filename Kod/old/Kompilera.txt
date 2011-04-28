gcc -c genetic.c
gcc -c greedy.c
gcc -o NodeGen NodeGenFromFile.c genetic.o greedy.o
