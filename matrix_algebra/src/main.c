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

  struct Matrix *sarrus_test_matrix = matrix_init(3, 3);

  double sarrus3x3_data[3][3] = {{1, 3, 2}, {4, -1, 2}, {1, -1, 0}};

  matrix_fill(sarrus_test_matrix, sarrus3x3_data);

  matrix_zero(first_matrix);
  matrix_zero(second_matrix);

  matrix_fill(first_matrix, first_data);
  matrix_fill(second_matrix, second_data);

  printf("Filled first matrix: \n");

  matrix_print(first_matrix);
  printf("\n");
  printf("Filled second matrix: \n");

  matrix_print(second_matrix);

  struct Matrix *multiplication_result =
      matrix_multiply(first_matrix, second_matrix);

  if (multiplication_result == NULL) {
    perror("Unable to multiply matrices, check their size...");
  } else {
    printf("Multiplication result: \n");
    matrix_print(multiplication_result);
  }

  double sarrus3x3_result;

  int sarrus3x3_status =
      matrix_determinant_sarrus3x3(sarrus_test_matrix, &sarrus3x3_result);

  printf("\n");

  if (sarrus3x3_status == -1) {
    perror("Error while computing matrix_determinant...");
  } else {
    printf("Determinant: %.2lf", sarrus3x3_result);
  }

  struct Matrix *inverse_result_matrix = matrix_init(3, 3);

  matrix_inverse_3x3(sarrus_test_matrix, inverse_result_matrix);

  printf("Inversed matrix: \n\n");

  matrix_print(inverse_result_matrix);

  matrix_free(first_matrix);
  matrix_free(second_matrix);
  matrix_free(multiplication_result);
  matrix_free(sarrus_test_matrix);
  return 0;
}