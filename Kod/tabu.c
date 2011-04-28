#include "Header.h"

// testa imorn bara ha en tabu_solution1 och skippa 2 3 4 för de blir ju aldrig användna

/*HUVUDPROGRAMET 
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				    TABU SEARCH
				xxxxxxxxxxxxxxxxxxx  
	   
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



//xxxxxxxxxxxxxxxxxxxxxxxxxxx Viktiga!!! xxxxxxxxxxxxxxxxxxxxxxxxxxx

<<<<<<< HEAD
#define max_step_minus_in_L_list 1 				// hur många tidigare steg vi skall förbjuda att gå på 35
#define allowed_stat_4_loss 2 						// antalet områden vi får förlora i ett steg
#define max_antal_INcomplete_tabu_solutions 5
#define TABU_MAX_LIKA 10

#define MAX_TABU_STEPS 300
int best_step_length=301;							//VIKTIGT steps får inte va för hög ty 2*(jagare=5)*800 = 8000 < int tabu_solution[8500]
#define START_FROM_THE_BEGINING_AGEN_NUMBER 4 		//antalet gånger man når MAX_TABU_STEPS innan man besetämeer att ingen lösning finns


#define to_easy_problem_problem_adjustment_set_nr_steps_to 4				//sätt denna till noll så blir du av med detta
#define to_easy_problem_problem_adjustment_go_agen_nr 2			// om 2 körs den två gånger
#define Mss_L_fuck_up 50000

=======
#define max_step_minus_in_L_list 0 				// hur många tidigare steg vi skall förbjuda att gå på 35
#define allowed_stat_4_loss 10 						// antalet områden vi får förlora i ett steg
#define max_antal_INcomplete_tabu_solutions 1000
#define TABU_MAX_LIKA 50

#define MAX_TABU_STEPS 200							//VIKTIGT steps får inte va för hög ty 2*(jagare=5)*800 = 8000 < int tabu_solution[8500]
#define START_FROM_THE_BEGINING_AGEN_NUMBER 5 		//antalet gånger man når MAX_TABU_STEPS innan man besetämeer att ingen lösning finns


#define to_easy_problem_problem_adjustment_set_nr_steps_to 0				//sätt denna till noll så blir du av med detta
#define to_easy_problem_problem_adjustment_go_agen_nr 0			// om 2 körs den två gånger
#define Mss_L_fuck_up 50
>>>>>>> 9212b72d62abf8b3e97fdd05bc91418edab2f73b



// MAX_TABU_STEPS = slutlösningens längd uppdaterade variabel 
//VIKTIGT steps får inte va för hög ty 2*(jagare=5)*800 = 8000 < int tabu_solution[8500] 



//typVÄRDEN:	max_step_minus_in_L_list			antal_områden*0,5	//ROWS*COLS*0,5
//typVÄRDEN:	allowed_stat_4_loss					????			
//typVÄRDEN:	max_antal_INcomplete_tabu_solutions		rellativt högt
//xxxxxxxxxxxxxxxxxxxxxxxxxxx Varibals xxxxxxxxxxxxxxxxxxxxxxxxxxx
//FREDRIK:
int ROWS;
int COLS;
int *tabu_solution;
//FELIX:
int *returned_Tabu_tabu_solution;
int **tabuMatris;  //int tabuMatris[ROWS][COLS];
int Mr_30=1;
int Mss_30=4;
int Mr_L=1; //vill ta bort Mr & Mss L men vi har dom med för säkerhetskull

int nr_of_tabus = 0;
//int best_step_length=1000;
int nr_of_complete_tabu_solutions = 0;
int max_antal_INcomplete_tabu_solutions_in_a_row_counter=0;
int number_of_stat_4_in_this_step = 0;
int number_of_stat_4_in_past_step = 0;
int hundra_raknare1=100;
int hundra_raknare2=1;
int tabu_algorithem_agen_number=0;

//FELIX versionshantering
int Tabu_save_number = 1; // sätter man denna till noll händer konstigheter
int Tabu_save_number_2 = 1;
int Tabu_save_number_3 = 1;
	

//xxxxxxxxxxxxxxxxxxxxxxxxxxx Functions xxxxxxxxxxxxxxxxxxxxxxxxxxx
//FREDRIK:
int tabu_calculateStates(int *path);
int tabu_getS4();
void tabu_printStates();
struct Node **NodeMatrix; // Node matrix

//FREDRIK och FELIX:
void tabu_getRandom(int *tabu_solution);

//FELIX:
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
	

 // i en liten fin matris med ettor och nollor
void print_K_matrix();
//void save_complete_tabu_solution_path();
int save_complete_tabu_solution_path();
void analys_tabu_solutions_and_update_Tabu_K_list(int *tabu_solution);

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  TABU ALGORITEM XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	  PREPARATIONS  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//Hunters_static
//Hunters

void preTabu(struct Node (*NodeMat)[SIZE], int *Hunters, int BREAK, int ROWS, int COLS) { // Do all pre-processing, which is to generate population.
	
	// xxxxxxxxxxxxxxxxxxxxx  SÄKERHETSÅTGÄRDER  xxxxxxxxxxxxxxxxxxxxx
	// variabel sättnig igen för säkerhetskull.	
	ROWS = ROWS;
	COLS = COLS;
	//tabu_solution[8500];
	//FELIX:
	//returned_Tabu_tabu_solution[8500];
	Mr_30=1;
	Mss_30=4;
	Mr_L=1; //vill ta bort Mr & Mss L men vi har dom med för säkerhetskull

	nr_of_tabus = 0;
	
	nr_of_complete_tabu_solutions = 0;
	max_antal_INcomplete_tabu_solutions_in_a_row_counter=0;
	number_of_stat_4_in_this_step = 0;
	number_of_stat_4_in_past_step = 0;
	hundra_raknare1=100;
	hundra_raknare2=1;
	tabu_algorithem_agen_number=0;
	
	


	//FELIX versionshantering
	Tabu_save_number = 1; // sätter man denna till noll händer konstigheter
	Tabu_save_number_2 = 1;
	Tabu_save_number_3 = 1;	
	
	/*
	printf("\n");
	printf("START preTabu\n");
	printf("\n");
	*/
	// xxxxxxxxxxxxxxxxxxxxx  SÄKERHET SLUT        xxxxxxxxxxxxxxxxxxxxx

	
	// "FÅ" PRINTS
	
	printf("ALL TABU PARAMETERS: \n");
	printf("max_step_minus_in_L_list \t\t\t\t%d\n", max_step_minus_in_L_list);
	printf("allowed_stat_4_loss \t\t\t\t\t%d\n", allowed_stat_4_loss);
	printf("max_antal_INcomplete_tabu_solutions \t\t\t%d\n", max_antal_INcomplete_tabu_solutions);
	printf("TABU_MAX_LIKA \t\t\t\t\t\t%d\n", TABU_MAX_LIKA);
	printf("MAX_TABU_STEPS\t\t\t\t\t\t%d\n", MAX_TABU_STEPS);
	printf("START_FROM_THE_BEGINING_AGEN_NUMBER\t\t\t%d\n", START_FROM_THE_BEGINING_AGEN_NUMBER);
	printf("to_easy_problem_problem_adjustment_set_nr_steps_to \t%d\n", to_easy_problem_problem_adjustment_set_nr_steps_to);
	printf("to_easy_problem_problem_adjustment_go_agen_nr \t\t%d\n", to_easy_problem_problem_adjustment_go_agen_nr);
	printf("Mss_L_fuck_up \t\t\t\t\t%d\n", Mss_L_fuck_up);
	
	printf("TABU_Pursuers \t\t\t\t\t\t%d\n", Hunters[0]);
	
	tabuMatris = malloc(ROWS * sizeof(int *));
	if(tabuMatris == NULL)
		fprintf(stderr, "tabuMatris out of memory\n");
	int i,j;
	for(i = 0; i < ROWS; i++)
	{
		tabuMatris[i] = malloc(COLS * sizeof(int));
		if(tabuMatris[i] == NULL)
			fprintf(stderr, "tabuMatris[i] out of memory\n");
	}
	tabu_solution = malloc(8500 * sizeof(int));
	memset(tabu_solution,0,sizeof(tabu_solution));
	returned_Tabu_tabu_solution = malloc(8500 * sizeof(int));
	memset(returned_Tabu_tabu_solution,0,sizeof(returned_Tabu_tabu_solution));
	/*** Allocate memory for NodeMatrix ***/
	NodeMatrix = malloc(ROWS * sizeof(struct Node *));
	if(NodeMatrix == NULL)
		fprintf(stderr, "NodeMatrix out of memory\n");
	for(i = 0; i < ROWS; i++)
	{
		NodeMatrix[i] = malloc(COLS * sizeof(struct Node));
		if(NodeMatrix[i] == NULL)
			fprintf(stderr, "NodeMatrix[i] out of memory\n");
	}
	for(i=0;i<ROWS;i++){
		for(j=0;j<COLS;j++){
			NodeMatrix[i][j] = NodeMat[i][j];
		}
	}
	
	// denna del sätter in ettor på varje platts det fins ett hinder i matrisen in i tabumatrisen
	// beövde denna tack och lov hade fredrik redan skivit den för eget bruk
	
	// testa för att bli av med stora tal
	int r,c;
	for(r = 0; r < ROWS; r++){
		for(c = 0; c < COLS; c++){ // For every node:
			tabuMatris[r][c]=0;
		}
	}
	for(r = 0; r < ROWS; r++){
		for(c = 0; c < COLS; c++){ // For every node:
			if(NodeMatrix[r][c].vision[0] == (struct Node *)0){ // Obstacle
				tabuMatris[r][c]=0;
			}
			else{
				tabuMatris[r][c]=1;
			}
		}
	}
	
	//Do actual pre-processing
	int pursuer,next=2;
	tabu_solution[0] = Hunters[0];
	//printf("Pursuers: %d\n", tabu_solution[0]);
	for(pursuer = 0; pursuer < Hunters[0]; pursuer++){
		tabu_solution[next] = Hunters[1+pursuer*2];
		tabu_solution[next+1] = Hunters[1+pursuer*2+1];
		//printf("(%d,%d)", tabu_solution[next],tabu_solution[next+1]);
		next = next+2;
	}
	/*
	printf("\n");
	printf("END preTabu\n");
	printf("\n");
	*/
}

// icke tabu from+1 om tabu from= from

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  TABU ALGORITEM XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX



void Tabu(int *tabuSolution) { // Main call function for Tabu Algorithm  annat namn Algorithm_Tabu_Search()
	
	printf( "START Tabu\n\n");
	
	int GOOO = 1;
	int STOOOP = 1;
	
	//START FUL FIX:  						//för om noll steget är en lösning:
	
	tabu_calculateStates(tabu_solution);
	if(tabu_getS4() == 0){
		//saves solution
		int q=2;
		int zz=0;
		for(q=2*(1+returned_Tabu_tabu_solution[0]);q<8500;q++){
			returned_Tabu_tabu_solution[q]=-1;
		}
		for(zz=0;zz<(2+2*tabu_solution[0]+2*tabu_solution[0]*tabu_solution[1]);zz++){
			returned_Tabu_tabu_solution[zz] = tabu_solution[zz];
		}
		//ignorerar algoritmen
		STOOOP = 0;
	
	}
	//END FUL FIX
	
	// ALGORITMEN:

	//while(tabu_solution[0]<steps){ // lite av en oändlig while loop
	
	
	while(GOOO==STOOOP){ // lite av en oändlig while loop
		
		if(tabu_solution[1]==hundra_raknare1){
			printf(" Antal steg tagna:  %d\n",hundra_raknare1 );
			hundra_raknare1+=100;
			if(tabu_solution[1]==MAX_TABU_STEPS){
				printf("tabu_solution[1]==MAX_TABU_STEPS\n");
				hundra_raknare2++;

				tabu_solution[1]=0;
				printf("steps1 %d\n",tabu_solution[1]);
				hundra_raknare1=100;
				//STOOOP=2;
				
				
				number_of_stat_4_in_this_step = 0;// VARFÖR VET JAG INTE
				number_of_stat_4_in_past_step = 0;// VARFÖR VET JAG INTE
				
				
				int q=2+2*tabu_solution[0];
				for(q=2+2*tabu_solution[0];q<8500;q++){
					tabu_solution[q]=-1;
				}
<<<<<<< HEAD
				tabu_solution[1]=0;
				printf("snabb?\n");
=======
				printf("Snabb 1?\n");
>>>>>>> 9212b72d62abf8b3e97fdd05bc91418edab2f73b
				if(hundra_raknare2==START_FROM_THE_BEGINING_AGEN_NUMBER){
					printf(" Recht MAX step 3 times, No solution Found\n");
					break;
				}
				printf("Snabb 2?\n");
			}
		}
		if(tabu_solution[1]==best_step_length){ // om lösnignen nått best_step_length så måste vi ju avbryta
			//självförstålig variabel för brytvilkor
			max_antal_INcomplete_tabu_solutions_in_a_row_counter++;
			if(max_antal_INcomplete_tabu_solutions==max_antal_INcomplete_tabu_solutions_in_a_row_counter){
				printf( "RECHT max INcomplete solutionsins\n");
				break;
			}
			tabu_solution[1]=0;
			int qq=2+2*tabu_solution[0];
			for(qq=2+2*tabu_solution[0];qq<8500;qq++){
				tabu_solution[qq]=-1;
			}
			//nollställer för tabut 30%
			number_of_stat_4_in_this_step = 0;
			number_of_stat_4_in_past_step = 0; 
		}
		//printf("Here 2 (%d, %d)\n", tabu_solution[0], tabu_solution[1]);
		tabu_getRandom(tabu_solution); 				// Generate a random step sequence from step 
		//printf("Here 3\n");
		tabu_calculateStates(tabu_solution);
		
		if(check_ALL_Tabu_lists(tabu_solution)==NOT_OK){
<<<<<<< HEAD
			printf("UUUUUUDDDDAAAAA %d\n",tabu_solution[1]);
			tabu_solution[1]-=1;
			printf("UUUUUUUDDDDDDDDDDAAAAAAA -1 %d\n",tabu_solution[1]);
			
			int hhh=0;
			for(hhh=0;hhh<2*(3+tabu_solution[0]+tabu_solution[1]*tabu_solution[0]);hhh+=2){
				// printar alla stegen 
				printf("(%d,%d)", tabu_solution[hhh], tabu_solution[hhh+1]);
			}
			printf("\n");
			print_K_matrix();
			printf("\n");
			tabu_printStates();
			printf("\n");
											if(tabu_solution[1]==MAX_TABU_STEPS){
											//printf("END\n");
											printf("steps2 %d\n",tabu_solution[1]);
											//STOOOP=2;
											}
=======
			//printf("Snabb 3?\n");
			tabu_solution[1]--;
>>>>>>> 9212b72d62abf8b3e97fdd05bc91418edab2f73b
		}
		//printf("\n");
		tabu_calculateStates(tabu_solution);
		if(tabu_getS4() == 0){
			 	//TA EJ BORT
			printf( "Nr_of_complete_tabu_solutions: %d\n",nr_of_complete_tabu_solutions);
			printf( "Using %d steps\n",tabu_solution[1]);
			int hh=0;
			for(hh=0;hh<2*(3+tabu_solution[0]+tabu_solution[1]*tabu_solution[0]);hh+=2){
				// printar alla stegen 
				printf("(%d,%d)", tabu_solution[hh], tabu_solution[hh+1]);
			}
			printf("\n");
			print_K_matrix();
			printf("\n");
			tabu_printStates();
			printf("\n");
			
			
			
			nr_of_complete_tabu_solutions++;
			
			//save_complete_tabu_solution_path(tabu_solution);
			if(save_complete_tabu_solution_path(tabu_solution)==OK){
				//printf("HALLLELLLUUULLLIIIIAAAAAAAA\n");
				break;
			}
			
			if(tabu_solution[1]==0 || tabu_solution[1]==1){ //nödvändig?
				//printf("Inga steg krävdes\n");
				tabu_solution[1]=0;
				int qqq=2+2*tabu_solution[0];
				for(qqq=2+2*tabu_solution[0];qqq<8500;qqq++){
					tabu_solution[qqq]=-1;
				}
				break;
			}
			
			tabu_solution[1]=0;
			int qqqq=2+2*tabu_solution[0];
			for(qqqq=2+2*tabu_solution[0];qqqq<8500;qqqq++){
				tabu_solution[qqqq]=-1;
			}
			//nollställer för tabut 30%
			number_of_stat_4_in_this_step = 0; 
			number_of_stat_4_in_past_step = 0;
			
		}
		if(tabu_solution[1]==MAX_TABU_STEPS){
		printf("END\n");
		printf("steps %d\n",tabu_solution[1]);
		//STOOOP=2;
		}	
	}
	
	/*
	printf("\n");
	printf( "Best complete tabu_solutions: (steps:%d) \n",returned_Tabu_tabu_solution[1]);
	int i;
	for(i=0;i<2*(1+returned_Tabu_tabu_solution[0]+returned_Tabu_tabu_solution[1]*returned_Tabu_tabu_solution[0]);i+=2){
		// printar alla stegen 
		printf("(%d,%d)", returned_Tabu_tabu_solution[i], returned_Tabu_tabu_solution[i+1]);
	}
	
	printf("\n");
	//returned_Tabu_tabu_solution[1]++;
	tabu_calculateStates(returned_Tabu_tabu_solution); // denna behövs faktiskt
	//printf("path length: %d\n", returned_Tabu_tabu_solution[1]);
	printf("\n\n");
	printf("State matrisen:\n");
	tabu_printStates(); // i from av en matris
	printf("Omraden kvar i States 4: %d\n", tabu_getS4());
	printf("\n\n");
	printf("Tabu State matrisen:\n");
	print_K_matrix(); // vilka rutor som har vilka värden, i from av en matris
	printf( "\n");
	printf( "antal tabu; %d\n", nr_of_tabus);
	printf( "\n");
	//printf("final i: %d\n", i);
	
	printf( "\n");
	
	*/
	int i;
	if(returned_Tabu_tabu_solution[1]<=200){
		for(i=0;i<2*(1+returned_Tabu_tabu_solution[0]+returned_Tabu_tabu_solution[1]*returned_Tabu_tabu_solution[0]);i++){
			tabuSolution[i] = returned_Tabu_tabu_solution[i];
		}
	}
	else{
		tabuSolution[0] = returned_Tabu_tabu_solution[0];
		tabuSolution[1] = -returned_Tabu_tabu_solution[1];
	}
	//printf( "END Tabu\n\n");
	for(i = 0; i < ROWS; i++){
		free(NodeMatrix[i]);
		free(tabuMatris[i]);
	}
	free(NodeMatrix);
	free(tabuMatris);
	free(tabu_solution);
	free(returned_Tabu_tabu_solution);
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

int check_ALL_Tabu_lists(int *tabu_solution){ // RETURN OK/NOT_OK

	//TABU 1
	if(check_K_Tabu_list_all_Hunters(tabu_solution)==OK){
		//printf("TABU1 OK\n");
		// TABU 2
		if (check_L_Tabu_list(tabu_solution)==OK){ // KOM PÅ VARFÖR DENN ALIGGER FÖRE L LIST??? 
			//printf("TABU2 OK\n");
			// TABU 3
				Mr_L=0;
			if(check_30_Tabu_list(tabu_solution)==OK){ // K list än så länge
				//printf("TABU3 OK\n");
				Mr_30=0;
				return OK;
			}
		}
	}
	//enbart för print
	nr_of_tabus++;
	return NOT_OK;
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   K START   
int check_K_Tabu_list_all_Hunters(int *tabu_solution){
	//check_K_Tabu_list(tabu_solution,i);
	int k;
	for(k=0;k<tabu_solution[0]; k++){
		if(check_K_Tabu_list_one_Hunter(tabu_solution,k)==NOT_OK){
			//printf("check_K_Tabu_list_all_Hunters NOT_OK\n");
			return NOT_OK;
		}
	}
	//printf("check_K_Tabu_list_all_Hunters OK\n");
	return OK;
}


int check_K_Tabu_list_one_Hunter(int *tabu_solution, int k){
	int rad = tabu_solution[    2+(2*tabu_solution[0]*tabu_solution[1]) +(2*k)]; 		// raden vi är på nu
	int kol = tabu_solution[1 + 2+(2*tabu_solution[0]*tabu_solution[1]) +(2*k)];	// colonen vi är på nu
	if(tabuMatris[rad][kol] == 0){
		
		//printf(" check_K_Tabu_list_one_Hunter NOT_OK: Tabu! (%d,%d) = %d \n", rad, kol, varde);
		return NOT_OK;
	}
	//printf("check_K_Tabu_list_one_Hunter OK\n");
	return OK;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   K END  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   30 START   
int check_30_Tabu_list(int *tabu_solution){

	return OK;
	// denna funktion skapar en hel del problem för hela algoritmen...
	// den fryser ibland om saker blir fel pga denna.

	// denna funktion kollar om steget som tas inte gör att vi förlorar mer 
	//än ett visst antal områden
	number_of_stat_4_in_this_step = tabu_getS4();	
	if(tabu_solution[1]<2){ // 0 or 1
		number_of_stat_4_in_past_step = tabu_getS4();
		return OK;
	}
	if(number_of_stat_4_in_this_step - allowed_stat_4_loss <= number_of_stat_4_in_past_step ){ //be om hjälp
		number_of_stat_4_in_past_step = tabu_getS4();
		//printf("30 OK\n ");
		return OK;
	}
	number_of_stat_4_in_past_step = tabu_getS4();
	// detta finns med för att ibland fasnar algoritmen
	Mr_30++;
	if(Mr_30==Mss_30){
		//printf("TTTTTTTTTTTTTTTTTTTTTAAAAAAAAAAAAABBBBBBBBBBUUUUUUUUUUUUUUUU Mr_30\n");
		Mr_30=0;
		return OK;
	}
	//return OK;
	return NOT_OK;
	
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   30 END   XXXXXXXXXXXXXXXXXXXXXXXXXXXXX



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   L START   (och aspirationsvilkoret)


int check_L_Tabu_list(int *tabu_solution){
	int kk;
	for(kk=0;kk<tabu_solution[0]; kk++){ // Steps through all pursuers
		//printf("check_L_Tabu_list START och k: %d\n",k);
		if(check_L_Tabu_list_X_past_steps(tabu_solution,kk)==NOT_OK){
			// aspriations vilkoret: det nedan förebygger låsning av programet.
			//check up
			if(tabu_up(tabu_solution,kk)==OK){ // sätt minustäcknet (i-1) i tabu_up  // vi har här en possition i tabu_solution som behöver bli satt till den åvanför  // dvs i funktionen nedan plusar vi på 1 upp och gör gemförelsen
				if(check_K_Tabu_list_one_Hunter_step_up(tabu_solution,kk)==OK){ // dom ligger i denna ordning pga att K listan är mer dominant samt underlättade skrivandet av tabu_up
					if(check_L_Tabu_list_X_past_steps_up(tabu_solution,kk)==OK){
						Mr_L++;
						if(Mr_L==Mss_L_fuck_up){
							printf("Mr_L up\n");
							Mr_L=0;
							return OK;
						}
						return NOT_OK;
					}
				}
			}
			//check right
			if(tabu_right(tabu_solution,kk)==OK){ // sätt minustäcknet (i-1) i tabu_up  // vi har här en possition i tabu_solution som behöver bli satt till den åvanför  // dvs i funktionen nedan plusar vi på 1 upp och gör gemförelsen
				if(check_K_Tabu_list_one_Hunter_step_right(tabu_solution,kk)==OK){
					if(check_L_Tabu_list_X_past_steps_right(tabu_solution,kk)==OK){
						Mr_L++;
						if(Mr_L==Mss_L_fuck_up){
							printf("Mr_L right\n");
							Mr_L=0;
							return OK;
						}
						return NOT_OK;
					}
				}
			}
			// check down
			if(tabu_down(tabu_solution,kk)==OK){ // sätt minustäcknet (i-1) i tabu_up  // vi har här en possition i tabu_solution som behöver bli satt till den åvanför  // dvs i funktionen nedan plusar vi på 1 upp och gör gemförelsen
				if(check_K_Tabu_list_one_Hunter_step_down(tabu_solution,kk)==OK){
					if(check_L_Tabu_list_X_past_steps_down(tabu_solution,kk)==OK){
						Mr_L++;
						if(Mr_L==Mss_L_fuck_up){
							printf("Mr_L down\n");
							Mr_L=0;
							return OK;
						}
						return NOT_OK;
					}
				}
			}
			//check left
			if(tabu_left(tabu_solution,kk)==OK){ // sätt minustäcknet (i-1) i tabu_up  // vi har här en possition i tabu_solution som behöver bli satt till den åvanför  // dvs i funktionen nedan plusar vi på 1 upp och gör gemförelsen
				if(check_K_Tabu_list_one_Hunter_step_left(tabu_solution,kk)==OK){
					if(check_L_Tabu_list_X_past_steps_left(tabu_solution,kk)==OK){
						Mr_L++;
						if(Mr_L==Mss_L_fuck_up){
							printf("Mr_L left\n");
							Mr_L=0;
							return OK;
						}
						return NOT_OK;
					}
				}
			}
			//break // vill att den skall gå till nästa jagare
		}
	}
	return OK;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



int tabu_up(int *tabu_solution, int kk){
	// vi ska ha positionen innan den vi är i. och se om den är okey innom matrisen
	int s = tabu_solution[1]-1;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk] -1; 	// raden vi är på i förra steget
	//int kol = tabu_solution[1 + 2+2*tabu_solution[0]+b*(2*tabu_solution[0])+2*k];	// colonen vi är på i förra steget
	if(rad==-1){
		//printf("tabu_up NOT_OK\n");
		return NOT_OK;
	}
	//printf("tabu_up OK\n");
	return OK;
}

int tabu_left(int *tabu_solution, int kk){
	// vi ska ha positionen innan den vi är i. och se om den är okey innom matrisen
	int s = tabu_solution[1]-1;
	//int rad = tabu_solution[    2+2*tabu_solution[0]+b*(2*tabu_solution[0])+2*k]; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk] -1;	// colonen vi är på i förra steget
	
	if(kol==-1){
		//printf("tabu_left NOT_OK\n");
		return NOT_OK;
	}
	//printf("tabu_left OK\n");
	return OK;
}

int tabu_right(int *tabu_solution, int kk){
	// vi ska ha positionen innan den vi är i. och se om den är okey innom matrisen
	int s = tabu_solution[1]-1;
	//int rad = tabu_solution[    2+2*tabu_solution[0]+b*(2*tabu_solution[0])+2*k]; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk] +1;	// colonen vi är på i förra steget
	
	if(kol==COLS){
		//printf("tabu_right NOT_OK\n");
		return NOT_OK;
	}
	//printf("tabu_right OK\n");
	return OK;
}

int tabu_down(int *tabu_solution, int kk){
	// vi ska ha positionen innan den vi är i. och se om den är okey innom matrisen
	int s = tabu_solution[1]-1;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk] +1; 	// raden vi är på i förra steget
	if(rad==ROWS){
		//printf("tabu_down NOT_OK\n");
		return NOT_OK;
	}
	//printf("tabu_down OK\n");
	return OK;
}


int check_K_Tabu_list_one_Hunter_step_up(int *tabu_solution, int kk){
	// backa ett steg sen gå up ett steg och sen kolla om denna tabu mot K listan 
	int s = tabu_solution[1]-1;
	int number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk] -1; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk];	// colonen vi är på i förra steget
	if(tabuMatris[rad][kol] == 0){
		//printf(" check_K_Tabu_list_one_Hunter_step_up NOT    L list upp Tabu! (%d,%d) = %d \n", rad, kol, varde);
		return NOT_OK;
	}
	//printf("check_K_Tabu_list_one_Hunter_step_up OK\n");
	return OK;

}

int check_K_Tabu_list_one_Hunter_step_right(int *tabu_solution, int kk){
	// backa ett steg sen gå right ett steg och sen kolla om denna tabu mot K listan 
	int s = tabu_solution[1]-1;
	int number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk]; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk] +1;	// colonen vi är på i förra steget
	if(tabuMatris[rad][kol] == 0){
		//printf("check_K_Tabu_list_one_Hunter_step_right NOT_OK    L list right Tabu! (%d,%d) = %d \n", rad, kol, varde);
		return NOT_OK;
	}
	//printf("check_K_Tabu_list_one_Hunter_step_right OK\n");
	return OK;

}

int check_K_Tabu_list_one_Hunter_step_down(int *tabu_solution, int kk){
	// backa ett steg sen gå down ett steg och sen kolla om denna tabu mot K listan 
	int s = tabu_solution[1]-1;
	int number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk] +1; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk];	// colonen vi är på i förra steget
	if(tabuMatris[rad][kol] == 0){
		//printf("check_K_Tabu_list_one_Hunter_step_down NOT_OK    L list right Tabu! (%d,%d) = %d \n", rad, kol, varde);
		return NOT_OK;
			
	}
	//printf("check_K_Tabu_list_one_Hunter_step_down OK\n");
	return OK;

}

int check_K_Tabu_list_one_Hunter_step_left(int *tabu_solution, int kk){
	// backa ett steg sen gå left ett steg och sen kolla om denna tabu mot K listan 
	
	int s = tabu_solution[1]-1;
	int number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk]; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk] -1;	// colonen vi är på i förra steget
	if(tabuMatris[rad][kol] == 0){
		//printf("check_K_Tabu_list_one_Hunter_step_left NOT_OK    L list right Tabu! (%d,%d) = %d \n", rad, kol, varde);
		return NOT_OK;
	}
	//printf("check_K_Tabu_list_one_Hunter_step_left OK\n");
	return OK;

}



int check_L_Tabu_list_X_past_steps(int *tabu_solution, int kk){
	// denna ska bara kolla om de 4 gamla stegen är tabu för varje jagare.
	int s=tabu_solution[1],number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk]; 	// raden vi är på nu
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk];	// colonen vi är på nu
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s=s-1;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		int rad_minus = tabu_solution[    2+(s)*(2*tabu_solution[0])+2*kk]; 	// raden s steg bakot från där vi är nu
		int kol_minus = tabu_solution[1 + 2+(s)*(2*tabu_solution[0])+2*kk];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			//printf("check_L_Tabu_list_X_past_steps NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	//printf("check_L_Tabu_list_X_past_steps OK\n");
	return OK;
}


int check_L_Tabu_list_X_past_steps_up(int *tabu_solution, int kk){
	// backa ett steg sen gå up ett steg och sen kolla om denna tabu mot L listan
	int s=tabu_solution[1]-1;
	int number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk] -1; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk];	// colonen vi är på i förra steget
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		
		int rad_minus = tabu_solution[    2+(s)*(2*tabu_solution[0])+2*kk]; 	// raden s steg bakot från där vi är nu
		int kol_minus = tabu_solution[1 + 2+(s)*(2*tabu_solution[0])+2*kk];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			//printf("check_L_Tabu_list_X_past_steps_up NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	//printf("check_L_Tabu_list_X_past_steps_up OK\n");
	return OK;
}

int check_L_Tabu_list_X_past_steps_right(int *tabu_solution, int kk){
	// backa ett steg sen gå right ett steg och sen kolla om denna tabu mot L listan
	int s=tabu_solution[1]-1;
	int number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk]; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk] +1;	// colonen vi är på i förra steget
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		
		int rad_minus = tabu_solution[    2+(s)*(2*tabu_solution[0])+2*kk]; 	// raden s steg bakot från där vi är nu
		int kol_minus = tabu_solution[1 + 2+(s)*(2*tabu_solution[0])+2*kk];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			//printf("check_L_Tabu_list_X_past_steps_right NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	//printf("check_L_Tabu_list_X_past_steps_right OK\n");
	return OK;

}
	
int check_L_Tabu_list_X_past_steps_down(int *tabu_solution, int kk){
	// backa ett steg sen gå down ett steg och sen kolla om denna tabu mot L listan
	int s = tabu_solution[1]-1;
	int number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk] +1; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk];	// colonen vi är på i förra steget
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		
		int rad_minus = tabu_solution[    2+(s)*(2*tabu_solution[0])+2*kk]; 	// raden s steg bakot från där vi är nu
		int kol_minus = tabu_solution[1 + 2+(s)*(2*tabu_solution[0])+2*kk];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			//printf("check_L_Tabu_list_X_past_steps_down NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	//printf("check_L_Tabu_list_X_past_steps_down OK\n");
	return OK;

}
	
int check_L_Tabu_list_X_past_steps_left(int *tabu_solution, int kk){ // i = steg nr, k = jagare nr
	// backa ett steg sen gå left ett steg och sen kolla om denna tabu mot L listan
	int s = tabu_solution[1]-1;
	int number_of_steps_backward=0;
	int rad = tabu_solution[    2+s*(2*tabu_solution[0])+2*kk]; 	// raden vi är på i förra steget
	int kol = tabu_solution[1 + 2+s*(2*tabu_solution[0])+2*kk]  -1;	// colonen vi är på i förra steget
	
	//kollar "i" antla steg bakot men inte mer än 4
	for(s;s>0;s--){
		if(number_of_steps_backward > max_step_minus_in_L_list){
			break;
		}
		int rad_minus = tabu_solution[    2+(s)*(2*tabu_solution[0])+2*kk]; 	// raden s steg bakot från där vi är nu
		int kol_minus = tabu_solution[1 + 2+(s)*(2*tabu_solution[0])+2*kk];	// colonen  s steg bakot från där vi är nu
		
		if(rad==rad_minus && kol==kol_minus){
			//printf("check_L_Tabu_list_X_past_steps_left NOT_OK\n");
			return NOT_OK;
		}
		number_of_steps_backward++;
	}
	return OK;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX   L END   XXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void print_K_matrix(){
	// skriver ut hur K_Tabu_list matrisen ser ut
	int r,c;
	for(r = 0; r < ROWS; r++){
		for(c = 0; c < COLS; c++){ // For every node:
			printf("%d ", tabuMatris[r][c]);
		}
		printf("\n");
	}
}

int save_complete_tabu_solution_path(int *tabu_solution){ //verion 2.0 samt 1.0
	int z;
	if(best_step_length == tabu_solution[1]){
		Tabu_save_number_3++;
		if(Tabu_save_number_3==TABU_MAX_LIKA){
			printf("TABU_MAX_LIKA BRYT VILKORET\n");
			int q=2;
			for(q=2*(1+returned_Tabu_tabu_solution[0]);q<8500;q++){
				returned_Tabu_tabu_solution[q]=-1;
			}
			//tabu_solution[1]++;
			for(z=0;z<2*(1+tabu_solution[0]+tabu_solution[0]*tabu_solution[1]);z++){
				returned_Tabu_tabu_solution[z] = tabu_solution[z];
			}
			//nytt tänk för att få bort dåliga lösnigar på lätta områden
			//vad ska ända här?: 
			//svar:om lösningen är kortare än 4 kör algoritmen igen
			if(tabu_solution[1]<=to_easy_problem_problem_adjustment_set_nr_steps_to){
				
				/*
				int to_easy_problem_problem_adjustment_set_nr_steps_to=5;
				int to_easy_problem_problem_adjustment_go_agen_nr=1; // om 2 körs den två gånger
				int tabu_algorithem_agen_number=0;
				*/
				
				tabu_algorithem_agen_number++;
				if(tabu_algorithem_agen_number<=to_easy_problem_problem_adjustment_go_agen_nr){
				

					// räkanre
					// nollställa matrisen //sätter alla till noll.
					//skriva in hinder till
					
					int r,c;
					for(r = 0; r < ROWS; r++){
						for(c = 0; c < COLS; c++){ // For every node:
							tabuMatris[r][c]=0;
						}
					}
					for(r = 0; r < ROWS; r++){
						for(c = 0; c < COLS; c++){ // For every node:
							if(NodeMatrix[r][c].vision[0] == (struct Node *)0){ // Obstacle
								tabuMatris[r][c]=0;
							}
							else{
								tabuMatris[r][c]=1;
							}
						}
					}				
					
					return NOT_OK;

	
				}
			}
			
			
			//nytt tänk för att få bort dåliga lösnigar på lätta områden
			return OK;
		}
	}
	else if(tabu_solution[1] < best_step_length){
		max_antal_INcomplete_tabu_solutions_in_a_row_counter=0; 
		best_step_length = tabu_solution[1];
		Tabu_save_number_3=0;
		
		int q=2;
		for(q=2*(1+returned_Tabu_tabu_solution[0]);q<8500;q++){
			returned_Tabu_tabu_solution[q]=-1;
		}
		for(z=0;z<(2+2*tabu_solution[0]+2*tabu_solution[0]*tabu_solution[1]);z++){
			returned_Tabu_tabu_solution[z] = tabu_solution[z];
		}
		analys_tabu_solutions_and_update_Tabu_K_list(tabu_solution);
	}
	else if(tabu_solution[1] > best_step_length){
		//Tabu_save_number_3=0;
	}
	
	return NOT_OK;
}

void analys_tabu_solutions_and_update_Tabu_K_list(int *tabu_solution){ //verion 2.0 samt 1.0
	//verson 2.0		ta bort komentarsmarkeringen längre ned så får du furra versionen
	// denna sker först när gemförelserna drar igång
	// sätter allt till noll??
	
	int r,c;
	int ee;
	int rr;
	int cc;
	/*
	printf("l0sningstegen till tabuMatris under\n");
	int www;
	for(www=0;www<2*(1+tabu_solution[0]+tabu_solution[1]*tabu_solution[0]);www+=2){
		// printar alla stegen 
		printf("(%d,%d)", tabu_solution[www], tabu_solution[www+1]);
		
	}
	printf("\n");
	*/
	
	for(r = 0; r < ROWS; r++){
		for(c = 0; c < COLS; c++){ // For every node:
				tabuMatris[r][c]=0;
		}
	}
	
	
	/*
			for(i=0;i<2*(1+2+tabu_solution[0]+tabu_solution[1]*tabu_solution[0]);i+=2){
			// printar alla stegen 
			printf("(%d,%d)", tabu_solution[i], tabu_solution[i+1]);
			}
	*/
	//2+2*tabu_solution[0]+
	for(ee=2; ee<2*(1+tabu_solution[0]+tabu_solution[1]*tabu_solution[0]);ee+=2){
		rr = tabu_solution[   ee]; 		// raden vi är på nu
		cc = tabu_solution[1 +ee];	// colonen vi är på nu
		tabuMatris[rr][cc]=1;	
	}
	/*
	printf("tabuMatrix 1\n");
	print_K_matrix();
	*/
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   FREDRIK    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   BÅBERG    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


void tabu_getRandom(int *tabu_solution){ // AV  fredrik och felix  // Generate random step-sequence from a given node
	int pursuer,stepnr=2*(1+tabu_solution[1]*tabu_solution[0]), nextStep;
	struct Node *current;
	for(pursuer=0;pursuer<tabu_solution[0];pursuer++){
		 current = &NodeMatrix[tabu_solution[stepnr]][tabu_solution[stepnr+1]];
		while(1==1){
			nextStep = ((int)((double)rand() / ((double)RAND_MAX + 1)*4));
			if(((*current).move[nextStep]) != 0)
				break;
		}
		tabu_solution[stepnr+2*tabu_solution[0]] = (*(current)->move[nextStep]).name[0];
		tabu_solution[stepnr+2*tabu_solution[0]+1] = (*(current)->move[nextStep]).name[1];
		stepnr = stepnr+2;
	}
	tabu_solution[1]++;
}

void tabu_printStates(){
	//printf("tabu_printStates\n");
	int r,c;
	for(r = 0; r < ROWS; r++){
		for(c = 0; c < COLS; c++){ // For every node:
			printf("%d ", NodeMatrix[r][c].state);
		}
		printf("\n");
	}
}

int tabu_getS4(){
	//printf("tabu_getS4\n");
	int S4=0,r,c;
	for(r = 0; r < ROWS; r++){
		for(c = 0; c < COLS; c++){ // For every node:
			if(NodeMatrix[r][c].state == 4){
				S4++;
			}
		}
	}
	return S4;
}

int tabu_calculateStates(int *path){ 	// version 2.0
	int currentStep=0,pursuer=0,r=0,c=0, nrS4=0;
	int S[ROWS][COLS], S_u[ROWS][COLS]; // Table of current and updated states
	memset(&S, 0, sizeof(S));
	memset(&S_u, 0, sizeof(S));
	for(r = 0; r < ROWS; r++){
		for(c = 0; c < COLS; c++){ // For every node:
			if(NodeMatrix[r][c].vision[0] != (struct Node *)0){ // Not obstacle
				S[r][c]=4;
				S_u[r][c]=4;
			}
		}
	}
	for(currentStep = 0; currentStep <= path[1];currentStep++){ // Go through every step, should terminate if no Node is in state 4.
		nrS4=0;
		for(pursuer=0;pursuer < path[0]; pursuer++){ // For each pursuer
			int r = path[2*(1+pursuer+path[0]*currentStep)];
			int c = path[2*(1+pursuer+path[0]*currentStep)+1];
			S[r][c] = 1; // Set state for S to 1 for each pursuer
			int k=0;
			while((NodeMatrix[r][c].vision[k]) != (struct Node *)0){ // Set state for S to 2 for each visible node not containing a pursuer
				int S_r = (*NodeMatrix[r][c].vision[k]).name[0];
				int S_c = (*NodeMatrix[r][c].vision[k]).name[1];
				if(S[S_r][S_c] != 1) // If not containing a pursuer
					S[S_r][S_c] = 2;
				k++;
			}
		} // All pursuers step currentStep has been placed in S
		int needUpdate = 1;
		while(needUpdate == 1){
			for(r = 0; r < ROWS; r++){
				for(c = 0; c < COLS; c++){ // For every node:
					if(S_u[r][c] != 0)
						S_u[r][c] = 4; // Set state 4 as default
					// Do nothing for obstacles
				}
			}
			for(pursuer=0;pursuer < path[0]; pursuer++){ // For each pursuer
				S_u[path[2*(1+pursuer+path[0]*currentStep)]][path[2*(1+pursuer+path[0]*currentStep)+1]] = 1; // Set state for S_u to 1 if it contains a pursuer
				int k=0;
				while((NodeMatrix[path[2*(1+pursuer+path[0]*currentStep)]][path[2*(1+pursuer+path[0]*currentStep)+1]].vision[k]) != 0){ // Set state for S_u to 2 if it is visible and doesn't contain a pursuer
					int S_r = (*NodeMatrix[path[2*(1+pursuer+path[0]*currentStep)]][path[2*(1+pursuer+path[0]*currentStep)+1]].vision[k]).name[0];
					int S_c = (*NodeMatrix[path[2*(1+pursuer+path[0]*currentStep)]][path[2*(1+pursuer+path[0]*currentStep)+1]].vision[k]).name[1];
					if(S_u[S_r][S_c] != 1) // If not containing a pursuer
						S_u[S_r][S_c] = 2;
					k++;
				}
			}
			for(r = 0; r < ROWS; r++){
				for(c = 0; c < COLS; c++){ // For every node:
					if(S_u[r][c]!=4){} // State has been updated in S_u
					else if(S[r][c]==1 && S_u[r][c]!=1){} // Did contain pursuer but currently does not.
					else if(S[r][c]==4){}
					else{
						int check = 1, direction;
						for(direction=0;direction<4;direction++){ // Go left,right,up,down
							if(NodeMatrix[r][c].move[direction] != (struct Node *)0){ // If it is possible to move
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
			for(r = 0; r < ROWS; r++){ /*** Check if update is needed ***/
				for(c = 0; c < COLS; c++){ // For every node:
					if(S[r][c] != S_u[r][c])
						needUpdate=1;
				}
			}
			for(r = 0; r < ROWS; r++){ /*** Set S to S_u before new iteration ***/
				for(c = 0; c < COLS; c++) // For every node:
					S[r][c] = S_u[r][c];
			}
		}
		for(r = 0; r < ROWS; r++){
			for(c = 0; c < COLS; c++){ // For every node:
				if(S[r][c]==4)
					nrS4++;
			}
		}
		if(nrS4==0){
			//tabu_solution found, stop taking steps
			break;
		}
	}
	if(nrS4>0)
		currentStep = (0-currentStep);
	for(r = 0; r < ROWS; r++){ // tabu_solution found or all steps used, write to nodeMatrix
		for(c = 0; c < COLS; c++){
			NodeMatrix[r][c].state = S[r][c];
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
