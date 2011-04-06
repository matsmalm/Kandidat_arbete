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
				doRoulette()
				doMutation()
				calculateFitness()
				sortTempPop()
			addToNewPopulation()
		doDecode()
						*/

#include "Header.h"
/*** Definitions ***/
#define MAX_GEN 10 // Maximum number of generations
#define POPULATION_SIZE 100 // Population size, static.
#define MAX_PURSUERS 10 // Maximum number of pursuers, just to allocate enough memory
#define MAX_STEPS 100 // Maximum number of steps, just to allocate enough memory

/*** Pre-declarations ***/
struct Gene;
struct Chromosome;


/*** Variables ***/
int PURSUERS; // Only a temporary value.
int STEPS = MAX_STEPS;
int GENERATIONS = 1;
struct Gene{ // Gene contains two parts, start[] which is starting position and allele[] which is direction of every step, 0=stay,1=left,2=right,3=up,4=down.
	int start[2];
	int allele[MAX_STEPS];
};
struct Chromosome{
	int fitnessValue[2]; // [0] = number of contaminated, [1] = required steps until no contamination.
	struct Gene gene[MAX_PURSUERS]; // One gene for each pursuer
};
struct Chromosome Population[POPULATION_SIZE];
struct Chromosome New_Population[POPULATION_SIZE];


/*** Functions ***/
void generatePopulation();
//void preGenetic(struct Node *NodeMat, int *Hunters, int BREAK);
void getRandom(struct Gene *g);
void calculateFitness(struct Chromosome *chrom);
void sortPopulation(struct Chromosome *pop);
void addToNewPopulation(struct Chromosome chrom);
void doCrossover();
void doMutation(struct Chromosome *chrom);
void doDecode();
void printBest(int popNr);

int storlek = 10;
struct Node **NodeMatrix;

/*** Preparations ***/
void preGenetic(struct Node (*NodeMat)[storlek], int *Hunters, int BREAK) { // Do all pre-processing, which is to generate population.
	printf("Pre-processing.\n");
	int i,j;

	NodeMatrix = malloc(storlek * sizeof(struct Node *));
	if(NodeMatrix == NULL)
	{
		fprintf(stderr, "out of memory\n");
	}
	for(i = 0; i < storlek; i++)
	{
		NodeMatrix[i] = malloc(storlek * sizeof(struct Node));
		if(NodeMatrix[i] == NULL)
		{
			fprintf(stderr, "out of memory\n");
		}
	}
	for(i=0;i<storlek;i++){
		for(j=0;j<storlek;j++){
			NodeMatrix[i][j] = NodeMat[i][j];
		}
	}
	STEPS = 10;
	GENERATIONS = BREAK;
	PURSUERS = Hunters[0];
	int k;
	for(i = 0; i < POPULATION_SIZE; i++){ // Set starting positions for every gene in the population.
		for(j = 0; j < PURSUERS; j++){
			for(k = 0; k < 2; k++){
				Population[i].gene[j].start[k] = Hunters[1+j*2+k];
			}
		}
	}
	generatePopulation();
	//printBest(0);
}
void generatePopulation() {
	//printf("\tGenerate population\n");
	int ChromNr, GeneNr;
	for(ChromNr = 0; ChromNr < POPULATION_SIZE; ChromNr++){ // For each Chromosome
		for(GeneNr = 0; GeneNr < PURSUERS; GeneNr++){ // For each Gene
			getRandom(&(Population[ChromNr].gene[GeneNr])); // Generate a random step sequence
		}
	}
}
void getRandom(struct Gene *g){ // Generate random step-sequence from a given node
	//printf("\t\tGenerate random step-sequence\n");
	int stepnr=1, nextStep;
	struct Node *current = &NodeMatrix[(*g).start[0]][(*g).start[1]];
	for(stepnr = 0; stepnr < STEPS; stepnr++){
		while(1==1){
			nextStep = ((int)((double)rand() / ((double)RAND_MAX + 1)*5));
			//printf("Try nextStep: %d\n", nextStep);
			if(nextStep == 4){
				break;
			}
			if((*current).move[nextStep] != 0){
				break;
			}
		}
		//printf("nextStep: %d\n", nextStep);
		(*g).allele[stepnr] = nextStep;
		if(nextStep != 4){
			current = (*current).move[nextStep];
		}
	}
}

/*** Algorithm ***/
void genAlg() { // Main call function for Genetic Algorithm
	printf("The genetic library\n");
	// Set Population to New_Population
	int currentGen, currentChromosome;
	for(currentGen = 0; currentGen < GENERATIONS; currentGen++){
		//printf("***** Generation %d *****\n", currentGen+1);
		for(currentChromosome = 0; currentChromosome < PURSUERS; currentChromosome++){
			//printf("Current Chromosome: %d\n", currentChromosome);
			calculateFitness(&Population[currentChromosome]);
			//sortPopulation(Population);
			addToNewPopulation(Population[0]);
			addToNewPopulation(Population[1]);
			doCrossover();
		}
	}
	doDecode();
	//printf("Decoding completed.\n");

	/*** Free memory for NodeMatrix ***/
	/*
	int i;
	for(i = 0; i < SIZE; i++){
		free(NodeMatrix[i]);
	}
	free(NodeMatrix);
	*/
}
void calculateFitness(struct Chromosome *chrom){
	//printf("\tCalculate fitness\n");
	int fitness[] = {0,0};
	(*chrom).fitnessValue[0] = fitness[0];
	(*chrom).fitnessValue[1] = fitness[1];
}
void sortPopulation(struct Chromosome *pop){
	//printf("\tSort population\n");
	struct Chromosome *temp;
	temp = &pop[1];
	pop[1] = pop[0];
	pop[0] = *temp;
}
void addToNewPopulation(struct Chromosome chrom){
	//printf("\tAdd to new population\n");
}
void doCrossover(){ // Will work with Population.
	//printf("\tDo crossover\n");
	struct Chromosome XoverPop[4];
	XoverPop[0] = Population[doRoulette()];
	XoverPop[1] = Population[doRoulette()];
	// Create offspring 1,2, place in [2], [3]
	doMutation(&XoverPop[2]);
	int tempPopChromosome;
	for(tempPopChromosome = 2; tempPopChromosome < 4; tempPopChromosome++){
		//printf("\t\t");
		calculateFitness(&XoverPop[tempPopChromosome]);
	}
	sortPopulation(XoverPop);
	addToNewPopulation(XoverPop[0]);
	addToNewPopulation(XoverPop[1]);
}
int doRoulette(){ // Return position in Population for the chromosome that was selected.
	//printf("\t\tDo roulette\n");
	return 0;
}
void doMutation(struct Chromosome *chrom){
	//printf("\t\tDo Mutation\n");
}
void doDecode(){ // Decode the best chromosome and return it
	//printf("Decode best chromosome\n");
	int stratLen = 1+2*(PURSUERS+STEPS); // Pursuers + start position + following steps
	int i,j,k,strategy[stratLen];
	strategy[0] = PURSUERS;
	for(i = 0; i < PURSUERS; i++){
		strategy[1] = Population[0].gene[i].start[0];
		strategy[2] = Population[0].gene[i].start[1];
	}
	for(i = 3; i < stratLen;i){ // Start att strategy[3] for steps, increments at end of loop.
		for(k=0;k<PURSUERS; k++){ // For each pursuer
			strategy[i+k] = Population[0].gene[i].allele[k];
		}
		i+=PURSUERS; // step to next pursuer location.
	}

}
void printBest(int popNr){
	//printf("Print best in population:\n");
	int i=0,j=0,k=0;
	for(j=0;j<PURSUERS; j++){ // For each pursuer
		printf("Gene %d:\t", j);
		printf("(%d,%d): ", Population[popNr].gene[j].start[0], Population[popNr].gene[j].start[1]);
		for(k=0;k<STEPS;k++){ // Print step sequence
			printf("%d ", Population[popNr].gene[j].allele[k]);
		}
		printf("\n");
	}
	printf("\n");
}


/* Pseudo-code:
	Pre-processing:
		Generate initial population:
			For each chromosome:
				For each starting point:
					Generate feasible random paths of length n*m = number of nodes
					Encode each path as (0,1,2,3,4,5) where 0 = stand still, 1 = go west, 2 = go east, 3 = go north, 4 = go south.
			
	Genetic Algorithms:
		Do:
			Calculate fitness value [int STATE_4, int MIN_STEPS].
			Cut all genes at MIN_STEPS (???).
			Add two best to new_population (Elitism).
			while(new_population < MAX_POPULATION):
				Select two chromosomes (Roulette wheel).
				Do crossover - With 60% probability take alternating genes from alternating parents.
					Do mutation - With 0.1% probability swap a random step, and make sure the following are feasible (step through and correct).
					Calculate fitness.
				Put the two (of four) with best fitness value in new_population.
		While (generations < MAX_GEN AND BEST_CHROMOSOME != WORST_CHROMOSOME)

		Return BEST_CHROMOSOME

	Variables:
		Chromosome Population[MAX_POPULATION] - should be sorted by fitness to be able to pick best and do roulette.
		Chromosome New_Population[MAX_POPULATION]
		int MAX_GEN
		int MAX_POPULATION
		int MIN_STEPS
		struct Chromosome
		int Gene[]
		ptr BEST_CHROMOSOME
		ptr WORST_CHROMOSOME
	Functions:
		generatePopulation()
		getRandom(Node)
		calculateFitness(Chromosome chrom)
		cutChromosomes()
		sortPopulation()
		doRoulette()
		doCrossover(Chromosome Parent_1, Chromosome Parent_2)
		doMutation(Chromosome Child)
		printBest(Chromosome chrom)
*/


	/*
	int j,k;
	for(j=0;j<MAX_PURSUERS; j++){
		for(k=0;k<MIN_STEPS; k++){
			fitness[1]+=(*chrom).gene[j].allele[k];
		}
	}
	*/

	/*
	int i=0,j=0,k=0;
	for(i=0;i<MAX_POPULATION;i++){
		for(j=0;j<MAX_PURSUERS; j++){
			for(k=0;k<MIN_STEPS; k++){
				(Population[i].gene[j].allele[k]) = getRandom();
			}
		}
	}
	*/

	//((*chrom)[0]).allele[((int)((double)rand() / ((double)RAND_MAX + 1)*MAX_PURSUERS))].allele[((int)((double)rand() / ((double)RAND_MAX + 1)*MAX_STEPS))] = ((int)((double)rand() / ((double)RAND_MAX + 1)*5));
	// checkValid, or retry/modify?

/*
void printBest(struct Chromosome *chrom){
	//printf("Print best in population:\n");
	int i=0,j=0,k=0;
	for(j=0;j<MAX_PURSUERS; j++){
		//printf("\t\tGene %d:\t", j);
		for(k=0;k<MIN_STEPS; k++){
			//printf("%d", (*chrom).gene[j].allele[k]);
		}
		//printf("\n");
	}
	//printf("\n");
	//printf("Fitness: %d\n", (*chrom).fitnessValue[1]);
	////printf("B[0]: %d\n", (&B[0][0]).name[0]);

}
*/

/*
	printf("Starting positions:\n(%d,%d)\n(%d,%d)\n(%d,%d)\n",
	(NodeMatrix)[Population[0].gene[0].start[0]][Population[0].gene[0].start[1]].name[0],
	(NodeMatrix)[Population[0].gene[0].start[0]][Population[0].gene[0].start[1]].name[1],

	(NodeMatrix)[Population[0].gene[1].start[0]][Population[0].gene[1].start[1]].name[0],
	(NodeMatrix)[Population[0].gene[1].start[0]][Population[0].gene[1].start[1]].name[1],

	(NodeMatrix)[Population[0].gene[2].start[0]][Population[0].gene[2].start[1]].name[0],
	(NodeMatrix)[Population[0].gene[2].start[0]][Population[0].gene[2].start[1]].name[1]);
*/
