#include "tphashmap.h"

void exit_w_one_on_failed_xalloc(void* ptr)
{
    if(!ptr) {
        printf("Out of memory. Exiting with 1!\n");
        exit(1);
    }
}

hmap_t* hmap_create(u_int16_t initial_capacity)
{
    hmap_t* hashmap     = malloc(1 * sizeof(hmap_t));
    exit_w_one_on_failed_xalloc(hashmap);
    static u_int16_t id = 0;

    hashmap->id = id;
    id++;

    hashmap->capacity  = initial_capacity;
    hashmap->cur_size  = 0;
    hashmap->last_size = 0;

    hashmap->keys      = malloc(initial_capacity * sizeof(multitype*));
    exit_w_one_on_failed_xalloc(hashmap->keys);
    hashmap->vals      = malloc(initial_capacity * sizeof(multitype*));
    exit_w_one_on_failed_xalloc(hashmap->vals);

    return hashmap;
}

void dump_hashmap(hmap_t* hashmap)
{
    printf("\nID\t\t\t: %u\n", hashmap->id);
    printf("Capacity\t\t: %u\n", hashmap->capacity);
    printf("Last size\t\t: %u\n", hashmap->last_size);
    printf("Current size\t\t: %u\n", hashmap->cur_size);

    if(hashmap->keys[hashmap->cur_size - 1]->ti == is_string) {
        printf("Key #%u is string\t: %s\n", (hashmap->cur_size - 1), hashmap->keys[hashmap->cur_size - 1]->t.stringtype);
    }

    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_string) {
        printf("Val #%u is string\t: %s\n", (hashmap->cur_size - 1), hashmap->vals[hashmap->cur_size - 1]->t.stringtype);
    }

    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_str_arr) {
        printf("Val #%u is string array: %s\n", (hashmap->cur_size - 1), hashmap->vals[hashmap->cur_size - 1]->t.str_arr_type[0], hashmap->vals[hashmap->cur_size - 1]->t.str_arr_type[1]);
    }

    if(hashmap->keys[hashmap->cur_size - 1]->ti == is_float) {
        printf("Key #%u is float\t: %f\n", (hashmap->cur_size - 1), hashmap->keys[hashmap->cur_size - 1]->t.floattype);
    }

    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_float) {
        printf("Val #%u is float\t: %f\n", (hashmap->cur_size - 1), hashmap->vals[hashmap->cur_size - 1]->t.floattype);
    }
    
    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_float_arr) {
        printf("Val #%u is float array\t: %f\n", (hashmap->cur_size - 1), (hashmap->vals[hashmap->cur_size - 1]->t.float_arr_type)[0]);
    }

    if(hashmap->keys[hashmap->cur_size - 1]->ti == is_double) {
        printf("Key #%u is double\t: %lf\n", (hashmap->cur_size - 1), hashmap->keys[hashmap->cur_size - 1]->t.doubletype);
    }
    
    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_double_arr) {
        printf("Val #%u is double array\t: %lf\n", (hashmap->cur_size - 1), (hashmap->vals[hashmap->cur_size - 1]->t.double_arr_type)[0]);
    }

    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_double) {
        printf("Val #%u is double\t: %lf\n", (hashmap->cur_size - 1), hashmap->vals[hashmap->cur_size - 1]->t.doubletype);
    }

    if(hashmap->keys[hashmap->cur_size - 1]->ti == is_int) {
        printf("Key #%u is int\t: %d\n", (hashmap->cur_size - 1), hashmap->keys[hashmap->cur_size - 1]->t.integertype);
    }

    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_int) {
        printf("Val #%u is int\t: %d\n", (hashmap->cur_size - 1), hashmap->vals[hashmap->cur_size - 1]->t.integertype);
    }

    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_int_arr) {
        printf("Val #%u is int array\t: %d %d\n", (hashmap->cur_size - 1), (hashmap->vals[hashmap->cur_size - 1]->t.int_arr_type)[0], (hashmap->vals[hashmap->cur_size - 1]->t.int_arr_type)[1]);    
    }

    if(hashmap->vals[hashmap->cur_size - 1]->ti == is_char) {
        printf("Val #%u is char\t\t: %c\n", (hashmap->cur_size - 1), hashmap->vals[hashmap->cur_size - 1]->t.chartype);
    }
}

multitype* init_string_type(char* str)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti            = is_string;
    mt->t.stringtype  = str;
    mt->size          = strlen(str) + 1;   

    return mt;
}

multitype* init_str_arr_type(char** str_arr, u_int32_t size)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti             = is_str_arr;
    mt->t.str_arr_type = str_arr;
    mt->size           = size;

    return mt;
}

multitype* init_char_type(char c)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti             = is_char;
    mt->t.integertype  = c;
    mt->size           = -1;

    return mt;
}

multitype* init_float_type(float fl)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti            = is_float;
    mt->t.floattype   = fl;
    mt->size          = -1;

    return mt;
}

multitype* init_float_arr_type(float* fl, u_int32_t size)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti                = is_float_arr;
    mt->t.float_arr_type  = fl;
    mt->size              = size;

    return mt;
}

multitype* init_double_type(double d)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti            = is_double;
    mt->t.doubletype  = d;
    mt->size          = -1;
    return mt;
}

multitype* init_double_arr_type(double* d, u_int32_t size)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti                 = is_double_arr;
    mt->t.double_arr_type  = d;
    mt->size               = size;
    
    return mt;
}

multitype* init_integer_type(int integer)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti             = is_int;
    mt->t.integertype  = integer;
    mt->size           = -1;

    return mt;
}

multitype* init_int_arr_type(int* int_arr, u_int32_t size)
{
    multitype* mt = malloc(1 * sizeof(multitype));
    exit_w_one_on_failed_xalloc(mt);
    mt->ti             = is_int_arr;
    mt->t.int_arr_type = int_arr;
    mt->size           = size;
    return mt;
}

bool check_key_blacklisted_type(multitype* key)
{
    /* Keys as opposed to values may only be of primitive datatypes */
    if(key->ti > 3)
        return true;

    return false;
}
    
bool check_str_arr_identical(char** arr1, char** arr2)
{
	u_int16_t loop_counter = 0;
	//The string array that is a value in the hashmap MUST be NULL terminated
	char** helpr_ptr = arr1;
	
	while(arr1) {
		if(strcmp(helpr_ptr[loop_counter], arr2[loop_counter]) != 0)
		    return false;
		    
		loop_counter++;
		helpr_ptr++;
	}
	return true;
}
    
u_int16_t hashmap_hash_key(hmap_t* hashmap, multitype* key)
{
    u_int16_t i = 0;
    
    // Check if key exists (collision detection))
    for(; i < hashmap->cur_size; i++) {
        if(key->ti == is_string) {
            if(strcmp(key->t.stringtype, hashmap->keys[i]->t.stringtype) == 0) {
                return i;
            }
        }
              
        if(key->ti == is_double) {
            if(key->t.doubletype == hashmap->keys[i]->t.doubletype) {
                return i;
            }
        }
        
        if(key->ti == is_float) {
            if(key->t.floattype == hashmap->keys[i]->t.floattype) {
                return i;
            }
        }
        
        if(key->ti == is_int) {
            if(key->t.integertype == hashmap->keys[i]->t.integertype) {
                return i;
            }
        }
    }

    //If key not found deal new slot at pos i
    return i;
}

void hashmap_insert(hmap_t* hashmap, multitype* key, multitype* val)
{
    if(check_key_blacklisted_type(key)) {
        printf("Keys may only be primitive types. Exiting with 1!\n");
        exit(1);
    }
    
    /**u_int16_t newslot = hashmap_hash_key(hashmap, key);
    
    if(newslot != hashmap->cur_size) {
		printf("Hashmap's current size:   %d\n", hashmap->cur_size);
		printf("New key slot being dealt: %d\n", newslot);
        printf("Something went wrong while assigning a new slot for your key (key hashing)\n");
	}**/

    if(hashmap->cur_size == (hashmap->capacity - 1)) {
        hashmap->capacity <<= 1;

        hashmap->keys   = realloc(hashmap->keys, (hashmap->capacity * sizeof(multitype*)));
        exit_w_one_on_failed_xalloc(hashmap->keys);
        hashmap->vals   = realloc(hashmap->vals, (hashmap->capacity * sizeof(multitype*)));
        exit_w_one_on_failed_xalloc(hashmap->vals);
    }

    hashmap->keys[hashmap->cur_size]   = key;
    hashmap->vals[hashmap->cur_size]   = val;

    if(hashmap->last_size == 0 && hashmap->cur_size == 0) {
        hashmap->cur_size                 = hashmap->last_size + 1;
    } else if(hashmap->last_size == 0 && hashmap->cur_size == 1) {
        hashmap->last_size                = 1;
        hashmap->cur_size                 = 2;
    } else {
        hashmap->cur_size                 = hashmap->cur_size  + 1;
        hashmap->last_size                = hashmap->last_size + 1;
    }

    dump_hashmap(hashmap);
}

u_int16_t* hashmap_get_val_check_key_even_exists(hmap_t* hashmap, multitype* key)
{
	u_int16_t* ret_int_array = malloc(2 * sizeof(u_int16_t));
	u_int16_t keypos = hashmap_hash_key(hashmap, key);
	ret_int_array[0] = keypos;
	ret_int_array[1] = hashmap->vals[keypos]->ti;
	
	if((hashmap->cur_size - 1) != keypos) 
	    // If slot is not the same number as hashmap's current size keyhash was erroneous
	    return NULL;
	else	
        return ret_int_array;
}

multitype* hashmap_get_val(hmap_t* hashmap, multitype* key)
{
	u_int16_t* keypos_and_type_indicator = hashmap_get_val_check_key_even_exists(hashmap, key);
		
	if(!keypos_and_type_indicator)
	    //No value found for key of interest
	    return NULL;
	
	u_int16_t   keypos = keypos_and_type_indicator[0];
	type_indicator ti = keypos_and_type_indicator[1];
	
	free(keypos_and_type_indicator);

	return hashmap->vals[keypos];
}

void free_hashmap(hmap_t* hashmap)
{
    free(hashmap->keys);
    free(hashmap->vals);

    free(hashmap);
}
