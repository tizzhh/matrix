#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

int s21_calc_complementss(matrix_t *A, matrix_t *result) {
  if (!is_matrix_valid(A) || result == NULL) return ERROR_INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCUALTION_ERROR;

  int res = 0;

  matrix_t minor = {0};
  if (s21_create_matrix(A->columns, A->rows, result) ||
      s21_create_matrix(A->columns - 1, A->rows - 1, &minor))
    res = ERROR_INCORRECT_MATRIX;

  double minor_res = 0;
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->rows; ++j) {
      for (int x = 0; x < A->rows - 1; ++x) {
        for (int y = 0; y < A->rows - 1; ++y) {
          minor.matrix[x][y] = 0;
        }
      }

      create_minor(&minor, A, i, j);

      for (int x = 0; x < A->rows - 1; ++x) {
        for (int y = 0; y < A->rows - 1; ++y) {
          printf("%.lf ", minor.matrix[x][y]);
        }
        printf("\n");
      }
      printf("\n");

      result->matrix[i][j] =
          s21_determinant(&minor, &minor_res) * pow(-1, i + j);
    }
  }
  s21_remove_matrix(&minor);
  return res;
}

int main(void) {
  int rows = 3, columns = 3;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  int status = s21_calc_complementss(&A, &result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
