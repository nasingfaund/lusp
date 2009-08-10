// DeepLight Engine (c) Zeux 2006-2009

#pragma once

struct lusp_object_t;
struct lusp_environment_t;
struct lusp_environment_slot_t;
struct lusp_vm_bytecode_t;

enum lusp_vm_opcode_t
{
	LUSP_VMOP_GET_OBJECT,
	LUSP_VMOP_GET_LOCAL,
	LUSP_VMOP_SET_LOCAL,
	LUSP_VMOP_GET_UPVAL,
	LUSP_VMOP_SET_UPVAL,
	LUSP_VMOP_GET_GLOBAL,
	LUSP_VMOP_SET_GLOBAL,
	LUSP_VMOP_PUSH,
	LUSP_VMOP_CALL,
	LUSP_VMOP_RETURN,
	LUSP_VMOP_JUMP,
	LUSP_VMOP_JUMP_IF,
	LUSP_VMOP_JUMP_IFNOT,
	LUSP_VMOP_CREATE_CLOSURE
};

struct lusp_vm_op_t
{
	enum lusp_vm_opcode_t opcode;
	
	union
	{
		struct
		{
			struct lusp_object_t* object;
		} get_object;
		
		struct
		{
			unsigned int index;
		} getset_local;
		
		struct
		{
			unsigned int index;
		} getset_upval;
		
		struct
		{
			struct lusp_environment_slot_t* slot;
		} getset_global;
		
		struct
		{
            unsigned int count;
		} call;
		
		struct
		{
		    int offset;
		} jump;
		
		struct
		{
		    struct lusp_vm_bytecode_t* code;
		} create_closure;
	};
};

struct lusp_vm_closure_t
{
	struct lusp_object_t** upvals[1];
};

struct lusp_vm_bytecode_t;

typedef struct lusp_object_t* (*lusp_vm_evaluator_t)(struct lusp_vm_bytecode_t* code, struct lusp_vm_closure_t* closure, struct lusp_object_t** eval_stack, unsigned int arg_count);

struct lusp_vm_bytecode_t
{
    struct lusp_environment_t* env;
    
    unsigned int local_count;
    unsigned int upval_count;

	struct lusp_vm_op_t* ops;
	unsigned int op_count;

	void* jit;
	
	lusp_vm_evaluator_t evaluator;
};

void lusp_dump_bytecode(struct lusp_vm_bytecode_t* code, bool deep);
