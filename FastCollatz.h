// --------------------------
// FastCollatz.h
// Copyright (C) 2015
// Adrian Iley
// --------------------------

#ifndef FastCollatz_h
#define FastCollatz_h

// --------
// includes
// --------

#include <cstdint>  // int64_t

/**
 * @param p the problem integer
 * @return the cycle length of p
 */
int collatz_plen (int64_t p);

#endif // FastCollatz_h
