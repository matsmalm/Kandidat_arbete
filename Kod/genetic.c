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
		doDecode()						*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*** Definitions ***/
#define MAX_GEN 100 // Maximum number of generations
#define POPULATION_SIZE 100 // Population size, static.
#define MAX_PURSUERS 20 // Maximum number of pursuers, just to allocate enough memory
#define MAX_STEPS 50 // Maximum number of steps, just to allocate enough memory

/*** Pre-declarations ***/
struct Gene;
struct Chromosome;
struct Node;

/*** Variables ***/
int PURSUERS; // Only a temporary value.
int STEPS = MAX_STEPS;
int GENERATIONS = 1;
struct Gene{
	int allele[2*MAX_STEPS];
};
struct Chromosome{
	int fitnessValue[2]; // [0] = number of contaminated, [1] = required steps until no contamination.
	struct Gene gene[MAX_PURSUERS]; // One gene for each pursuer
};
struct Chromosome Population[POPULATION_SIZE];
struct Chromosome New_Population[POPULATION_SIZE];
struct Node *NodeMatrix; // Pointer to the Node matrix
long STARTTIME;

/*** Functions ***/
void generatePopulation();
void preGenetic(struct Node *NodeMat, int *Hunters, int BREAK);
void getRandom(struct Gene *g);
void calculateFitness(struct Chromosome *chrom);
void sortPopulation(struct Chromosome *pop);
void addToNewPopulation(struct Chromosome chrom);
void doCrossover();
void doMutation(struct Chromosome *chrom);
void doDecode();
void printBest();

/*** Preparations ***/
void preGenetic(struct Node *NodeMat, int *Hunters, int BREAK) { // Do all pre-processing, which is to generate population.
	STEPS = 5;
	GENERATIONS = BREAK;
	PURSUERS = Hunters[0];
	int i, j, k;
	for(i = 0; i < POPULATION_SIZE; i++){
		for(j = 0; j < PURSUERS; j++){
			for(k = 0; k < 2; k++){
				Population[i].gene[j].allele[k] = Hunters[j*2+1+k];
			}
		}
	}
	//printf("Pre-processing.\n");
	////printf("Name: (%d)\n", (*NodeMat[0][0]).name[0]);
	NodeMatrix = NodeMat; // Make the Node Matrix available for the genetic algorithm.
	generatePopulation();
}
void generatePopulation() {
	//printf("\tGenerate population\n");
	int ChromNr, GeneNr;
	for(ChromNr = 0; ChromNr < POPULATION_SIZE; ChromNr++){
		for(GeneNr = 0; GeneNr < PURSUERS; GeneNr++){
			getRandom(&(Population[ChromNr].gene[GeneNr]));
		}
	}
}
void getRandom(struct Gene *g){ // Generate random step-sequence from a given node
	////printf("\t\tGenerate random step-sequence\n");
	int stepnr=1;
	for(stepnr = 1; stepnr < STEPS; stepnr++){
		(*g).allele[2*stepnr] = ((int)((double)rand() / ((double)RAND_MAX + 1)*5));
		(*g).allele[2*stepnr+1] = ((int)((double)rand() / ((double)RAND_MAX + 1)*5));
	}
}

/*** Algorithm ***/
void genAlg() { // Main call function for Genetic Algorithm
	//printf("The genetic library\n");
	// Set Population to New_Population
	int currentGen, currentChromosome;
	for(currentGen = 0; currentGen < GENERATIONS; currentGen++){
		//printf("***** Generation %d *****\n", currentGen+1);
		for(currentChromosome = 0; currentChromosome < PURSUERS; currentChromosome++){
			//printf("Current Chromosome: %d\n", currentChromosome);
			calculateFitness(&Population[currentChromosome]);
			sortPopulation(Population);
			addToNewPopulation(Population[0]);
			addToNewPopulation(Population[1]);
			doCrossover();
		}
	}
	doDecode();
	printBest();
}
void calculateFitness(struct Chromosome *chrom){
	//printf("\tCalculate fitness\n");
	int fitness[] = {0,0};
	(*chrom).fitnessValue[0] = fitness[0];
	(*chrom).fitnessValue[1] = fitness[1];
}
void sortPopulation(struct Chromosome *pop){
	//printf("\tSort population\n");
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
}
void printBest(){
	//printf("Print best in population:\n");
	int i=0,j=0,k=0;
	for(j=0;j<PURSUERS; j++){
		//printf("Gene %d:\t", j);
		for(k=0;k<STEPS; k++){
			//printf("(%d,%d) ", Population[0].gene[j].allele[2*k], Population[0].gene[j].allele[2*k+1]);
		}
		//printf("\n");
	}
	//printf("\n");
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
