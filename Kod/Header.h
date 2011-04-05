#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "genetic.h"
#include "greedy.h"

#define SIZE 10

struct Node; // Forward definition to be able to use pointers to another node in each node.

struct Node{
	int name[2]; // rowindex = 0, columnindex = 1.
	struct Node *vision[SIZE*SIZE]; // Array with pointers to all Node visible.
	struct Node *move[4]; // Array with pointers to all Node possible to move to.
	int state; // States 1-4. 1 = contains pursuer, 2 = seen by pursuer, 3 = guaranteed safe, 4 = none of states 1-3.
	//int left,down,up,right; // To be removed.
}B[SIZE][SIZE];

