#ifndef C_HASHMAP_H
#define C_HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef enum type_indicator {
    is_int,
    is_float,
    is_double,
    is_string,
     /** Complex types go here
     * they are blacklisted as key types
     * This makes it easy to just check > 4
     * Char is primitive but cause problems over 256 (always collides)
     * **/
    is_char,
    is_str_arr,
    is_double_arr,
    is_float_arr,
    is_int_arr
}type_indicator;

typedef union type {
    int     integertype;
    float   floattype;
    double  doubletype;
    char*   stringtype;
    /** Complex types go here
     * they are blacklisted as key types
     * This makes it easy to just check > 4
     * Char is primitive but cause problems over 256 (always collides)
     * **/
    char    chartype;
    char**  str_arr_type;
    float*  float_arr_type;
    double* double_arr_type;
    int*    int_arr_type;
}type;

typedef struct multitype {
    type_indicator ti;
    type           t;
    //non array types will have a size of -1. String counts as array type since char*
    int64_t        size;
}multitype;

typedef struct hmap_t {
    u_int16_t       id;
    u_int16_t       capacity;
    u_int16_t       last_size;
    u_int16_t       cur_size;
    multitype**     keys;
    multitype**     vals;
}hmap_t;

void exit_w_one_on_failed_xalloc(void* ptr);
hmap_t* hmap_create(u_int16_t initial_capacity);
void dump_hashmap(hmap_t* hashmap);
multitype* init_string_type(char* str);
multitype* init_str_arr_type(char** str_arr, u_int32_t size);
multitype* init_char_type(char c);
multitype* init_float_type(float fl);
multitype* init_float_arr_type(float* fl, u_int32_t size);
multitype* init_double_type(double d);
multitype* init_double_arr_type(double* d, u_int32_t size);
multitype* init_integer_type(int integer);
multitype* init_int_arr_type(int* int_arr, u_int32_t size);
bool check_key_blacklisted_type(multitype* key);
bool check_str_arr_identical(char** arr1, char** arr2);
u_int16_t hashmap_hash_key(hmap_t* hashmap, multitype* key);
void hashmap_insert(hmap_t* hashmap, multitype* key, multitype* val);
u_int16_t* hashmap_get_val_check_key_even_exists(hmap_t* hashmap, multitype* key);
multitype* hashmap_get_val(hmap_t* hashmap, multitype* key);
void free_hashmap(hmap_t* hashmap);

#endif
