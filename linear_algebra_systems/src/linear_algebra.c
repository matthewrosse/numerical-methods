#include "../include/linear_algebra.h"
#include "../include/matrix.h"
#include <stdio.h>

struct Matrix *inverse_matrix_method(struct Matrix *matrix,
                                     struct Matrix *constant_terms) {
  struct Matrix *inverse_matrix = matrix_init(matrix->rows, matrix->cols);

  int inverse_matrix_result = matrix_inverse_3x3(matrix, inverse_matrix);

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

struct Matrix *gauss_elimination_method(struct Matrix *matrix,
                                        struct Matrix *constant_terms) {
  struct Matrix **upper_triangular_result =
      matrix_get_upper_triangular(matrix, constant_terms);

  struct Matrix *upper_triangular_matrix = upper_triangular_result[0];
  struct Matrix *upper_triangular_constant_terms = upper_triangular_result[1];

  struct Matrix *result =
      matrix_init(constant_terms->rows, constant_terms->cols);

  int n = (int)constant_terms->rows;

  for (int i = n - 1; i >= 0; i--) {
    result->data[i][0] = upper_triangular_constant_terms->data[i][0];

    for (int j = i + 1; j < n; j++) {
      result->data[i][0] -=
          upper_triangular_matrix->data[i][j] * result->data[j][0];
    }

    result->data[i][0] =
        result->data[i][0] / upper_triangular_matrix->data[i][i];
  }

  matrix_free(upper_triangular_result[0]);
  matrix_free(upper_triangular_result[1]);
  free(upper_triangular_result);

  return result;
}

struct Matrix *matrix_clone(struct Matrix *matrix) {
  struct Matrix *result = matrix_init(matrix->rows, matrix->cols);

  for (size_t i = 0; i < result->rows; i++) {
    for (size_t j = 0; j < result->cols; j++) {
      result->data[i][j] = matrix->data[i][j];
    }
  }

  return result;
}

struct Matrix **matrix_get_upper_triangular(struct Matrix *matrix,
                                            struct Matrix *constant_terms) {
  struct Matrix **result_array =
      (struct Matrix **)malloc(sizeof(struct Matrix *) * 2);

  struct Matrix *cloned_matrix = matrix_clone(matrix);
  struct Matrix *cloned_constant_terms = matrix_clone(constant_terms);

  // jest kwadratowa
  size_t n = cloned_matrix->rows;

  double multiplier = 0;

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (j > i) {
        multiplier = cloned_matrix->data[j][i] / cloned_matrix->data[i][i];

        for (size_t k = i; k < n + 1; k++) {
          if (k != n) {
            cloned_matrix->data[j][k] = cloned_matrix->data[j][k] -
                                        multiplier * cloned_matrix->data[i][k];
          } else {
            cloned_constant_terms->data[j][0] =
                cloned_constant_terms->data[j][0] -
                multiplier * cloned_constant_terms->data[i][0];
          }
        }
      }
    }
  }

  result_array[0] = cloned_matrix;
  result_array[1] = cloned_constant_terms;

  return result_array;
}

void linear_equation_print_result(struct Matrix *matrix) {
  for (size_t i = 0; i < matrix->rows; i++) {
    printf("x%ld = %.2lf\n", i + 1, matrix->data[i][0]);
  }
}
