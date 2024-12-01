/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "0xffff",
    /* First member's full name */
    "fa1c4",
    /* First member's email address */
    "azesinter@mail.ustc.edu.cn",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define init_size 0

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/* Block header/footer */
#define set_4(ptr, value) (*(unsigned int*)(ptr) = (value))
#define get_4(ptr) (*(unsigned int*)(ptr))
#define set_8(ptr, value) (*(unsigned long long*)(ptr) = (value))
#define get_8(ptr) (*(unsigned long long*)(ptr))
#define pack(size, if_use) ((size) | (if_use))
#define set_size(ptr, value) (set_4(ptr + 4, value))
#define get_size(ptr) (get_4(ptr + 4))
#define is_inuse(ptr) (get_size(ptr) & 1)

static char* mem_start_brk;
static char* mem_brk;
static char* mem_max_addr;

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    mem_init();
    mem_start_brk = mem_heap_lo();
    mem_sbrk(init_size);
    set_size(mem_start_brk, init_size);
    mem_brk = mem_start_brk;
    mem_max_addr = mem_start_brk + init_size;
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    int new_size = ALIGN(8 + size + SIZE_T_SIZE);
    int sign = 0;
    void* result;

    for (result = mem_brk;;) 
    {
        if (!is_inuse(result) && get_size(result) >= new_size) 
        {
            if (get_size(result) - new_size <= 8)
            {
                new_size = get_size(result);
                set_size(result, pack(new_size, 1)); // mark inuse flag
                set_4(result + new_size, new_size); // set size
            }
            else
            {
                set_4(result + get_size(result), get_size(result) - new_size);
                set_size(result + new_size, get_size(result) - new_size);
                set_4(result + new_size, new_size);
                set_size(result, pack(new_size, 1));
            }
            break;
        }

        if (result == mem_brk && sign) // extend heap
        {
            result = mem_sbrk(new_size);
            set_size(result, pack(new_size, 1));
            set_4(result + new_size, new_size);
            mem_max_addr += new_size;
            return result + 8;
        }

        result += get_size(result) & (~0-1);
        if (result >= mem_max_addr) 
        {
            result = mem_start_brk;
            sign = 1;
        }
    }

    mem_brk = result + new_size;
    if (mem_brk >= mem_max_addr) 
        mem_brk = mem_start_brk;
    return result + 8;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    char* p = ptr - 8;
    int pre_inuse, post_inuse, size;
    size = get_size(p) - 1;
    set_size(p, size & (~0-1));
    set_4(p + size, size);
    pre_inuse = is_inuse(p - get_4(p)) || (get_4(p) == 0);
    post_inuse = is_inuse(p + get_size(p)) || (p + size == mem_max_addr);
    if (!pre_inuse && !post_inuse) 
    {
        size = get_size(p) + get_size(p - get_4(p)) + get_size(p + get_size(p));
        p = p - get_4(p);
        set_size(p, size);
        set_4(p + size, size);
    }
    else if (!pre_inuse) 
    {
        size = get_size(p) + get_size(p - get_4(p));
        p = p - get_4(p);
        set_size(p, size);
        set_4(p + size, size);
    }
    else if (!post_inuse)
    {
        size = get_size(p) + get_size(p + get_size(p));
        set_size(p, size);
        set_4(p + size, size);
    }
    if (mem_brk > p && mem_brk < (p + size))
        mem_brk = p;
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void* p = ptr - 8;
    void* new_ptr;
    int new_size = ALIGN(8 + size + SIZE_T_SIZE);
    size_t copySize;
    int pre_inuse, post_inuse, p_size;
    p_size = get_size(p) - 1;
    copySize = p_size - 8;
    if (new_size > p_size) 
    {
        pre_inuse = is_inuse(p - get_4(p)) || (get_4(p) == 0);
        post_inuse = is_inuse(p + p_size);
        if (!pre_inuse) 
        {
            p_size += get_size(p - get_4(p));
            p = p - get_4(p);
            if (p_size >= new_size)
            {
                memcpy(p + 8, ptr, copySize);
                if (p_size - new_size <= 8)
                {
                    new_size = p_size;
                    set_size(p, pack(p_size, 1));
                    set_4(p + p_size, p_size);
                }
                else
                {
                    set_4(p + p_size, p_size - new_size);
                    set_size(p + new_size, p_size - new_size);
                    set_4(p + new_size, new_size);
                    set_size(p, pack(new_size, 1));
                }
                if (mem_brk > p && mem_brk < p + new_size)
                    mem_brk = p;
                return p + 8;
            }
        }

        if (!post_inuse) 
        {
            if (p + p_size == mem_max_addr)
            {
                if (!pre_inuse)
                    memcpy(p + 8, ptr, copySize);
                mem_sbrk(new_size - p_size);
                set_size(p, pack(new_size, 1));
                set_4(p + new_size, new_size);
                mem_max_addr += new_size - p_size;
                return p + 8;
            }
            else
            {
                p_size += get_size(p + p_size);
                if (p_size >= new_size)
                {
                    memcpy(p + 8, ptr, copySize);
                    if (p_size - new_size <= 8)
                    {
                        new_size = p_size;
                        set_size(p, pack(p_size, 1));
                        set_4(p + p_size, p_size);
                    }
                    else
                    {
                        set_4(p + p_size, p_size - new_size);
                        set_size(p + new_size, p_size - new_size);
                        set_4(p + new_size, new_size);
                        set_size(p, pack(new_size, 1));
                    }
                    if (mem_brk > p && mem_brk < p + new_size)
                        mem_brk = p;
                    return p + 8;
                }
            }
        }

        p = mm_malloc(size);
        memcpy(p, ptr, copySize);
        mm_free(ptr);
        return p;
    }
    else if (new_size < p_size - 8)
    {
        set_4(p + p_size, p_size - new_size);
        set_size(p + new_size, p_size - new_size);
        set_4(p + new_size, new_size);
        set_size(p, pack(new_size, 1));
    }

    return p + 8;
}
