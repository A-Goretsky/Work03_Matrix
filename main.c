#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  struct matrix *edges;
  struct matrix *identityTest;

  struct matrix *test1, *test2, *test3;

  identityTest = new_matrix(3, 3);
  edges = new_matrix(4, 4);
  test1 = new_matrix(4, 4);
  test2 = new_matrix(4, 7);
  test3 = new_matrix(4, 4);
  //printf("~~~Testing print_matrix~~~\n");
  //print_matrix(edges);
  //printf("\n");
  printf("~~~Testing ident~~~\n");
  ident(edges);
  print_matrix(edges);
  printf("\n");
  printf("~~~Testing ident 2~~~\n");
  identityTest = new_matrix(3, 3);
  ident(identityTest);
  print_matrix(identityTest);
  printf("\n");
  printf("~~~Testing scalar_mult~~~\n");
  printf("Populating Random Matrix:\n");
  //populating random matrix
  int x, y;
  int num = 0;
  for (x = 0; x < test1->rows; x++) {
      for (y = 0; y < test1->cols; y++) {
          num = rand() % 100;
          test1->m[x][y] = num;
      }
  }
  print_matrix(test1);
  printf("\n");

  //testing scalar_mult;
  printf("Multiply matrix by 4\n");
  scalar_mult(4, test1);
  print_matrix(test1);
  printf("\n");

  printf("Multiply matrix by identity matrix\n");
  matrix_mult(test1, edges);
  print_matrix(edges);
  printf("\n");

  printf("Populating Second Random Matrix\n");
  int x1;
  int y1;
  int num1;
  for (x1 = 0; x1 < test2->rows; x1++) {
      for (y1 = 0; y1 < test2->cols; y1++) {
          num1 = rand() % 100;
          test2->m[x1][y1] = num1;
      }
  }

  print_matrix(test2);
  printf("\n");

  printf("Product of random matrices:\n");
  matrix_mult(test1, test2);
  print_matrix(test2);

  //DRAWING TIME
  color c;
  c.red = 106;
  c.green = 90;
  c.blue = 205;

  color c1;
  c1.red = 250;
  c1.green = 40;
  c1.blue = 50;
  clear_screen(s);

  printf("\n");
  struct matrix *drawing = new_matrix(4, 4);
  drawing->lastcol = 0;
  struct matrix *drawing1 = new_matrix(4, 4);
  drawing1->lastcol = 0;
  for (int i = 0; i < 25; i++) {
      add_edge(drawing, 0, 0, 0, XRES, 20 * i, 0);
      //add_edge(p2, XRES, YRES-20*i, 0, 20*i, YRES, 0);
  }
  for (int i = 0; i < 25; i++) {
      add_edge(drawing1, XRES, YRES, 0, 0, 20 * i, 0);
      //add_edge(p2, XRES, YRES-20*i, 0, 20*i, YRES, 0);
  }
  //add_edge(drawing1, 0, 500, 0, 500, 0, 0);
  draw_lines(drawing1, s, c1);
  //add_edge(drawing, 0, 0, 0, 150, 150, 200);
  print_matrix(drawing);
  draw_lines(drawing, s, c);
  display(s);
  save_extension(s, "image.png");

  //free_matrix(drawing);
  free_matrix(identityTest);
}
