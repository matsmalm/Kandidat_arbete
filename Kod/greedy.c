/*
notes to self:
-sätt solution som en global variabel istället?
-i funktionen get_area: kanske representera områden som sammanslagning av noder?
antag att vi har fyra områden i en yta och två rand områden till ytan. skapa en struct "yta" som innehåller antal ränder, lista med pekare på structen rand. structen rand i sin tur innehåller en lista med pekare på rand-områden samt en parameter som visar randens karaktär.

*/
//  function call-order:


//---------------variabel declaration---------------------------  
#define TRUE 1;
#define FALSE 0;
#define designatedirection 50;
#define close;     //parameter for cost function. distance to boundry
#define unique: // parameter for cost function. unique visible boundrys
#define priority; // parameter for cost function. priorized visible boundrys
#define big_vision;  // parameter for cost function. largest vision

struct greedy{
  //  int tile_distance[]; //tabell med avståndet mellan alla nod-par
  // int total_area[];  //total_area={totalt antal områden,r1,k1, r2,k2,...}, område1=(r1,k1)
  // struct Node node_matrix; //B[][]
  // int Break[]; //brytvillkor för algoritm{nuvarande värde, givet brytvillkor}
  // int solution[]; //solution= {antal jagare,antal steg, sj1r1,sj1k1,..., sj1r2,sj1k2,...}
}
 struct Area{
   /*
    int area_type;
    struct Node area_adress; //pekar på en nod inom ett ickesett område.
    struct Node boundry; //pekar på rand-noderna till ett ickesett område.
   */
}


//-------------------end variabel definitions----------------------


//------------------Function initialization-----------------------------
  void/* struct greedy */preGreedy(struct Node *NodeMat, int *Hunters, int BREAK);
void alloc_Matrix_enviroment();
void create_tables(/*int *tile_distance, int *total_area*/);
void get__node_distance(/*int tile_distance*/);
void get_total_area(/*int *total_area*/);
void greedyAlg(/*struct greedy *input*/);
void/*int*/ run(/*struct greedy *input*/);
void /*int*/ enviroment_cleared();
void /*int*/ test_break(/*struct greedy *input*/);
void release_alloc_Matrix_enviroment();
void one_iteration(/*struct greedy *input, int *move_strat*/);
void preparation();
void get_conditions(/*int *team_vision, struct greedy *input*/);
void get_vision(/*struct greedy *input*/);
void get_areas(/*struct greedy *input*/);
void subtract_vision(/*struct Node area, int *team_vision*/);
void identify_boundry(/*int areaindex*/);
void find_boundry(/*int areaindex*/);
void classify_boundry(/*area,boundry*/);
void check_boundry_priority(/*area, boundry*/);
void set_boundry(/*boundry, prio*/);
void get_hunter_equiv();
void evaluation(/*int *next_move*/);
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
void /*struct Node*/ get_bestmove(/*from*/); 
void put_movestrat(/*int startindex,struct Node *from, struct Node *to*/);
void update_states();


//===========********======PREGREEDY========**********=============
struct greedy preGreedy(struct Node *NodeMat, int *Hunters, int BREAK);{
  /*int tile_distance[];
  int total_area[];
  alloc_Matrix_enviroment();
  createTables(int *tile_distance, int *total_area);
  struct greedy start;
  start.tile_distance=tile_distance[];
  start.total_area=total_area[];
  start.node_matrix=NodeMatrix[][];
  start.solution=Hunters[];
  start.Break=BREAK;
  return start;*/
}


void alloc_Matrix_enviroment(){
  //allokera minne för nodmatris
}
void create_tables(/*int *tile_distance, int *total_area*/){
  /*
    get_node_distance(int tile_distance);
    get_total_area(int total_area);
  */
}

void get_node_distance(/*int tile_distance*/){

}

void get_total_area(/*int total_area*/){

}

//*************************END PREGREEDY*******************************







//%%%%%%%%%%%%%%%%%%%%%------GREEDY------&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void greedyAlg(/*struct greedy *input*/){
  /*
  int i=0;
  while (run(int input.solution[],int input.Break)==TRUE){
    one_iteration(struct greedy *input);
}
  release_alloc_Matrix_enviroment();
  return//output är samma som input, men vi har trixat med structen.
}

int run(struct greedy *input){
  if (enviroment_cleared()==TRUE){
    return FALSE;
  }else if(test_break(input)==TRUE){
    return FALSE;
  }else{
    return TRUE;}
 }
  */
}

void /*int*/ enviroment_cleared(){
  /*  


//kolla om området är säkrat i nuläget
   
  if(){
    //område säkrat
    return FALSE
}

  return TRUE;
*/
}

void /*int*/ test_break(/*struct greedy *input*/){
  /*
  if (input.Break[0]==input.Break[1]){
    return FALSE;
  }
  return TRUE;
  */
}

void release_alloc_Matrix_enviroment(){
  // släpp allokerat minne för matrisen NodeMatrix
}

void one_iteration(/*struct greedy *input, int *move_strat*/){
  /*
  preparations(); //tar fram nödvändig data för en iteration
  evaluation(*move_strat); //beräknar kostnader
  move(struct greedy *input); // flyttar till bästa kostnad
  return;
  */
}

/*===================one_iteration(): Phase one, Preparations================================*/
void preparation(){ //tar fram alla startdata för en iteration
  /*
 int team_vision[];
 get_conditions(int team_vision); 
 get_hunter_equiv();

 return //skicka ut boundrys(med tillhörande prioritet), ytor, ekvivalent jagare;
  */
}

void get_conditions(/*int *team_vision, struct greedy *input*/){ //fastställ vilka områden som finns utanför synfält, namnge och definiera ränder
  /*
  get_vision(*input); //skriv in gruppens sikt som states i NodeMatrix
  get_areas(*input);
  return;
  */
}

void get_vision(/*struct greedy *input*/){
  //find the total sight of the team, function partly solved in greedy.c ??
/*
förslag:
loop
-ta position från en jagare
-ändra state i aktuell nod
-hämta vision för aktuell nod
-ändra states till synlig i de rutor som finns i vision.
loop end
  return;
*/
}

void get_areas(/*struct greedy *input*/){
  /*  struct Node areaindex[];
  struct Node *p1;
  *p1=areaindex[0];
  subtract_vision(p1, *team_vision); //compare areas in sight of team with total amount of tiles.
  int i=0;
  while(i<areaindex){
    identify_boundry(areaindex[i]);
    i++;
  }
  */
}

void subtract_vision(/*struct Node area, int *team_vision*/){
  /*

ta fram index på de områden som inte ligger inom synfältet.
 
förslag:
-ta in global tabel med alla områden
-ta in array med team_vision
-ta fram punkt (i,j) ur tabell med alla områden
-kolla om samma punkt finns i team_vision
-om inte: 

   

  return; //skicka tillbaka vilka områden som finns
  */
}

void identify_boundry(/*int areaindex*/){
  /*
  find_boundry(areaindex);
  classify_boundry(area, boundry);
  */
}

void find_boundry(/*int areaindex*/){
  //find the boundrys to the given area
  /*
  return boundry, number of boundrys;
  */
}

void classify_boundry(/*area, boundry*/){
  /*
  int prio=check_boundry_priority(area,boundry);
  set_boundry(boundry, prio);
  return;
  */
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
}

void set_boundry(/*boundry, prio*/){
  //tillskriv randen den medskickade prioriteten.
}


void get_hunter_equiv(){
  /*
-ta aktuell nod.
-undersök om flyttbara noders synfält redan finns med inom aktuellt synfält från gruppen
-om det finns någon ekvivalent position: skapa en fiktiv jagare

  return;
  */
}

/*====================one_iteration():Phase two, Evaluation=======================================*/
void valuation(/*int *next_move*/){ //använder data från preparation och designerar värden till noder som går at flytta till
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
}

void solve_knappsack(/*antal_att_delegera, data från make_distance*/){
  //solve knappsack problem? priorize boundrys of priority 1 or 3 (?)
}

void designate_direction(/*solution_from_knappsack*/){
  //given a hunter and a path to a boundry, add the amount designatedirection to the first step in the path.
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
}

void add_close_boundry_value(/*jagare[i]*/){
  //addera värdet close på den/de flyttbara noder med kortast avstånd till någon rand
}

void add_unique_guarding_value(/*jagare[i]*/){
  //addera värdet unique på den/de flyttbara noder som ser unika rand-områden
}

void add_priority_guarding_value(/*jagare[i]*/){
  //addera värdet priority på den/de flyttbara noder som ser unika prioritetsområden
}

void add_big_vision_value(/*jagare[i]*/){
  //addera värdet big_vision på den/de flyttbara noder som ser mest
}

void find_best_cost(){
  /*
för varje jagare:
-läs av vilken ruta som har högst värde
   */ 
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
    to=get_bestmove(from); //find the moveable tile to move
    put_movestrat(index, from, to); // move and update the number of moves made
} 
  update_states(); //jämför tillstånd för förflyttning med efter, uppdaterar tillståndsändringar
  return;
  */
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
}

void /*struct Node*/ get_bestmove(/*from*/){ 
 /*
-hämta nod (r,k) ur NodeMatrix
-hämta vilken nod som har bäst värde enligt utdata från evaluation()
- sätt to=nod som ska flyttas till
   
 return to
 */
}

void put_movestrat(/*int startindex,struct Node *from, struct Node *to*/){
  /*
-hämta nya positioner genom to.name[]
-beräkna rätt index att placera de nya positionerna på i solution[]
-lägg in jagarnas nya positionerpositioner i slutet på solution[]
-addera ett till solution [1] (antal steg gjorda)
  */
  return;
}

void update_states(){
  /*
-läs av nuvarande states i NodeMatrix
-jämför förhållande före och efter förflyttning
-updatera de states som har förändrats.
   */
  return;
}


//XXXXXXXXXXXXXXXXXXX---------END GREEDY---------XXXXXXXXXXXXXXXXXXXXXXXX
