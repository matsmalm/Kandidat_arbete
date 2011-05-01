#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hashtab.h"
#include <time.h>

#define SIZE 75 // Set to at least the maximum size of your environments, 1024 (1024^2 nodes) should be enough. Bigger SIZE means longer computation time.
#define MAX_SIZE_SOLUTION 400 //set to a maximum size of solution array
#define MAX_TOTAL_AREA 100
#define MAX_SIZE_TOTAL_VISION 40



struct Node; // Forward definition to be able to use pointers to another node in each node.

struct Node{
	int name[2]; // rowindex = 0, columnindex = 1.
	struct Node *vision[SIZE*SIZE]; // Array with pointers to all Node visible
	struct Node *move[4]; // Array with pointers to all Node possible to move to.
	int state; // States 1-4. 1 = contains pursuer, 2 = seen by pursuer, 3 = guaranteed safe, 4 = none of states 1-3.
	//int left,down,up,right; // To be removed.
};

struct greedy{
  hashtab_t *tile_distance; //hash-tabell med avståndet mellan alla nod-par
  struct Node *total_area[MAX_TOTAL_AREA];  //total_area={totalt antal områden,r1,k1, r2,k2,...}, område1=(r1,k1)
  struct Node *total_vision_zero[MAX_SIZE_TOTAL_VISION];
  struct Node *node_matrix[SIZE][SIZE]; //B[][]
  int Break[2]; //brytvillkor för algoritm{nuvarande värde, givet brytvillkor}
  int solution[MAX_SIZE_SOLUTION]; //solution= {antal jagare,antal steg, sj1r1,sj1k1,..., sj1r2,sj1k2,...}
  int solution_iter_index;
};
