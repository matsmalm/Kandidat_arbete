#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define STACKSIZE 10000

void push(int i);
int pop(void);
int empty(void);
void create(int *A, int obstacle);
write(int *matr, int ok );
int firstOne(int *matr);
int exists(int *arr, int max, int find);
int canReach(int *matr);
int test(int *matr);

// Variables to be used:
int SIZE;
int  *tos, *p1, stack[STACKSIZE];
FILE *fileOK;
FILE *fileEJOK;
int width,height;
int obstacles;

void push(int i)
{
  p1++;
  if(p1 == (tos+STACKSIZE)) {
    printf("Stack Overflow. Please increase STACKSIZE if you have very large environments.\n");
    exit(1);
  }
  *p1 = i;
}

int pop(void)
{
  if(p1 == tos) {
    printf("Stack Underflow.\n");
    exit(1);
  }
  p1--;
  return *(p1+1);
}

int empty(void){
	if (p1==tos){
		return 1;
	}else return 0;
}

void create(int *A, int obstacle) {
	int i = 1,j=0;
	A[0]=0;
	for(i=1;i<=SIZE;i++){
		A[i]=1;
	}
	for(i=1;i<=obstacle;i++){
		do{
			j = (1+(int)((double)rand() / ((double)RAND_MAX + 1) * SIZE));
			if(A[j]==1){
				A[j]=0;
				break;
			}
		}while (1==1);
	}
	if(test(A)==0){
		write(A, 0);
	}else{
		write(A,1);
	}
}
write(int *matr, int ok ){
	int i,j;
	if(ok==1){
		fprintf(fileOK, "Works: \n");
		for(i=0;i<height;i++){
			for(j=1;j<=width;j++){
				fprintf(fileOK, "%d", matr[i*width+j]);
				if(j!=(width)){
					fprintf(fileOK, " ");
				}
			}
			if(i!=(height-1)){
				fprintf(fileOK, "\n");
			}
		}
		fprintf(fileOK, "\n\n");
	}else{
		fprintf(fileEJOK, "Does not work: \n");
		for(i=0;i<height;i++){
			for(j=1;j<=width;j++){
				fprintf(fileEJOK, "%d", matr[i*width+j]);
				if(j!=(width)){
					fprintf(fileEJOK, " ");
				}
			}
			if(i!=(height-1)){
				fprintf(fileEJOK, "\n");
			}
		}
		fprintf(fileEJOK, "\n\n");
	}
}
int firstOne(int *matr){
	int i=1;
	while(matr[i]!=1){
		i++;
	}
	return i;
}
int exists(int *arr, int max, int find){
	int i;
	for(i=0;i<=max;i++){
		if(find==arr[i]){
			return 1;
		}
	}
	return 0;
}
int canReach(int *matr){
	int pos = firstOne(&(*matr));
	int x;
	tos=stack;
	p1=stack;
	int reachSize=SIZE*2;
	int canReach[reachSize];
	int i=1,reachMax=0;
	for(i=0;i<reachSize;i++){
		canReach[i]=NULL;
	}
	push(pos);
	while(1==1){
		x=pop();
		if(exists(canReach,reachMax,x)==0){
			canReach[reachMax]=x;
			reachMax++;
		}
		/* Fetch neighbour not in canReach */
		int c=x%width;
		int r=(1+(x-c)/width);
		if((matr[x-1]==1) && (x%width!=1)){ // Not left edge.
			if(exists(canReach,reachMax,(x-1))==0){
				push(x-1);
			}
		}
		if((matr[x+1]==1) && (x%width!=0)){ // Not right edge.
			if(exists(canReach,reachMax,(x+1))==0){
				push(x+1);
			}
		}
		if(x>width){ // Not first row
			if(matr[x-width]==1){ // On top.
				if(exists(canReach,reachMax,(x-width))==0){
					push(x-width);
				}
			}
		}
		if(x<=(height-1)*width){ // Not last row
			if(matr[x+width]==1){ // Below.
				if(exists(canReach,reachMax,(x+width))==0){
					push(x+width);
				}
			}
		}
		if(empty()==1){
			break;
		}
	}
	int g=0,tot=0;
	while(g<reachMax){
		tot++;
		g++;
	}
	return tot;
}
int test(int *matr){
	if(canReach(matr) < (SIZE-obstacles)){
		return 0;
	}
	return 1;
}

int main(){
	fileOK=fopen("OK.txt", "a+");
	fileEJOK=fopen("notOK.txt", "a+");
	
	height=20;// Set number of rows
	width=20;// Set number of columns
	obstacles=100;// Set number of obstacles
	SIZE = (width*height);
	int A[SIZE];
	int antal=20; // Number of matrices to be created
	int rad=0,col=0,rep=0; // Used in loops
	srand(time(0)); // Resets random.
	int z = 0;
	for(z=0;z<antal;z++){
		create(A, obstacles);
	}
	fclose(fileOK);
	fclose(fileEJOK);
	return EXIT_SUCCESS;
}