
#include "Header.h"
#include "genetic.h"
#include "greedy.h"
#include <sys/time.h>

//#define SIZE 10 // Set to at least the maximum size of your environments, 1024 (1024^2 nodes) should be enough. Bigger SIZE means longer computation time.
int A[SIZE][SIZE]; // The matrix of the area to create a network from.
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

void place(); // For each allowed position (a_ij=1 i A), give B values at position b_ij.
void setMove(struct Node *b); // Give element b_ij moveable elements in B.
struct Node *getMove(struct Node *from, int dir); //From current position b_ij, move to right/left/up/down.
int getLeft(struct Node *b); // Fetch the number of possible steps to left.
int getRight(struct Node *b); // Fetch the number of possible steps to right.
int getUp(struct Node *b); // Fetch the number of possible steps upwards.
int getDown(struct Node *b); // Fetch the number of possible steps downwards.
void setVision(struct Node *b); // Calculate visible nodes.
int numVisible(struct Node *b); // Calculate how many visible nodes there is from a node.
void printArea(void);
void printCommon(int *Hunters);
FILE *fr = NULL;
FILE *res = NULL;
FILE *purPaths = NULL;
int ROWS=0,COLS=0,OBS=0;
struct Node B[SIZE][SIZE];
int *Hunters;


struct Path{
	int path[10];
};

void place() {
	int i=0, j=0;
	for(i=0;i<ROWS;i++){
			for(j=0;j<COLS;j++){
				if(A[i][j]==1){
					B[i][j].name[0] = i;
					B[i][j].name[1] = j;
					B[i][j].move[LEFT] = NULL;
					B[i][j].move[RIGHT] = NULL;
					B[i][j].move[UP] = NULL;
					B[i][j].move[DOWN] = NULL;
					setMove(&B[i][j]);
					B[i][j].state = 4;
				}
			}
	}
	for(i=0;i<ROWS;i++){
			for(j=0;j<COLS;j++){
				if(A[i][j]==1){
					setVision(&B[i][j]);
				}else{
				  B[i][j].state=25;
				  B[i][j].vision[0]= (struct Node *)0;
				}
			}
	}
}
void setMove(struct Node *b){
	int i = (*b).name[0];
	int j = (*b).name[1];
	if(j>0 && A[i][j-1]==1){ //Left
		(*b).move[LEFT]=(&(*getMove(b,LEFT)));
	}else{
		(*b).move[LEFT]=NULL;
	}
	if(j<COLS && A[i][j+1]==1){ //Right
		(*b).move[RIGHT]=(&(*getMove(b,RIGHT)));
	}else{
		(*b).move[RIGHT]=NULL;
	}
	if(i>0 && A[i-1][j]==1){ //Up
		(*b).move[UP]=(&(*getMove(b,UP)));
	}else{
		(*b).move[UP]=NULL;
	}
	if(i<COLS && A[i+1][j]==1){ //Down
		(*b).move[DOWN]=(&(*getMove(b,DOWN)));
	}else{
		(*b).move[DOWN]=NULL;
	}
}
struct Node *getMove(struct Node *from, int dir){
	struct Node *to;
	if(dir==LEFT){
		to = &(B[(*from).name[0]][((*from).name[1]-1)]);
	}else if(dir==RIGHT){
		to = &(B[(*from).name[0]][((*from).name[1]+1)]);
	}else if(dir==UP){
		to = &(B[((*from).name[0]-1)][(*from).name[1]]);
	}else if(dir==DOWN){
		to = &(B[((*from).name[0]+1)][(*from).name[1]]);
	}else {
		printf("Something went wrong.\n");
	}
	return to;
}
int getLeft(struct Node *b) {
	if((*b).move[LEFT] == NULL){ // No more steps to the left.
		int s=0;
		return s;
	}else{
		int s = getLeft(getMove(&(*b), LEFT))+1;
		return s;
	}
	printf("Something went very wrong.\n");
	return 0;
}
int getRight(struct Node *b) {
	if((*b).move[RIGHT] == NULL){ // No more steps to the left.
		int s=0;
		return s;
	}else{
		int s = getRight(getMove(&(*b), RIGHT))+1;
		if(s>=9){
		}
		return s;
	}
	printf("Something went very wrong.\n");
	return 0;
}
int getUp(struct Node *b) {
	if((*b).move[UP]==NULL){
		int s=0;
		return s;
	}else{
		int s = getUp(getMove(&(*b), UP))+1;
		return s;
	}
	printf("Something went very wrong.\n");
	return 0;
}
int getDown(struct Node *b) {
	if((*b).move[DOWN]==NULL){
		int s=0;
		return s;
	}else{
		int s = getDown(getMove(&(*b), DOWN))+1;
		return s;
	}
	printf("Something went very wrong.\n");
	return 0;
}
void setVision(struct Node *b) {
	int r = (*b).name[0];
	int k = (*b).name[1];
	int v = 0; // Counter for vision[]
	int i=0;
	while(i<SIZE*SIZE){
	  (*b).vision[i]=(struct Node *)0;
	  i++;
	}
	int z;
	int Lmax=SIZE,Rmax=SIZE,Umax=SIZE,Dmax=SIZE;
	struct Node *temp;
	// Left
	temp = &(*b);
	Lmax = getLeft(b);
	Rmax = getRight(b);
	Umax = getUp(b);
	Dmax = getDown(b);
	z=k;
	while(z>=Lmax-k)
	{
		(*b).vision[v] = temp;
		v++;
		if (getUp(temp)<Umax){
			Umax = getUp(temp);
		}
		if(getDown(temp)<Dmax){
			Dmax = getDown(temp);
		}
		i = r;
		while(i>(r-Umax)){
			if(getUp(temp)!=0){
				temp = getMove(temp, UP);
				(*b).vision[v] = temp;
				v++;
			}
			i--;
		}
		temp = &B[r][z];
		i = r;
		while(i<(r+Dmax)){
			if(getDown(temp)!=0){
				temp = getMove(temp, DOWN);
				(*b).vision[v] = temp;
				v++;
			}
			i++;
		}
		if((B[r][z]).move[LEFT] != NULL) {
			z--;
			temp = &B[r][z];
		}else{
			break;
		}
	}
	
	// Right
	temp = getMove(&(*b),RIGHT);
	Lmax = getLeft(b);
	Rmax = getRight(b);
	Umax = getUp(b);
	Dmax = getDown(b);
	z=k+1;
	while(z<=k+Rmax)
	{
		(*b).vision[v] = temp;
		v++;
		if (getUp(temp)<Umax){
			Umax = getUp(temp);
		}
		if(getDown(temp)<Dmax){
			Dmax = getDown(temp);
		}
		i = r;
		while(i>(r-Umax)){
			if(getUp(temp)!=0){
				temp = getMove(temp, UP);
				(*b).vision[v] = temp;
				v++;
			}
			i--;
		}
		temp = &B[r][z];
		i = r;
		while(i<(r+Dmax)){
			if(getDown(temp)!=0){
				temp = getMove(temp, DOWN);
				(*b).vision[v] = temp;
				v++;
			}
			i++;
		}
		if((B[r][z]).move[RIGHT] != NULL) {
			z++;
			temp = &B[r][z];
		}else{
			break;
		}
	}
}
int numVisible(struct Node *b) {
	int i,visible = 0;
	for(i=0;i<(SIZE*SIZE);i++){
		if((&((*b).vision[i]))!=0){
			visible++;
		}
	}
	return visible;
}
int readFromFile() {
	resetAB();
	ROWS=0;
	COLS=0;
	OBS=0;
	int tmpcols=0;
	int currentcol=0;
	char line[2048]; // Maimum number of columns*2, line length. Should allow about 1025 columns.
	while ( fgets ( line, sizeof line, fr ) != NULL ){ /* read a line */
		currentcol=0;
		tmpcols=0;
		int i=0;
		while(1==1){
			if(line[i]!='\n'){
				i++;
				tmpcols++;
			}else{
				break;
			}
		}
		if(line[0]!='\n'){
			ROWS++;
		}
		if(tmpcols>COLS){
			COLS=tmpcols;
		}
		if(line[0]!='\n'){
			for(i=0;i<=COLS;i++){
				if((line[i] != ' ') && (line[i] != '\n')){ // Will only happen for 0 and 1 in the matrix.
					A[ROWS-1][currentcol] = (int) strtol(&line[i],NULL,10);
					if(A[ROWS-1][currentcol]==0){
						OBS++;
					}
					currentcol++;
				}
			}
		}else{
			break;
		}
		for(i=0;i<COLS;i++){
			line[i]=0;
		}
	}
	if(ROWS==0){ // Shift between two matrices, can stop reading.
		return -1;
	}
	COLS = (int)(COLS/2+1);
	return 1;
}
int resetAB() {
	int r=0,c=0;
	for(r=0;r<SIZE;r++){
		for(c=0;c<SIZE;c++){
			A[r][c]=0;
		}
	}
}
void getStartPositions(int *Hunters){
	Hunters[0] = 3;
	int i;
	for(i=1;i<1+2*Hunters[0];i+=2){
		while(1==1){
			int r = (int)((double)rand() / ((double)RAND_MAX + 1)*ROWS);
			int c = (int)((double)rand() / ((double)RAND_MAX + 1)*COLS);
			if(B[r][c].vision[0] != 0){
				Hunters[i]=r;
				Hunters[i+1]=c;
				break;
			}
		}
	}
	printf("%d pursuers in positions: ", Hunters[0]);
	for(i=1;i<1+2*Hunters[0];i+=2){
		printf("(%d,%d)", Hunters[i], Hunters[i+1]);
	}
	printf("\n");
}
int main() {
	srand(time(0)); // Resets random.
	fr = fopen("OK.txt", "r"); // Open file once
	int numMatrices=0;
	struct timeval beforeGen, beforeTab, beforeGre, afterGen, afterTab, afterGre;
	while(readFromFile() != -1){
		numMatrices++;
		place();
		Hunters = malloc(21*sizeof(int));
		res = fopen("RESULTS.txt", "a+"); // Open file once, will overwrite each run. "a+" = append, "w" = (over)write
		purPaths = fopen("PATHS.txt", "a+"); // Open file once, will overwrite each run. "a+" = append, "w" = (over)write
		printArea();
		//int Hunter_static[]={2,2,0,4,4};
		int BREAK = 100;
		int envLoop=0;
		for(envLoop=0;envLoop<1;envLoop++){ // Same area 4 times, with different start positions
			memset(Hunters,0,sizeof(Hunters));
			getStartPositions(Hunters);
			fprintf(res, "Algorithm\t");
			fprintf(res, "Genetic  \t");
			fprintf(res, "Greedy   \t");
			fprintf(res, "Tabu     \n");
			printf("Using %d pursuers\n", Hunters[0]);
			/****
			Here we should be able to call our algorithms, since B will contain the graph network.
			****/
			/*** Genetic ***/
			int numPur;
			for(numPur=Hunters[0];numPur>=2;numPur--){ // Loop from Hunters[1] down to 2 pursuers
				Hunters[0] = numPur;
				printf("Hunters[0]: %d\n", Hunters[0]);
				printCommon(Hunters); // Write all common info to RESULTS.txt
				int sameEnv=0;
				for(sameEnv=0;sameEnv<1;sameEnv++){ // Loop with same parameters 4 times
					fprintf(res, "%d.%d.%d.%d\n", numMatrices, envLoop, numPur, sameEnv);
					printf("Loop %d of 4 in sameEnv\n", sameEnv);
					printf("Genetic\n");
					int geneticSolution[2*(1+Hunters[0]*200)];
					memset(geneticSolution,-1,sizeof(geneticSolution));
					preGenetic(&B, Hunters, BREAK, ROWS, COLS);
					gettimeofday(&beforeGen, NULL);

					genAlg(geneticSolution); // Main Genetic Algorithm program.
					gettimeofday(&afterGen, NULL);

					/*** Greedy ***/
					struct greedy start;
					//start = preGreedy(&B, Hunters, &BREAK);
					gettimeofday(&beforeGre, NULL);
					//greedyAlg(&start);
					gettimeofday(&afterGre, NULL);
					/*** Tabu ***/

					printf("Tabu\n");
					int tabuSolution[2*(1+Hunters[0]*200)];
					memset(tabuSolution,-1,sizeof(tabuSolution));
				    preTabu(&B, Hunters, BREAK, ROWS, COLS);
					gettimeofday(&beforeTab, NULL);
				    Tabu(tabuSolution); // Main Genetic Algorithm program.
					gettimeofday(&afterTab, NULL);
					printf("Tabu End\n");
					// Print statistics to RESULTS.txt
					/*fprintf(res, "Time     \t");
					fprintf(res, "%.2f     \t", ((double) (genEnd - genStart)) / CLOCKS_PER_SEC);
					fprintf(res, "%.2f     \n", ((double) (tabEnd - tabStart)) / CLOCKS_PER_SEC);*/
					fprintf(res, "Time     \t");
					fprintf(res, "%.4f     \t", ((double) (afterGen.tv_sec - beforeGen.tv_sec)*1000 + (afterGen.tv_usec-beforeGen.tv_usec)/1000)/1000);
					fprintf(res, "%.4f     \t", ((double) (afterGre.tv_sec - beforeGre.tv_sec)*1000 + (afterGre.tv_usec-beforeGre.tv_usec)/1000)/1000);
					fprintf(res, "%.4f     \t\n", ((double) (afterTab.tv_sec - beforeTab.tv_sec)*1000 + (afterTab.tv_usec-beforeTab.tv_usec)/1000)/1000);
					fprintf(res, "Steps    \t");
					fprintf(res, "%d       \t", geneticSolution[1]);
					fprintf(res, "%d       \t", start.solution[1]);
					fprintf(res, "%d       \n", tabuSolution[1]);
					// Print path to separate file (PATHS.txt)
					fprintf(purPaths, "%d.%d.%d.%d\n", numMatrices, envLoop, numPur, sameEnv);
					int i,genDone=0,greDone=0,tabDone=0,pur=0;
					fprintf(purPaths, "Genetic: \n");
					for(pur=0;pur<Hunters[0];pur++){
						for(i=2*(1+pur);i<2*(1+Hunters[0]+Hunters[0]*geneticSolution[1]);i+=2*Hunters[0]){
							fprintf(purPaths, "(%d,%d) ", geneticSolution[i], geneticSolution[i+1]);
						}
						fprintf(purPaths, "\n");
					}
					fprintf(purPaths, "Tabu: \n");
					for(pur=0;pur<Hunters[0];pur++){
						for(i=2*(1+pur);i<2*(1+Hunters[0]+Hunters[0]*tabuSolution[1]);i+=2*Hunters[0]){
							fprintf(purPaths, "(%d,%d) ", tabuSolution[i], tabuSolution[i+1]);
						}
						fprintf(purPaths, "\n");
					}
					fprintf(purPaths, "\n");
				}
			}
		}
		fclose(purPaths); // Close the result file once
		fclose(res); // Close the result file once
		free(Hunters);
	}
	printf("There were %d matrices in input file.\n", numMatrices);
	fclose (fr); // Close file once.
	printf("End main\n");
	return EXIT_SUCCESS;
}
void printCommon(int *Hunters){
	int i;
	fprintf(res, "         \t         \t         \tPursuers \t%d         \t", Hunters[0]);
	for(i=1;i<1+2*Hunters[0];i+=2){
		fprintf(res, "(%d,%d)", Hunters[i], Hunters[i+1]);
	}
	fprintf(res, "\n");
}
void printArea(){
	// Prints environment, rows, columns, obstacles to RESULTS.txt
	int i,j;
	for(i=0;i<ROWS;i++){
		for(j=0;j<COLS;j++){
			fprintf(res, "%d ", A[i][j]);
		}
		fprintf(res, "\n");
	}
	fprintf(res, "Rows: %d\n", ROWS);
	fprintf(res, "Columns: %d\n", COLS);
	fprintf(res, "Obstacles: %d\n", OBS);
}
