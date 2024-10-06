#include "./C_Matrix/matrix.h"
#include "./C_Matrix/matrix_op.h"
#include "./Lua_Header/lua_header.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


// uint64_t double_to_uint64(double value) {
//     if (value < 0.0) {
//         // Handle negative values appropriately
//         return 0; // Or any other appropriate action
//     }
//     // Cast the double to uint64_t
//     return (uint64_t)value;
// }


//For light user data
typedef struct lm {
    Matrix* matrix;
} luaMatrix;

//
int matrixL_create(lua_State* L) {
    //Parameters
    lua_Integer x = luaL_checkinteger(L, 1);
    lua_Integer y = luaL_checkinteger(L, 2);

    //Allocation
    Matrix* new = create_matrix((uint64_t) x, (uint64_t) y);

    //Failed to allocate. Push nil. Return 1
    if (new == NULL) {
        lua_pushnil(L);
        return 1;
    }

    //Otherwise create a luaMatrix to hold new. Push the luaMatrix. Return 1

    luaMatrix* target = (luaMatrix*) malloc(sizeof(luaMatrix));
    target->matrix = new;

    lua_pushlightuserdata(L, target);
    return 1;
}

//Always need to be called
int matrixL_free(lua_State* L) {
    luaMatrix* lm = (luaMatrix*) lua_touserdata(L, 1);
    free_matrix(lm->matrix); //Free the internal matrix
    free(lm); //Free the pointer to internal matrix
    return 0;
}

//Get an element from the matrix.
//All of the checks must be implemented in Lua to avoid clutter in the C code
int matrixL_get(lua_State* L) {
    luaMatrix* lm = (luaMatrix*) lua_touserdata(L, 1);
    lua_Integer x = luaL_checkinteger(L, 2);
    lua_Integer y = luaL_checkinteger(L, 3);

    lua_pushnumber(L, lm->matrix->matrix[y][x]);

    return 1;
}

//Set the element
int matrixL_set(lua_State* L) {
    luaMatrix* lm = (luaMatrix*) lua_touserdata(L, 1);
    lua_Integer x = luaL_checkinteger(L, 2);
    lua_Integer y = luaL_checkinteger(L, 3);
    lua_Number number = luaL_checknumber(L, 4);

    // printf("X: %lld, Y: %lld, Number: %f\n", x, y, number);

    lm->matrix->matrix[y][x] = number;

    return 0;
}

int matrixL_add(lua_State* L) {
    //Arguments
    luaMatrix* a = (luaMatrix*) lua_touserdata(L, 1);
    luaMatrix* b = (luaMatrix*) lua_touserdata(L, 2);
    
    //Create the result matrix
    Matrix* c = create_matrix(a->matrix->x, a->matrix->y);

    //Perform addition
    int stat = matrix_add(a->matrix, b->matrix, c);

    if (stat != 1) {
        printf("NIGGA IT'S NOT 1");
        luaL_error(L, "Something went wrong. Go fuck yourself");
    }
    
    //Create a pointer to the resulting matrix
    luaMatrix* result = (luaMatrix*) malloc(sizeof(luaMatrix));
    result->matrix = c;

    //Push the resulting matrix
    lua_pushlightuserdata(L, result);
    return 1;
}

int matrixL_sub(lua_State* L) {
    //Arguments
    luaMatrix* a = (luaMatrix*) lua_touserdata(L, 1);
    luaMatrix* b = (luaMatrix*) lua_touserdata(L, 2);
    
    //Create the result matrix
    Matrix* c = create_matrix(a->matrix->x, a->matrix->y);

    //Perform addition
    int stat = matrix_sub(a->matrix, b->matrix, c);

    if (stat != 1) {
        printf("Stat is not 1 in matrixL_sub");
        luaL_error(L, "Something went wrong");
    }
    
    //Create a pointer to the resulting matrix
    luaMatrix* result = (luaMatrix*) malloc(sizeof(luaMatrix));
    result->matrix = c;

    //Push the resulting matrix
    lua_pushlightuserdata(L, result);
    return 1;
}

int matrixL_mul(lua_State* L) {
    luaMatrix* a = (luaMatrix*) lua_touserdata(L, 1);
    luaMatrix* b = (luaMatrix*) lua_touserdata(L, 2);

    Matrix* c = create_matrix(b->matrix->x, a->matrix->y);

    int stat = matrix_mul(a->matrix, b->matrix, c);

    if (stat != 1) {
        fprintf(stderr, "Something went wrong");
        luaL_error(L, "Something went wrong");
    }

    //Create a pointer to the resulting matrix
    luaMatrix* result = (luaMatrix*) malloc(sizeof(luaMatrix));
    result->matrix = c;

    //Push the resulting matrix
    lua_pushlightuserdata(L, result);
    return 1;
}

const luaL_Reg functions[] = {
    {"create", matrixL_create},
    {"free", matrixL_free},
    // {"dimensions", matrixL_getdimension},
    {"add", matrixL_add},
    {"sub", matrixL_sub},
    {"mul", matrixL_mul},
    {"get", matrixL_get},
    {"set", matrixL_set},
    {NULL, NULL}
};


//Gateway function that opens the rest of the function
int lua_matrix_library(lua_State* L) {
    printf("Starting library\n");
    luaL_newlib(L, functions);
    return 1;
}
















