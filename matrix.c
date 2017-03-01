#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m
Returns:

print the matrix
*/
void print_matrix(struct matrix *m) {
    int x;
    int y;
    for (x = 0; x < m->rows; x++) {
        printf("|");
        for (y = 0; y < m->cols; y++) {
            double temp = m->m[x][y];
            printf(" %.2lf ", temp);
        }
        printf("|\n");
    }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns:

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
    int x;
    int y;
    for (x = 0; x < m->rows; x++) {
        for (y = 0; y < m->cols; y++) {
            if (y == x) {
                m->m[x][y] = 1;
            }
            else {
                m->m[x][y] = 0;
            }
        }
    }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m
Returns:

multiply each element of m by x
*/
void scalar_mult(double num, struct matrix *m) {
    int x;
    int y;
    for (x = 0; x < m->rows; x++) {
        for (y = 0; y < m->cols; y++) {
            m->m[x][y] = (num * m->m[x][y]);
        }
    }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
    int x;
    int y;
    int z;
    double num = 0.0;
    struct matrix *ans;
    ans = new_matrix(b->rows, b->cols);
    for (x = 0; x < b->rows; x++) {
        for (y = 0; y < b->cols; y++) {
            for (z = 0; z < a->rows; z++) {
                num += a->m[x][z] * b->m[z][y];
            }
            ans->m[x][y] = num;
        }
    }

    copy_matrix(ans, b);
    free_matrix(ans);
}


/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols
Returns:

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m
Returns:

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols
Returns:

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {

  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++)
    for (c=0; c < a->cols; c++)
      b->m[r][c] = a->m[r][c];
}
