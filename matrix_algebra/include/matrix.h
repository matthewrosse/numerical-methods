#ifndef MATRIX_H
#include <stddef.h>

#define MATRIX_H

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

struct Matrix *matrix_add(struct Matrix *first_matrix,
                          struct Matrix *second_matrix);

struct Matrix *matrix_subtract(struct Matrix *first_matrix,
                               struct Matrix *second_matrix);

struct Matrix *matrix_multiply(struct Matrix *first_matrix,
                               struct Matrix *second_matrix);

struct Matrix *matrix_create_identity(const size_t size);

int matrix_determinant_sarrus3x3(struct Matrix *matrix, double *result);
int matrix_determinant_sarrus2x2(struct Matrix *matrix, double *result);

int matrix_inverse_3x3(struct Matrix *matrix, struct Matrix *result);

struct Matrix *matrix_create_minor(struct Matrix *matrix, size_t row,
                                   size_t col);

struct Matrix *matrix_transpose(struct Matrix *matrix);

struct Matrix *matrix_read_from_file(char *path, char *delimiter);

double matrix_laplace_determinant(struct Matrix *matrix);

#endif