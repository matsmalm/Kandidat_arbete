
#include "Header.h"
#include "genetic.h"
#include "greedy.h"

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
FILE *fr = NULL;
int ROWS=0,COLS=0;
struct Node B[SIZE][SIZE];


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
	Hunters[0] = 2;
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
	while(readFromFile() != -1){
		numMatrices++;
		place();
		int Hunters[21];
		memset(Hunters,0,sizeof(Hunters));	
	       	getStartPositions(Hunters);

		int BREAK = 10;
		int Hunter_static[]={2,2,0,4,4};
		/****
		Here we should be able to call our algorithms, since B will contain the graph network.
		****/
		int i;
		for(i = Hunters[0];i>1;i--){
			Hunters[0] = i;
			printf("Pursuers: %d\n", Hunters[0]);
			/*** Genetic ***/
			//printf("Genetic\n");
			/*			int geneticSolution[2*(1+Hunters[0]*1000)];
			preGenetic(&B, &Hunters, BREAK, ROWS, COLS);
			genAlg(geneticSolution, &Hunters); // Main Genetic Algorithm program.
			if(geneticSolution[1]<0)
				printf("No solution found for %d pursuers\n", geneticSolution[0]);
			else{
				printf("Using %d pursuers, a solution of %d steps was obtained:\n", geneticSolution[0], geneticSolution[1]);
				//int i;
				//for(i=2;i<=2*(geneticSolution[0]+geneticSolution[0]*geneticSolution[1]);i+=2)
					//printf(" (%d,%d)", geneticSolution[i], geneticSolution[i+1]);
				//printf("\n");
			}
			//printf("Genetic completed\n");*/
			/*** Greedy ***/
			printf("Greedy\n");
			struct greedy start=preGreedy(B, &Hunter_static, &BREAK);
			greedyAlg(&start);
			//printf("Greedy completed\n");		
			/*** Tabu ***/
		}
	}
	printf("There were %d matrices in input file.\n", numMatrices);
	fclose (fr); // Close file once.
	printf("End main\n");
	printf("End\n");
	return EXIT_SUCCESS;
}
