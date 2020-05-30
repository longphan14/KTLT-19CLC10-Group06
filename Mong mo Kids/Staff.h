#ifndef _STAFF_H_
#define _STAFF_H_
#include "Header.h"

void updateSemester();

void importCourse();
void addCourse();
void viewListCourse();
void insertCourse(ifstream &filein, ofstream &fileout);
void editStudent();
void viewAllLecturer();
void viewListCourse();
void removeCourse();
void deleteSemester();
void viewSemester();
void addStudentToCourse();
void removeStudent();
void viewListStudentinCourse();
void removeStudentinCourse();
void searchViewAttendanceList();
void spviewAttendanceList(string filename, string courseID);
void viewAttendanceList();
void spviewStudentAttendanceList(string filename);
void searchViewScoreboardList();
void ViewScoreboardList();
void spViewScoreboardList();
void viewListStudentinClass();
void changeClass();
void editAttendance(string ID);
#endif
