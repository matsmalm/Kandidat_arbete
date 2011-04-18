/*
notes to self:
-s�tt solution som en global variabel ist�llet?
-i enviroment_cleared, korrigera konstanten "correct_size=22"
-i enviroment_cleared, korrigera villkor rad 205 s� att alla tillst�nd skilda fr�n os�krade
 
-i get_vision(), rad 330 eventuellt uppdatera states s� att man skiljer p� sedd, och unikt sedd
-f�resl� SIZE och OBSTACLE som globala, f�r att kunna s�tta storlekar p� array etc.
-frig�r allocerat minne fr�n get_area() mellan itterationer
*/
//  function call-order:

#include "Header.h"
#include "greedy.h"
//---------------variabel declaration---------------------------  
#define TRUE 1
#define FALSE 0
#define designatedirection 50
#define close 1     //parameter for cost function. distance to boundry
#define unique 1 // parameter for cost function. unique visible boundrys
#define priority 1 // parameter for cost function. priorized visible boundrys
#define big_vision 1  // parameter for cost function. largest vision

#define SEEN 2
#define HUNTER 1
#define CONTAMINED 4
#define SECURED 3
//priorities
#define PRIO_SECURED 5
#define PRIO_VIS_ONE_BOUND 4
#define PRIO_VIS_SEV_BOUND 3
#define PRIO_ONE_BOUND 2
#define PRIO_SEV_BOUND 1

#define CHECKED 20
#define MARKED 10

#define UNIQUE 100

#define MAX_SIZE_AREA_COLLECTION 40
struct valuation{
  //solution[solution_iter_index+rj] placerar radindex f�r jagare j i aktuell iteration.
  struct Node *total_vision[MAX_SIZE_TOTAL_VISION];
  struct Area *area_collection[MAX_SIZE_AREA_COLLECTION];
};

struct move{
  struct Node *next_move[30];
};

struct Area{
   
  int area_type;
  //struct Node area_adress; //pekar p� en nod inom ett ickesett omr�de.
  struct Node *interior[MAX_TOTAL_AREA];
  struct Node *boundry_nodes[MAX_TOTAL_AREA]; //pekar p� rand-noderna till ett ickesett omr�de.
  struct Node *boundry_vision[MAX_TOTAL_AREA];
  int number_of_boundries;
   
};




//-------------------end variabel definitions----------------------

//-------------------defining a queue----------------------
/*
 *  FILE   : queue.h
 *  AUTHOR : Jeffrey Hunter
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Define queue record structure and
 *           all forward declarations.
 */

//#include <stdio.h>  , imported by Header.h
//#include <stdlib.h>,   imported by Header.h

#define Error(Str)        FatalError(Str)
#define FatalError(Str)   fprintf(stderr, "%s\n", Str), exit(1)

typedef struct Node* ElementType;

#ifndef _Queue_h

  struct QueueRecord;
  typedef struct QueueRecord *Queue;

  int         IsEmpty(Queue Q);
  int         IsFull(Queue Q);
  Queue       CreateQueue(int MaxElements);
  void        DisposeQueue(Queue Q);
  void        MakeEmpty(Queue Q);
  void        Enqueue(ElementType X, Queue Q);
  ElementType Front(Queue Q);
  void        Dequeue(Queue Q);
  ElementType FrontAndDequeue(Queue Q);

#endif  /* _Queue_h */

/*
 *  FILE   : queue.c
 *  AUTHOR : Jeffrey Hunter
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Implement all functions required
 *           for a Queue data structure.
 */

//#include "queue.h" , given above
//#include <stdlib.h>   already imported by Header.h

#define MinQueueSize (1)

struct QueueRecord {
  int Capacity;
  int Front;
  int Rear;
  int Size;
  ElementType *Array;
};

int IsEmpty(Queue Q) {
    return   Q->Size == 0;
}

int TryIfEmpty(Queue Q) {
  if (IsEmpty(Q)){
      return TRUE;
}
    return FALSE;
}


int IsFull(Queue Q) {
  return Q->Size == Q->Capacity;
}

Queue CreateQueue(int MaxElements) {
  Queue Q;

  if (MaxElements < MinQueueSize) {
    Error("CreateQueue Error: Queue size is too small.");
  }

  Q = malloc (sizeof(struct QueueRecord));
  if (Q == NULL) {
    FatalError("CreateQueue Error: Unable to allocate more memory.");
  }

  Q->Array = malloc( sizeof(ElementType) * MaxElements );
  if (Q->Array == NULL) {
    FatalError("CreateQueue Error: Unable to allocate more memory.");
  }

  Q->Capacity = MaxElements;
  MakeEmpty(Q);

  return Q;
}

void MakeEmpty(Queue Q) {

  Q->Size = 0;
  Q->Front = 1;
  Q->Rear = 0;

}

void DisposeQueue(Queue Q) {
  if (Q != NULL) {
    free(Q->Array);
    free(Q);
  }
}

static int Succ(int Value, Queue Q) {
  if (++Value == Q->Capacity) {
    Value = 0;
  }
  return Value;
}

void Enqueue(ElementType X, Queue Q) {

  if (IsFull(Q)) {
    Error("Enqueue Error: The queue is full.");
  } else {
    Q->Size++;
    Q->Rear = Succ(Q->Rear, Q);
    Q->Array[Q->Rear] = X;
  }

}

ElementType Front(Queue Q) {

  if (!IsEmpty(Q)) {
    return Q->Array[Q->Front];
  }
  Error("Front Error: The queue is empty.");

  /* Return value to avoid warnings from the compiler */
  return ;

}

void Dequeue(Queue Q) {

  if (IsEmpty(Q)) {
    Error("Dequeue Error: The queue is empty.");
  } else {
    Q->Size--;
    Q->Front = Succ(Q->Front, Q);
  }

}

ElementType FrontAndDequeue(Queue Q) {

  ElementType X = (struct Node *)0;

  if (IsEmpty(Q)) {
    Error("FrontAndDequeue Error: The queue is empty.");
  } else {
    Q->Size--;
    X = Q->Array[Q->Front];
    Q->Front = Succ(Q->Front, Q);
  }
  return X;

}


//-------------------end of queue definition--------------



//-------------------DEFINING A STACK---------------------
#define STACKSIZE 10000

int  *tos, *p1, stack[STACKSIZE];
void push(int i)
{
  p1++;
  if(p1 == (tos+STACKSIZE)) {
    printf("Stack Overflow. Please increase STACKSIZE if you have very large environments.\n");
    exit(1);
  }
  *p1 = i;
}

int pop(void)
{
  if(p1 == tos) {
    printf("Stack Underflow.\n");
    exit(1);
  }
  p1--;
  return *(p1+1);
}

int empty(void){
	if (p1==tos){
		return 1;
	}else return 0;
}

//-------------------end of stack definition---------



//------------------Function initialization-----------------------------
/*struct greedy preGreedy(struct Node *NodeMat, int *Hunters, int *BREAK); init in greedy.h*/
void create_tables(struct greedy *poutput);
void get_node_distance(/*int tile_distance*/);
/*klar*/void get_total_area(struct greedy *input); //l�gger pekare i input som pekar p� alla B[i][j]
/*void greedyAlg(struct greedy *input); init in greedy.h*/
/*KLAR*/int run(struct greedy *input);
/*KLAR*/int enviroment_cleared();
/*KLAR*/int test_break(struct greedy *input);
void one_iteration(struct greedy *input/*, int *move_strat*/);
struct valuation preparation(struct greedy *input);
/*KLAR*/void get_conditions(/*int *team_vision, struct greedy *input*/);
/*KLAR*/void get_vision(struct greedy *input, struct valuation *output);
/*KLAR*/int is_in_vision(struct valuation *input, struct Node *tile); //anv�nds inte i nul�get
/*KLAR*/void get_total_areas(/*struct greedy *input*/);
/*KLAR*/int is_checked();
/*KLAR*/void get_area();
/*KLAR*/void check_boundry_priority(/*area, boundry*/);
void get_hunter_equiv();
struct move valuation(/*int *next_move*/);
void designate_boundry(/*antal_att_delegera, boundry, jagare*/);
void make_distance(/*boundry, jagare*/);
void add_directional_value(/*antal_att_delegera, data fr�n make_distance*/);
void solve_knappsack(/*antal_att_delegera, data fr�n make_distance*/);
void designate_direction(/*solution_from_knappsack*/);
void add_geometric_value();
void add_close_boundry_value(/*jagare[i]*/);
void add_unique_guarding_value(/*jagare[i]*/);
void add_priority_guarding_value(/*jagare[i]*/);
void add_big_vision_value(/*jagare[i]*/);
void find_best_cost();
void move(/*struct greedy *input*/);
void get_hunter(/*struct greedy *input,int i*/);
void /*struct Node*/ get_best_move(/*from*/); 
void put_movestrat(/*int startindex,struct Node *from, struct Node *to*/);
void update_states();


//===========********======PREGREEDY========**********=============
struct greedy preGreedy(struct Node (*NodeMat)[SIZE][SIZE], int *Hunters, int *BREAK){
  struct greedy output;
  int i=0;
  int *p1=NULL;
  int temp=0;
  int *pos=NULL;
  struct greedy *poutput=NULL;
  poutput=&output;
  memset (&output,0,sizeof(output));
 //fill node_matrix
  output.node_matrix=NodeMat;
  /*
  //set total_vision[i]=-1
  while(i<MAX_SIZE_TOTAL_VISION){
    output.total_vision_zero[i]=(struct Node *)0;
  i++;
}
  i=0;
  // set total_area[i]=-1
  while(i<MAX_TOTAL_AREA){
  output.total_area[i]=(struct Node *)0;
  i++;
}
  i=0;
  */
  //fill Break values.
  output.Break[1]=(*BREAK);
  output.Break[0]=0;

  p1=&Hunters[0];

  //fill solution[]={number of pursuers, number of itterations, starting pos.,{-1}}
  output.solution[0]=*p1;
  output.solution[1]=0;
  while(i<=Hunters[0]*2){
    output.solution[i+2]=*(p1+i+1);
    i++; 
  }
  i++;
  while (i<MAX_SIZE_SOLUTION){
    output.solution[i]=-1;
    i++; 
  }

  create_tables(poutput); //skriv in tabeller i output struct

  printf("\n\n");

  return output;
}

void create_tables(struct greedy *poutput){
  printf("create_tables\n");
  printf("    ");
  get_node_distance(/*pekare p� output*/);
  get_total_area(poutput);

  return;
}

void get_node_distance(/*pekare p� output*/){
  printf("get_node_distance, end.\n");
  /*
s� l�nge det finns noder i total_area;
-ta en nod
-ber�kna kortaste avst�ndet till var och en av noderna i total_area
-l�gg int avst�nd i index find_distance_index(*from,*to)


-k�r A* eller liknande f�r att ber�kna kortaste avst�nd mellan tv� omr�den
-spara i en (Hash?)tabell
-skriv tabell via pekare till output
*/


  return;
}

void get_total_area(struct greedy *input){ 
//l�gger alla pekare som pekar p� var sin nod i globala B i input.total_area[] 
  int i=0;
  int row=0;
  int kol=0;
  struct Node (*temp)[SIZE][SIZE]=(*input).node_matrix;
  while (row<SIZE){
    kol=0;
    while(kol<SIZE){
      if(i>80){
	break;
      }
      else if((*temp)[row][kol].state!=25){
	if((*temp)[row][kol].vision[0]!=(struct Node *)0){
	  (*input).total_area[i]=&(*temp)[row][kol];	
	  i++;	
	}
      }
      kol++;
    }
    if (i>80){
      break;
    }
    row++;
  }
  return;
}

//*************************END PREGREEDY*******************************







//%%%%%%%%%%%%%%%%%%%%%------GREEDY------&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void greedyAlg(struct greedy *input){
  printf("greedyAlg\n");
  (*input).solution_iter_index=2;
  while (run(input)==TRUE){
    (*input).solution_iter_index=(*input).solution_iter_index+2*(*input).solution[0]*(*input).solution[1];
    one_iteration(input);
    (*input).Break[0]=(*input).Break[0]+1;
    ((*input).solution[1])++;
  }
  return;   //output ska vara samma som input, men vi har trixat med structen.  
}

int run(struct greedy *input){
  if (enviroment_cleared(input)==TRUE){
    return FALSE;
  }else if(test_break(input)==TRUE){
    return FALSE;
  }else
    return TRUE;
}

int enviroment_cleared(struct greedy *input){
  int i=0;
  int correct_size=22;
  struct Node *temp=(*input).total_area[0];
  while (/*(*temp).vision[0]!=(struct Node *)0*/i<correct_size){
    if((*temp).state==4){
      printf("enviroment_cleared return: FALSE\n");
      return FALSE;
    }
    i++;
  }

  printf("enviroment_cleared return: TRUE\n");
  return TRUE;
}

int test_break(struct greedy *input){
  if ((*input).Break[0]!=(*input).Break[1]){
    return FALSE;
  }else{
    return TRUE;
  }
}


void one_iteration(struct greedy *input){
  printf("one_iteration\n");
  printf("    ");
  struct valuation prep_info=preparation(input); //tar fram n�dv�ndig data f�r en iteration
  printf("    ");
  struct move val_info=valuation(&prep_info, input); //ber�knar kostnader
  printf("    ");
  move(/*struct greedy *input*/); // flyttar till b�sta kostnad
  return;
}

/*===================one_iteration(): Phase one, Preparations================================*/
struct valuation preparation(struct greedy *input){ //tar fram alla startdata f�r en iteration
 
  printf("preparation\n");
  struct valuation output;

  memset(&output, 0, sizeof(output));

  get_conditions(input, &output);
  printf("      ");
  get_hunter_equiv();
  return output;
}

void get_conditions(struct greedy *input, struct valuation *output){ //fastst�ll vilka omr�den som finns utanf�r synf�lt, namnge och definiera r�nder
  get_vision(input, output); //skriv in gruppens sikt som states i NodeMatrix
  get_total_areas(input, output);
  return;
}

void get_vision(struct greedy *input, struct valuation *output){
  //find the total sight of the team, update states correspondingly
  int j=0;
  int k=0;
  int i=0;
  int row=0;
  int kol=0;
  struct Node (*temp)[SIZE][SIZE]=(*input).node_matrix;
  struct Node *hunter;
  struct Node *temp2;
  Queue vision=CreateQueue(MAX_TOTAL_AREA);
 

  while(j<(*input).solution[0]){
    row=(*input).solution[(*input).solution_iter_index+2*j];
    kol=(*input).solution[(*input).solution_iter_index+2*j+1];
    hunter=&(*temp)[row][kol];
    (*hunter).state=HUNTER+CHECKED;
    (*output).total_vision[i]=hunter;
    i++;
    Enqueue(hunter,vision);
    j++;  
  }
  j=0; 
  while(j<(*input).solution[0]){
    temp2=FrontAndDequeue(vision);
    while((*temp2).vision[k]!=(struct Node *)0){
      if ((*(*temp2).vision[k]).state<CHECKED){
	(*(*temp2).vision[k]).state=SEEN+CHECKED;
	(*output).total_vision[i]=(*temp2).vision[k];
	i++;
      }
      k++;
    }
    k=0;
    j++;
  }
  DisposeQueue(vision);
  return;
}

int is_in_vision(struct valuation *input, struct Node *tile){
  int i=0;
  while (1==1){
    if((*input).total_vision[i]==tile){
      return TRUE;
    }
    if((*input).total_vision[i]==(struct Node *)0){
      return FALSE;
    }
    i++;
  }
}

void get_total_areas(struct greedy *input, struct valuation *output){
  /*  struct Node *checked_tiles[MAX_SIZE_TOTAL_VISION];
  memset(checked_tiles, 0, sizeof(checked_tiles));
  */

  Queue unchecked_queue=CreateQueue(MAX_TOTAL_AREA);
  struct Node *tile;


  int i=0;
  int k=0;
  while ((*input).total_area[i]!=(struct Node *)0){
    tile=(*input).total_area[i];
    if ((*tile).state<CHECKED){
      Enqueue(tile, unchecked_queue);
      if((*tile).state<MARKED){
	struct Area *area=malloc(sizeof(struct Area));
	get_area(tile, area);
	(*output).area_collection[k]=area;
	k++;
      }
    }
    i++;

  }
  i=0;
  while ((*output).area_collection[i]!=(struct Area *)0){
    check_boundry_priority((*output).area_collection[i]);
  i++;
  }
  return;
}

void get_area(struct Node *tile, struct Area *input){
  int i=0;
  int k=0;
  int l=1;
  int m=0;
  struct Node *node_temp;
  // struct Area *output_get_area;
  //  struct Area area_temp;
  //  output_get_area=(struct Area*) malloc(sizeof(struct Area));
  memset(input, 0,sizeof(struct Area));
  
  if ((*tile).state<MARKED){
    (*input).interior[0]=tile;
    (*tile).state=(*tile).state+MARKED;
  }
  Queue list= CreateQueue(MAX_TOTAL_AREA);
  Queue tree =CreateQueue(MAX_TOTAL_AREA);
  Enqueue(tile, list);
  Enqueue(tile, tree);

  while(TryIfEmpty(list)==FALSE){
    node_temp=FrontAndDequeue(list);
    i=0;
    while(i<4){ //f�r alla flyttbara fr�n node_temp utf�r:
      if ((*node_temp).move[i]==(struct Node *)0){
	i++;
      }else if((*(*node_temp).move[i]).state>=CHECKED){
	//det �r en nod som �r synlig, dvs boundry
	//kolla om den redan finns i boundry_nodes, om inte: l�gg in den.
	m=0;
	if((*input).boundry_nodes[m]==(struct Node *)0){
	    (*input).boundry_nodes[k]=(*node_temp).move[i];
	    ((*input).number_of_boundries)++;
	    k++;
	  }
	while ((*input).boundry_nodes[m]!=(struct Node *)0){
	  
	  if((*node_temp).move[i]==(*input).boundry_nodes[m]){
	    break;
	  }
	  m++;
	  if((*input).boundry_nodes[m]==(struct Node *)0){
	    (*input).boundry_nodes[k]=(*node_temp).move[i];
	    ((*input).number_of_boundries)++;
	    k++;
	    break;
	  }
	}      
	
	i++;
	
      }else if ((*(*node_temp).move[i]).state>=MARKED){  //is marked
	//det �r en redan unders�kt interior point
	i++;
      }else if((*(*node_temp).move[i]).state<MARKED){ //is unmarked
	//det �r en ny nod inom omr�det.
	(*(*node_temp).move[i]).state=	(*(*node_temp).move[i]).state+MARKED;
	Enqueue((*node_temp).move[i], list);
	Enqueue((*node_temp).move[i], tree);
	(*input).interior[l]=(*node_temp).move[i];
	l++;
	i++;
      }      
    }
  }
  
  DisposeQueue(list);
  DisposeQueue(tree);
  return;
}

void check_boundry_priority(struct Area *input){
  int i=0;
  int k=0;
  int j=0;
  int m=0;
  if( (*(*input).interior[0]).state==SECURED){
    (*input).area_type=PRIO_SECURED;
    return;
  }
  if((*input).number_of_boundries==1){ //har endast EN rand-Nod
    //    kolla om man kan se hela interior fr�n rand
    k=0;
    while((*(*input).boundry_nodes[0]).vision[k]!=(struct Node *)0){
      if((*input).interior[0]==(*(*input).boundry_nodes[i]).vision[k]){
	(*input).area_type=PRIO_VIS_ONE_BOUND;
	return;
      }
      k++;
    }
    (*input).area_type=PRIO_ONE_BOUND;
    return;
  }
  else{
    //kolla om man ser hela interior fr�n rand
    i=0;
    Queue vision=CreateQueue(MAX_TOTAL_AREA);
    struct Node *node_temp;
    while ((*input).boundry_nodes[i]!=(struct Node *)0){ //l�gg randernas totala synf�lt i en k�.
      while((*(*input).boundry_nodes[i]).vision[j]!=(struct Node *)0){
	Enqueue((*(*input).boundry_nodes[i]).vision[j], vision);
	j++;
      }
      i++;
    }
    while (TryIfEmpty(vision)==FALSE){
      node_temp=FrontAndDequeue(vision);
      if((*node_temp).state<=CHECKED){
	m=0;
	while((*input).interior[m]!=(struct Node *)0){
	  if ((*input).interior[m]==node_temp){
	    (*node_temp).state=(*node_temp).state+MARKED;
	    break;
	  }
	  m++;
	}
      }
    }
    m=0;
    while((*input).interior[m]!=(struct Node *)0){
      if((*(*input).interior[m]).state<=CHECKED){
	(*input).area_type=PRIO_SEV_BOUND;
	return;
      }
      m++;
    }
    (*input).area_type=PRIO_VIS_SEV_BOUND;  
    return;
  }
}

void get_hunter_equiv(){
  /*
-ta aktuell nod.
-unders�k om flyttbara noders synf�lt redan finns med inom aktuellt synf�lt fr�n gruppen
-om det finns n�gon ekvivalent position: skapa en fiktiv jagare

  return;
  */
  printf("get_hunter_equiv, end.\n");
  return;
}

/*====================one_iteration():Phase two, Evaluation=======================================*/
struct move valuation(struct valuation *input_val, struct greedy *input_greedy){ //anv�nder data fr�n preparation och designerar v�rden till noder som g�r at flytta till
  /*
vill veta fr�n preparation:
-antal omr�den
-fullst�ndig rand till varje omr�de
-karakt�r p� rand a,b,c,d,e
-jagarpositioner

vill veta allm�nt:
-tillg�ng till tabel med kortaste v�gen mellan omr�den.

  if (antal_jagare<=antal_omr�den){
    designate_boundry(antal_jagare);
  }else {
    designate_boundry(antal_omr�den);
}
  int i=0;
  while(i<antal_jagare){
    add_geometric_value();
    *next_move=find_best_cost();
  }
  return;
  */

  /*
-skapa array f�r varje jagare med fem index, ett f�r varje flyttbar nod.
-k�r adderingsfunktioner och l�gger v�rden i varje index enligt algoritm
-k�r find_best_cost f�r att best�mma vilken nod som varje jagare ska g� till (den med h�gst v�rde)
-skicka ut array med pekare till varje nod som jagarna ska g� till.
   */
  int i=0;
  int row=0;
  int kol=0;
  int hunter_temp[100][5];
  memset(&hunter_temp,0,sizeof(hunter_temp));
  



  printf("valuation\n");
  printf("      ");
  designate_boundry();
  printf("      ");
  while(i<(*input_greedy).solution[0]){
    row=(*input_greedy).solution[(*input_greedy).solution_iter_index+2*i];
    kol=(*input_greedy).solution[(*input_greedy).solution_iter_index+2*i+1];
    struct Node *position=&(*(*input_greedy).node_matrix[row])[kol];
    add_geometric_value(&hunter_temp[i], position);
  printf("      ");
  find_best_cost();
  i++;
  }
  return;
}

void designate_boundry(/*antal_att_delegera, boundry, jagare*/){
  /*
-ta en rand
-ta en jagare
-ta fram avst�nd mellan rand och jagare
  */
  /*
  make_distance(boundry, jagare); //r�kna fram kortaste v�g f�r varje jagare till varje rand
  add_directional_value(antal_att_delegera); // givet de val som finns fr�n make_distance v�lj b�sta
  */
  printf("designate_boundry\n");
  printf("        ");
  make_distance();
  printf("        ");
  add_directional_value();
  return;
}

void make_distance(/*boundry, jagare*/){
  /*
  int i=0;
  while (i<antal_boundrys){
    /*
-get hunter position
-look up distance to all boundries in table
     
 }
  return; //the distance for each hunter to each boundry
*/
  printf("make_distance, end.\n");
  return;
}

void add_directional_value(/*antal_att_delegera, data fr�n make_distance*/){
  /*
  solve_knappsack(antal_att_delegera, data fr�n make_distance);
  int i=0;  
  while(i<antal_att_delegera){
    designate_direction(solution_from_knappsack);
    i++;
}
  return;
  */
  printf("add_directional_value\n");
  printf("          ");
  solve_knappsack();
  printf("          ");
  designate_direction();
  return;
}

void solve_knappsack(/*antal_att_delegera, data fr�n make_distance*/){
  //solve knappsack problem? priorize boundrys of priority 1 or 3 (?)
  printf("solve_knappsack, end.\n");
  return;
}

void designate_direction(/*solution_from_knappsack*/){
  //given a hunter and a path to a boundry, add the amount designatedirection to the first step in the path.
  printf("designate_direction, end.\n");  
return;
}

void add_geometric_value(int (*input)[5], struct Node *position){
  /* 
  int i=0;
  while(i<antal_jagare){
    add_close_boundry_value(jagare[i]);
    add_unique_guarding_value(jagare[i]);
    add_priority_guarding_value(jagare[i]);
    add_big_vision_value(jagare[i]);
  }
  return;
  */
  printf("add_geometric_value\n");
  printf("        ");
  add_close_boundry_value();
  printf("        ");
  add_unique_guarding_value();
  printf("        ");
  add_priority_guarding_value();
  printf("        ");
  add_big_vision_value(input, position);
  return;
}

void add_close_boundry_value(/*jagare[i]*/){
  //addera v�rdet close p� den/de flyttbara noder med kortast avst�nd till n�gon rand
  printf("add_close_boundry_value,end.\n");
  return;

}

void add_unique_guarding_value(/*jagare[i]*/){
  //addera v�rdet unique p� den/de flyttbara noder som ser unika rand-omr�den
  printf("add_unique_guarding_value, end.\n");
  return;
}

void add_priority_guarding_value(/*jagare[i]*/){
  //addera v�rdet priority p� den/de flyttbara noder som ser unika prioritetsomr�den
  printf("add_priority_guarding_value, end.\n");
  return;
}

void add_big_vision_value(int (*input)[5], struct Node *position){
  //addera v�rdet big_vision p� den/de flyttbara noder som ser mest
  printf("add_big_vision_value, end.\n");
  return;
}

void find_best_cost(){
  /*
f�r varje jagare:
-l�s av vilken ruta som har h�gst v�rde
   */ 
  printf("find_best_cost, end.\n");
  return; //pekare p� vilken nod som har h�gsta v�rde
}


/*====================one_iteration(): Phase three, Movement======================================*/

void move(/*struct greedy *input*/){ //anv�nder data fr�n evaluation, flyttar till de noder med b�st kostnad, updaterar states, skickar resultat av en iteration.
  /*
  int i=1;//index f�r jagarnummer.
  struct Node *from;
  struct Node *to;
  int index;
  while (i<=input.solution[0]){ //input.solution[0]= antal jagare
    from =&get_hunter(input, i,r,k); //get current hunter position
    to=get_best_move(from); //find the moveable tile to move
    put_movestrat(index, from, to); // move and update the number of moves made
} 
  update_states(); //j�mf�r tillst�nd f�r f�rflyttning med efter, uppdaterar tillst�nds�ndringar
  return;
  */
  printf("move\n");
  printf("      ");
  get_hunter();
  printf("      ");
  get_best_move();
  printf("      ");
  put_movestrat();
  printf("      ");
  update_states();
  return;
}

void get_hunter(/*struct greedy *input,int i*/){
  /*  
int antaljagare= input.solution[0];
  int antalsteg= input.solution[1];
  int rindex=(2*antaljagare*antalsteg+1)+i;
  int kindex=(2*antaljagare*antalsteg+1)+2i;
  int r=input.solution[rindex];
  int k=input.solution[kindex];
  return input.NodeMatrix.[r][k];
  */
  printf("get_hunter, end.\n");
  return;
}

void /*struct Node*/ get_best_move(/*from*/){ 
 /*
-h�mta nod (r,k) ur NodeMatrix
-h�mta vilken nod som har b�st v�rde enligt utdata fr�n evaluation()
- s�tt to=nod som ska flyttas till
   
 return to
 */
  printf("get_best_move, end.\n");
  return;
}

void put_movestrat(/*int startindex,struct Node *from, struct Node *to*/){
  /*
-h�mta nya positioner genom to.name[]
-ber�kna r�tt index att placera de nya positionerna p� i solution[]
-l�gg in jagarnas nya positionerpositioner i slutet p� solution[]
-addera ett till solution [1] (antal steg gjorda)
  */
  printf("put_movestrat, end.\n");
  return;
}

void update_states(){
  /*
-l�s av nuvarande states i NodeMatrix
-j�mf�r f�rh�llande f�re och efter f�rflyttning
-updatera de states som har f�r�ndrats.
   */
  printf("update_states, end.\n");
  return;
}


//XXXXXXXXXXXXXXXXXXX---------END GREEDY---------XXXXXXXXXXXXXXXXXXXXXXXX
