#include "Header.h"


/*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				    TABU SEARCH
				xxxxxxxxxxxxxxxxxxx  
inehåller: psevdokod, kod, och komentarer
programspråk C
av: felix blumenberg.. under MYCKET assistans av Fredrik Båberg 			   
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/



/*hur man kompillerar:
-----------------------------------------

cygdrive
kompilera:
gcc –o NodeGen NodeGenFromFile.c genetic.o greedy.o
köra:
./NodeGen
------------------------------------------
*/

/*TANKARSKRÄP

Tom... är du här?


TANKAR:
111111111111111111111111111111111111111111
hur ska tabulistan se ut?
humm... 
första tanken är att det ska va en lista med olika kordinater ij ur vår huvudmatris 
dvs tabuna är kombinationer av i och j ur B[i][j] laggda i en lista

problemet med detta är att hur i helvete ska jag göra 30% tabu villkoret?


behöver jag nu möjligheten att gämföra 
ett steg (med säkrrat_värde= 8
mot annat steg (med säkrat_värde = 9 
dvs flera ställen att spara steget på... 

nej kan gemföra mellan gammla
current_position_solution()
och
current_position_solution_in_progress()


2222222222222222222222222222222222222222222
 ASPIRATION ASPIRATIONS ASPIRATIONSVILKORET 
===========5===========
BESKRIVNING:
Beräkning av apirations tillståndet =>6
TANKAR:
hur i helvete ser aspirationsvillkoret ut?

JO:
1
yta säkrad + yta sedda = bästa någonsinn.
2
om i K kritiskt område av typen (ser slutet ) har du tillgång att backa (
 men nås du ser slutet i tunneln så sätts tunnelns slut tabu)
omformulering när du kommer till denna punkt raderas hela tabulistan med tidigare steg. 
och lägger till allt längst in i gången.






- exmpel:
om vi går hit så säkrar vi ett område!
vi minskar total säkrad yta med %
vi minskar totala antalet sedda ytor 


yta säkrad + yta sedda = bästa någonsinn.
där säkrade och sedda inte-får/får va samma yta.

man ser väldigt mycket fårn denna yta tex ( ogillar denna redan ex står still där hela tiden.)
FUNKTIONER:







33333333333333333333333333333333
tabu problemet med 30%

först steg om 30% förlust tabu

först S-listan
sen 30% 
då den slår till så stannar vi och gör följande
en jagare står still de andra går sitt steg randomat till sig sen innan.
sen gör vi detta för alla jagare en efter en, tills det funkar, om det inte funkar randomar vi om hela steget.


tan


44444444444444444444444444444444

tabu  *S- listan kan va lösningen som spottas ut för där sparas alla steg varje jagare gjorde. 
i en lång lista.

nytt steghamnar högst upp steg första steget längst ner.
*/

/*Future
void getRandom(struct Gene *g, int from, int nrSteps);
int calculateStates(int *solution); //solution = complete_solution[]

1
Solution[] = {antal jagare,antal_steg = 0, sj1r1,sj1k1,..., sj1r2,sj1k2,...};

2
getRandom()
Solution[] = {antal jagare,antal_steg > 0, sj1r1,sj1k1,..., sj1r2,sj1k2,...};

3
//området är tabu
4
OM calculateStates(int *Solution) != 0:
	GOTO 2
OM max_antal_steg >= antal_stege: 
	GOTO 1
4
4.1 uppdaterar: antal_steg = max_antal_steg
4.2 sparas i en lista för framtida gemförelser

5
gemför listan av:
Solution[] = {antal jagare,antal_steg > 0, sj1r1,sj1k1,..., sj1r2,sj1k2,...};

*/

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX



/*HUVUDPROGRAMET 
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				    TABU SEARCH
				xxxxxxxxxxxxxxxxxxx  
alla funktioner åvan ihoppbakade i dessa två nedan		   
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/
//xxxxxxxxxxxxxxx


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  GLOBAL VARIBALS XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX     AND SUCH     XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//xxxxxxxxxxxxxxxxxxxxxxxxxxx Definitions xxxxxxxxxxxxxxxxxxxxxxxxxxx
#define OK 1
#define NOT_OK 0
//max_step_minus_in_L_list anticyklingsvilkoret 
#define max_step_minus_in_L_list 5



//xxxxxxxxxxxxxxxxxxxxxxxxxxx Varibals xxxxxxxxxxxxxxxxxxxxxxxxxxx
int TABU_ROWS = 0;
int TABU_COLS = 0;
int solution[2000];
int tabuMatris[SIZE][SIZE];  //int tabuMatris[TABU_ROWS][TABU_COLS];
int qqq=0; 

//xxxxxxxxxxxxxxxxxxxxxxxxxxx Functions xxxxxxxxxxxxxxxxxxxxxxxxxxx
//FREDRIK
int calculateStates(int *path);
int getS4();
void printStates();
struct Node **NodeMatrix; // Node matrix

//FREDRIK och FELIX
void getRandom(int from);

//FELIX
int check_ALL_Tabu_lists(); //i vilken TRE delar ingår K,30,L

//del K
int check_K_Tabu_list_all_Hunters();
int check_K_Tabu_list_one_Hunter(); //alla returenerar OK eller NOT_OK

//del 30
int check_30_Tabu_list();

//del L
int check_L_Tabu_list();
int check_L_Tabu_list_X_past_steps();
//del L check right
int tabu_up();
int check_K_Tabu_list_one_Hunter_step_up();
int check_L_Tabu_list_X_past_steps_up();

// del L check right
int tabu_right();
int check_K_Tabu_list_one_Hunter_step_right();
int check_L_Tabu_list_X_past_steps_right();

// del L check down
int tabu_down();
int check_K_Tabu_list_one_Hunter_step_down();
int check_L_Tabu_list_X_past_steps_down();

// del L check left
int tabu_left();
int check_K_Tabu_list_one_Hunter_step_left();
int check_L_Tabu_list_X_past_steps_left();
	

 
void print_Tabu_States(); 



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX     HÅRD KOD     XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX     OMRÅDE       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX



//tabuMatris[TABU_ROWS][TABU_COLS]
/*

	//hordkodningsyta:
	tabuMatris[2][3]=1;
	tabuMatris[3][3]=1;
	tabuMatris[4][3]=1;
	tabuMatris[2][4]=1;
	tabuMatris[3][4]=1;
	tabuMatris[4][4]=1;
	//slut


2= jagarna startar där
3= tabu områdena
1 1 1 1 1
1 0 1 1 2
1 0 1 3 3
1 0 1 3 3
0 2 1 3 3
*/



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  TABU ALGORITEM XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	  PREPARATIONS  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


void preTabu(struct Node (*NodeMat)[SIZE], int *Hunters, int BREAK) { // Do all pre-processing, which is to generate population.
	printf("\n");
	printf("START preTabu\n");
	printf("\n");
	
	


	
	int i,j;
	/*** Allocate memory for NodeMatrix ***/
	NodeMatrix = malloc(SIZE * sizeof(struct Node *));
	if(NodeMatrix == NULL)
		fprintf(stderr, "out of memory\n");
	for(i = 0; i < SIZE; i++)
	{
		NodeMatrix[i] = malloc(SIZE * sizeof(struct Node));
		if(NodeMatrix[i] == NULL)
			fprintf(stderr, "out of memory\n");
	}
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			NodeMatrix[i][j] = NodeMat[i][j];
			/*** Check number of rows and columns of B. */
			if(NodeMatrix[i][j].vision[0] != 0){
				if(NodeMatrix[i][j].name[0]+1 > TABU_ROWS)
					TABU_ROWS = 1+NodeMatrix[i][j].name[0];
				if(NodeMatrix[i][j].name[1]+1 > TABU_COLS)
					TABU_COLS = 1+NodeMatrix[i][j].name[1];
			}
		}
	}
	
	// denna del sätter in ettor på varje platts det fins ett hinder i matrisen in i tabumatrisen
	// beövde denna tack och lov hade fredrik redan skivit den för eget bruk
	int r,c;
	for(r = 0; r < TABU_ROWS; r++){
		for(c = 0; c < TABU_COLS; c++){ // For every node:
			if(NodeMatrix[r][c].vision[0] == 0){ // Obstacle
				tabuMatris[r][c]=1;
			}
			else{
				tabuMatris[r][c]=0;
			}
		}
	}
	
	
	//tabuMatris[1][2]=1;
	//tabuMatris[1][1]=1;
	//tabuMatris[2][1]=1;
	//tabuMatris[3][2]=1;
	/*
	//hordkodningsyta:
	tabuMatris[2][1]=0;
	tabuMatris[2][3]=0;
	tabuMatris[3][3]=0;
	tabuMatris[4][3]=0;
	tabuMatris[2][4]=0;
	tabuMatris[3][4]=0;
	tabuMatris[4][4]=0;
	//slut
	*/
	
	//Do actual pre-processing
	int pursuer,next=2;
	solution[0] = Hunters[0];
	printf("Pursuers: %d\n", solution[0]);
	for(pursuer = 0; pursuer < Hunters[0]; pursuer++){
		solution[next] = Hunters[1+pursuer*2];
		solution[next+1] = Hunters[1+pursuer*2+1];
		printf("(%d,%d)", solution[next],solution[next+1]);
		next = next+2;
	}
	printf("\n");
	printf("END preTabu\n");
	printf("\n");
}

// icke tabu from+1 om tabu from= from

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  TABU ALGORITEM XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX



void Tabu() { // Main call function for Tabu Algorithm  annat namn Algorithm_Tabu_Search()

	printf( "START Tabu\n\n");
	//int tabuMatris[TABU_ROWS][TABU_COLS]
	
	// ONE SOLUTION CREATER:
	int i, steps=100; // step = slutlösningens längd uppdaterade variabel
	for(i=0;i<steps;i++){
		
		getRandom(i); // Generate a random step sequence from step #
		i=check_ALL_Tabu_lists(solution,i);
		//check_L_Tabu_list_X_past_steps(solution,i,0);
		//check_L_Tabu_list_X_past_steps(solution,i,1);
		calculateStates(solution); // =antalet steg det tog för lösning (inte helt optimerad beräknare.
		if(getS4() == 0){
			
			printf( "Complett solution path:\n");
			// här kommer en funktion in som skall:
			//spara den completta lösningen från solution[] till någon lista med alla completta lösningar
		
			break;
		}
		
	}

	//MASSA PRINTS:
	for(i=0;i<2*(1+solution[1]*solution[0]);i+=2){
		// printar alla stegen 
		printf("(%d,%d)", solution[i], solution[i+1]);
	}
	printf("\n");
	printf("path length: %d\n", solution[1]);
	printf("\n\n");
	printf("State matrisen:\n");
	printStates(); // i from av en matris
	printf("Omraden kvar i States 4: %d\n", getS4());
	printf("\n\n");
	printf("Tabu State matrisen:\n");
	print_Tabu_States(); // vilka rutor som har vilka värden, i from av en matris
	printf( "\n");
	printf( "antal tabu; %d\n", qqq);
	printf( "\n");
	printf("i: %d\n", i);
	printf( "\n");
	printf( "END Tabu\n\n");
	//qqq=0;
	for(i = 0; i < SIZE; i++){
		free(NodeMatrix[i]);
	}
	free(NodeMatrix);
	return;
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   NEEDED    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  FUNKTIONS  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX



int check_ALL_Tabu_lists(int *solution, int i){

	// TABU 1	
	if(check_K_Tabu_list_all_Hunters(solution,i)==OK){
		// TABU 2
		printf("TABU2 OK\n");
		if (check_30_Tabu_list(solution,i)==OK){ // KOM PÅ VARFÖR DENN ALIGGER FÖRE L LIST??? 
			// TABU 3
			if(check_L_Tabu_list(solution,i)==OK){ // K list än så länge
				printf("TABU3 OK\n");
				return i;
			}
		}
	}
	printf("Tabu\n");
	i--;
	qqq++;
	printf("i: %d\n", i);
	if(i<0){
		i=0;
	}
	return i;
}



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   K START   
int check_K_Tabu_list_all_Hunters(int *solution, int i){
	//check_K_Tabu_list(solution,i);
	
	int k;
	for(k=0;k<solution[0]; k++){
		if(check_K_Tabu_list_one_Hunter(solution,i,k)==NOT_OK){
			printf("check_K_Tabu_list_all_Hunters NOT_OK\n");
			return NOT_OK;
		}
	}
	printf("check_K_Tabu_list_all_Hunters OK\n");
	return OK;
}

int check_K_Tabu_list_one_Hunter(int *solution, int i, int k){
	
	int rad = solution[    2+2*solution[0]+i*(2*solution[0])+2*k]; 		// raden vi är på nu
	int kol = solution[1 + 2+2*solution[0]+i*(2*solution[0])+2*k];	// colonen vi är på nu
	
	if(tabuMatris[rad][kol] != 0){

		int varde = tabuMatris[rad][kol];
		printf(" check_K_Tabu_list_one_Hunter NOT_OK: Tabu! (%d,%d) = %d \n", rad, kol, varde);
			
		
		return NOT_OK;
			
	}
	printf("check_K_Tabu_list_one_Hunter OK\n");
	return OK;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   K END  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   30 START   


int check_30_Tabu_list(int *solution, int i){
	printf("check_30_Tabu_list OK\n ");
	calculateStates(solution);
	int sBefore = getS4();
	solution[1]--;
	calculateStates(solution);
	solution[1]++;
	int sAfter = getS4();
	if(sBefore-10<=sAfter){
		return OK;
	}
	printf("30 NOT OK ****************************************************\n");
	return NOT_OK;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   30 END   XXXXXXXXXXXXXXXXXXXXXXXXXXXXX



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   L START   


int check_L_Tabu_list(int *solution, int i){
	int k;
	for(k=0;k<solution[0]; k++){
		printf("check_L_Tabu_list START och k: %d\n",k);
		//text
		if(check_L_Tabu_list_X_past_steps(solution,i,k)==NOT_OK){
			printf("check_L_Tabu_list_X_past_steps NOT OK\n");
			printf("\n");
			// aspriations vilkoret: det nedan förebygger låsning av programet.
			
			//check up
			if(tabu_up(solution,i,k)==OK){ // sätt minustäcknet (i-1) i tabu_up  // vi har här en possition i solution som behöver bli satt till den åvanför  // dvs i funktionen nedan plusar vi på 1 upp och gör gemförelsen
				if(check_K_Tabu_list_one_Hunter_step_up(solution,i,k)==OK){ // dom ligger i denna ordning pga att K listan är mer dominant samt underlättade skrivandet av tabu_up
					if(check_L_Tabu_list_X_past_steps_up(solution,i,k)==OK){
						return NOT_OK;
					}
					
				}
			
			}
			
			//check right
			if(tabu_right(solution,i,k)==OK){ // sätt minustäcknet (i-1) i tabu_up  // vi har här en possition i solution som behöver bli satt till den åvanför  // dvs i funktionen nedan plusar vi på 1 upp och gör gemförelsen
				if(check_K_Tabu_list_one_Hunter_step_right(solution,i,k)==OK){
					if(check_L_Tabu_list_X_past_steps_right(solution,i,k)==OK){
						return NOT_OK;
					}
					
				}
			
			}
			
			// check down
			if(tabu_down(solution,i,k)==OK){ // sätt minustäcknet (i-1) i tabu_up  // vi har här en possition i solution som behöver bli satt till den åvanför  // dvs i funktionen nedan plusar vi på 1 upp och gör gemförelsen
				if(check_K_Tabu_list_one_Hunter_step_down(solution,i,k)==OK){
					if(check_L_Tabu_list_X_past_steps_down(solution,i,k)==OK){
						return NOT_OK;
					}
					
				}
			
			}
			
			//check left
			if(tabu_left(solution,i,k)==OK){ // sätt minustäcknet (i-1) i tabu_up  // vi har här en possition i solution som behöver bli satt till den åvanför  // dvs i funktionen nedan plusar vi på 1 upp och gör gemförelsen
				if(check_K_Tabu_list_one_Hunter_step_left(solution,i,k)==OK){
					if(check_L_Tabu_list_X_past_steps_left(solution,i,k)==OK){
						return NOT_OK;
					}
					
				}
			
			}
	
			//break // vill att den skall gå till nästa jagare
		
		}
		continue;	// hoppar till forlopen gör om för nästa jagare
	}
	
	return OK;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



int tabu_up(int *solution, int i, int k){
	// vi ska ha positionen innan den vi är i. och se om den är okey innom matrisen
	
	int b;
	b=i-1;
	
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k] -1; 	// raden vi är på i förra steget
	//int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k];	// colonen vi är på i förra steget
	
	if(rad==-1){
		printf("tabu_up NOT_OK\n");
		return NOT_OK;
	}
	printf("tabu_up OK\n");
	return OK;
}

int tabu_left(int *solution, int i, int k){
	// vi ska ha positionen innan den vi är i. och se om den är okey innom matrisen
	
	int b;
	b=i-1;
	
	//int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k]; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k] -1;	// colonen vi är på i förra steget
	
	if(kol==-1){
		printf("tabu_left NOT_OK\n");
		return NOT_OK;
	}
	printf("tabu_left OK\n");
	return OK;
}

int tabu_right(int *solution, int i, int k){
	// vi ska ha positionen innan den vi är i. och se om den är okey innom matrisen
	
	int b;
	b=i-1;
	
	//int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k]; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k] +1;	// colonen vi är på i förra steget
	
	if(kol==TABU_COLS){
		printf("tabu_right NOT_OK\n");
		return NOT_OK;
	}
	printf("tabu_right OK\n");
	return OK;
}

int tabu_down(int *solution, int i, int k){
	// vi ska ha positionen innan den vi är i. och se om den är okey innom matrisen
	
	int b;
	b=i-1;
	
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k] +1; 	// raden vi är på i förra steget
	//int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k];	// colonen vi är på i förra steget
	
	if(rad==TABU_ROWS){
		printf("tabu_down NOT_OK\n");
		return NOT_OK;
	}
	printf("tabu_down OK\n");
	return OK;
}




int check_K_Tabu_list_one_Hunter_step_up(int *solution, int i, int k){
	// backa ett steg sen gå up ett steg och sen kolla om denna tabu mot K listan 
	
	int b;
	b=i-1;
	int s,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k] -1; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k];	// colonen vi är på i förra steget
	if(tabuMatris[rad][kol] != 0){

		int varde = tabuMatris[rad][kol];
		printf(" check_K_Tabu_list_one_Hunter_step_up NOT    L list upp Tabu! (%d,%d) = %d \n", rad, kol, varde);
			
		//printf("Tabu!\n");
		
		return NOT_OK;
			
	}
	printf("check_K_Tabu_list_one_Hunter_step_up OK\n");
	return OK;

}

int check_K_Tabu_list_one_Hunter_step_right(int *solution, int i, int k){
	// backa ett steg sen gå right ett steg och sen kolla om denna tabu mot K listan 
	
	int b;
	b=i-1;
	int s,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k]; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k] +1;	// colonen vi är på i förra steget
	if(tabuMatris[rad][kol] != 0){

		int varde = tabuMatris[rad][kol];
		printf("check_K_Tabu_list_one_Hunter_step_right NOT_OK    L list right Tabu! (%d,%d) = %d \n", rad, kol, varde);

		return NOT_OK;
	}
	printf("check_K_Tabu_list_one_Hunter_step_right OK\n");
	return OK;

}

int check_K_Tabu_list_one_Hunter_step_down(int *solution, int i, int k){
	// backa ett steg sen gå down ett steg och sen kolla om denna tabu mot K listan 
	
	int b;
	b=i-1;
	int s,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k] +1; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k];	// colonen vi är på i förra steget
	if(tabuMatris[rad][kol] != 0){

		int varde = tabuMatris[rad][kol];
		printf("L list down Tabu! (%d,%d) = %d \n", rad, kol, varde);
		printf("check_K_Tabu_list_one_Hunter_step_down NOT_OK\n");	
		//printf("Tabu!\n");
		return NOT_OK;
			
	}
	printf("check_K_Tabu_list_one_Hunter_step_down OK\n");
	return OK;

}

int check_K_Tabu_list_one_Hunter_step_left(int *solution, int i, int k){
	// backa ett steg sen gå left ett steg och sen kolla om denna tabu mot K listan 
	
	int b;
	b=i-1;
	int s,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k]; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k] -1;	// colonen vi är på i förra steget
	if(tabuMatris[rad][kol] != 0){

		int varde = tabuMatris[rad][kol];
		printf("L list left Tabu! (%d,%d) = %d \n", rad, kol, varde);
			
		printf("check_K_Tabu_list_one_Hunter_step_left NOT_OK\n");
		return NOT_OK;
			
	}
	printf("check_K_Tabu_list_one_Hunter_step_left OK\n");
	return OK;

}




//XXXXXXXXXXXXXXXXXXXXXXXXXX

/*

int check_L_Tabu_list_X_past_steps(int *solution, int i, int k){ // return OK/NOT_O
	// denna ska bara kolla om de 4 gamla stegen är tabu för varje jagare.

	
	// alla if utifall korta steg.
	if (i==1){
		int s;
		
		int rad = solution[    2+2*solution[0]+i*(2*solution[0])+2*k]; 	// raden vi är på nu
		int kol = solution[1 + 2+2*solution[0]+i*(2*solution[0])+2*k];	// colonen vi är på nu

		for(s=1;s<2;s++){
			int rad_minus = solution[    2+2*solution[0]+(i-s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
			int kol_minus = solution[1 + 2+2*solution[0]+(i-s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
			if(rad==rad_minus && kol==kol_minus){
				return NOT_OK;
			}
		}
	
	}
	
	
	
	if (i==2){
		int s;
		
		int rad = solution[    2+2*solution[0]+i*(2*solution[0])+2*k]; 	// raden vi är på nu
		int kol = solution[1 + 2+2*solution[0]+i*(2*solution[0])+2*k];	// colonen vi är på nu

		for(s=1;s<3;s++){
			int rad_minus = solution[    2+2*solution[0]+(i-s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
			int kol_minus = solution[1 + 2+2*solution[0]+(i-s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
			if(rad==rad_minus && kol==kol_minus){
				return NOT_OK;
			}
		}
	
	}
	
	
	
	if (i==3){
		int s;
		
		int rad = solution[    2+2*solution[0]+i*(2*solution[0])+2*k]; 	// raden vi är på nu
		int kol = solution[1 + 2+2*solution[0]+i*(2*solution[0])+2*k];	// colonen vi är på nu

		for(s=1;s<4;s++){
			int rad_minus = solution[    2+2*solution[0]+(i-s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
			int kol_minus = solution[1 + 2+2*solution[0]+(i-s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
			if(rad==rad_minus && kol==kol_minus){
				return NOT_OK;
			}
		}
		
	
	}
	
	
	
	if (i >= 4){
		int s;
		
		int rad = solution[    2+2*solution[0]+i*(2*solution[0])+2*k]; 	// raden vi är på nu
		int kol = solution[1 + 2+2*solution[0]+i*(2*solution[0])+2*k];	// colonen vi är på nu

		for(s=1;s<5;s++){
			int rad_minus = solution[    2+2*solution[0]+(i-s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
			int kol_minus = solution[1 + 2+2*solution[0]+(i-s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
			if(rad==rad_minus && kol==kol_minus){
				return NOT_OK;
			}
		}
	
	}
	
	return OK;
}
*/




int check_L_Tabu_list_X_past_steps(int *solution, int i, int k){ // return OK/NOT_O
	// denna ska bara kolla om de 4 gamla stegen är tabu för varje jagare.
	//printf("check_L_Tabu_list_X_past_steps\n");
	
	int s=i,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+i*(2*solution[0])+2*k]; 	// raden vi är på nu
	int kol = solution[1 + 2+2*solution[0]+i*(2*solution[0])+2*k];	// colonen vi är på nu
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s=i-1;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		
		int rad_minus = solution[    2+2*solution[0]+(s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
		int kol_minus = solution[1 + 2+2*solution[0]+(s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			printf("check_L_Tabu_list_X_past_steps NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	printf("check_L_Tabu_list_X_past_steps OK\n");
	return OK;
}




int check_L_Tabu_list_X_past_steps_up(int *solution, int i, int k){
	// backa ett steg sen gå up ett steg och sen kolla om denna tabu mot L listan
	
	int b;
	b=i-1;
	int s,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k] -1; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k];	// colonen vi är på i förra steget
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s=i-1;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		
		int rad_minus = solution[    2+2*solution[0]+(s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
		int kol_minus = solution[1 + 2+2*solution[0]+(s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			printf("check_L_Tabu_list_X_past_steps_up NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}printf("check_L_Tabu_list_X_past_steps_up OK\n");
	return OK;
}

int check_L_Tabu_list_X_past_steps_right(int *solution, int i, int k){
	// backa ett steg sen gå right ett steg och sen kolla om denna tabu mot L listan
	
	int b;
	b=i-1;
	int s,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k]; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k] +1;	// colonen vi är på i förra steget
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s=i-1;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		
		int rad_minus = solution[    2+2*solution[0]+(s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
		int kol_minus = solution[1 + 2+2*solution[0]+(s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			printf("check_L_Tabu_list_X_past_steps_right NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	printf("check_L_Tabu_list_X_past_steps_right OK\n");
	return OK;

}
	
int check_L_Tabu_list_X_past_steps_down(int *solution, int i, int k){
	// backa ett steg sen gå down ett steg och sen kolla om denna tabu mot L listan
	
	int b;
	b=i-1;
	int s,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k] +1; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k];	// colonen vi är på i förra steget
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s=i-1;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		
		int rad_minus = solution[    2+2*solution[0]+(s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
		int kol_minus = solution[1 + 2+2*solution[0]+(s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			printf("check_L_Tabu_list_X_past_steps_down NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	printf("check_L_Tabu_list_X_past_steps_down OK\n");
	return OK;

}
	
int check_L_Tabu_list_X_past_steps_left(int *solution, int i, int k){
	// backa ett steg sen gå left ett steg och sen kolla om denna tabu mot L listan
	
	int b;
	b=i-1;
	int s,number_of_steps_backward=0;
	int rad = solution[    2+2*solution[0]+b*(2*solution[0])+2*k]; 	// raden vi är på i förra steget
	int kol = solution[1 + 2+2*solution[0]+b*(2*solution[0])+2*k]  -1;	// colonen vi är på i förra steget
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s=i-1;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		
		int rad_minus = solution[    2+2*solution[0]+(s)*(2*solution[0])+2*k]; 	// raden s steg bakot från där vi är nu
		int kol_minus = solution[1 + 2+2*solution[0]+(s)*(2*solution[0])+2*k];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			printf("check_L_Tabu_list_X_past_steps_left NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	printf("check_L_Tabu_list_X_past_steps_left OK\n");
	return OK;

}

	
	
	
	
	
	

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   L END   XXXXXXXXXXXXXXXXXXXXXXXXXXXXX



void print_Tabu_States(){
	// skriver ut hur K_Tabu_list matrisen ser ut
	int r,c;
	for(r = 0; r < TABU_ROWS; r++){
		for(c = 0; c < TABU_COLS; c++){ // For every node:
			printf("%d ", tabuMatris[r][c]);
		}
		printf("\n");
	}
}



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   FREDRIK    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   BÅBERG    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


void getRandom(int from){ // AV  fredrik och felix  // Generate random step-sequence from a given node
	
	int pursuer,stepnr=2*(1+from*solution[0]), nextStep;
	struct Node *current;
	for(pursuer=0;pursuer<solution[0];pursuer++){
		 current = &NodeMatrix[solution[stepnr]][solution[stepnr+1]];
		while(1==1){
			nextStep = ((int)((double)rand() / ((double)RAND_MAX + 1)*4));
			if(((*current).move[nextStep]) != 0)
				break;
		}
		
		solution[stepnr+2*solution[0]] = (*(current)->move[nextStep]).name[0];
		solution[stepnr+2*solution[0]+1] = (*(current)->move[nextStep]).name[1];
		stepnr = stepnr+2;
	}
	solution[1]=(from+1)/solution[0];
}


void printStates(){
	//printf("printStates\n");
	int r,c;
	for(r = 0; r < TABU_ROWS; r++){
		for(c = 0; c < TABU_COLS; c++){ // For every node:
			printf("%d ", NodeMatrix[r][c].state);
		}
		printf("\n");
	}
}


int getS4(){
	//printf("getS4\n");
	int S4=0,r,c;
	for(r = 0; r < TABU_ROWS; r++){
		for(c = 0; c < TABU_COLS; c++){ // For every node:
			if(NodeMatrix[r][c].state == 4){
				S4++;
			}
		}
	}
	return S4;
}


int calculateStates(int *path){
	//printf("calculateStates\n");
	int currentStep,pursuer;
	int S[TABU_ROWS][TABU_COLS], S_u[TABU_ROWS][TABU_COLS];
	int r,c;
	//Set default values for S and S_u 
	for(r = 0; r < TABU_ROWS; r++){
		for(c = 0; c < TABU_COLS; c++){ // For every node:
			if(NodeMatrix[r][c].vision[0] == 0){ // Obstacle
				S[r][c]=0;
				S_u[r][c]=0;
				NodeMatrix[r][c].state = 0;
			}
			else{
				S[r][c]=4;
				S_u[r][c]=4;
				NodeMatrix[r][c].state = 4;
			}
		}
	}
	//For all steps 
	for(currentStep = 0; currentStep < path[1];currentStep++){ // Go through every step, should terminate if no Node is in state 4.
		// Set values in S 
		for(pursuer=0;pursuer < path[0]; pursuer++){ // For each pursuer
			// State 1 
			S[path[2*(1+currentStep+pursuer)]][path[2*(1+currentStep+pursuer)+1]] = 1; // Set state for S to 1 for each pursuer
			// State 2
			int k=0;
			while((NodeMatrix[path[2*(1+currentStep+pursuer)]][path[2*(1+currentStep+pursuer)+1]].vision[k]) != 0){ // Set state for S to 2 for each visible node not containing a pursuer
				int S_r = (*NodeMatrix[path[2*(1+currentStep+pursuer)]][path[2*(1+currentStep+pursuer)+1]].vision[k]).name[0];
				int S_c = (*NodeMatrix[path[2*(1+currentStep+pursuer)]][path[2*(1+currentStep+pursuer)+1]].vision[k]).name[1];
				if(S[S_r][S_c] != 1) // If not containing a pursuer
					S[S_r][S_c] = 2;
				k++;
			}
		}
		int needUpdate = 1;
		while(needUpdate == 1){
			for(r = 0; r < TABU_ROWS; r++){
				for(c = 0; c < TABU_COLS; c++){ // For every node:
					if(S_u[r][c] == 0){} // Do nothing for obstacles
					else
						S_u[r][c] = 4; // Set state 4 as default
				}
			}
			//Set S1 for pursuers, S2 for visible
			for(pursuer=0;pursuer < path[0]; pursuer++){ // For each pursuer
				//State 1 
				S_u[path[2*(1+currentStep+pursuer)]][path[2*(1+currentStep+pursuer)+1]] = 1; // Set state for S_u to 1 if it contains a pursuer
				// State 2 
				int k=0;
				while((NodeMatrix[path[2*(1+currentStep+pursuer)]][path[2*(1+currentStep+pursuer)+1]].vision[k]) != 0){ // Set state for S_u to 2 if it is visible and doesn't contain a pursuer
					int S_r = (*NodeMatrix[path[2*(1+currentStep+pursuer)]][path[2*(1+currentStep+pursuer)+1]].vision[k]).name[0];
					int S_c = (*NodeMatrix[path[2*(1+currentStep+pursuer)]][path[2*(1+currentStep+pursuer)+1]].vision[k]).name[1];
					if(S_u[S_r][S_c] != 1) // If not containing a pursuer
						S_u[S_r][S_c] = 2;
					k++;
				}
			}
			//Check state 3,4
			for(r = 0; r < TABU_ROWS; r++){
				for(c = 0; c < TABU_COLS; c++){ // For every node:
					if(S_u[r][c]!=4){} // State has been updated in S_u
					//else if(S[r][c]==1 && S_u[r][c]!=1){} // Did contain pursuer but currently does not.
					else if(S[r][c]==4){}
					else{
						int check = 1, direction;
						for(direction=0;direction<4;direction++){ // Go left,right,up,down
							if(NodeMatrix[r][c].move[direction] != 0){ // If it is possible to move
								int S_r = (*NodeMatrix[r][c].move[direction]).name[0];
								int S_c = (*NodeMatrix[r][c].move[direction]).name[1];
								if(S[S_r][S_c] == 4){
									check = 0;
									break;
								}
							}
						}
						if(check==1) // If not in state 4
							S_u[r][c]=3;
					}
				}
			}
			needUpdate=0;
			for(r = 0; r < TABU_ROWS; r++){ /*** Check if update is needed ***/
				for(c = 0; c < TABU_COLS; c++){ // For every node:
					if(S[r][c] != S_u[r][c]){
						needUpdate=1;
					}
				}
			}
			for(r = 0; r < TABU_ROWS; r++){ /*** Set S to S_u before new iteration ***/
				for(c = 0; c < TABU_COLS; c++){ // For every node:
					S[r][c] = S_u[r][c];
				}
			}
		}
		//Set states in NodeMatrix to S 
		for(r = 0; r < TABU_ROWS; r++){
			for(c = 0; c < TABU_COLS; c++){ // For every node:
				NodeMatrix[r][c].state = S[r][c];
			}
		}
		if(getS4()==0){
			//Can stop calculate states, solution found.
			path[1]=currentStep;
			return currentStep;
		}

	}
	return currentStep;
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXX WHERE THIS LIFE ENDS ANOTHERS BEGIN  XXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


