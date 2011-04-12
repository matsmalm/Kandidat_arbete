/*
notes to self:
-sätt solution som en global variabel istället?
-i enviroment_cleared, korrigera konstanten "correct_size=22"
-i enviroment_cleared, korrigera villkor rad 205 så att alla tillstånd skilda från osäkrade
 
-i get_vision(), rad 330 eventuellt uppdatera states så att man skiljer på sedd, och unikt sedd
-föreslå SIZE och OBSTACLE som globala, för att kunna sätta storlekar på array etc.
-i definition av struct greedy: försök hitta lösning på variabel längd av solution[]
-i funktionen get_area: kanske representera områden som sammanslagning av noder?
antag att vi har fyra områden i en yta och två rand områden till ytan. skapa en struct "yta" som innehåller antal ränder, lista med pekare på structen rand. structen rand i sin tur innehåller en lista med pekare på rand-områden samt en parameter som visar randens karaktär.

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

#define SEEN 1
#define HUNTER 2
#define CONTAMINED 3
#define SECURED 4

#define MAX_SIZE_AREA_COLLECTION 40
struct valuation{
  //solution[solution_iter_index+rj] placerar radindex för jagare j i aktuell iteration.
  struct Node *total_vision[MAX_SIZE_TOTAL_VISION];
  struct Area *area_collection[MAX_SIZE_AREA_COLLECTION];
};

struct move{

};


struct Area{
   
    int area_type;
  //struct Node area_adress; //pekar på en nod inom ett ickesett område.
    struct Node *boundry[MAX_TOTAL_AREA]; //pekar på rand-noderna till ett ickesett område.
   
};




//-------------------end variabel definitions----------------------

//-------------------DEFINING A STACK---------------------
#define STACKSIZE 10000000

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
/*klar*/void get_total_area(struct greedy *input); //lägger pekare i input som pekar på alla B[i][j]
/*void greedyAlg(struct greedy *input); init in greedy.h*/
/*KLAR*/int run(struct greedy *input);
/*KLAR*/int enviroment_cleared();
/*KLAR*/int test_break(struct greedy *input);
void one_iteration(struct greedy *input/*, int *move_strat*/);
struct valuation preparation(struct greedy *input);
void get_conditions(/*int *team_vision, struct greedy *input*/);
/*KLAR*/void get_vision(struct greedy *input, struct valuation *output);
/*KLAR*/int is_in_vision(struct valuation *input, struct Node *tile);
void get_total_areas(/*struct greedy *input*/);
/*KLAR*/int is_checked();
void get_area();
void subtract_vision(/*struct Node area, int *team_vision*/);
void identify_boundry(/*int areaindex*/);
void find_boundry(/*int areaindex*/);
void classify_boundry(/*area,boundry*/);
void check_boundry_priority(/*area, boundry*/);
void set_boundry(/*boundry, prio*/);
void get_hunter_equiv();
struct move valuation(/*int *next_move*/);
void designate_boundry(/*antal_att_delegera, boundry, jagare*/);
void make_distance(/*boundry, jagare*/);
void add_directional_value(/*antal_att_delegera, data från make_distance*/);
void solve_knappsack(/*antal_att_delegera, data från make_distance*/);
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
  //fill node_matrix
  output.node_matrix=NodeMat;

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
  get_node_distance(/*pekare på output*/);
  printf("    ");
  get_total_area(poutput);

  return;
}

void get_node_distance(/*pekare på output*/){
  printf("get_node_distance, end.\n");
  /*
så länge det finns noder i total_area;
-ta en nod
-beräkna kortaste avståndet till var och en av noderna i total_area
-lägg int avstånd i index find_distance_index(*from,*to)


-kör A* eller liknande för att beräkna kortaste avstånd mellan två områden
-spara i en (Hash?)tabell
-skriv tabell via pekare till output
*/


  return;
}

void get_total_area(struct greedy *input){ 
//lägger alla pekare som pekar på var sin nod i globala B i input.total_area[] 
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


void one_iteration(struct greedy *input/*, int *move_strat*/){
  printf("one_iteration\n");
  printf("    ");
  struct valuation prep_info=preparation(input); //tar fram nödvändig data för en iteration
  printf("    ");
  struct move val_info=valuation(/**move_strat*/); //beräknar kostnader
  printf("    ");
  move(/*struct greedy *input*/); // flyttar till bästa kostnad
  return;
}

/*===================one_iteration(): Phase one, Preparations================================*/
struct valuation preparation(struct greedy *input){ //tar fram alla startdata för en iteration
  /*
 int team_vision[];
 get_conditions(int team_vision); 
 get_hunter_equiv();

 return //skicka ut boundrys(med tillhörande prioritet), ytor, ekvivalent jagare;
  */
  printf("preparation\n");
  struct valuation output;

  memset(output.total_vision, 0, sizeof(output.total_vision));

  printf("      ");
  get_conditions(input, &output);
  printf("      ");
  get_hunter_equiv();
  return output;
}

void get_conditions(struct greedy *input, struct valuation *output){ //fastställ vilka områden som finns utanför synfält, namnge och definiera ränder
  printf("get_conditions\n");
  get_vision(input, output); //skriv in gruppens sikt som states i NodeMatrix
  printf("        ");
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
  struct Node *pvision= *(*output).total_vision;
  struct Node *hunter;
  struct Node *temp2;
  while(j<(*input).solution[0]){
    row=(*input).solution[(*input).solution_iter_index+2*j];
    kol=(*input).solution[(*input).solution_iter_index+2*j+1];
    hunter=&(*temp)[row][kol];
    (*hunter).state=HUNTER;
    k=0;
    temp2=(*hunter).vision[k];
    while ( temp2!= (struct Node *)0){
      if(is_in_vision(output,(*hunter).vision[k])==FALSE){
	(*output).total_vision[i]=(*hunter).vision[k];
	i++;
      }
      //eventuellt uppdatera states som att den inte är unikt sedd
      k++;
      temp2=(*hunter).vision[k];
      }
    j++;
  }
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
  int i=0;
  struct Node *checked_tiles[MAX_SIZE_TOTAL_VISION];
  memset(checked_tiles, 0, sizeof(checked_tiles));
  while((*output).total_vision[i]!=(struct Node *)0){
      checked_tiles[i]=(*output).total_vision[i]; //lägg alla element i total vision i en array med kollade noder
      i++;
    }

  struct Area area;
  struct Node *tile;
  i=0;
  while ((*input).total_area[i]!=(struct Node *)0){
    tile=(*input).total_area[i];
    if (is_checked(tile, &checked_tiles)==FALSE){// <-styr över vilka noder som är "checked"
      get_area(/*tile, (*output).area_collection[i], checked_tiles*/);     
    }
    i++;
  }
  
  printf("get_total_areas\n");
  printf("              ");
  subtract_vision(input, output);
  printf("              ");
  identify_boundry(/*input, output*/);
  return;
}

int is_checked(struct Node *tile, struct Node *(*checked_tiles)){
  int i=0;
  while(1==1){
    if(checked_tiles[i]==tile){
      return TRUE;
    }
    if(checked_tiles[i]==(struct Node *)0){
      checked_tiles[i]=tile;
      return FALSE;
    }
    i++;  
  }
}

void get_area(){
  /*
-ta in tile (som inte ligger i checked_tiles)
-för alla flyttbara noder från tile:
    -om den ligger i checked_tiles: lägg den som en rand
    -om den inte ligger i checked_tiles: kolla alla flyttbara noder (utom dig själv) från den flyttbara noden
*/

return;
}

void subtract_vision(struct greedy *input, struct valuation *output){
/*
ta fram index på de områden som inte ligger inom synfältet. 

return; //skicka tillbaka vilka områden som finns
*/


  printf("subtract_vision, end.\n");
  return;
}

void identify_boundry(/*int areaindex*/){
  printf("identify_boundry\n");
  printf("                ");
  find_boundry(/*areaindex*/);
  printf("                ");
  classify_boundry(/*area, boundry*/);
  return;
}

void find_boundry(/*int areaindex*/){
  //find the boundrys to the given area
  /*
  return boundry, number of boundrys;
  */
  printf("find_boundry, end.\n");
  return;
}

void classify_boundry(/*area, boundry*/){
  /*
  int prio=check_boundry_priority(area,boundry);
  set_boundry(boundry, prio);
  return;
  */
  printf("classify_boundry\n");
  printf("                    ");
  check_boundry_priority();
  printf("                    ");
  set_boundry();
return;
}

void check_boundry_priority(/*area, boundry*/){
  /*givet en yta och tillhörande ränder:
-är ytan är säkrad -> prio=5
-kan man se hela ytan från alla områden på randen?
         -ja: är antalet områden i randen mer än ett?
	           -ja: prio ->3
		   -nej:prio ->1
         -nej: är antalet områden i randen mer än ett?
                   -ja: prio->4
		   -nej: prio->2
  */
  printf("check_boundry_priority, end.\n");
  return;
}

void set_boundry(/*boundry, prio*/){
  //tillskriv randen den medskickade prioriteten.
  printf("set_boundry, end.\n");
  return;
}


void get_hunter_equiv(){
  /*
-ta aktuell nod.
-undersök om flyttbara noders synfält redan finns med inom aktuellt synfält från gruppen
-om det finns någon ekvivalent position: skapa en fiktiv jagare

  return;
  */
  printf("get_hunter_equiv, end.\n");
  return;
}

/*====================one_iteration():Phase two, Evaluation=======================================*/
struct move valuation(/*int *next_move*/){ //använder data från preparation och designerar värden till noder som går at flytta till
  /*
vill veta från preparation:
-antal områden
-fullständig rand till varje område
-karaktär på rand a,b,c,d,e
-jagarpositioner

vill veta allmänt:
-tillgång till tabel med kortaste vägen mellan områden.

  if (antal_jagare<=antal_områden){
    designate_boundry(antal_jagare);
  }else {
    designate_boundry(antal_områden);
}
  int i=0;
  while(i<antal_jagare){
    add_geometric_value();
    *next_move=find_best_cost();
  }
  return;
  */
  printf("valuation\n");
  printf("      ");
  designate_boundry();
  printf("      ");
  add_geometric_value();
  printf("      ");
  find_best_cost();
  return;
}

void designate_boundry(/*antal_att_delegera, boundry, jagare*/){
  /*
-ta en rand
-ta en jagare
-ta fram avstånd mellan rand och jagare
  */
  /*
  make_distance(boundry, jagare); //räkna fram kortaste väg för varje jagare till varje rand
  add_directional_value(antal_att_delegera); // givet de val som finns från make_distance välj bästa
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

void add_directional_value(/*antal_att_delegera, data från make_distance*/){
  /*
  solve_knappsack(antal_att_delegera, data från make_distance);
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

void solve_knappsack(/*antal_att_delegera, data från make_distance*/){
  //solve knappsack problem? priorize boundrys of priority 1 or 3 (?)
  printf("solve_knappsack, end.\n");
  return;
}

void designate_direction(/*solution_from_knappsack*/){
  //given a hunter and a path to a boundry, add the amount designatedirection to the first step in the path.
  printf("designate_direction, end.\n");  
return;
}

void add_geometric_value(){
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
  add_big_vision_value();
  return;
}

void add_close_boundry_value(/*jagare[i]*/){
  //addera värdet close på den/de flyttbara noder med kortast avstånd till någon rand
  printf("add_close_boundry_value,end.\n");
  return;

}

void add_unique_guarding_value(/*jagare[i]*/){
  //addera värdet unique på den/de flyttbara noder som ser unika rand-områden
  printf("add_unique_guarding_value, end.\n");
  return;
}

void add_priority_guarding_value(/*jagare[i]*/){
  //addera värdet priority på den/de flyttbara noder som ser unika prioritetsområden
  printf("add_priority_guarding_value, end.\n");
  return;
}

void add_big_vision_value(/*jagare[i]*/){
  //addera värdet big_vision på den/de flyttbara noder som ser mest
  printf("add_big_vision_value, end.\n");
  return;
}

void find_best_cost(){
  /*
för varje jagare:
-läs av vilken ruta som har högst värde
   */ 
  printf("find_best_cost, end.\n");
  return; //pekare på vilken nod som har högsta värde
}


/*====================one_iteration(): Phase three, Movement======================================*/

void move(/*struct greedy *input*/){ //använder data från evaluation, flyttar till de noder med bäst kostnad, updaterar states, skickar resultat av en iteration.
  /*
  int i=1;//index för jagarnummer.
  struct Node *from;
  struct Node *to;
  int index;
  while (i<=input.solution[0]){ //input.solution[0]= antal jagare
    from =&get_hunter(input, i,r,k); //get current hunter position
    to=get_best_move(from); //find the moveable tile to move
    put_movestrat(index, from, to); // move and update the number of moves made
} 
  update_states(); //jämför tillstånd för förflyttning med efter, uppdaterar tillståndsändringar
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
-hämta nod (r,k) ur NodeMatrix
-hämta vilken nod som har bäst värde enligt utdata från evaluation()
- sätt to=nod som ska flyttas till
   
 return to
 */
  printf("get_best_move, end.\n");
  return;
}

void put_movestrat(/*int startindex,struct Node *from, struct Node *to*/){
  /*
-hämta nya positioner genom to.name[]
-beräkna rätt index att placera de nya positionerna på i solution[]
-lägg in jagarnas nya positionerpositioner i slutet på solution[]
-addera ett till solution [1] (antal steg gjorda)
  */
  printf("put_movestrat, end.\n");
  return;
}

void update_states(){
  /*
-läs av nuvarande states i NodeMatrix
-jämför förhållande före och efter förflyttning
-updatera de states som har förändrats.
   */
  printf("update_states, end.\n");
  return;
}


//XXXXXXXXXXXXXXXXXXX---------END GREEDY---------XXXXXXXXXXXXXXXXXXXXXXXX
