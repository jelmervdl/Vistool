#include "tools.h"

void PrintMat(CvMat *A){
  int i, j;
  for (i = 0; i < A->rows; i++)
    {
      printf("\n"); 
      switch (CV_MAT_DEPTH(A->type))
	{
	case CV_32F:
	case CV_64F:
	  for (j = 0; j < A->cols; j++)
	    printf ("%8.3f ", (float)cvGetReal2D(A, i, j));
	  break;
	case CV_8U:
	case CV_16U:
	  for(j = 0; j < A->cols; j++)
	    printf ("%6d",(int)cvGetReal2D(A, i, j));
	  break;
	default:
	  break;
	}
    }
  printf("\n");
}
