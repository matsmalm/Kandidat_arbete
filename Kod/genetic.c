#include <string.h>
#include "Header.h"

/*** Definitions ***/
#define GENETIC_MAX_GEN 500 // Maximum number of GENETIC_GENERATIONS
#define GENETIC_POPULATION_SIZE 200 // Population size, static.
#define GENETIC_MAX_GENETIC_PURSUERS 10 // Maximum number of GENETIC_PURSUERS, just to allocate enough memory
#define GENETIC_MAX_STEPS 200 // Maximum number of steps, just to allocate enough memory

/*** Variables ***/
int GENETIC_PURSUERS = 0; // Only a temporary value.
int GENETIC_GENERATIONS = 0; // Only a temporary value.
int GENETIC_ROWS = 0;
int GENETIC_COLS = 0;
float GENETIC_CONVERGENCE_PERCENT = 0.05; // %/100 of population to be equal to break early.

/*** Pre-declarations ***/
struct Gene{ // Gene contains two parts, start[] which is starting position and allele[] which is direction of every step, 0=stay,1=left,2=right,3=up,4=down.
	int start[2];
	int allele[GENETIC_MAX_STEPS];
};
struct Chromosome{
	int fitnessValue[2]; // [0] = number of contaminated, [1] = required steps until no contamination.
	struct Gene gene[GENETIC_MAX_GENETIC_PURSUERS]; // One gene for each pursuer
};
struct Chromosome Population[GENETIC_POPULATION_SIZE];
struct Chromosome New_Population[GENETIC_POPULATION_SIZE];

/*** Functions ***/
//void preGenetic(struct Node (*NodeMat)[SIZE], int *Hunters, int BREAK);
void getRandom(struct Gene *g, int from);
void calculateFitness(struct Chromosome *pop);
void sortPopulation(struct Chromosome *pop, int popSize);
void addToNewPopulation(struct Chromosome chrom);
void doMutation(struct Chromosome *chrom);
void doDecode(struct Chromosome *pop, int *returnPath);
void doReproduce(void);
int calculateStates(int *path);
void printStates(void);
//int getS4(void);

struct Node **NodeMatrix; // Node matrix
typedef int (*compfn)(const void*, const void*); // For quicksort
int compare(struct Chromosome *, struct Chromosome *); // For quicksort
int NewPopLocation = 0;

/*** Preparations ***/
void preGenetic(struct Node (*NodeMat)[SIZE], int *Hunters, int BREAK) { // Do all pre-processing, which is to generate population.
	GENETIC_GENERATIONS = BREAK;
	GENETIC_PURSUERS = Hunters[0];
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
				if(NodeMatrix[i][j].name[0]+1 > GENETIC_ROWS)
					GENETIC_ROWS = 1+NodeMatrix[i][j].name[0];
				if(NodeMatrix[i][j].name[1]+1 > GENETIC_COLS)
					GENETIC_COLS = 1+NodeMatrix[i][j].name[1];
			}
		}
	}
	/*** Do actual pre-processing ***/
	int k;
	for(i = 0; i < GENETIC_POPULATION_SIZE; i++) // Set starting positions for every gene in the population.
		for(j = 0; j < GENETIC_PURSUERS; j++)
			for(k = 0; k < 2; k++)
				Population[i].gene[j].start[k] = Hunters[1+j*2+k];
	/*** Generate population ***/
	int ChromNr, GeneNr;
	for(ChromNr = 0; ChromNr < GENETIC_POPULATION_SIZE; ChromNr++){ // For each Chromosome
		for(GeneNr = 0; GeneNr < GENETIC_PURSUERS; GeneNr++){ // For each Gene
			getRandom(&(Population[ChromNr].gene[GeneNr]),0); // Generate a random step sequence
		}
	}
}
void getRandom(struct Gene *g, int from){ // Generate random step-sequence from a given node
	int stepnr=from, nextStep;
	struct Node *current = &NodeMatrix[(*g).start[0]][(*g).start[1]];
	for(stepnr = from; stepnr < GENETIC_MAX_STEPS; stepnr++){
		while(1==1){
			nextStep = ((int)((double)rand() / ((double)RAND_MAX + 1)*5));
			if(nextStep == 4)
				break;
			if((*current).move[nextStep] != 0)
				break;
		}
		(*g).allele[stepnr] = nextStep;
		if(nextStep != 4)
			current = (*current).move[nextStep];
	}
}
/*** Algorithm ***/
void genAlg(int *solution) { // Main call function for Genetic Algorithm
	int currentGeneration, currPop=0;
	printf("**** Genetic Algorithm info ****\n");
	printf("\nPopulation size:\t%d\n", GENETIC_POPULATION_SIZE);
	printf("Pursuers:\t\t%d\n", GENETIC_PURSUERS);
	printf("Maximum steps:\t\t%d\n", GENETIC_MAX_STEPS);
	printf("Maximum generations:\t%d\n", GENETIC_GENERATIONS);
	printf("Convergence %%:\t\t%d\n\n", abs(GENETIC_CONVERGENCE_PERCENT*100));
	for(currentGeneration = 0; currentGeneration < GENETIC_GENERATIONS; currentGeneration++){
		//printf("Generation %d\n", currentGeneration, GENETIC_GENERATIONS);
		/*** New generation ***/
		for(currPop = 0; currPop < GENETIC_POPULATION_SIZE; currPop++){ // Calculate fitness for every strategy.
			calculateFitness(&Population[currPop]);
		}
		sortPopulation(Population, GENETIC_POPULATION_SIZE); // Sort the population after fitness
		addToNewPopulation(Population[0]);
		addToNewPopulation(Population[1]);
		while(NewPopLocation < GENETIC_POPULATION_SIZE){
			doReproduce();
		}
		if(NewPopLocation<GENETIC_POPULATION_SIZE){
			printf("Missing\n");
		}
		sortPopulation(New_Population, GENETIC_POPULATION_SIZE);
		/*** Swap populations ***/
		int i;
		for(i = 0; i < GENETIC_POPULATION_SIZE; i++){
			Population[i] = New_Population[i];
		}
		if((Population[0].fitnessValue[0]==Population[abs(GENETIC_POPULATION_SIZE*GENETIC_CONVERGENCE_PERCENT)].fitnessValue[0])){ // If 90% of the population has the same fitness, no need to continue to do more generations.
			if(Population[0].fitnessValue[1]==Population[abs(GENETIC_POPULATION_SIZE*GENETIC_CONVERGENCE_PERCENT)].fitnessValue[1]){
				printf("Done\n");
				break;
			}
		}
	}
	solution[0]=GENETIC_PURSUERS;
	solution[1]=Population[0].fitnessValue[1]+1;
	doDecode(&Population[0], solution);
	calculateStates(solution);
	if(getS4() != 0){
		printf("Unsolved\n");
		solution[1] = -solution[1];
	}
	//printStates();
	//printf("End of Genetic Algorithm.\nTook %d generations.\n", currentGeneration);
	/*** Free memory for NodeMatrix ***/
	int i;
	for(i = 0; i < SIZE; i++){
		free(NodeMatrix[i]);
	}
	free(NodeMatrix);
	return;
}
void calculateFitness(struct Chromosome *pop){
	//printf("calculateFitness\n");
	int calcPath[2*(1+GENETIC_MAX_STEPS*GENETIC_PURSUERS)];
	calcPath[0]=GENETIC_PURSUERS;
	calcPath[1]=GENETIC_MAX_STEPS;
	doDecode(&(*pop), calcPath);
	calculateStates(calcPath);
	(*pop).fitnessValue[1] = calculateStates(calcPath);
	(*pop).fitnessValue[0] = getS4();
	//printf("Fitness: %d,%d\n", (*pop).fitnessValue[0], (*pop).fitnessValue[1]);
	//printStates();
}
void addToNewPopulation(struct Chromosome chrom){
	//printf("addToNewPopulation\n");
	New_Population[NewPopLocation] = chrom;
	NewPopLocation++;
}
void doReproduce(){
	//printf("doReproduce\n");
	struct Chromosome XoverPop[4];
	XoverPop[0] = Population[selectParent()];
	XoverPop[1] = Population[selectParent()];
	/*** Crossover ***/
	int GeneNr;
	for(GeneNr = 0; GeneNr < GENETIC_PURSUERS; GeneNr++){
		XoverPop[2].gene[GeneNr  ] = XoverPop[0].gene[GeneNr];
		XoverPop[3].gene[GeneNr  ] = XoverPop[1].gene[GeneNr];
		XoverPop[2].gene[GeneNr+1] = XoverPop[1].gene[GeneNr+1];
		XoverPop[3].gene[GeneNr+1] = XoverPop[0].gene[GeneNr+1];
		GeneNr++;
	}
	/*** Mutation ***/
	//doMutation(XoverPop);
	/*** sort to add best individes ***/
	int i = 0;
	for(i=0;i<4;i++)
		calculateFitness(&XoverPop[i]); // Calculate fitness for each new chromosome.
	sortPopulation(XoverPop, 4);
	addToNewPopulation(XoverPop[0]);
	addToNewPopulation(XoverPop[1]);
}
int selectParent(){ // Return position in Population for the chromosome that was selected.
	//printf("selectParent\n");
	return ((int)((double)rand() / ((double)RAND_MAX + 1)*GENETIC_POPULATION_SIZE));
}
void doMutation(struct Chromosome *chrom){ // Mutate Chromosome
	//printf("doMutation\n");
	int i;
	for(i = 0; i < 2; i++){
		int mutationProp = 5; // probability of mutation*100
		int randomValue = ((int)((double)rand() / ((double)RAND_MAX + 1)*100)); // Random number between 0 and 999
		int randomGene = ((int)((double)rand() / ((double)RAND_MAX + 1)*GENETIC_MAX_GENETIC_PURSUERS)); // Random number between 0 and 999
		if(randomValue < mutationProp){
			//printf("Mutation!\n");
			//getRandom(&((*chrom).gene[randomGene]),((int)((double)rand() / ((double)RAND_MAX + 1)*GENETIC_MAX_STEPS))); // Generate a new random path for a random gene.
		}
	}
}
void doDecode(struct Chromosome *pop, int *returnPath){ // Decode the best chromosome and return it
	//printf("doDecode\n");
	//printf("Pursuers: %d, Steps: %d\n", returnPath[0], returnPath[1]);
	int i,pursuer,step;
	/*** Starting positions ***/
	int location = 2;
	for(pursuer=0;pursuer<returnPath[0];pursuer++){
		returnPath[location]=(*pop).gene[pursuer].start[0];
		returnPath[location+1]=(*pop).gene[pursuer].start[1];
		location+=2;
	}
	/*** Following positions ***/
	int prevR=0,prevC=0,currentR=0,currentC=0;
	for(step=0;step<returnPath[1];step++){
		for(pursuer=0;pursuer<returnPath[0];pursuer++){
			prevR = returnPath[location-2*returnPath[0]];
			prevC = returnPath[location-2*returnPath[0]+1];
			if((*pop).gene[pursuer].allele[step]==4){
				currentR=prevR;
				currentC=prevC;
				returnPath[location] = prevR;
				returnPath[location+1] = prevC;
			}
			else{
				currentR=(*NodeMatrix[ prevR ][ prevC ].move[(*pop).gene[pursuer].allele[step]]).name[0];
				currentC=(*NodeMatrix[ prevR ][ prevC ].move[(*pop).gene[pursuer].allele[step]]).name[1];
				returnPath[location] = currentR;
				returnPath[location+1] = currentC;
			}
			location+=2;
		}
	}
}
int calculateStates(int *tempPath){
	//printf("calculateStates\n");
	int currentStep,j;
	int rows = GENETIC_ROWS; // Number of rows in matrix, to avoid unnecessary checks.
	int cols = GENETIC_COLS; // Number of cols in matrix, to avoid unnecessary checks.
	int S[rows][cols], S_u[rows][cols];
	int r,c;
	/*** Set default values for S and S_u ***/
	for(r = 0; r < rows; r++){
		for(c = 0; c < cols; c++){ // For every node:
			if(NodeMatrix[r][c].vision[0] == 0){
				S[r][c]=0; // Obstacle
				S_u[r][c]=0; // Obstacle
				NodeMatrix[r][c].state = 0;
			}
			else{
				S[r][c]=4;
				S_u[r][c]=4;
				NodeMatrix[r][c].state = 4;
			}
		}
	}
	/*** For all steps ***/
	for(currentStep = 0; currentStep < tempPath[1];currentStep++){ // Go through every step, should terminate if no Node is in state 4.
		/*** Set values in S ***/
		for(j=0;j < tempPath[0]; j++){ // For each pursuer
			/*** State 1 ***/
			S[tempPath[2+2*currentStep+2*j]][tempPath[2+2*currentStep+2*j+1]] = 1; // Set state for S to 1	//NodeMatrix[tempPath[2*j]][tempPath[2*j+1]].state = 1; // Set S=1 for pursuer j in position (row,col) given by (tempPath[2*j], tempPath[2*j+1]).
			/*** State 2 ***/
			int k=0;
			while((NodeMatrix[tempPath[2+2*currentStep+2*j]][tempPath[2+2*currentStep+2*j+1]].vision[k]) != 0){ // Set S2 for every visible node not in S1.
				int S_r = (*NodeMatrix[tempPath[2+2*currentStep+2*j]][tempPath[2+2*currentStep+2*j+1]].vision[k]).name[0];
				int S_c = (*NodeMatrix[tempPath[2+2*currentStep+2*j]][tempPath[2+2*currentStep+2*j+1]].vision[k]).name[1];
				if(S[S_r][S_c] != 1){
					S[S_r][S_c] = 2;
				}
				k++;
			}
		}
		int needUpdate = 1;
		while(needUpdate == 1){
			/*** Set S4 for all S_u (not obstacle) ***/
			for(r = 0; r < rows; r++){
				for(c = 0; c < cols; c++){ // For every node:
					if(NodeMatrix[r][c].vision[0] == 0){
						S_u[r][c]=0; // Obstacle
					}
					else{
						S_u[r][c] = 4;
					}
				}
			}
			/*** Set S1 for pursuers, S2 for visible ***/
			for(j=0;j < GENETIC_PURSUERS; j++){ // For each pursuer
				/*** State 1 ***/
				S_u[tempPath[2+2*currentStep+2*j]][tempPath[2+2*currentStep+2*j+1]] = 1; // Set state for S_u to 1, since that value will be needed.
				/*** State 2 ***/
				int k=0;
				while((NodeMatrix[tempPath[2+2*currentStep+2*j]][tempPath[2+2*currentStep+2*j+1]].vision[k]) != 0){
					int S_r = (*NodeMatrix[tempPath[2+2*currentStep+2*j]][tempPath[2+2*currentStep+2*j+1]].vision[k]).name[0];
					int S_c = (*NodeMatrix[tempPath[2+2*currentStep+2*j]][tempPath[2+2*currentStep+2*j+1]].vision[k]).name[1];
					if(S_u[S_r][S_c] != 1){
						S_u[S_r][S_c] = 2;
					}
					k++;
				}
			}
			/*** Check state 3,4 ***/
			for(r = 0; r < rows; r++){
				for(c = 0; c < cols; c++){ // For every node:
					if(S[r][c]==1 && S_u[r][c]==1){
					}
					else if(S_u[r][c]==2){
					}
					else if(S[r][c]==0){
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
			for(r = 0; r < rows; r++){ /*** Check if update is needed ***/
				for(c = 0; c < cols; c++){ // For every node:
					if(S[r][c] != S_u[r][c]){
						needUpdate=1;
					}
				}
			}
			for(r = 0; r < rows; r++){ /*** Set S to S_u before new iteration ***/
				for(c = 0; c < cols; c++){ // For every node:
					S[r][c] = S_u[r][c];
				}
			}
		}
		/*** Set states in NodeMatrix to S ***/
		for(r = 0; r < rows; r++){
			for(c = 0; c < cols; c++){ // For every node:
				NodeMatrix[r][c].state = S[r][c];
			}
		}
		if(getS4()==0){
			//Can stop calculate states, solution found.
			tempPath[1]=currentStep;
			return currentStep;
		}

	}
	return currentStep;
}
void sortPopulation(struct Chromosome *pop, int popSize){
	//printf("sortPopulation\n");
	qsort((void *) pop, popSize, sizeof(struct Chromosome), (compfn)compare );
}
void printStates(){
	//printf("printStates\n");
	int r,c;
	for(r = 0; r < GENETIC_ROWS; r++){
		for(c = 0; c < GENETIC_COLS; c++){ // For every node:
			printf("%d ", NodeMatrix[r][c].state);
		}
		printf("\n");
	}
}
int getS4(){
	//printf("getS4\n");
	int S4=0,r,c;
	for(r = 0; r < GENETIC_ROWS; r++){
		for(c = 0; c < GENETIC_COLS; c++){ // For every node:
			if(NodeMatrix[r][c].state == 4){
				S4++;
			}
		}
	}
	return S4;
}
int compare(struct Chromosome *chrom1, struct Chromosome *chrom2){ // Compares two pointers to sort by fitness function. Basic code found at http://support.microsoft.com/kb/73853
	//printf("compare\n");
	if ( chrom1->fitnessValue[0] < chrom2->fitnessValue[0])
		return -1;
	else if ( chrom1->fitnessValue[0] > chrom2->fitnessValue[0])
		return 1;
	else{		
		if ( chrom1->fitnessValue[1] < chrom2->fitnessValue[1])
			return -1;
		else if (chrom1->fitnessValue[1] > chrom2->fitnessValue[1])
			return 1;
		else
			return 0;
	}
}
