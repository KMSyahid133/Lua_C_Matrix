//The strassen algorithm for matrix multiplication
//m1 = (a11 + a22) x (b11 + b22)
//m2 = (a12 + a22) x b11
//m3 = a11 * (b12 - b22)
//m4 = a22 * (B21 - b11)
//m5 = (a11 + a12) x b22
//m6 = (a21 - a11) x (b11 + b12)
//m7 = (a12 - a22) x (b21 + b22)


/*
    [c11 c12] = [   m1 + m4 -m5 + m7,   m3 + m5             ]
    [c21 c22]   [   m2 + m4         ,   m1 - m2 + m3 + m6   ]
*/

#include <stdio.h>
#include "matrix.h"

/*
    m1 = (a11 + a22) x (b11 + b22)
    m2 = (a12 + a22) x b11
    m3 = a11 * (b12 - b22)
    m4 = a22 * (B21 - b11)
    m5 = (a11 + a12) x b22
    m6 = (a21 - a11) x (b11 + b12)
    m7 = (a12 - a22) x (b21 + b22)
    [c11 c12] = [   m1 + m4 -m5 + m7,   m3 + m5             ]
    [c21 c22]   [   m2 + m4         ,   m1 - m2 + m3 + m6   ]
*/
int multiply(Matrix* a, Matrix* b, Matrix* result, dimension sector_y, dimension sector_x)
{
    //Sector x
    dimension one_x = (0 + (sector_x*2) );
    dimension two_x = (1 + (sector_x*2) );

    //Sector y
    dimension one_y = (0 + (sector_y*2) );
    dimension two_y = (1 + (sector_y*2) );

    //
    element a11 = a->matrix[one_y][one_x];
    element a12 = a->matrix[two_y][one_x];
    element a21 = a->matrix[one_y][two_x];
    element a22 = a->matrix[two_y][two_x];

    element b11 = b->matrix[one_y][one_x];
    element b12 = b->matrix[two_y][one_x];
    element b21 = b->matrix[one_y][two_x];
    element b22 = b->matrix[two_y][two_x];

    //Calculations
    printf("one_x: %llu | two_x: %llu\n", one_x, two_x);
    printf("one_y: %llu | two_y: %llu\n", one_y, two_y);
    printf("a11: %f a12: %f a21: %f a22: %f\n", a11, a12, a21, a22);
    printf("b11: %f b12: %f b21: %f b22: %f\n", b11, b12, b21, b22);

    return 0;
}


/*
    Returns:
    -1 Size does not fit
    -2 Size is not a perfect square
*/ 
int strassen(Matrix* a, Matrix* b, Matrix* result)
{
    //All A, B and result need to be N*N

    if (
        (a->x == b->x) && (b->x == result->x) && 
        (a->y == b->y) && (b->y == result->y)
        )
    {
        return -1;
    }

    //Check the squareness of the matrix
    if (
        (! ( (a->x & (a->x-1)) == 0)) && (! ( ( a->y & (a->y-1) ) == 0)) && //Check a if square matrix
        (! ( (b->x & (b->x-1)) == 0)) && (! ( ( b->y & (b->y-1) ) == 0)) && //Check b if square matrix
        (! ( (result->x & (result->x-1)) == 0)) && (! ( ( result->y & (result->y-1) ) == 0)) //Check result if square matrix
        )
    {
        return -2;
    }

    for (dimension y = 0; y < (a->y / 2); y++)
    {
        for (dimension x = 0; x < (a->x /2); x++)
        {
            printf("Multiply\n");
            multiply(a, b, result, y, x);
        }
    }

    return 0;
}

