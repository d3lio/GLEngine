/**
  * Debug Utils - definitions / declarations for debug routines.
  *
  * Purpose:
  *
  *     Easier debug procedures.
  */

#pragma once
#ifndef __DEBUGUTILS__
#define __DEBUGUTILS__

#include <assert.h>

#ifndef NDEBUG
    #define DEBUG(stream,format,...) fprintf (stream, "DEBUG: " format "\n  File: %s\n  Line: %d\n\n", __VA_ARGS__, __FILE__, __LINE__)
#else
    #define DEBUG(stream,format,...) ((void) 0)
#endif

#define ERROR(msg) fprintf (stderr, "ERROR: " msg "\n  File: %s\n  Line: %d\n\n", __FILE__, __LINE__)

template <typename T, size_t S>
inline size_t lengthOfArray2D (T a[][S])
{
    return sizeof (*a) / sizeof (T) * S;
}

template <typename T>
inline size_t lengthOfArray (T& a)
{
    return sizeof (T) / sizeof (*a);
}

#endif