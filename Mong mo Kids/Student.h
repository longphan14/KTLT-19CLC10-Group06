#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "Header.h"

struct scoreData{
	float Midterm;
	float Final;
	float Bonus;
	float Total;
};

struct studentData{
	int ID;	// MSSV
	string Name;
	int Gender; // gioi tinh , 0: Nam, 1: Nu
	string DoB;	// Ngay thang nam sinh
	string Password;
	int Attendance[20]; // Diem danh : 1: Co mat, 0: Vang
	int Status; // 0: Hoc sinh nay nghi hoc, 1: Hoc sinh nay van con di hoc
	scoreData Score; // Diem cua hoc sinh
	const int tpye; // type = 2 la hoc sinh
	studentData() : type(2){}; 
};
#endif
