/*
function [assignment, cost] = assignmentoptimal(distMatrix)
*/
/*
source code taken from: http://www.mathworks.com/matlabcentral/fileexchange/6543
Using the functions from C:
(1)-The mex-files always contain a function called "mexFunction" that is needed for MATLAB and a function called "assignment_xx". You can use the second if you want to apply the algorithms directly from C. If you do not have MATLAB installed, you have to replace the mx-functions (e.g. mxCalloc) by ordinary C-functions and delete the two include lines.
(2)-If you decide to use the functions in C, you might need the column indices to start from 0, not from 1 as in MATLAB. Just delete the definition of ONE_INDEXING and you are done. If you do not need to handle infinite values in your applications, also delete the definition of CHECK_FOR_INF.
(3)-Two more points to take care of when using C: The assignment vector is defined as a double precision array, as MATLAB uses double precision values anyway. When referencing elements with the computed assignment vector in C, you have to change all function declarations to use integer values. Further, the distance or cost matrix of size MxN is defined as a double precision array of N*M elements. Matrices are saved MATLAB-internally in row-order (i.e. the matrix [1 2; 3 4] will be stored as a vector [1 3 2 4], NOT [1 2 3 4]).
 */

//(1)#include <mex.h>
//(1)#include <matrix.h>
//(2)#define CHECK_FOR_INF
//(2)#define ONE_INDEXING
#include "Header.h"

#define true 1
#define false 0
#define infinity 9999

void assignmentoptimal(/*(3)double*/int *assignment, /*(3)double*/int *cost, /*(3)double*/int *distMatrix, int nOfRows, int nOfColumns);
void buildassignmentvector(/*(3)double*/int *assignment, /*(3)bool*/ int *starMatrix, int nOfRows, int nOfColumns);
void computeassignmentcost(/*(3)double*/int *assignment, /*(3)double*/int *cost, /*(3)double*/int *distMatrix, int nOfRows);
void step2a(/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim);
void step2b(/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim);
void step3 (/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim);
void step4 (/*(3)double*/int *assignment,/*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col);
void step5 (/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim);
/*
(1)void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
(1){
(1)/*(3)double*//*int *assignment, *cost, *distMatrix;
(1)	int nOfRows, nOfColumns;
(1)	
(1)*//* Input arguments *//*
(1)	nOfRows    = mxGetM(prhs[0]); //byta detta mot ett känt tal?
(1)	nOfColumns = mxGetN(prhs[0]); //byta detta mot ett känt tal?
(1)	distMatrix = mxGetPr(prhs[0]); // byta detta mot kända tal från hashtable?
(1)	
(1)*//* Output arguments *//*
(1)	plhs[0]    = mxCreateDoubleMatrix(nOfRows, 1, mxREAL);
(1)	plhs[1]    = mxCreateDoubleScalar(0);
(1)	assignment = mxGetPr(plhs[0]);
(1)	cost       = mxGetPr(plhs[1]);
(1)	
(1)*//* Call C-function *//*
(1)	assignmentoptimal(assignment, cost, distMatrix, nOfRows, nOfColumns);	
(1)}
*/
void assignmentoptimal(/*(3)double*/int *assignment, /*(3)double*/int *cost, /*(3)double*/int *distMatrixIn, int nOfRows, int nOfColumns)
{
	/*(3)double*/int *distMatrix, *distMatrixTemp, *distMatrixEnd, *columnEnd, value, minValue;
	/*(3)bool*/ int *coveredColumns, *coveredRows, *starMatrix, *newStarMatrix, *primeMatrix;
	int nOfElements, minDim, row, col;
	//#ifdef CHECK_FOR_INF
	//	/*(3)bool*/ int infiniteValueFound;
	//	/*(3)double*/int maxFiniteValue, infValue;
	//#endif
	printf("assignmentoptmal\n");
	/* initialization */
	*cost = 0;
	for(row=0; row<nOfRows; row++)
	  //#ifdef ONE_INDEXING
	  //		assignment[row] =  0.0;
	  //#else
		assignment[row] = -1.0;
	//#endif
	
	/* generate working copy of distance Matrix */
	/* check if all matrix elements are positive */
	nOfElements   = nOfRows * nOfColumns;
	//	distMatrix    = (/*(3)double*/int *)/*(1)mxM*/malloc(nOfElements * sizeof(/*(3)double*/int));
	distMatrix    = (int *)malloc(nOfElements * sizeof(int)); //samma som rad ovanför, utan massa inline kommentarer...
	distMatrixEnd = distMatrix + nOfElements;
	for(row=0; row<nOfElements; row++)
	{
		value = distMatrixIn[row];
		//	if(mxIsFinite(value) && (value < 0))
		//	mexErrMsgTxt("All matrix elements have to be non-negative.");
		distMatrix[row] = value;
	}

	/*#ifdef CHECK_FOR_INF*/
	/* check for infinite values */
	/*	maxFiniteValue     = -1;
	infiniteValueFound = false;
	
	distMatrixTemp = distMatrix;
	while(distMatrixTemp < distMatrixEnd)
	{
		value = *distMatrixTemp++;
		if(mxIsFinite(value))
		{
			if(value > maxFiniteValue)
				maxFiniteValue = value;
		}
		else
			infiniteValueFound = true;
	}
	if(infiniteValueFound)
	{
		if(maxFiniteValue == -1) /* all elements are infinite */
			return;
		
		/* set all infinite elements to big finite value */
		/*	if(maxFiniteValue > 0)
			infValue = 10 * maxFiniteValue * nOfElements;
		else
			infValue = 10;
		distMatrixTemp = distMatrix;
		while(distMatrixTemp < distMatrixEnd)
			if(mxIsInf(*distMatrixTemp++))
				*(distMatrixTemp-1) = infValue;
	}
	#endif*/
				
	/* memory allocation */
	coveredColumns = (/*(3)bool*/ int *)/*(1)mxC*/calloc(nOfColumns,  sizeof(/*(3)bool*/ int));
	coveredRows    = (/*(3)bool*/ int *)/*(1)mxC*/calloc(nOfRows,     sizeof(/*(3)bool*/ int));
	starMatrix     = (/*(3)bool*/ int *)/*(1)mxC*/calloc(nOfElements, sizeof(/*(3)bool*/ int));
	primeMatrix    = (/*(3)bool*/ int *)/*(1)mxC*/alloc(nOfElements, sizeof(/*(3)bool*/ int));
	newStarMatrix  = (/*(3)bool*/ int *)/*(1)mxC*/calloc(nOfElements, sizeof(/*(3)bool*/ int)); /* used in step4 */

	/* preliminary steps */
	if(nOfRows <= nOfColumns)
	{
		minDim = nOfRows;
		
		for(row=0; row<nOfRows; row++)
		{
			/* find the smallest element in the row */
			distMatrixTemp = distMatrix + row;
			minValue = *distMatrixTemp;
			distMatrixTemp += nOfRows;			
			while(distMatrixTemp < distMatrixEnd)
			{
				value = *distMatrixTemp;
				if(value < minValue)
					minValue = value;
				distMatrixTemp += nOfRows;
			}
			
			/* subtract the smallest element from each element of the row */
			distMatrixTemp = distMatrix + row;
			while(distMatrixTemp < distMatrixEnd)
			{
				*distMatrixTemp -= minValue;
				distMatrixTemp += nOfRows;
			}
		}
		
		/* Steps 1 and 2a */
		for(row=0; row<nOfRows; row++)
			for(col=0; col<nOfColumns; col++)
				if(distMatrix[row + nOfRows*col] == 0)
					if(!coveredColumns[col])
					{
						starMatrix[row + nOfRows*col] = true;
						coveredColumns[col]           = true;
						break;
					}
	}
	else /* if(nOfRows > nOfColumns) */
	{
		minDim = nOfColumns;
		
		for(col=0; col<nOfColumns; col++)
		{
			/* find the smallest element in the column */
			distMatrixTemp = distMatrix     + nOfRows*col;
			columnEnd      = distMatrixTemp + nOfRows;
			
			minValue = *distMatrixTemp++;			
			while(distMatrixTemp < columnEnd)
			{
				value = *distMatrixTemp++;
				if(value < minValue)
					minValue = value;
			}
			
			/* subtract the smallest element from each element of the column */
			distMatrixTemp = distMatrix + nOfRows*col;
			while(distMatrixTemp < columnEnd)
				*distMatrixTemp++ -= minValue;
		}
		
		/* Steps 1 and 2a */
		for(col=0; col<nOfColumns; col++)
			for(row=0; row<nOfRows; row++)
				if(distMatrix[row + nOfRows*col] == 0)
					if(!coveredRows[row])
					{
						starMatrix[row + nOfRows*col] = true;
						coveredColumns[col]           = true;
						coveredRows[row]              = true;
						break;
					}
		for(row=0; row<nOfRows; row++)
			coveredRows[row] = false;
		
	}	
	
	/* move to step 2b */
	step2b(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);

	/* compute cost and remove invalid assignments */
	computeassignmentcost(assignment, cost, distMatrixIn, nOfRows);
	
	/* free allocated memory */
	/*(1)mxF*/free(distMatrix);
	/*(1)mxF*/free(coveredColumns);
	/*(1)mxF*/free(coveredRows);
	/*(1)mxF*/free(starMatrix);
	/*(1)mxF*/free(primeMatrix);
	/*(1)mxF*/free(newStarMatrix);

	return;
}

/********************************************************/
void buildassignmentvector(/*(3)double*/int *assignment, /*(3)bool*/ int *starMatrix, int nOfRows, int nOfColumns)
{
	int row, col;
	  printf("in buildassignmentvector\n");
	for(row=0; row<nOfRows; row++)
		for(col=0; col<nOfColumns; col++)
			if(starMatrix[row + nOfRows*col])
			{
#ifdef ONE_INDEXING
				assignment[row] = col + 1; /* MATLAB-Indexing */
#else
				assignment[row] = col;
#endif
				break;
			}
}

/********************************************************/
void computeassignmentcost(/*(3)double*/int *assignment, /*(3)double*/int *cost, /*(3)double*/int *distMatrix, int nOfRows)
{
  printf("in computeassignmentcost\n");
	int row, col;
#ifdef CHECK_FOR_INF
	/*(3)double*/int value;
#endif
	
	for(row=0; row<nOfRows; row++)
	{
#ifdef ONE_INDEXING
		col = assignment[row]-1; /* MATLAB-Indexing */
#else
		col = assignment[row];
#endif

		if(col >= 0)
		{
#ifdef CHECK_FOR_INF
			value = distMatrix[row + nOfRows*col];
			if(mxIsFinite(value))
				*cost += value;
			else
#ifdef ONE_INDEXING
				assignment[row] =  0.0;
#else
				assignment[row] = -1.0;
#endif

#else
			*cost += distMatrix[row + nOfRows*col];
#endif
		}
	}
}

/********************************************************/
void step2a(/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim)
{
	/*(3)bool*/ int *starMatrixTemp, *columnEnd;
	int col;
  printf("in step 2a\n");	
	/* cover every column containing a starred zero */
	for(col=0; col<nOfColumns; col++)
	{
		starMatrixTemp = starMatrix     + nOfRows*col;
		columnEnd      = starMatrixTemp + nOfRows;
		while(starMatrixTemp < columnEnd){
			if(*starMatrixTemp++)
			{
				coveredColumns[col] = true;
				break;
			}
		}	
	}

	/* move to step 3 */
	step2b(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

/********************************************************/
void step2b(/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim)
{
	int col, nOfCoveredColumns;
	  printf("in step 2b\n");
	/* count covered columns */
	nOfCoveredColumns = 0;
	for(col=0; col<nOfColumns; col++)
		if(coveredColumns[col])
			nOfCoveredColumns++;
			
	if(nOfCoveredColumns == minDim)
	{
		/* algorithm finished */
		buildassignmentvector(assignment, starMatrix, nOfRows, nOfColumns);
	}
	else
	{
		/* move to step 3 */
		step3(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
	}
	
}

/********************************************************/
void step3(/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim)
{
  printf("in step 3\n");
	/*(3)bool*/ int zerosFound;
	int row, col, starCol;

	zerosFound = true;
	while(zerosFound)
	{
		zerosFound = false;		
		for(col=0; col<nOfColumns; col++)
			if(!coveredColumns[col])
				for(row=0; row<nOfRows; row++)
					if((!coveredRows[row]) && (distMatrix[row + nOfRows*col] == 0))
					{
						/* prime zero */
						primeMatrix[row + nOfRows*col] = true;
						
						/* find starred zero in current row */
						for(starCol=0; starCol<nOfColumns; starCol++)
							if(starMatrix[row + nOfRows*starCol])
								break;
						
						if(starCol == nOfColumns) /* no starred zero found */
						{
							/* move to step 4 */
							step4(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim, row, col);
							return;
						}
						else
						{
							coveredRows[row]        = true;
							coveredColumns[starCol] = false;
							zerosFound              = true;
							break;
						}
					}
	}
	
	/* move to step 5 */
	step5(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

/********************************************************/
void step4(/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col)
{	
  printf("in step 4\n");
	int n, starRow, starCol, primeRow, primeCol;
	int nOfElements = nOfRows*nOfColumns;
	
	/* generate temporary copy of starMatrix */
	for(n=0; n<nOfElements; n++)
		newStarMatrix[n] = starMatrix[n];
	
	/* star current zero */
	newStarMatrix[row + nOfRows*col] = true;

	/* find starred zero in current column */
	starCol = col;
	for(starRow=0; starRow<nOfRows; starRow++)
		if(starMatrix[starRow + nOfRows*starCol])
			break;

	while(starRow<nOfRows)
	{
		/* unstar the starred zero */
		newStarMatrix[starRow + nOfRows*starCol] = false;
	
		/* find primed zero in current row */
		primeRow = starRow;
		for(primeCol=0; primeCol<nOfColumns; primeCol++)
			if(primeMatrix[primeRow + nOfRows*primeCol])
				break;
								
		/* star the primed zero */
		newStarMatrix[primeRow + nOfRows*primeCol] = true;
	
		/* find starred zero in current column */
		starCol = primeCol;
		for(starRow=0; starRow<nOfRows; starRow++)
			if(starMatrix[starRow + nOfRows*starCol])
				break;
	}	

	/* use temporary copy as new starMatrix */
	/* delete all primes, uncover all rows */
	for(n=0; n<nOfElements; n++)
	{
		primeMatrix[n] = false;
		starMatrix[n]  = newStarMatrix[n];
	}
	for(n=0; n<nOfRows; n++)
		coveredRows[n] = false;
	
	/* move to step 2a */
	step2a(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

/********************************************************/
void step5(/*(3)double*/int *assignment, /*(3)double*/int *distMatrix, /*(3)bool*/ int *starMatrix, /*(3)bool*/ int *newStarMatrix, /*(3)bool*/ int *primeMatrix, /*(3)bool*/ int *coveredColumns, /*(3)bool*/ int *coveredRows, int nOfRows, int nOfColumns, int minDim)
{
	/*(3)double*/int h, value;
	int row, col;
	printf("in step five \n");	
	/* find smallest uncovered element h */
	h = infinity;//mxGetInf();	
	for(row=0; row<nOfRows; row++)
		if(!coveredRows[row])
			for(col=0; col<nOfColumns; col++)
				if(!coveredColumns[col])
				{
					value = distMatrix[row + nOfRows*col];
					if(value < h)
						h = value;
				}
	
	/* add h to each covered row */
	for(row=0; row<nOfRows; row++)
		if(coveredRows[row])
			for(col=0; col<nOfColumns; col++)
				distMatrix[row + nOfRows*col] += h;
	
	/* subtract h from each uncovered column */
	for(col=0; col<nOfColumns; col++)
		if(!coveredColumns[col])
			for(row=0; row<nOfRows; row++)
				distMatrix[row + nOfRows*col] -= h;
	
	/* move to step 3 */
	step3(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

