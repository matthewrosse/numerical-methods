#include "../include/matrix.h"
#include <stdio.h>

struct Matrix *matrix_init(const size_t n_rows, const size_t n_cols) {
  struct Matrix *matrix = malloc(sizeof(struct Matrix));
  matrix->rows = n_rows;
  matrix->cols = n_cols;

  matrix->data = malloc(matrix->rows * sizeof(double *));

  for (size_t i = 0; i < matrix->cols; i++) {
    matrix->data[i] = malloc(matrix->cols * sizeof(double));
  }

  matrix_zero(matrix);

  return matrix;
}

void matrix_free(struct Matrix *matrix) {
  for (size_t i = 0; i < matrix->cols; i++) {
    free(matrix->data[i]);
  }
  free(matrix->data);

  free(matrix);
}

void matrix_zero(struct Matrix *matrix) {
  for (size_t i = 0; i < matrix->rows; i++) {
    for (size_t j = 0; j < matrix->cols; j++) {
      matrix->data[i][j] = 0;
    }
  }
}

void matrix_print(struct Matrix *matrix) {
  for (size_t i = 0; i < matrix->rows; i++) {
    for (size_t j = 0; j < matrix->cols; j++) {
      printf("%.2lf ", matrix->data[i][j]);
    }
    printf("\n");
  }
}

void matrix_fill(struct Matrix *matrix,
                 double data[matrix->rows][matrix->cols]) {
  for (size_t i = 0; i < matrix->rows; i++) {
    for (size_t j = 0; j < matrix->cols; j++) {
      matrix->data[i][j] = data[i][j];
    }
  }
}