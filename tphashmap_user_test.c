#include "tphashmap.h"

int main(int argc, char** argv)
{
    hmap_t* my_hashmap_ptr = hmap_create(1);
    
    double start_double_key = 0.0d;
    double start_double_val = 0.0d;
    multitype* mt_key_1 = NULL;
    multitype* mt_val_1 = NULL;
    
    for(u_int16_t i = 0; i < 32767; i++) {
		start_double_key += 0.111d;
		start_double_val += 0.222d;
		mt_key_1 = init_double_type(start_double_key);
        mt_val_1 = init_double_type(start_double_val);
        hashmap_insert(my_hashmap_ptr, mt_key_1, mt_val_1);
        multitype* mt = hashmap_get_val(my_hashmap_ptr, mt_key_1);
        if(mt && mt->ti == is_double) {
			printf("Found key!\n");
		}
	}
    
    /**multitype* mt_key_1 = init_string_type("Hello");
    char* mt_val_1_heap_str = malloc(6 * sizeof(char));
    mt_val_1_heap_str = "World";
    multitype* mt_val_1 = init_string_type(mt_val_1_heap_str);
    
    multitype* mt_key_2 = init_integer_type(1);
    multitype* mt_val_2 = init_integer_type(1);
    
    char** str_arr_val_3 = malloc(2 * sizeof(char*));
    str_arr_val_3[0] = "AAAA";
    str_arr_val_3[1] = "BBBB";
    multitype* mt_key_3 = init_float_type(5.0f);
    multitype* mt_val_3 = init_str_arr_type(str_arr_val_3, 2);
    
    multitype* mt_key_4 = init_double_type(10.0d);
    int* mt_val4_heap_int_arr = malloc(6 * sizeof(int));
    mt_val4_heap_int_arr[0] = 11;
    mt_val4_heap_int_arr[1] = 22;
    mt_val4_heap_int_arr[2] = 33;
    mt_val4_heap_int_arr[3] = 44;
    mt_val4_heap_int_arr[4] = 55;
    multitype* mt_val_4 = init_int_arr_type(mt_val4_heap_int_arr, 5);
    

    hashmap_insert(my_hashmap_ptr, mt_key_1, mt_val_1);
    hashmap_insert(my_hashmap_ptr, mt_key_2, mt_val_2);
    hashmap_insert(my_hashmap_ptr, mt_key_3, mt_val_3);
    hashmap_insert(my_hashmap_ptr, mt_key_4, mt_val_4);
    
    multitype* mt = hashmap_get_val(my_hashmap_ptr, mt_key_1);
    if(mt && mt->ti == is_char) {
			printf("Found key!\n");
	}
	
	int size_char_arr = 0;
    while(*(mt_val_3->t.str_arr_type)) {
		size_char_arr++;
		printf("%d: Pointer address %p, value %s\n", size_char_arr, mt_val_3->t.str_arr_type, *(mt_val_3->t.str_arr_type));
		mt_val_3->t.str_arr_type++;
		if(size_char_arr == mt_val_3->size - 1)
		    break;
	}
	
	printf("String array has size of: %d\n\n\n", size_char_arr);
	
	int size_int_arr = 0;
    while(mt_val_4->t.int_arr_type) {
		size_int_arr++;
		printf("%d: Pointer address %p, value %d\n", size_int_arr, mt_val_4->t.int_arr_type, *(mt_val_4->t.int_arr_type));
		mt_val_4->t.int_arr_type++;
		if(size_int_arr == mt_val_4->size - 1)
		    break;
	}**/

    free_hashmap(my_hashmap_ptr);    

    return true;
}
