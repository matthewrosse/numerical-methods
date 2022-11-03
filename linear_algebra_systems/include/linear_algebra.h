#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H
#include "../include/matrix.h"
#include <stdlib.h>

struct Matrix *inverse_matrix_method(struct Matrix *matrix,
                                     struct Matrix *constant_terms);

struct Matrix *cramer_method(struct Matrix *matrix,
                             struct Matrix *constant_terms);

#endif
