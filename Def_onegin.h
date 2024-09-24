//#define __DBACK

#ifdef __DBACK
    #define  __danya_back( ... )  __VA_ARGS__
#else
    #define __danya_back(...)
#endif

#include "TxLib.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

//#define DEBUG

#ifdef DEBUG
#define dbg        if (1)
#define DBG(...)   __VA_ARGS__
#else
#define dbg        if (0)
#define DBG(...)
#endif

typedef int(*Cmpr_fn_t)(const void*  a, const void* b);

struct STRING
{
    char* str_addr;
    char* end_addr;
};

struct ONEGIN
{
    long fsize, string_quantity;
    char* buffer_addr;
    STRING* str_data;
    STRING* original_data;
    const char * name;
};
