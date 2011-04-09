/*	Function call-order:
	preGenetic()
		generatePopulation()
			getRandom()
	genAlg()
		calculateFitness()
		sortPopulation()
		addToNewPopulation(Population[0], Population[1])
		while(New_Population < MAX_POPULATION):
			doCrossover()
				doSelect()
				doMutation()
				calculateFitness()
				sortTempPop()
			addToNewPopulation()
		doDecode()
						*/
#include <string.h>
#include "Header.h"

/*** Definitions ***/
#define MAX_GEN 20 // Maximum number of generations
#define POPULATION_SIZE 1 // Population size, static.
#define MAX_GENETIC_PURSUERS 10 // Maximum number of GENETIC_PURSUERS, just to allocate enough memory
#define MAX_STEPS 1 // Maximum number of steps, just to allocate enough memory

/*** Pre-declarations ***/
struct Gene;
struct Chromosome;

/*** Variables ***/
int GENETIC_PURSUERS = 0; // Only a temporary value.
int GENERATIONS = 0; // Only a temporary value.
int GENETIC_ROWS = 0;
int GENETIC_COLS = 0;

struct Gene{ // Gene contains two parts, start[] which is starting position and allele[] which is direction of every step, 0=stay,1=left,2=right,3=up,4=down.
	int start[2];
	int allele[MAX_STEPS];
};
struct Chromosome{
	int fitnessValue[2]; // [0] = number of contaminated, [1] = required steps until no contamination.
	struct Gene gene[MAX_GENETIC_PURSUERS]; // One gene for each pursuer
};
struct Chromosome Population[POPULATION_SIZE];
struct Chromosome New_Population[POPULATION_SIZE];

/*** Functions ***/
void generatePopulation();
void preGenetic(struct Node (*NodeMat)[SIZE], int *Hunters, int BREAK);
void getRandom(struct Gene *g);
void calculateFitness(struct Chromosome *chrom);
void sortPopulation(struct Chromosome *pop, int popSize);
void addToNewPopulation(struct Chromosome chrom);
void doCrossover();
void doMutation(struct Chromosome *chrom);
void doDecode(struct Chromosome *chrom, int *returnPath, int stratLen);
void printBest(int popNr);
void printFitness(void);
void doReproduce(void);
void swapPopulations(void);
void calculateStates(struct Chromosome *chrom);

struct Node **NodeMatrix;
typedef int (*compfn)(const void*, const void*);
int compare(struct Chromosome *, struct Chromosome *);
int NewPopLocation = 0;

/*** Preparations ***/
void preGenetic(struct Node (*NodeMat)[SIZE], int *Hunters, int BREAK) { // Do all pre-processing, which is to generate population.
	//printf("Pre-processing.\n");
	GENERATIONS = BREAK;
	GENETIC_PURSUERS = Hunters[0];
	int i,j;

	/*** Allocate memory for NodeMatrix ***/
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
			
			/*** Check number of rows and columns of B. */
			if(NodeMatrix[i][j].vision[0] != 0){
				if(NodeMatrix[i][j].name[0]+1 > GENETIC_ROWS){
					GENETIC_ROWS = 1+NodeMatrix[i][j].name[0];
				}
				if(NodeMatrix[i][j].name[1]+1 > GENETIC_COLS){
					GENETIC_COLS = 1+NodeMatrix[i][j].name[1];
				}
			}
		}
	}
	/*** Do actual pre-processing ***/
	int k;
	for(i = 0; i < POPULATION_SIZE; i++){ // Set starting positions for every gene in the population.
		for(j = 0; j < GENETIC_PURSUERS; j++){
			for(k = 0; k < 2; k++){
				Population[i].gene[j].start[k] = Hunters[1+j*2+k];
			}
		}
	}
	generatePopulation();
}
void generatePopulation() {
	//printf("\tGenerate population\n");
	int ChromNr, GeneNr;
	for(ChromNr = 0; ChromNr < POPULATION_SIZE; ChromNr++){ // For each Chromosome
		for(GeneNr = 0; GeneNr < GENETIC_PURSUERS; GeneNr++){ // For each Gene
			getRandom(&(Population[ChromNr].gene[GeneNr])); // Generate a random step sequence
		}
	}
}
void getRandom(struct Gene *g){ // Generate random step-sequence from a given node
	//printf("\t\tGenerate random step-sequence\n");
	int stepnr=1, nextStep;
	struct Node *current = &NodeMatrix[(*g).start[0]][(*g).start[1]];
	for(stepnr = 0; stepnr < MAX_STEPS; stepnr++){
		while(1==1){
			nextStep = ((int)((double)rand() / ((double)RAND_MAX + 1)*5));
			if(nextStep == 4){
				break;
			}
			if((*current).move[nextStep] != 0){
				break;
			}
		}
		(*g).allele[stepnr] = nextStep;
		if(nextStep != 4){
			current = (*current).move[nextStep];
		}
	}
}

/*** Algorithm ***/
void genAlg() { // Main call function for Genetic Algorithm
	printf("The genetic library\n");
	int currentGeneration, currentChromosome;
	for(currentGeneration = 0; currentGeneration < GENERATIONS; currentGeneration++){
		printf("***** Generation %d *****\n", currentGeneration+1);
		for(currentChromosome = 0; currentChromosome < POPULATION_SIZE; currentChromosome++){ // Calculate fitness for every strategy.
			calculateFitness(&Population[currentChromosome]);
		}
		sortPopulation(Population, POPULATION_SIZE); // Sort the population after fitness
		//printFitness();
		int NewPopSize = 2;
		addToNewPopulation(Population[0]);
		if(POPULATION_SIZE>2){
			addToNewPopulation(Population[1]);
		}
		else{
			NewPopSize = 1;
		}
		while(NewPopSize < POPULATION_SIZE){
			//printf("Location: %d\nPopulation size: %d\n", NewPopLocation, POPULATION_SIZE);
			//printf("%d Reproduce:\n", NewPopSize);
			doReproduce();
			NewPopSize+=2;
			//printf("%d End Reproduce\n", NewPopSize);
		}
		//printf("Location: %d\nPopulation size: %d\n", NewPopLocation, POPULATION_SIZE);
		//printf("Hej2\n");
		
		//printf("Swap populations\n");
		swapPopulations();
		NewPopSize = 2;
		NewPopLocation = 0;
		//printf("Start over\n");
	}
	//printf("Sort population after final generation\n");
	sortPopulation(Population, POPULATION_SIZE); // Sort the population after fitness
	//doDecode(&Population[0]); //Decode best strategy to correct output, node index instead of directions
	/*** Free memory for NodeMatrix ***/
	int i;
	for(i = 0; i < SIZE; i++){
		free(NodeMatrix[i]);
	}
	free(NodeMatrix);
	printf("End of Genetic Algorithm.\n");
}
void calculateFitness(struct Chromosome *chrom){
	//printf("\tCalculate fitness\n");
	int fitness[] = {0,0};
	fitness[0] = 0;
	fitness[1] = ((int)((double)rand() / ((double)RAND_MAX + 1)*100));
	(*chrom).fitnessValue[0] = fitness[0];
	(*chrom).fitnessValue[1] = fitness[1];
	calculateStates(chrom);
}
void sortPopulation(struct Chromosome *pop, int popSize){
	//printf("\tSort population (of size %d)\n", popSize);
	qsort((void *) pop, popSize, sizeof(struct Chromosome), (compfn)compare );
}
void addToNewPopulation(struct Chromosome chrom){
	//printf("\tAdd to new population\n");
	if(NewPopLocation >= POPULATION_SIZE){
		printf("Population full\n");
		return;
	}
	New_Population[NewPopLocation] = chrom;
	NewPopLocation++;
}
void doReproduce(){
	//printf("Reproduce!\n");
	struct Chromosome XoverPop[4];
	XoverPop[0] = Population[doSelect()];
	XoverPop[1] = Population[doSelect()];
	doCrossover(&XoverPop);
	doMutation(XoverPop);
	sortPopulation(XoverPop, 4);
	//printf("Add best to new population.\n");
	addToNewPopulation(XoverPop[0]);
	if(POPULATION_SIZE>3 && NewPopLocation < POPULATION_SIZE){
		//printf("Add second best to new population.\n");
		addToNewPopulation(XoverPop[1]);
	}else{
		NewPopLocation++;
		//printf("Only added one from reproduction\n");
	}
}
void doCrossover(struct Chromosome *parentPop){ // Will work with Population.
	//printf("\tDo crossover\n");
	// Create offspring 1,2 from parents in [0], [1], place in [2], [3]
	int GeneNr;
	for(GeneNr = 0; GeneNr < GENETIC_PURSUERS; GeneNr++){
		parentPop[2].gene[GeneNr  ] = parentPop[0].gene[GeneNr];
		parentPop[2].gene[GeneNr+1] = parentPop[1].gene[GeneNr];
		parentPop[3].gene[GeneNr  ] = parentPop[1].gene[GeneNr];
		parentPop[3].gene[GeneNr+1] = parentPop[0].gene[GeneNr];
		GeneNr++;
	}
}
int doSelect(){ // Return position in Population for the chromosome that was selected.
	//printf("Do random selection\n");
	return ((int)((double)rand() / ((double)RAND_MAX + 1)*POPULATION_SIZE));
}
void doMutation(struct Chromosome *chrom){ // Mutate Chromosome
	//printf("\t\tDo Mutation\n");
	int i;
	for(i = 0; i < 2; i++){
		int mutationProp = 5; // probability of mutation*100
		int randomValue = ((int)((double)rand() / ((double)RAND_MAX + 1)*100)); // Random number between 0 and 999
		int randomGene = ((int)((double)rand() / ((double)RAND_MAX + 1)*MAX_GENETIC_PURSUERS)); // Random number between 0 and 999
		if(randomValue < mutationProp){
			//printf("Mutation!\n");
			//getRandom(&((*chrom).gene[randomGene])); // Generate a new random path for a random gene.
		}
	}
}
void doDecode(struct Chromosome *chrom, int *returnPath, int stratLen){ // Decode the best chromosome and return it
	//printf("Decode best chromosome\n");
	/*
	 * int i,j,k,strategy[stratLen];
	strategy[0] = GENETIC_PURSUERS;
	for(i = 1; i < 2*GENETIC_PURSUERS; i++){
		for(j = 0; j < 2; j++){
			strategy[i+j] = Population[0].gene[i].start[j];
		}
		i++;
	}
	for(i = 3; i < stratLen;i){ // Start att strategy[3] for steps, increments at end of loop.
		for(k=0;k<GENETIC_PURSUERS; k++){ // For each pursuer
			strategy[i+k] = Population[0].gene[i].allele[k];
		}
		i+=GENETIC_PURSUERS; // step to next pursuer location.
	}
	* */
}
void printBest(int popNr){ // Print the best solution
	printf("Print best in population:\n");
	int i=0,j=0,k=0;
	for(j=0;j<GENETIC_PURSUERS; j++){ // For each pursuer
		printf("Gene %d:\t", j);
		printf("(%d,%d): ", Population[popNr].gene[j].start[0], Population[popNr].gene[j].start[1]);
		for(k=0;k<MAX_STEPS;k++){ // Print step sequence
			printf("%d ", Population[popNr].gene[j].allele[k]);
		}
		printf("\n");
	}
	printf("\n");
}
int compare(struct Chromosome *chrom1, struct Chromosome *chrom2){ // Compares two pointers to sort by fitness function. Basic code found at http://support.microsoft.com/kb/73853
	if ( chrom1->fitnessValue[0] < chrom2->fitnessValue[0]){
		return -1;
	}
	else if ( chrom1->fitnessValue[0] > chrom2->fitnessValue[0]){
		return 1;
	}
	else{		
		if ( chrom1->fitnessValue[1] < chrom2->fitnessValue[1]){
			return -1;
		}
		else if (chrom1->fitnessValue[1] > chrom2->fitnessValue[1]){
			return 1;
		}
		else{
			return 0;
		}
	}
}
void printFitness(void){ // Print fitness of best population, should be run after the population is sorted
	int i;
	for (i = 0; i < POPULATION_SIZE; i++){
		printf("(%d,%d)", Population[i].fitnessValue[0], Population[i].fitnessValue[1]);
	}
	printf("\n");
}
void swapPopulations(){
	//printf("Swap populations\n");
	int i;
	for(i = 0; i < POPULATION_SIZE; i++){
		Population[i] = New_Population[i];
	}
}
void calculateStates(struct Chromosome *chrom){
	int stratLen = 1+2*(GENETIC_PURSUERS+MAX_STEPS); // GENETIC_PURSUERS + start position + following steps
	//int tempPath[stratLen];
	int tempPath[] = {0,0,4,0,3,4,0,0,4,0,3,4};
	//doDecode(chrom, tempPath, stratLen); // Returns an array with [#GENETIC_PURSUERS, pursuer 1 start row, pursuer 1 start column, ..., pursuer 1 move 2 row, puruser 2 move 2 column, ...]
	int currentStep,j;
	int S[GENETIC_ROWS][GENETIC_COLS];
	int S_u[GENETIC_ROWS][GENETIC_COLS];
	for(currentStep = 0; currentStep < MAX_STEPS;currentStep++){ // Go through every step, should terminate if no Node is in state 4.
		/*** Set values in S ***/
		for(j=0;j < GENETIC_PURSUERS; j++){ // For each pursuer
			/*** State 1 ***/
			S[tempPath[2*j]][tempPath[2*j+1]] = 1; // Set state for S to 1	//NodeMatrix[tempPath[2*j]][tempPath[2*j+1]].state = 1; // Set S=1 for pursuer j in position (row,col) given by (tempPath[2*j], tempPath[2*j+1]).
			/*** State 2 ***/
			int k=0;
			while((NodeMatrix[tempPath[2*j]][tempPath[2*j+1]].vision[k]) != 0){
				int S_r = (*NodeMatrix[tempPath[2*j]][tempPath[2*j+1]].vision[k]).name[0];
				int S_c = (*NodeMatrix[tempPath[2*j]][tempPath[2*j+1]].vision[k]).name[1];
				if(S[S_r][S_c] != 1){
					S[S_r][S_c] = 2;
				}
				k++;
			}
		}
		int needUpdate = 1,r,c;
		while(needUpdate == 1){
			/*** Set S4 for all S_u ***/
			for(r = 0; r < GENETIC_ROWS; r++){
				for(c = 0; c < GENETIC_COLS; c++){ // For every node:
					S_u[r][c] = 4;
				}
			}
			/*** Set S1 for pursuers, S2 for visible ***/
			for(j=0;j < GENETIC_PURSUERS; j++){ // For each pursuer
				/*** State 1 ***/
				S_u[tempPath[2*j]][tempPath[2*j+1]] = 1; // Set state for S_u to 1, since that value will be needed.
				/*** State 2 ***/
				int k=0;
				while((NodeMatrix[tempPath[2*j]][tempPath[2*j+1]].vision[k]) != 0){
					int S_r = (*NodeMatrix[tempPath[2*j]][tempPath[2*j+1]].vision[k]).name[0];
					int S_c = (*NodeMatrix[tempPath[2*j]][tempPath[2*j+1]].vision[k]).name[1];
					if(S_u[S_r][S_c] != 1){
						S_u[S_r][S_c] = 2;
					}
					k++;
				}
			}
			/*** Check state 3,4 ***/
			for(r = 0; r < GENETIC_ROWS; r++){
				for(c = 0; c < GENETIC_COLS; c++){ // For every node:
					if(S[r][c] == S_u[r][c] || S[r][c]==2 && S_u[r][c] == 2){
					}
					else if(S[r][c]==2 && S_u[r][c] == 1){
						S_u[r][c] = 3;
					}
					else{
						int check = 1, moveNr;
						for(moveNr=0;moveNr<4;moveNr++){
							if(  NodeMatrix[r][c].move[moveNr] != 0   ){						
								int S_r = (*NodeMatrix[r][c].move[moveNr]).name[0];
								int S_c = (*NodeMatrix[r][c].move[moveNr]).name[1];
								if(S[S_r][S_c] == 4){
									check = 0;
									break;
								}
							}
						}
						if(check==1){
							S_u[r][c]=3;
						}
					}
				}
			}
			needUpdate=0;
			for(r = 0; r < GENETIC_ROWS; r++){ /*** Check if update is needed ***/
				for(c = 0; c < GENETIC_COLS; c++){ // For every node:
					if(S[r][c] != S_u[r][c]){
						needUpdate=1;
					}
				}
			}
			for(r = 0; r < GENETIC_ROWS; r++){ /*** Set S to S_u before new iteration ***/
				for(c = 0; c < GENETIC_COLS; c++){ // For every node:
					S[r][c] = S_u[r][c];
				}
			}
		}
		/*** Set states in NodeMatrix to S ***/
		for(r = 0; r < GENETIC_ROWS; r++){
				for(c = 0; c < GENETIC_COLS; c++){ // For every node:
					NodeMatrix[r][c].state = S[r][c];
				}
			}
	}
	//printf("Calculated states\n");
	
	/* Pseudo code:
	 * Repeat for each step:
	 * 
	 * int S_u[SIZE][SIZE];
	 * Set S=1 for each pursuer position.
	 * Set S=2 for each vision for every pursuer, IF NOT S=1
	 * check = 1
	 * while (check == 1){
	 * Set S_u = 4 for all nodes
	 * Set S_u=1 and S_u=2.
	 * 	For each node:
	 * 	If S==1 && S_u == 1{}
	 * 	Else if S==2 && S_u==2{}
	 * 	Else if S==2 && S_u==1
	 * 		S_u = 3
	 * 	Else{
	 * 		check = 1
	 * 		for m in move(){
	 * 			if S==4
	 * 				check = 0, break
	 * 		if check == 1
	 * 			S_u = 3
	 * 	check = 0
	 * 	For each node:
	 * 		if S != S_u
	 * 			check = 1
	 * 		S = S_u
	 * 
	 * End by writing S to NodeMatrix.
	 * */
}
