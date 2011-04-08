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

//globala variabler:-----------------------------------------------
//struct vars greedy; // struct med alla n�dv�ndiga variabler. 
struct Node **NodeMatrix; //Deklaration av nodn�tverket, omr�det.
int allArea[SIZE]; //Array med alla omr�den. index j�mt: rad, index udda: kolumn. 
int Hunter_pos[SIZE];   //Array med jagarnas positioner. jagare ett har (0,1) som index f�r (rad, kolumn).
int sight_size=100; //best�mmer maxstorleken p� hur m�nga unika omr�den alla jagare kan se tillsammans.
int sight[100];  //array med alla omr�den som syns av jagare.
//-----------------------------------------------------------------

//Deklaration av lokala funktioner:--------------------------------

//klara;
void getAreas();   //h�mtar alla omr�den och skriver dessa till int allArea[]
void getHunterpos(int *Hunter, int max);  // skriver jagarnas position till int Hunter_pos[]

//inte klara:
void one_hunter_vision(int r, int k, int *l, int *numvision);
void hunterVision(int *Hunter); // - evaluates starting conditions 
void nameCont(); // - name all contamined areas
void  identifyBoundry(); //- indentify boundry category a,b,c,d,e
void  extendBoundry(); //- extend boundrys of category a,c
void findEquiv(); // - find possible equivalent hunter positions
void evalCost(); // - purpose: run costfunctions and designate values for each direction
void evalDist();  //evaluate the distance to boundrys
void addDirection();// - add value to the directions that doesn't increase the distance to designated boundry
void designateArea(int high_low); // - designate one area to each hunter, category a,c must be chosen.   
void addDirection(); // - add value to the directions that doesn't increase the distance to designated boundry
void addGuardUniqueBound(); // - add value to directions closest to boundry
void addCatAC(); // - add value to directions where boundrys of category A and C are guarded uniquely
void addGuardVision(); // - add value to directions with maximum vision
void addOddness(); // - add a small value to a direction, to disable problems with extreme symmetry
void moveHunter(); // - moves hunters to maximum gain positions according to evalCost()
void uppdateEnv(); // - uppdate states and enviroment


//-----------------------------------------------------------------
/*struct vars{
  int sight;
  int max_hunter_index;
  int size;
}
*/

void preGreedy(struct Node (*NodeMat)[SIZE], int *Hunter, int BREAK){
  printf("Preprocessing greedy: \n");
 
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
  getAreas();
  int max= 2*Hunter[0];
  int *p1= &max;
  /*  
  //  testainneh�ll i Hunter
  i=0;
  while(i<=max){
    printf("Hunter[i]: %d \n", Hunter[i]);
    i++;  
  }
  */

  getHunterpos(Hunter, *p1);
}


void getAreas(){
  int rad=0;
  int kol=0;
  int i=0;
  while (rad<SIZE){
    while (kol<SIZE){
      if(NodeMatrix[rad][kol].vision[0]!=0){
	allArea[i]=rad;
	i++;
	allArea[i]=kol;
	i++;
      }
      kol++;
    }
    kol=0;
    rad++;
  }
  return;
}

void getHunterpos(int *Hunter, int max){
  int i=0;
  int *p1=&Hunter[1];
  //printf("Hunter 0: %d \n", *p1);
  int x;
  while (i<max){
    x= *(p1+i);
    //    printf("Hunter+1: %d \n", x);
    Hunter_pos[i]=x;
    // printf("Hunter_pos[%d] %d \n", i, Hunter_pos[i]);
    i++;
  }
  printf("excecuted getHunterpos \n");
  return;
}



void greedyAlg(struct Node *Map, int *Hunter, int BREAK){
  
  hunterVision(Hunter); // - evaluates starting conditions 
}



void hunterVision(int *Hunter){
  printf("init. hunterVision \n");
  int sight[sight_size]; //justera storlek s� att den passar till vad som �r rimligt... g�rna anpassat...
  int j=0;
  int r;
  int k;
  int i=0;
  int sight_length=0;
  int numsight=0;
  int *p1;
  int *p2;
  p1=&numsight;
  p2=&sight_length;
  printf("vid start g�ller:\n");
  printf("sight_length: %d\n",sight_length);
  printf("numsight: %d\n", numsight);
  printf("\n");
  while(j<2*Hunter[0]){
    r=Hunter_pos[j];
    j++;
    k=Hunter_pos[j];
    j++;
    printf("(%d, %d)\n", r,k);
    printf("init. onehunter run %d\n",j);
    one_hunter_vision(r,k,p2,p1);
    printf("exit. onehunter run %d\n",j);
    printf("\n");

    // printf("nu e sight_length: %d \n",sight_length);
    // printf("numsight: %d \n", numsight);
}
  /*  printf("numsight: %d \n", numsight);
   printf("sight: ");
 while (i<numsight){
   //  printf("(%d, ", sight[i]);
   i++;
   printf("%d) \n", sight[i]);
   i++;
}
  */

  /*
    1. skapa en array "sight" med alla omr�den som syns
    2. s� l�nge det finns jagare:
    3. ta en jagare
    4. h�mta synf�ltet f�r denna jagare ur NodeMatrix
    5. addera alla omr�den (som inte redan finns d�r)  till "sight"
    6. j�mf�r med "allArea[]" vilka omr�den som inte finns i "sight"
    7. identifiera vilka ytor detta ger
    8. peka p� n�gon slags adress till de olika ytorna.
  */
  
  
  printf("exit huntervision\n");
}

void one_hunter_vision(int r, int k, int *l, int *numsight){

  /*
  int h;
  h=0;
  while (h< 8){
  sight[(*l)]=2;
  (*l)++;
  (*numsight)++;
  h++;
  }

  */

  struct Node *self;
  struct Node *seen;
  int stop=0;
  int i=0;  

  self=&NodeMatrix[r][k];       //self �r en pekare p� noden (r,k)
  while ((*self).vision[i]!=0){ //kolla hur m�nga omr�den som syns fr�n self, lagra detta i "stop"
    i++;
    stop++;
  }
  i=0;
  int x;
  int m;  
  while (i<stop){ //s� l�nge det finns omr�den som syns fr�n (r,k)
    m=0;
    x=0;
    seen=(*self).vision[i];   //seen �r en av omr�dena som syns fr�n (r,k)
    while(m<=2*(*numsight)){
      if (sight[m]==(*seen).name[0]){
	if(sight[m+1]==(*seen).name[1]){//om b�da index redan finns bryt
	  x=1;
	  break;
	}
      }
      m=m+2;
    }
    if(x==0){ //om inga indexpar st�mde �verens ovan, l�gg till index i sight, �ka numsight
      sight[(*l)]=(*seen).name[0];
      (*l)++;
      sight[(*l)]=(*seen).name[1];
      (*l)++;
      (*numsight)++;	
    }

    i++;
  }
  i=0;  
}


void nameCont(){
  /*
    s� l�nge det finns pekare till olika ytor:
    1. ta en yta
    2. tillskriv ytan ett tillst�nd (s�krad, os�krad)
    3. tillskriv ytan ett namn/nummer
*/


}
void identifyBoundry(){
  /*
    s� l�nge det finns pekare till olika ytor:
    start loop
    1. ta en yta
    2. hitta alla omr�den vid randen till ytan.
    3. �r omr�det s�krat?
            tillskriv omr�det tillst�nd e
    4. finns det endast ett omr�de?
            kan man se hela omr�det fr�n randen?
	                 tillskriv omr�det tillst�nd a
			 loop return
	    tillskriv omr�det tillst�nd b
	    loop return
    5. kan man se hela omr�det fr�n randen?
            tillskriv omr�det tillst�nd c
	    loop return
    6. tillskriv omr�det tillst�nd d            
       loopreturn
   */

}
