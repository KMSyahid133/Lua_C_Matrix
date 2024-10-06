#ifndef MATRIX_OP
#define MATRIX_OP 1

#include "matrix.h"
/// @brief Standard matrix add operation. Adds a and b and the result will be written to c.      
/// @param a Is the first matrix
/// @param b Is the second matrix
/// @param c Is where the result will be stored
/// @return -1: If it the size doesn't match. 1: If it succeed
int matrix_add(Matrix* a, Matrix* b, Matrix* c);

/// @brief Standard matrix add operation. Adds a and b and the result will be written to c.      
/// @param a Is the first matrix
/// @param b Is the second matrix
/// @param c Is where the result will be stored
/// @return -1: If it the size doesn't match. 1: If it succeed
int matrix_sub(Matrix* a, Matrix* b, Matrix* c);

int matrix_mul(Matrix* a, Matrix* b, Matrix* result);

#endif