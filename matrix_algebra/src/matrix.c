#include "../include/matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Matrix *matrix_init(const size_t n_rows, const size_t n_cols) {
  struct Matrix *matrix = malloc(sizeof(struct Matrix));
  matrix->rows = n_rows;
  matrix->cols = n_cols;

  matrix->data = malloc(matrix->rows * sizeof(double *));

  for (size_t i = 0; i < matrix->rows; i++) {
    matrix->data[i] = malloc(matrix->cols * sizeof(double));
  }

  matrix_zero(matrix);

  return matrix;
}

void matrix_free(struct Matrix *matrix) {
  for (size_t i = 0; i < matrix->rows; i++) {
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

void matrix_fill(struct Matrix *matrix, double **data) {
  for (size_t i = 0; i < matrix->rows; i++) {
    for (size_t j = 0; j < matrix->cols; j++) {
      matrix->data[i][j] = data[i][j];
    }
  }
}

struct Matrix *matrix_multiply(struct Matrix *first_matrix,
                               struct Matrix *second_matrix) {
  if (first_matrix->cols != second_matrix->rows) {
    return NULL;
  }

  struct Matrix *result = matrix_init(first_matrix->rows, second_matrix->cols);

  double sum = 0;

  for (size_t i = 0; i < first_matrix->rows; i++) {
    for (size_t j = 0; j < second_matrix->cols; j++) {
      sum = 0;
      for (size_t k = 0; k < first_matrix->cols; k++) {
        sum += first_matrix->data[i][k] * second_matrix->data[k][j];
      }
      result->data[i][j] = sum;
    }
  }

  return result;
}

struct Matrix *matrix_add(struct Matrix *first_matrix,
                          struct Matrix *second_matrix) {
  if (first_matrix->rows != second_matrix->rows ||
      first_matrix->cols != second_matrix->rows) {
    return NULL;
  }

  struct Matrix *result = matrix_init(first_matrix->rows, first_matrix->cols);

  for (size_t i = 0; i < first_matrix->cols; i++) {
    for (size_t j = 0; j < first_matrix->rows; j++) {
      result->data[i][j] = first_matrix->data[i][j] + second_matrix->data[i][j];
    }
  }

  return result;
}

struct Matrix *matrix_subtract(struct Matrix *first_matrix,
                               struct Matrix *second_matrix) {
  if (first_matrix->rows != second_matrix->rows ||
      first_matrix->cols != second_matrix->rows) {
    return NULL;
  }

  struct Matrix *result = matrix_init(first_matrix->rows, first_matrix->cols);

  for (size_t i = 0; i < first_matrix->cols; i++) {
    for (size_t j = 0; j < first_matrix->rows; j++) {
      result->data[i][j] = first_matrix->data[i][j] - second_matrix->data[i][j];
    }
  }

  return result;
}

int matrix_determinant_sarrus3x3(struct Matrix *matrix, double *result) {
  if (matrix->rows != matrix->cols || matrix->rows != 3) {
    return -1;
  }

  *result = 0;

  double **arr = matrix->data;

  for (size_t i = 0; i < 3; i++) {
    *result += arr[0][i] * (arr[1][(i + 1) % 3] * arr[2][(i + 2) % 3] -
                            arr[1][(i + 2) % 3] * arr[2][(i + 1) % 3]);
  }

  return 0;
}

int matrix_determinant_sarrus2x2(struct Matrix *matrix, double *result) {
  if (matrix->rows != matrix->cols || matrix->rows != 2) {
    return -1;
  }

  *result = 0;

  double **arr = matrix->data;

  *result = arr[0][0] * arr[1][1] - arr[1][0] * arr[0][1];

  return 0;
}

struct Matrix *matrix_create_minor(struct Matrix *matrix, size_t row,
                                   size_t col) {
  struct Matrix *result = matrix_init(matrix->rows - 1, matrix->cols - 1);

  int minor_row, minor_col;
  for (size_t i = 0; i < matrix->rows; i++) {
    minor_row = i;
    if (i > row) {
      minor_row--;
    }
    for (size_t j = 0; j < matrix->cols; j++) {
      minor_col = j;
      if (j > col) {
        minor_col--;
      }
      if (i != row && j != col) {
        result->data[minor_row][minor_col] = matrix->data[i][j];
      }
    }
  }

  return result;
}

struct Matrix *matrix_transpose(struct Matrix *matrix) {
  struct Matrix *result = matrix_init(matrix->cols, matrix->rows);

  for (size_t i = 0; i < matrix->rows; i++) {
    for (size_t j = 0; j < matrix->cols; j++) {
      result->data[j][i] = matrix->data[i][j];
    }
  }

  return result;
}

int matrix_inverse_3x3(struct Matrix *matrix, struct Matrix *result) {
  if (result == NULL || matrix->rows != result->rows ||
      matrix->cols != result->cols) {
    return -1;
  }

  double determinant;
  int determinant_status = matrix_determinant_sarrus3x3(matrix, &determinant);

  if (determinant_status == -1 || determinant == 0) {
    return -1;
  }

  struct Matrix *transposed_matrix = matrix_transpose(matrix);

  for (size_t i = 0; i < result->rows; i++) {
    for (size_t j = 0; j < result->cols; j++) {
      struct Matrix *current_minor =
          matrix_create_minor(transposed_matrix, i, j);
      double determinant2x2_result;
      // status check needed
      matrix_determinant_sarrus2x2(current_minor, &determinant2x2_result);
      result->data[i][j] =
          (1.0 / determinant) * pow(-1, i + j) * determinant2x2_result;
      matrix_free(current_minor);
    }
  }

  matrix_free(transposed_matrix);

  return 0;
}

int *matrix_get_size_from_file(char *path, char *delimiter) {
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    return NULL;
  }

  char buf[1000];

  int rows = 0;

  char *line = fgets(buf, 1000, file);
  rows++;

  char *tokenized_line = strtok(line, delimiter);

  unsigned int cols = 0;

  while (tokenized_line != NULL) {
    cols++;
    tokenized_line = strtok(NULL, delimiter);
  }

  while (fgets(line, 1000, file) != NULL) {
    rows++;
  }

  fclose(file);

  int *result = (int *)malloc(sizeof(int) * 2);
  result[0] = rows;
  result[1] = cols;

  return result;
}

struct Matrix *matrix_read_from_file(char *path, char *delimiter) {
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    fclose(file);
    return NULL;
  }

  int *matrix_size = matrix_get_size_from_file(path, delimiter);

  if (matrix_size == NULL) {
    fclose(file);
    return NULL;
  }

  struct Matrix *matrix = matrix_init(matrix_size[0], matrix_size[1]);

  for (size_t i = 0; i < matrix->rows; i++) {
    for (size_t j = 0; j < matrix->cols; j++) {
      double buffer;
      fscanf(file, "%lf", &buffer);
      matrix->data[i][j] = buffer;
    }
  }

  free(matrix_size);
  fclose(file);

  return matrix;
}

double matrix_laplace_determinant(struct Matrix *matrix) {
  if (matrix->rows == 3 && matrix->cols == 3) {
    double result;
    matrix_determinant_sarrus3x3(matrix, &result);
    return result;
  }

  double result;

  srand(time(NULL));
  unsigned int rand_row = rand() % (matrix->rows);

  double **arr = matrix->data;

  for (size_t i = 0; i < matrix->cols; i++) {
    struct Matrix *sub_matrix = matrix_create_minor(matrix, rand_row, i);

    result += arr[rand_row][i] * pow(-1, rand_row + i) *
              matrix_laplace_determinant(sub_matrix);
    matrix_free(sub_matrix);
  }

  return result;
}

struct Matrix *matrix_create_identity(const size_t size) {
  struct Matrix *identity_matrix = matrix_init(size, size);

  for (size_t i = 0; i < identity_matrix->rows; i++) {
    for (size_t j = 0; j < identity_matrix->cols; j++) {
      if (i == j) {
        identity_matrix->data[i][j] = 1;
      }
    }
  }

  return identity_matrix;
}