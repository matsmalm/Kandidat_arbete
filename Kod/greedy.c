/*
  function call-order:
    void preGreedy(struct Node *NodeMat, int *Hunters, int BREAK)
       getAreas()  -- creates an array with a list of all indices of the enviroment
       getHunterpos() -- creates an array with the hunter startpositions
 
    greedyAlg(struct Node *NodeMat, int *Hunters, int BREAK)
       one iteration:
-----------------Phase One, Preparations-----------------------------
       hunterVision() - evaluates starting conditions 
       nameCont() - name all contamined areas
       identifyBoundry() - indentify boundry category a,b,c,d,e
       extendBoundry() - extend boundrys of category a,c
       findEquiv() - find possible equivalent hunter positions
---------------------------------------------------------------------
*********************************************************************
-----------------Phase Two, Cost Evaluatuion-------------------------	   
       evalCost() - purpose: run costfunctions and designate values for each direction
         evalDist() - evaluate distance for each hunter to each boundry
           if (number of hunters)>= (number of areas){
	       designateArea(HigH) - designate one area to each hunter, category a,c must be chosen.
	       addDirection() - add value to the directions that doesn't increase the distance to designated boundry
           }
	   else {
	       designateArea(Low) - designate one hunter to each area, category
	       addDirection() - add values to the directions that dosen't increase the distance to designated boundry
	   }
	 
         addGuardUniqueBound() - add value to directions closest to boundry
         addCatAC() - add value to directions where boundrys of category A and C are guarded uniquely
	 addGuardVision() - add value to directions with maximum vision
	 addOddness() - add a small value to a direction, to disable problems with extreme symmetry
	 
---------------------------------------------------------------------
*********************************************************************
-----------------Phase three, move ----------------------------------
         moveHunter() - moves hunters to maximum gain positions according to evalCost()
	 uppdateEnv() - uppdate states and enviroment
---------------------------------------------------------------------
return: array with move strategy. 



*/



#include "Header.h"

struct Node **NodeMatrix; //global deklaration av nodnätverket, området.
int allArea[2*SIZE*SIZE]; //global array med alla områden. index jämt: rad, index udda: kolumn. 


void getAreas(){
  int rad=0;
  int kol=0;
  int i=0;
  //fortsätt här
  while (rad<SIZE){
    while (kol<SIZE){
      printf("NodeMatrix[%d][%d]. vision är: %d \n", rad, kol, NodeMatrix[rad][kol].vision[0]);
      if(NodeMatrix[rad][kol].vision[0]!=0){
	allArea[i]=rad;
	i++;
	allArea[i]=kol;
	i++;
      }
      kol++;
    }
    rad++;
  }
  return;
}



void preGreedy(struct Node (*NodeMat)[SIZE], int *Hunter, int BREAK){
  printf("Preprocessing greedy: \n ");

  int i,j;
  NodeMatrix = malloc(SIZE * sizeof(struct Node *));
  if(NodeMatrix == NULL)
    {
      fprintf(stderr, "out of memory\n");
    }
  for(i = 0; i < SIZE; i++)
    {
      NodeMatrix[i] = malloc(SIZE * sizeof(struct Node));
      if(NodeMatrix[i] == NULL)
	{
	  fprintf(stderr, "out of memory\n");
	}
    }
  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      NodeMatrix[i][j] = NodeMat[i][j];
    }
  }
  int *p1;  //declare integer pointer
  int *p2; //p2 as an pointer to an integer.
  allArea[5]=100;
  int indx;
  p2=&indx; //points p2 to the memory allocated for the variable indx
  *p2=0;  // sends the value 0 to the memory allocated for indx, eg. sets indx=0
  p1= &allArea[indx];
  printf("nukors getArea \n");
  getAreas();

}

void greedyAlg(struct Node *Map, int *Hunter, int BREAK){
}
