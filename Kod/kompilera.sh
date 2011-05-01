gcc -g -O2 -c genetic.c
gcc -g -O2 -c greedy.c
gcc -g -O2 -c hashtab.c
gcc -g -O2 -c tabu.c
gcc -g -O2 -lm -o NodeGen NodeGenFromFile.c genetic.o greedy.o hashtab.o tabu.o
