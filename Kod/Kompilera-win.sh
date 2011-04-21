gcc -g -c genetic.c && gcc -g -c greedy.c && gcc -g -c tabu.c && gcc -g -c hashtab.c && gcc -g -lm -o NodeGen NodeGenFromFile.c genetic.o greedy.o hashtab.o tabu.o
