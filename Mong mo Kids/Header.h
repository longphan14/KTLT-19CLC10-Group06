#ifndef _HEADER_H_
#define _HEADER_H_
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


using namespace std;

struct accountData{
	string ID;
	string Password;
	string Name;
	int Gender;
};

struct scoreData{
	float Midterm;
	float Final;
	float Bonus;
	float Total;
};

struct userData{
	string ID;	// MSSV
	string Name;
	int Gender; // gioi tinh , 0: Nam, 1: Nu
	string DoB;	// Ngay thang nam sinh
	string Password;
	string className;
	int Attendance[20]; // Diem danh : 1: Co mat, 0: Vang
	int Status; // 0: Hoc sinh nay nghi hoc, 1: Hoc sinh nay van con di hoc
	scoreData Score; // Diem cua hoc sinh
	int Type; // 1: Giam vu , 2 : Hoc sinh, 3 : Giang vien
	string Degree;
};

struct courseData{
	string courseID;
	string courseName;
	string className;
	string lecturerAccount;
	string startDate;
	string endDate;
	string DoW;
	string startTime;
	string endTime;
	string Room;
};

//****SYSTEM*****//
int checkChoice(string Choice, int Number);
void clearScreen();
void warnScreen();
int choiceScreen(int Number);
int checkPassword(string, string, accountData &);
void insertDataUser(ofstream &fo, userData * &Data, int size);
void takeDataUser(ifstream &fi, userData * &Data, int &size, int type);
void takeDataCourse(ifstream &fi, userData * &Lecturer, courseData * &Course, int &size);
void insertDataCourse(ofstream &fo, userData * &Lecturer, courseData * &Course, int &size);
void changePassword(string Username, string Password, int type);

//***************//

//User Interface STAFF//
void Login();
void firstUI();
void showMenu();
void studentFeatureUI();
void editFeatureStu();
void viewFeatureStu();
void courseFeatureUI();
void editFeatureCourse();	
void staffUI();
//**************//	

//User Interface STUDENT//
void studentUI();
//*********************//

//User Interface LECTURER//
void lecturerUI();
//**********************//	
#endif					
