#include <string.h>
#include "Header.h"

/*** Definitions ***/
#define GENETIC_MAX_GEN 100 // Maximum number of GENETIC_GENERATIONS
#define GENETIC_POPULATION_SIZE 1000 // Population size, static.
#define GENETIC_MAX_PURSUERS 20 // Maximum number of GENETIC_PURSUERS, just to allocate enough memory
#define GENETIC_MAX_STEPS 200 // Maximum number of steps, just to allocate enough memory

/*** Variables ***/
int GENETIC_PURSUERS = 0; // Only a temporary value.
int GENETIC_GENERATIONS = 0; // Only a temporary value.
float GENETIC_CONVERGENCE_PERCENT = 0.99; // fraction of population to be equal to break early.
float GENETIC_MUTATION_PROBABILITY = 0.05; // fraction of mutation probability.
int ROWS;
int COLS;

/*** Pre-declarations ***/
struct Gene{ // Gene contains two parts, start[] which is starting position and allele[] which is direction of every step, 0=stay,1=left,2=right,3=up,4=down.
	int start[2];
	int allele[GENETIC_MAX_STEPS];
};
struct Chromosome{
	int inS4; // Number of nodes in S4
	int chrSteps; // Number of steps to reach solution
	struct Gene gene[GENETIC_MAX_PURSUERS]; // One gene for each pursuer
	float fitnessScore;
};
struct Chromosome *Population;
struct Chromosome *New_Population;
struct Node **NodeMatrix; // Node matrix
typedef int (*compfn)(const void*, const void*); // For quicksort
int compareFitness(struct Chromosome *chrom1, struct Chromosome *chrom2); // For quicksort
int NewPopLocation;

/*** Functions ***/
void preGenetic(struct Node (*NodeMat)[SIZE], int *Hunters, int BREAK, int ROWS, int COLS);
void getRandom(struct Gene *g, int from);
void calculateFitness(struct Chromosome *pop);
void sortPopulation(struct Chromosome *pop, int popSize);
void addToNewPopulation(struct Chromosome chrom);
void doMutation(struct Chromosome *chrom);
void doDecode(struct Chromosome *pop, int *returnPath);
void doReproduce(void);
int calculateStates(int *path);
void printStates(void);
int getS4(void);

/*** Preparations ***/
void preGenetic(struct Node (*NodeMat)[SIZE], int *Hunters, int BREAK, int ROWS, int COLS) { // Do all pre-processing, which is to generate population.
	Population = malloc(GENETIC_POPULATION_SIZE * sizeof(struct Chromosome));
	
	if(Population == NULL)
		fprintf(stderr, "Population out of memory\n");
	New_Population = malloc(GENETIC_POPULATION_SIZE * sizeof(struct Chromosome));
	
	if(New_Population == NULL)
		fprintf(stderr, "New_Population out of memory\n");
	NewPopLocation = 0;
	
	GENETIC_GENERATIONS = BREAK;
	GENETIC_PURSUERS = Hunters[0];
	int i,j;
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
	for(i=0;i<ROWS;i++)
		for(j=0;j<COLS;j++)
			NodeMatrix[i][j] = NodeMat[i][j];
	/*** Do actual pre-processing ***/
	int k;
	for(i = 0; i < GENETIC_POPULATION_SIZE; i++){ // Reset all genes.
		for(j = 0; j < GENETIC_PURSUERS; j++)
			for(k=0;k<GENETIC_MAX_STEPS;k++)
				Population[i].gene[j].allele[k] = 4;
				
		Population[i].inS4=99; // Reset fitness value (S4)
		Population[i].chrSteps=99; // Reset fitness value (steps)
		Population[i].fitnessScore = 9; // Low value = bad solution
	}
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
	for(stepnr = 0; stepnr < GENETIC_MAX_STEPS; stepnr++){
		while(1==1){
			if(stepnr<from)
				nextStep = (*g).allele[stepnr];
			else
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
	int currentGeneration=0, currentPopulation=0;
	printf("**** Genetic Algorithm info ****\n");
	printf("Population size:\t%d\n", GENETIC_POPULATION_SIZE);
	printf("Pursuers:\t\t%d\n", GENETIC_PURSUERS);
	printf("Maximum steps:\t\t%d\n", GENETIC_MAX_STEPS);
	printf("Maximum generations:\t%d\n", GENETIC_GENERATIONS);
	printf("Convergence %%:\t\t%d\n", abs(GENETIC_CONVERGENCE_PERCENT*100));
	printf("Mutation %%:\t\t%d\n", abs(GENETIC_MUTATION_PROBABILITY*100));
	for(currentPopulation = 0; currentPopulation < GENETIC_POPULATION_SIZE; currentPopulation++){ // Calculate fitness for every strategy.
		calculateFitness(&Population[currentPopulation]);
	}
	sortPopulation(Population, GENETIC_POPULATION_SIZE); // Sort the population after fitness
	
	for(currentGeneration = 0; currentGeneration < GENETIC_GENERATIONS; currentGeneration++){
		/*** New generation ***/
		addToNewPopulation(Population[0]); // Elite selection
		addToNewPopulation(Population[1]); // Elite selection
		while(NewPopLocation < GENETIC_POPULATION_SIZE)
			doReproduce(); // Reproduction
		sortPopulation(New_Population, GENETIC_POPULATION_SIZE); // Sort the new population after fitness
		/*** Swap populations ***/
		int i;
		for(i = 0; i < GENETIC_POPULATION_SIZE; i++)
			Population[i] = New_Population[i]; // Overwrite old population with new
		if(Population[0].inS4 == 0) // If a complete solution has been found, check if convergence level is reached
			if((Population[0].chrSteps==Population[abs(GENETIC_POPULATION_SIZE*GENETIC_CONVERGENCE_PERCENT)].chrSteps)) // If 90% of the population has the same number of steps, no need to continue to do more generations.
				if(Population[0].fitnessScore==Population[abs(GENETIC_POPULATION_SIZE*GENETIC_CONVERGENCE_PERCENT)].fitnessScore) // Redundant check, check fitness score
					break;
		NewPopLocation=0;
	}
	printf("%d generations used.\n", currentGeneration);
	solution[0]=GENETIC_PURSUERS; // Write number of pursuers to solution
	solution[1]=GENETIC_MAX_STEPS; // Write maximum number of steps to solution
	if(Population[0].chrSteps<=200){
		doDecode(&Population[0], solution); // Decode solution to positions
		solution[1]=calculateStates(solution); // Calculate states, and update steps to minimum
	}
	else
		solution[1]=Population[0].chrSteps; // If the solution was to long, or not found, no need to return path
	/*** Free allocated memory ***/
	free(Population);
	free(New_Population);
	/*** Free memory for NodeMatrix ***/
	int i;
	for(i = 0; i < ROWS; i++)
		free(NodeMatrix[i]);
	free(NodeMatrix);
	return;
}
void calculateFitness(struct Chromosome *pop){
	int calcPath[2*(1+GENETIC_PURSUERS+GENETIC_MAX_STEPS*GENETIC_PURSUERS)]; // Temporary variable for path
	calcPath[0]=GENETIC_PURSUERS; // Number of pursuers
	calcPath[1]=GENETIC_MAX_STEPS; // Number of steps
	doDecode(&(*pop), calcPath); // Decode allele to positions
	int temp = calculateStates(calcPath); // Calculate states
	(*pop).chrSteps = temp; // Write number of steps to individual
	if(temp>=0)
		(*pop).inS4 = 0; // If number of steps was positive, no nodes were in state 4
	else
		(*pop).inS4 = getS4(); // Write number of nodes in state 4
	(*pop).fitnessScore = 1000/(1+(*pop).inS4+abs((*pop).chrSteps)); // Set fitness to 1000/(1+S4+steps), 1000 to scale fitness, 1+ to avoid division by 0.
}
void addToNewPopulation(struct Chromosome chrom){ // Adds a new individual to the new population
	New_Population[NewPopLocation] = chrom;
	NewPopLocation++;
}
void doReproduce(){
	struct Chromosome XoverPop[4]; // Small population of 4 individuals
	XoverPop[0] = Population[selectParent()]; // Select parent 1
	XoverPop[1] = Population[selectParent()]; // Select parent 2
	/*** Crossover ***/
	int GeneNr;
	for(GeneNr = 0; GeneNr < GENETIC_PURSUERS; GeneNr++){ // Take one gene from each parent
		XoverPop[2].gene[GeneNr  ] = XoverPop[0].gene[GeneNr];
		XoverPop[3].gene[GeneNr  ] = XoverPop[1].gene[GeneNr];
		XoverPop[2].gene[GeneNr+1] = XoverPop[1].gene[GeneNr+1];
		XoverPop[3].gene[GeneNr+1] = XoverPop[0].gene[GeneNr+1];
		GeneNr++;
	}
	/*** Mutation ***/
	doMutation(&XoverPop[2]); // Mutate the generated individual
	doMutation(&XoverPop[3]); // Mutate the generated individual
	/*** sort to add best individes ***/
	int i = 0;
	for(i=2;i<4;i++)
		calculateFitness(&XoverPop[i]); // Calculate fitness for children
	sortPopulation(XoverPop, 4); // Sort after fitness
	addToNewPopulation(XoverPop[0]); // Add best individual to new population
	addToNewPopulation(XoverPop[1]); // Add second best individual to new population
}
int selectParent(){ // Return position in Population for the chromosome that was selected.
	int totFitness = 0, i=0, parentNr=0;
	for(i=0;i<GENETIC_POPULATION_SIZE;i++)
		totFitness += Population[i].fitnessScore; // Calculate sum of fitness for population
	int randNr = ((int)((double)rand() / ((double)RAND_MAX + 1)*abs(totFitness))); // Generate a random number between 0 and totalFitness
	totFitness = 0;
	for(parentNr=0;parentNr<GENETIC_POPULATION_SIZE;parentNr++){
		totFitness += Population[parentNr].fitnessScore;
		if(totFitness > randNr)
			return parentNr; // Return the first parent with as high fitness as was randomly generated
	}
}
void doMutation(struct Chromosome *child){ // Mutate Chromosome
	int randomFrom = ((int)((double)rand() / ((double)RAND_MAX + 1)*GENETIC_MAX_STEPS));// Random step between 0 and current max steps
	int randomGene = ((int)((double)rand() / ((double)RAND_MAX + 1)*GENETIC_PURSUERS)); // Random number between 0 and GENETIC_PURSUERS
	int randomValue = ((int)((double)rand() / ((double)RAND_MAX + 1)*100)); // Random number between 0 and 99
	if(randomValue < GENETIC_MUTATION_PROBABILITY*100)
		getRandom(&(*child).gene[randomGene], randomFrom); // Generate part of new gene
}
void doDecode(struct Chromosome *pop, int *returnPath){ // Decode the best chromosome and return it
	int i=0,pursuer=0,step=0;
	/*** Starting positions ***/
	int location = 2;
	for(pursuer=0;pursuer<returnPath[0];pursuer++){ // Write starting positions to path
		returnPath[location]=(*pop).gene[pursuer].start[0];
		returnPath[location+1]=(*pop).gene[pursuer].start[1];
		location+=2;
	}
	/*** Following positions ***/
	int prevR=0,prevC=0,currentR=0,currentC=0;
	for(step=0;step<returnPath[1];step++){
		for(pursuer=0;pursuer<returnPath[0];pursuer++){
			prevR = returnPath[2*(1+pursuer+returnPath[0]*step)]; // Previous row
			prevC = returnPath[location-2*returnPath[0]+1]; // Previous column
			int dir = 4;
			dir = (*pop).gene[pursuer].allele[step]; // Direction (from the allele)
			if(dir==4){ // If the pursuer stands still
				currentR=prevR;
				currentC=prevC;
				returnPath[2*(1+pursuer+returnPath[0]*(step+1))] = prevR;
				returnPath[2*(1+pursuer+returnPath[0]*(step+1))+1] = prevC;
			}
			else{
				currentR=(*NodeMatrix[ prevR ][ prevC ].move[(*pop).gene[pursuer].allele[step]]).name[0]; // Get new row
				currentC=(*NodeMatrix[ prevR ][ prevC ].move[(*pop).gene[pursuer].allele[step]]).name[1]; // Get new column
				returnPath[2*(1+pursuer+returnPath[0]*(step+1))] = currentR;
				returnPath[2*(1+pursuer+returnPath[0]*(step+1))+1] = currentC;
			}
			location+=2;
		}
	}
}
int calculateStates(int *path){
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
			//Solution found, stop taking steps
			break;
		}
	}
	if(nrS4>0)
		currentStep = (0-currentStep);
	for(r = 0; r < ROWS; r++) // Solution found or all steps used, write to nodeMatrix
		for(c = 0; c < COLS; c++)
			NodeMatrix[r][c].state = S[r][c];
	return currentStep;
}
void sortPopulation(struct Chromosome *pop, int popSize){
	qsort((void *) pop, popSize, sizeof(struct Chromosome), (compfn)compareFitness ); // Use qsort to sort population after fitness
}
void printStates(){ // Prints a matrix with all states
	int r,c;
	for(r = 0; r < ROWS; r++){
		for(c = 0; c < COLS; c++) // For every node:
			printf("%d ", NodeMatrix[r][c].state);
		printf("\n");
	}
	printf("\n");
}
int getS4(){ // Returns the number of nodes in state 4
	int S4=0,r,c;
	for(r = 0; r < ROWS; r++)
		for(c = 0; c < COLS; c++) // For every node:
			if(NodeMatrix[r][c].state == 4)
				S4++;
	return S4;
}
int compareFitness(struct Chromosome *chrom1, struct Chromosome *chrom2){ // Compares two pointers to sort by fitness function. Basic code found at http://support.microsoft.com/kb/73853
	if ( chrom1->fitnessScore > chrom2->fitnessScore)
		return -1;
	else if ( chrom1->fitnessScore < chrom2->fitnessScore)
		return 1;
	else{		
		if ( chrom1->inS4 < chrom2->inS4)
			return -1;
		else if (chrom1->inS4 > chrom2->inS4)
			return 1;
		else
			return 0;
	}
}
