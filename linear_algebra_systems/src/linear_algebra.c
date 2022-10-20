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
