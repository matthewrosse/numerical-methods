#include "../include/lu_distribution.h"
#include "../include/linear_algebra.h"
#include "../include/matrix.h"

struct Matrix **lu_distribution(struct Matrix *matrix) {
  struct Matrix **result = matrix_get_upper_triangular_with_multipliers(matrix);

  return result;
}