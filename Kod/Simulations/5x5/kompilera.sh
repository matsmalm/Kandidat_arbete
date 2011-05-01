gcc -O2 -c genetic.c
gcc -O2 -c greedy.c
gcc -O2 -c hashtab.c
gcc -O2 -c tabu.c
gcc -O2 -lm -o NodeGen-5x5 NodeGenFromFile.c genetic.o greedy.o hashtab.o tabu.o
