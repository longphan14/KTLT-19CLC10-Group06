#ifndef _LECTURER_H_
#define _LECTURER_H_
#include "Header.h"
#include "Staff.h"

void editAttendance(string LecturerID);
void spinputLecturer(string LecturerID , string &filename, string &filename1, string &studentID, string &CourseID, string &Classname);
void viewAttendanceListOfLecturer(string ID);
void editScoreboard(string LecturerID);
void spinputLecturerScoreboard(string LecturerID , string &filename, string &filename1, string &studentID, string &CourseID, string &Classname);
#endif					
