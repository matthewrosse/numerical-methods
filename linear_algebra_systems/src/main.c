#include "../include/linear_algebra.h"
#include "../include/matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  struct Matrix *matrix =
      matrix_read_from_file("../test_files/cwiczenie1_macierz.txt", " ");
  struct Matrix *constant_terms =
      matrix_read_from_file("../test_files/cwiczenie1_wyrazy_wolne.txt", " ");

  printf("First matrix: \n");
  matrix_print(matrix);

  printf("Constant terms: \n");
  matrix_print(constant_terms);

  struct Matrix *matrix_result_inverse_matrix =
      inverse_matrix_method(matrix, constant_terms);

  printf("Matrix result inverse matrix: \n");
  matrix_print(matrix_result_inverse_matrix);

  matrix_free(matrix);
  matrix_free(constant_terms);
  matrix_free(matrix_result_inverse_matrix);
  return 0;
}
