#ifndef MATRIX_H
#define MATRIX_H
#include <stdlib.h>

struct Matrix {
  size_t rows;
  size_t cols;
  double **data;
};

struct Matrix *matrix_init(const size_t n_rows, const size_t n_cols);

void matrix_free(struct Matrix *matrix);

void matrix_zero(struct Matrix *matrix);

void matrix_print(struct Matrix *matrix);

void matrix_fill(struct Matrix *matrix,
                 double data[matrix->rows][matrix->cols]);

#endif