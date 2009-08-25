// DeepLight Engine (c) Zeux 2006-2009

#pragma once

#include <lusp/object.h>
#include <lusp/memory.h>
#include <lusp/vm/bytecode.h>

static inline struct lusp_vm_upval_t* mkupval(struct lusp_vm_upval_t** list, struct lusp_object_t* ref)
{
    // look for ref in list
    for (struct lusp_vm_upval_t* upval = *list; upval; upval = upval->next)
        if (upval->ref == ref)
            return upval;
            
    // create new upval
    struct lusp_vm_upval_t* result = (struct lusp_vm_upval_t*)lusp_memory_allocate(sizeof(struct lusp_vm_upval_t));
    DL_ASSERT(result);
    
    result->ref = ref;
    result->next = *list;
    *list = result;
    
    return result;
}

static inline struct lusp_vm_upval_t* close_upvals(struct lusp_vm_upval_t* list, struct lusp_object_t* begin)
{
    while (list->ref >= begin)
    {
        struct lusp_vm_upval_t* next = list->next;
        
        list->object = *list->ref;
        list->ref = &list->object;
        
        list = next;
    }
    
    return list;
}

static inline struct lusp_object_t create_list(struct lusp_object_t* begin, struct lusp_object_t* end)
{
    DL_ASSERT(begin <= end);
    
    struct lusp_object_t head = lusp_mknull();
    struct lusp_object_t tail = lusp_mknull();
    
    for (struct lusp_object_t* i = begin; i != end; ++i)
    {
        struct lusp_object_t cell = lusp_mkcons(*i, lusp_mknull());
        
        if (tail.type != LUSP_OBJECT_NULL) tail = tail.cons[1] = cell;
        else head = tail = cell;
    }
    
    return head;
}

