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

void matrix_fill(struct Matrix *matrix, double **data);

struct Matrix *matrix_multiply(struct Matrix *first_matrix,
                               struct Matrix *second_matrix);

int matrix_determinant_sarrus3x3(struct Matrix *matrix, double *result);
int matrix_determinant_sarrus2x2(struct Matrix *matrix, double *result);

int matrix_inverse_3x3(struct Matrix *matrix, struct Matrix *result);

struct Matrix *matrix_create_minor(struct Matrix *matrix, size_t row,
                                   size_t col);

struct Matrix *matrix_transpose(struct Matrix *matrix);

struct Matrix *matrix_read_from_file(char *path, char *delimiter);

#endif