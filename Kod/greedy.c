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

void getAreas(struct Node *B[SIZE][SIZE],int *point, int *index){
  int rad=0;
  int kol=0;
  int i=1;
  printf("före while har vi,  point = %d \n", *point);
  while (rad<SIZE){
    
    while (kol<SIZE){
      //      printf("test varv %d namn %d \n", i, B[rad][kol].name[0]);
	*point=rad;
	*index++;
	*point=kol;
	*index++;
	printf("varv nummer %d, point = %d \n", i, *point);
	i++;
	//}
	kol++;
    }
    rad++;
  }
  return;
}

void preGreedy(struct Node *B[SIZE][SIZE], int *Hunter, int BREAK){
  int allArea[2*SIZE*SIZE];

  int *p1;  //declare integer pointer
  int *p2; //p2 as an pointer to an integer.
  allArea[5]=100;
  int indx;
  p2=&indx; //points p2 to the memory allocated for the variable indx
  *p2=0;  // sends the value 0 to the memory allocated for indx, eg. sets indx=0
  p1= &allArea[indx];
  printf("nukors getArea \n");
  getAreas(B, p1, p2);
  int j=0;
  /* while (j<SIZE*SIZE){   
    printf("%d \n",allArea[j]);
    j++;
    }*/
}

void greedyAlg(struct Node *Map, int *Hunter, int BREAK){
}
