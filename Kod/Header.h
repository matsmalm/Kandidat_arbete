#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 20 // Set to at least the maximum size of your environments, 1024 (1024^2 nodes) should be enough. Bigger SIZE means longer computation time.

struct Node; // Forward definition to be able to use pointers to another node in each node.

struct Node{
	int name[2]; // rowindex = 0, columnindex = 1.
	struct Node *vision[SIZE*SIZE]; // Array with pointers to all Node visible.
	struct Node *move[4]; // Array with pointers to all Node possible to move to.
	int state; // States 1-4. 1 = contains pursuer, 2 = seen by pursuer, 3 = guaranteed safe, 4 = none of states 1-3.
	//int left,down,up,right; // To be removed.
};

struct greedy{
  int tile_distance[400]; //tabell med avståndet mellan alla nod-par
  struct Node *total_area[100];  //total_area={totalt antal områden,r1,k1, r2,k2,...}, område1=(r1,k1)
  struct Node (*node_matrix)[SIZE][SIZE]; //B[][]
  int Break[2]; //brytvillkor för algoritm{nuvarande värde, givet brytvillkor}
  int solution[200]; //solution= {antal jagare,antal steg, sj1r1,sj1k1,..., sj1r2,sj1k2,...}
};
