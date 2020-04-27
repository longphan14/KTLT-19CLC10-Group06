#ifndef _STAFF_H_
#define _STAFF_H_
#include "Header.h"

struct staffData{
	string ID;
	string Password;
	const int type ; // la giam vu
	staffData() : type(1){};
};
#endif
