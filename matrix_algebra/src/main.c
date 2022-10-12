#include "../include/matrix.h"
#include <stdio.h>

int main(int argc, char **argv) {
  struct Matrix *first_matrix = matrix_init(5, 5);
  struct Matrix *second_matrix = matrix_init(5, 5);

  double first_data[5][5] = {
      {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5},
      {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5},
  };

  double second_data[5][5] = {
      {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5},
      {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5},
  };

  matrix_zero(first_matrix);
  matrix_zero(second_matrix);

  matrix_fill(first_matrix, first_data);
  matrix_fill(second_matrix, second_data);

  printf("Filled first matrix: \n");

  matrix_print(first_matrix);
  printf("\n");
  printf("Filled second matrix: \n");

  matrix_print(second_matrix);

  matrix_free(first_matrix);
  matrix_free(second_matrix);
  return 0;
}