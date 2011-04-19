gcc -g -c genetic.c
gcc -g -c greedy.c
gcc -g -c hashtab.c
gcc -g -c assignemtoptimal_impl.c
gcc -g -o NodeGen NodeGenFromFile.c genetic.o greedy.o hashtab.o assignmentoptimal_impl.o