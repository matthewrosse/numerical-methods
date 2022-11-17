#include "../include/linear_algebra.h"
#include "../include/lu_distribution.h"
#include "../include/matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  struct Matrix *matrix =
      matrix_read_from_file("../test_files/cwiczenie1_macierz.txt", " ");

  printf("Matrix: \n");
  matrix_print(matrix);
  printf("\n");
  printf("-------------------------------------\n");
  printf("\n");

  struct Matrix **lu_result = lu_distribution(matrix);

  printf("L: \n");
  matrix_print(lu_result[0]);
  printf("\n");
  printf("U: \n");
  matrix_print(lu_result[1]);
  printf("\n");

  matrix_free(lu_result[0]);
  matrix_free(lu_result[1]);
  free(lu_result);

  matrix_free(matrix);

  return 0;
}
