/*
notes to self:
-s�tt solution som en global variabel ist�llet?
-i funktionen get_area: kanske representera omr�den som sammanslagning av noder?
antag att vi har fyra omr�den i en yta och tv� rand omr�den till ytan. skapa en struct "yta" som inneh�ller antal r�nder, lista med pekare p� structen rand. structen rand i sin tur inneh�ller en lista med pekare p� rand-omr�den samt en parameter som visar randens karakt�r.

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
  //  int tile_distance[]; //tabell med avst�ndet mellan alla nod-par
  // int total_area[];  //total_area={totalt antal omr�den,r1,k1, r2,k2,...}, omr�de1=(r1,k1)
  // struct Node node_matrix; //B[][]
  // int Break[]; //brytvillkor f�r algoritm{nuvarande v�rde, givet brytvillkor}
  // int solution[]; //solution= {antal jagare,antal steg, sj1r1,sj1k1,..., sj1r2,sj1k2,...}
}
 struct Area{
   /*
    int area_type;
    struct Node area_adress; //pekar p� en nod inom ett ickesett omr�de.
    struct Node boundry; //pekar p� rand-noderna till ett ickesett omr�de.
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
  //allokera minne f�r nodmatris
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
  return//output �r samma som input, men vi har trixat med structen.
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


//kolla om omr�det �r s�krat i nul�get
   
  if(){
    //omr�de s�krat
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
  // sl�pp allokerat minne f�r matrisen NodeMatrix
}

void one_iteration(/*struct greedy *input, int *move_strat*/){
  /*
  preparations(); //tar fram n�dv�ndig data f�r en iteration
  evaluation(*move_strat); //ber�knar kostnader
  move(struct greedy *input); // flyttar till b�sta kostnad
  return;
  */
}

/*===================one_iteration(): Phase one, Preparations================================*/
void preparation(){ //tar fram alla startdata f�r en iteration
  /*
 int team_vision[];
 get_conditions(int team_vision); 
 get_hunter_equiv();

 return //skicka ut boundrys(med tillh�rande prioritet), ytor, ekvivalent jagare;
  */
}

void get_conditions(/*int *team_vision, struct greedy *input*/){ //fastst�ll vilka omr�den som finns utanf�r synf�lt, namnge och definiera r�nder
  /*
  get_vision(*input); //skriv in gruppens sikt som states i NodeMatrix
  get_areas(*input);
  return;
  */
}

void get_vision(/*struct greedy *input*/){
  //find the total sight of the team, function partly solved in greedy.c ??
/*
f�rslag:
loop
-ta position fr�n en jagare
-�ndra state i aktuell nod
-h�mta vision f�r aktuell nod
-�ndra states till synlig i de rutor som finns i vision.
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

ta fram index p� de omr�den som inte ligger inom synf�ltet.
 
f�rslag:
-ta in global tabel med alla omr�den
-ta in array med team_vision
-ta fram punkt (i,j) ur tabell med alla omr�den
-kolla om samma punkt finns i team_vision
-om inte: 

   

  return; //skicka tillbaka vilka omr�den som finns
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
  /*givet en yta och tillh�rande r�nder:
-�r ytan �r s�krad -> prio=5
-kan man se hela ytan fr�n alla omr�den p� randen?
         -ja: �r antalet omr�den i randen mer �n ett?
	           -ja: prio ->3
		   -nej:prio ->1
         -nej: �r antalet omr�den i randen mer �n ett?
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
-unders�k om flyttbara noders synf�lt redan finns med inom aktuellt synf�lt fr�n gruppen
-om det finns n�gon ekvivalent position: skapa en fiktiv jagare

  return;
  */
}

/*====================one_iteration():Phase two, Evaluation=======================================*/
void valuation(/*int *next_move*/){ //anv�nder data fr�n preparation och designerar v�rden till noder som g�r at flytta till
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
}

void solve_knappsack(/*antal_att_delegera, data fr�n make_distance*/){
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
  //addera v�rdet close p� den/de flyttbara noder med kortast avst�nd till n�gon rand
}

void add_unique_guarding_value(/*jagare[i]*/){
  //addera v�rdet unique p� den/de flyttbara noder som ser unika rand-omr�den
}

void add_priority_guarding_value(/*jagare[i]*/){
  //addera v�rdet priority p� den/de flyttbara noder som ser unika prioritetsomr�den
}

void add_big_vision_value(/*jagare[i]*/){
  //addera v�rdet big_vision p� den/de flyttbara noder som ser mest
}

void find_best_cost(){
  /*
f�r varje jagare:
-l�s av vilken ruta som har h�gst v�rde
   */ 
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
    to=get_bestmove(from); //find the moveable tile to move
    put_movestrat(index, from, to); // move and update the number of moves made
} 
  update_states(); //j�mf�r tillst�nd f�r f�rflyttning med efter, uppdaterar tillst�nds�ndringar
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
-h�mta nod (r,k) ur NodeMatrix
-h�mta vilken nod som har b�st v�rde enligt utdata fr�n evaluation()
- s�tt to=nod som ska flyttas till
   
 return to
 */
}

void put_movestrat(/*int startindex,struct Node *from, struct Node *to*/){
  /*
-h�mta nya positioner genom to.name[]
-ber�kna r�tt index att placera de nya positionerna p� i solution[]
-l�gg in jagarnas nya positionerpositioner i slutet p� solution[]
-addera ett till solution [1] (antal steg gjorda)
  */
  return;
}

void update_states(){
  /*
-l�s av nuvarande states i NodeMatrix
-j�mf�r f�rh�llande f�re och efter f�rflyttning
-updatera de states som har f�r�ndrats.
   */
  return;
}


//XXXXXXXXXXXXXXXXXXX---------END GREEDY---------XXXXXXXXXXXXXXXXXXXXXXXX
