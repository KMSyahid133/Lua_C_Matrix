#ifndef MATRIX_H
#define MATRIX_H 1

#include <stdint.h>

//This is the integer type that will used to define the matrix dimension
//Must be a unsigned number for more range and error prevention
//uint64_t is the default 
#define dimension uint16_t

//This is the type that will be used
//double is the default
#define element double



typedef struct matrix {
    dimension x; //This is the column. 0 to x-1
    dimension y; //This is the row. 0 to y-1
    element** matrix; //row comes first, column second
} Matrix;

Matrix* create_matrix(dimension x, dimension y);

/// @brief Always call this at the end!!!!!
/// @param target Is the matrix to be freed
void free_matrix(Matrix* target);

#endif