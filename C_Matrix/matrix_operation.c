#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//BRUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUH
void size_error(char Axis, dimension a, dimension b, char* variable_name_a, char* variable_name_b)
{
    //Black magic
    static char* message = "00000000000000000000000";
    static int checked = 0;
    if (checked == 0) {
        switch (sizeof(dimension))
        {
            case sizeof(uint64_t):
                message = "Dimension %c %s: %llu\n";
                break;
            case sizeof(uint32_t):
                message = "Dimension %c %s: %u\n";
                break;
            case sizeof(uint16_t):
                message = "Dimension %c %s: %hu\n";
                break;
            case sizeof(uint8_t):
                message = "Dimension %c %s: %hhu\n";
                break;
            default:
                message = "Unsupported integer type";
                break;
        }

        checked = 1;
    }

    fprintf(stderr, "Size %c is not the same\n", Axis);
    fprintf(stderr, message, Axis, variable_name_a, a);
    fprintf(stderr, message, Axis, variable_name_b, b);
}

/// @brief Standard matrix add operation. Adds a and b and the result will be written to c.      
/// @param a 
/// @param b 
/// @param c 
/// @return -1: If it the size doesn't match. 1: If it succeed
int matrix_add(Matrix* a, Matrix* b, Matrix* c)
{
    dimension X = 1;
    dimension Y = 1;

    //Dimension check

    //Dimension X check
    if (a->x != b->x) {
        size_error('X', a->x, b->x, "A", "B");
        return -1;
    }

    //Dimension Y check
    if (a->y != b->y) {
        size_error('Y', a->y, b->y, "A", "B");
        return -1;
    }

    X = a->x;
    Y = a->y;

    //Result matrix size check
    //X check
    if (X != c->x) {
        size_error('X', a->x, c->x, "A", "C");
        return -1;
    }

    //Y check
    if (Y != c->x) {
        size_error('Y', a->y, c->y, "A", "C");
        return -1;
    }

    //FINALLY TIME TO DO SOME ADDITION

    for (dimension y = 0; y < Y; y++) //Row iteration
    {
        for (dimension x = 0; x < X; x++) //Column iteration
        {
            c->matrix[y][x] = (a->matrix[y][x] + b->matrix[y][x]);
        }
    }


    return 1;
}

/// @brief Standard matrix subtract operation. Subtracts a and b and the result will be written to c.      
/// @param a 
/// @param b 
/// @param c 
/// @return -1: If it the size doesn't match. 1: If it succeed
int matrix_sub(Matrix* a, Matrix* b, Matrix* c)
{
    dimension X = 1;
    dimension Y = 1;

    //Dimension check

    //Dimension X check
    if (a->x != b->x) {
        size_error('X', a->x, b->x, "A", "B");
        return -1;
    }

    //Dimension Y check
    if (a->y != b->y) {
        size_error('Y', a->y, b->y, "A", "B");
        return -1;
    }

    X = a->x;
    Y = a->y;

    //Result matrix size check
    //X check
    if (X != c->x) {
        size_error('X', a->x, c->x, "A", "C");
        return -1;
    }

    //Y check
    if (Y != c->x) {
        size_error('Y', a->y, c->y, "A", "C");
        return -1;
    }

    //FINALLY TIME TO DO SOME SUBTRACTION

    for (dimension y = 0; y < Y; y++) //Row iteration
    {
        for (dimension x = 0; x < X; x++) //Column iteration
        {
            c->matrix[y][x] = (a->matrix[y][x] - b->matrix[y][x]);
        }
    }


    return 1;
}

//=============================
//MATRIX MULTIPLICATION
//=============================

//=============================
//HELPER FUNCTIONS
//=============================

//both a and be should be the same len
element dot_product(dimension a_len, element* a, element* b)
{
    element result = 0;

    for (dimension i = 0; i < a_len; i++)
    {
        result += a[i] * b[i];
    }

    return result;
}

int get_row(Matrix* target, dimension row, element* array)
{
    if (row > target->y)
    {
        fprintf(stdout, "The row wanted is bigger than the size of matrix row");
        return -1;
    }
    
    for (dimension i = 0; i < target->x ; i++)
    {
        array[i] = target->matrix[row][i];
    }

    return 1;
}

int get_column(Matrix* target, dimension column, element* array)
{
    if (column > target->x)
    {
        fprintf(stdout, "The column wanted is bigger than the size of matrix row");
        return -1;
    }
    
    for (dimension i = 0; i < target->y ; i++)
    {
        array[i] = target->matrix[i][column];
    }

    return 1;
}


int matrix_mul(Matrix* a, Matrix* b, Matrix* result)
{
    dimension X = 1; dimension Y = 1;

    //Dimension check
    if (a->x != b->y)
    {
        fprintf(stderr, "A column is not the same as B row\n");
        return -1;
    }

    if (result->y != a->y)
    {
        fprintf(stderr, "Result matrix y dimension is not compatible\n");
        return -1;
    }

    if (result->x != b->x)
    {
        fprintf(stderr, "Result matrix x dimension is not compatible\n");
        return -1;
    }

    X = result->x; Y = result->y;

    element* a_row = (element*) calloc(a->x, sizeof(element));
    element* b_column = (element*) calloc(b->y, sizeof(element));

    if (a_row == NULL)
    {
        fprintf(stderr, "Lack of memory. Unable to perform matrix multiplication");
        return -1;
    }

    if (b_column == NULL)
    {
        fprintf(stderr, "Lack of memory. Unable to perform matrix multiplication");
        return -1;
    }

    for (dimension y = 0; y < Y; y++)
    {
        // printf("Row\n");
        get_row(a, y, a_row);
        for (dimension x = 0; x < X; x++)
        {
            // printf("Column ");
            get_column(b, x, b_column);
            result->matrix[y][x] = dot_product(a->x, a_row, b_column);
            // printf("ColumnDone\n");
        }
        // printf("RowDone\n");
    }

    free(a_row);
    free(b_column);

    return 1;
}

