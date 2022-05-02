#include "stdafx.h"
// Work on this file
// change size_t to 8 bit
void * operator new(size_t n)
{
	void * const p = malloc(n);
	// handle p == 0
	return p;
}

void operator delete(void * p) // or delete(void *, std::size_t)
{
	free(p);
}