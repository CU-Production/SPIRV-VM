#ifndef __SPIRV_VM_RESULT_H__
#define __SPIRV_VM_RESULT_H__

#include <spvm/types.h>
#include <spvm/value.h>
#include <spvm/spirv.h>

enum spvm_result_type {
	spvm_result_type_none,
	spvm_result_type_string,
	spvm_result_type_extension,
	spvm_result_type_function_type,
	spvm_result_type_type,
	spvm_result_type_variable,
	spvm_result_type_constant,
	spvm_result_type_function,
	spvm_result_type_access_chain,
	spvm_result_type_label
};
typedef struct {
	spvm_word argc;
} spvm_function_info;
typedef struct {
	SpvDecoration type;
	spvm_word literal1, literal2;
} spvm_decoration;
typedef struct spvm_result {
	char type;

	spvm_string name;
	spvm_word pointer; // pointer to spvm_result
	SpvStorageClass storage_class;
	struct spvm_result* parameter_owner;

	spvm_word value_count;
	spvm_value* value;

	spvm_word decoration_count;
	spvm_decoration* decorations;

	/* spvm_result_type_function */
	spvm_word return_type;

	/* spvm_result_type_extension */
	spvm_word extension_name; // index in the spvm_program::imports

	/* spvm_result_type_function_type */
	spvm_word param_count;
	spvm_word* param_type;

	/* function & label */
	spvm_source source_location;

	/* op type */
	char value_type;
	unsigned int value_bitmask;
	char value_sign;
} spvm_result;
typedef spvm_result* spvm_result_t;


void spvm_decoration_read(spvm_source src, SpvDecoration decor, spvm_word* literal1, spvm_word* literal2);
void spvm_result_add_decoration(spvm_result_t result, SpvDecoration decor, spvm_word literal1, spvm_word literal2);
void spvm_result_allocate_value(spvm_result_t val, spvm_word count);
void spvm_result_allocate_typed_value(spvm_result_t val, spvm_result* results, spvm_word type);

#endif // __SPIRV_VM_RESULT_H__