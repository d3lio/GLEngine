#pragma once
#ifndef _ENGINE_DEFINES_H_
#define _ENGINE_DEFINES_H_

#undef NDEBUG
// Uncomment to remove assertions
//#define NDEBUG
#include <cassert>

#ifndef NULL
    #define NULL 0
#elif NULL != 0
    #undef NULL
    #define NULL 0
#endif

#define ENGINE_APIENTRY __declspec(dllexport)

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef long long int ll;
typedef unsigned long long int ull;

#endif