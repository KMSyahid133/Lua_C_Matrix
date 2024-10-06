#include "matrix.h"
#include <stdlib.h>
#include <stdint.h>

Matrix* create_matrix(dimension x, dimension y) {
    //Allocate the memory
    Matrix* new = (Matrix*) malloc(sizeof(Matrix));

    //Failed to allocate memory
    if (new == NULL) {
        return NULL;
    }
    
    //Assign dimension
    new->x = x;
    new->y = y;
    
    //Allocate the matrix

    new->matrix = (element**) malloc(y * sizeof(element*)); // Need Y amount of arrays 

    for (dimension i = 0; i < y; i++) 
    {   
        new->matrix[i] = (element*) malloc(x * sizeof(element)); // Need X amount of element space for each arrays

        //If allocation fails destroy everything
        if (new->matrix[i] == NULL)
        {
            //Delete all of the 'cells'
            for (dimension j = 0; j < i; j++)
            {
                free(new->matrix[j]);
            }
            free(new->matrix);
            free(new);
            return NULL;
        }
    }

    //Set the things to 0

    for (dimension i = 0; i < y; i++) //Row loop
    {
        for (dimension j = 0; j < x; j++)
        {
            new->matrix[i][j] = 0.0;
        }
    }


    return new;
}

/// @brief Always call this at the end!!!!!
/// @param target Is the matrix to be freed
void free_matrix(Matrix* target) {
    for (dimension y = 0; y < target->y; y++) {
        free(target->matrix[y]);
    }
    free(target);
}





