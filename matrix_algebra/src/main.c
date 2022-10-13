#include "../include/matrix.h"
#include <stdio.h>

int main(int argc, char **argv) {
  struct Matrix *first_matrix =
      matrix_read_from_file("../test_files/matrix_1.txt", " ");

  struct Matrix *second_matrix =
      matrix_read_from_file("../test_files/matrix_2.txt", " ");

  struct Matrix *sarrus_test_matrix =
      matrix_read_from_file("../test_files/sarrus_test_matrix.txt", " ");

  printf("First matrix: \n");

  matrix_print(first_matrix);

  printf("\n");

  printf("Second matrix: \n");

  matrix_print(second_matrix);

  printf("\n");

  struct Matrix *multiplication_result =
      matrix_multiply(first_matrix, second_matrix);

  if (multiplication_result == NULL) {
    perror("Unable to multiply matrices, check their size...\n");
  } else {
    printf("Multiplication result: \n");
    matrix_print(multiplication_result);
  }

  printf("\n");

  printf("Matrix used to calculate determinant: \n");

  matrix_print(sarrus_test_matrix);

  printf("\n");

  double sarrus3x3_result;

  int sarrus3x3_status =
      matrix_determinant_sarrus3x3(sarrus_test_matrix, &sarrus3x3_result);

  if (sarrus3x3_status == -1) {
    perror("Error while computing matrix_determinant...");
  } else {
    printf("Determinant: %.2lf\n", sarrus3x3_result);
  }

  printf("\n");

  struct Matrix *inverse_result_matrix = matrix_init(3, 3);

  matrix_inverse_3x3(sarrus_test_matrix, inverse_result_matrix);

  printf("Inversed matrix: \n\n");

  matrix_print(inverse_result_matrix);

  printf("\n");

  struct Matrix *minor_test_main =
      matrix_read_from_file("../test_files/matrix_laplace_5x5.txt", " ");

  struct Matrix *minor_test = matrix_create_minor(minor_test_main, 1, 0);
  struct Matrix *minor_test2 = matrix_create_minor(minor_test_main, 1, 1);

  printf("MINOR1: \n");

  matrix_print(minor_test);

  printf("MINOR2: \n");

  matrix_print(minor_test2);

  printf("\n");
  printf("\n");

  double laplace_determinant = matrix_laplace_determinant(minor_test_main);

  printf("\n");
  printf("Laplace determinant: %lf\n", laplace_determinant);

  struct Matrix *identity_matrix = matrix_create_identity(10);
  printf("\nIdentity matrix: \n");
  matrix_print(identity_matrix);
  printf("\n");

  matrix_free(first_matrix);
  matrix_free(second_matrix);
  matrix_free(sarrus_test_matrix);
  matrix_free(multiplication_result);
  matrix_free(inverse_result_matrix);

  matrix_free(minor_test_main);
  matrix_free(minor_test);
  matrix_free(minor_test2);
  matrix_free(identity_matrix);
  return 0;
}