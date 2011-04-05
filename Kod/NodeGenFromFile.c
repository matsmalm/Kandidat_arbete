
#include "Header.h"

#define SIZE 10 // Set to at least the maximum size of your environments, 1024 (1024^2 nodes) should be enough. Bigger SIZE means longer computation time.
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


struct Path{
	int path[10];
};

void place() {
	int i=0, j=0;
	for(i=0;i<5;i++){
			for(j=0;j<5;j++){
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
	for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				if(A[i][j]==1){
					setVision(&B[i][j]);
				}
			}
	}
}
void setMove(struct Node *b){
	int i = (*b).name[0];
	int j = (*b).name[1];
	if(j>0 && A[i][j-1]==1){ //Left
		//(*b).left=1;
		(*b).move[LEFT]=(&(*getMove(b,LEFT)));
	}else{
		//(*b).left=0;
		(*b).move[LEFT]=NULL;
	}
	if(j<4 && A[i][j+1]==1){ //Right
		//(*b).right=1;
		(*b).move[RIGHT]=(&(*getMove(b,RIGHT)));
	}else{
		//(*b).right=0;
		(*b).move[RIGHT]=NULL;
	}
	if(i>0 && A[i-1][j]==1){ //Up
		//(*b).up=1;
		(*b).move[UP]=(&(*getMove(b,UP)));
	}else{
		//(*b).up=0;
		(*b).move[UP]=NULL;
	}
	if(i<4 && A[i+1][j]==1){ //Down
		//(*b).down=1;
		(*b).move[DOWN]=(&(*getMove(b,DOWN)));
	}else{
		//(*b).down=0;
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
	if((*b).move[RIGHT]==NULL){
		int s=0;
		return s;
	}else{
		int s = getRight(getMove(&(*b), RIGHT))+1;
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
	while ( fgets ( line, sizeof line, fr ) != NULL ) /* read a line */
	{
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
int main() {
	srand(time(0)); // Resets random.
	fr = fopen("OK.txt", "r"); // Open file once
	int numMatrices=0;
	while(readFromFile() != -1){
		numMatrices++;
		place();
		int NUM_PUR = 3;
		int Hunters[] = {NUM_PUR, 0, 0, 1, 2, 1,1};
		int BREAK = 1;
		/****
		 Here we should be able to call our algorithms, since B will contain the graph network.
		 ****/

		preGenetic(B, Hunters, BREAK);
		genAlg(); // Main Genetic Algorithm program.
		
		printf("start greedy: \n");
		preGreedy(B, Hunters, BREAK);
		greedyAlg(B, Hunters, BREAK);


}


	printf("There were %d matrices in input file.\n", numMatrices);
	fclose (fr); // Close file once.
	printf("End main\n");
	return EXIT_SUCCESS;

}
