#include "../include/linear_algebra.h"
#include "../include/matrix.h"
#include <stdio.h>

struct Matrix *inverse_matrix_method(struct Matrix *matrix,
                                     struct Matrix *constant_terms) {
  struct Matrix *inverse_matrix = matrix_init(matrix->rows, matrix->cols);

  int inverse_matrix_result = matrix_inverse_3x3(matrix, inverse_matrix);

  matrix_print(inverse_matrix);

  if (inverse_matrix_result == -1) {
    perror("invese_matrix_result");
    exit(1);
  }

  struct Matrix *result_matrix =
      matrix_multiply(inverse_matrix, constant_terms);

  matrix_free(inverse_matrix);

  return result_matrix;
}

struct Matrix *cramer_method_helper_substitute_matrix(
    struct Matrix *matrix, struct Matrix *constant_terms, int column) {
  struct Matrix *result = matrix_init(matrix->rows, matrix->cols);

  for (size_t i = 0; i < result->rows; i++) {
    for (size_t j = 0; j < result->cols; j++) {
      result->data[i][j] = matrix->data[i][j];
    }
  }

  for (size_t i = 0; i < result->rows; i++) {
    result->data[i][column] = constant_terms->data[i][0];
  }

  return result;
}

struct Matrix *cramer_method(struct Matrix *matrix,
                             struct Matrix *constant_terms) {
  double matrix_determinant = matrix_laplace_determinant(matrix);

  struct Matrix *result = matrix_init(matrix->rows, 1);

  for (size_t i = 0; i < constant_terms->rows; i++) {
    struct Matrix *substituted_matrix =
        cramer_method_helper_substitute_matrix(matrix, constant_terms, i);

    printf("Substituted matrix, N: %ld\n", i);
    matrix_print(substituted_matrix);
    printf("\n");

    result->data[i][0] =
        matrix_laplace_determinant(substituted_matrix) / matrix_determinant;

    matrix_free(substituted_matrix);
  }

  return result;
}
