#include "../include/linear_algebra.h"
#include "../include/matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  struct Matrix *matrix =
      matrix_read_from_file("../test_files/cwiczenie1_macierz.txt", " ");
  struct Matrix *constant_terms =
      matrix_read_from_file("../test_files/cwiczenie1_wyrazy_wolne.txt", " ");

  struct Matrix *big_matrix =
      matrix_read_from_file("../test_files/duza_macierz_test.txt", " ");
  struct Matrix *big_matrix_constant_terms =
      matrix_read_from_file("../test_files/duza_macierz_test_wolne.txt", " ");

  // printf("First matrix: \n");
  // matrix_print(matrix);

  // printf("Constant terms: \n");
  // matrix_print(constant_terms);

  // struct Matrix *matrix_result_inverse_matrix =
  //     inverse_matrix_method(matrix, constant_terms);

  // printf("Matrix result inverse matrix: \n");
  // matrix_print(matrix_result_inverse_matrix);
  printf("First matrix: \n");
  matrix_print(matrix);
  printf("\n");
  printf("Constant terms: \n");
  matrix_print(constant_terms);
  printf("\n");

  // struct Matrix *matrix_result_cramer_method =
  //     cramer_method(matrix, constant_terms);

  struct Matrix **upper_triangular_result =
      matrix_get_upper_triangular(matrix, constant_terms);

  struct Matrix *big_matrix_result_gauss =
      gauss_elimination_method(big_matrix, big_matrix_constant_terms);

  // printf("Macierz gornotrojkatna: \n");
  // printf("\n");
  // matrix_print(upper_triangular_result[0]);
  // printf("\n");
  // printf("Constant terms: \n");
  // matrix_print(upper_triangular_result[1]);
  // printf("\n");

  // printf("WYNIK CRAMERA: \n");

  // matrix_print(matrix_result_cramer_method);

  // printf("Wynik gaussa: \n");

  // struct Matrix *gauss_result_matrix =
  //     gauss_elimination_method(matrix, constant_terms);

  // matrix_print(gauss_result_matrix);
  //
  printf("Big matrix gauss result: \n");
  printf("\n");
  linear_equation_print_result(big_matrix_result_gauss);

  matrix_free(matrix);
  matrix_free(constant_terms);
  // matrix_free(matrix_result_inverse_matrix);
  // matrix_free(matrix_result_cramer_method);

  matrix_free(upper_triangular_result[0]);
  matrix_free(upper_triangular_result[1]);
  // matrix_free(gauss_result_matrix);
  matrix_free(big_matrix);
  matrix_free(big_matrix_constant_terms);
  matrix_free(big_matrix_result_gauss);

  free(upper_triangular_result);
  return 0;
}
