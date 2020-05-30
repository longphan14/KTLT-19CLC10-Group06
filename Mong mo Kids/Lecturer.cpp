#include "Lecturer.h"

void editAttendance(string LecturerID){
	
	
	string filename, studentID, CourseID, filename1;
	
	spinputLecturer(LecturerID, filename, filename1, studentID, CourseID);
	if(filename == ""){
		return jobFeature();
	}

	while(true){
		int week;
		userData *student;
		int size = 0;
		ifstream fi;
		fi.open(filename.c_str());
		takeDataUser(fi, student, size, 4);
		fi.close();
	
		
		spviewAttendanceList(filename1, CourseID);
		cout << "Week to edit: ";
		cin >> week;
		for(int i = 0; i < size; i++){
			if(student[i].ID == studentID){
				int choice;
				cout << "Enter edit(1: appearance, 2: not appearance, 3: not available): ";
				cin >> choice;
				if(choice == 1)
					student[i].Attendance[week - 1] = 1;
				else if(choice == -1)
					student[i].Attendance[week - 1] = 0;
				else
					student[i].Attendance[week - 1] = -1;
				insertDataStudentInCourse(filename, student, size);
				cout << "Changed successfully!" << endl;
				string key;
				cout << "Press any key to return: ";
				cin >> key;
				system("CLS");
				return jobFeature();
			}
		}
	}
}


void spinputLecturer(string LecturerID , string &filename, string &filename1, string &studentID, string &CourseID){
	ifstream fi1, fi;
	string semesterCurrent;
	userData* Lecturer;
	courseData* Course;
	int size = 0;
	int S = 0;
	bool check = false;
	takeCurrentSemester(semesterCurrent);
	filename1 = "fileCourse/" + semesterCurrent + "-Schedule.txt";
	fi1.open(filename1.c_str());
	takeDataCourse(fi1, Lecturer, Course, size);
	fi1.close();
	for(int i = 0; i < size; i++){
		if(Lecturer[i].ID == LecturerID){
			cout << i + 1 << "." << Course[i].courseID << "-" << Course[i].courseName << endl;
			S++;
			check = true;
		}
	}
	int NO;
	cout << "Enter Number of Order: ";
	cin >> NO;
	CourseID = Course[NO - 1].courseID;
	filename = "fileCourse/" + semesterCurrent + "-" + Course[NO - 1].className + "-" + Course[NO - 1].courseID + "-Student.txt";
	ifstream fi2;
	userData* UserData; 
	courseData Course2;
	int size2;
	fi2.open(filename.c_str());
	takeDataUser(fi2, UserData, size2, 4);
	fi2.close();
	if(check == true){
		spviewStudentAttendanceList(filename);
		cout << "Enter Student ID: ";
		cin >> studentID;
		for(int i = 0; i < size2; i++){
			if(UserData[i].ID == studentID){
				while(true){
				cout << "Do you want to edit this student: " << endl;
				cout << "0.No     1. Yes" << endl;
				int numberChoice = choiceScreen(1);
				if(numberChoice == -1){
					cout << "Error Enter!" << endl;
				}
				else if(numberChoice == 0){
					filename = "";
					return;
					}
				else{
					return;
				}
				}
			}
		}
	}
	else{
		cout << "Don't have any course!";
	}
}
