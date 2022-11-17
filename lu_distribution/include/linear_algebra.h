#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H
#include "../include/matrix.h"
#include <stdlib.h>

struct Matrix *inverse_matrix_method(struct Matrix *matrix,
                                     struct Matrix *constant_terms);

struct Matrix *cramer_method(struct Matrix *matrix,
                             struct Matrix *constant_terms);

struct Matrix *gauss_elimination_method(struct Matrix *matrix,
                                        struct Matrix *constant_terms);

struct Matrix **
matrix_get_upper_triangular_with_constant_terms(struct Matrix *matrix,
                                                struct Matrix *constant_terms);

struct Matrix **
matrix_get_upper_triangular_with_multipliers(struct Matrix *matrix);

void linear_equation_print_result(struct Matrix *matrix);

#endif
