#include <stdio.h>
#include "smart_ptr.h"
#include <vld.h>

class second;

class first
{
public:
	ptr_weak<second> secptr;
};

class second
{
public:
	ptr<first> secptr;
};
/*
 *  ---     ---
 *  | | --> | |
 *  | | <-- | |
 *  ---     ---
 *   ^       ^
 *   |       |
 *   p1      p2
 */
int main()
{
 	ptr<first> p1 (new first());
 	ptr<second> p2 (new second());
	p1->secptr = p2;
	p2->secptr = p1;
}
