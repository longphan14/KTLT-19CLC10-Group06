#ifndef _LECTURER_H_
#define _LECTURER_H_
#include "Header.h"

struct lecturerData{
	string Name;
	string Gender;
	string Degree; // Bang cap
	string DoB;
	string Password;
	string ID;
	const int type;
	lecturerData() : type(2){};
};
#endif					
