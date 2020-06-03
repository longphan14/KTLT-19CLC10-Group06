#include "Lecturer.h"

void editAttendance(string LecturerID){
	
	
	string filename, studentID, CourseID, filename1, Classname;
	
	spinputLecturer(LecturerID, filename, filename1, studentID, CourseID, Classname);
	if(filename == ""){
		return jobFeature();
	}

	while(true){
		string week2;
		userData *student;
		int size = 0;
		ifstream fi;
		fi.open(filename.c_str());
		takeDataUser(fi, student, size, 4);
		fi.close();
	
		
		spviewAttendanceList(filename1, CourseID);
		stringstream week1;
		int week;
		cout << "Week to edit: ";
		cin >> week2;
		week1 << week2;
		week1 >> week;
		if(week == 0 || week > size){
			cout << "Invalid Enter!" << endl;
			return jobFeature();
		}
		for(int i = 0; i < size; i++){
			if(student[i].ID == studentID){
				stringstream choice2;
				string choice1;
				int choice;
				cout << "Enter edit(1: appearance, 2: not appearance, 3: not available): ";
				cin >> choice1;
				choice2 << choice1;
				choice2 >> choice;
				if(choice == 0 || choice > 3){
					cout << "Invalid Enter!" << endl;
					return jobFeature();
				}
				else if(choice == 1)
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


void viewAttendanceListOfLecturer(string ID){
	int size = 0;
	string currentSemester;
	string LecturerChoice[100];
	userData* Lecturer;
	courseData* Course;
	takeCurrentSemester(currentSemester);
	ifstream fi;
	ifstream fi2;
	string filename ="fileCourse/" + currentSemester + "-Schedule.txt";
	fi.open(filename.c_str());
	takeDataCourse(fi, Lecturer, Course, size);
	int number = 0;	
	courseData courseLecturer[50];		
	for (int i = 0; i < size; i++){
		if (ID == Lecturer[i].ID){
			cout << "Classes Instructed: " << endl;
			cout << number << ". "<< Course[i].courseID << " - " <<  Course[i].courseName << endl;
			courseLecturer[number++] = Course[i];
		}	
	}
	if (number == 0){
		cout << "This lecturer does not instruct any class!!" << endl;
		cout << "Press any keys to return!" << endl;
		string key;
		cin >> key;
		system("CLS");
		viewFeatureOfLecturer();
	}
	cout << "Please choose class to view attendance list!" << endl;
	int numberChoice = choiceScreen(number - 1);
	string filename2 = "fileCourse/" + currentSemester + "-" + courseLecturer[numberChoice].className+ "-" + courseLecturer[numberChoice].courseID +"-Student.txt";
	if (numberChoice == -1){
		cout << "Wrong Class!" << endl;
	}
	else
	{
		spviewStudentAttendanceList(filename2);	
	}
	cout << "Press any keys to return!!" << endl;
	string key;
	cin >> key;
	system("CLS");
	viewFeatureOfLecturer();
}


void editScoreboard(string LecturerID){
	string filename, studentID, CourseID, filename1, Classname;
	spinputLecturerScoreboard(LecturerID, filename, filename1, studentID, CourseID, Classname);
	if(filename == ""){
		return jobFeature();
	}

	while(true){
		userData *student;
		int size = 0;
		ifstream fi;
		fi.open(filename.c_str());
		takeDataUser(fi, student, size, 4);
		fi.close();
		stringstream ss1, ss2, ss3, ss4;
		string midterm1, bonus1, final1, total1;
		int midterm, bonus, final, total;
		cout << "Midterm: " ;
		cin >> midterm1;
		ss1 << midterm1;
		ss1 >> midterm;
		cout << "Bonus: " ;
		cin >> bonus1;
		ss2 << bonus1;
		ss2 >> bonus;
		cout << "Final: ";
		cin >> final1;
		ss3 << final1;
		ss3 >> final;
		cout << "Total: ";
		cin >> total1;
		ss4 << total1;
		ss4 >> total;
		for(int i = 0; i < size; i++){
			if(student[i].ID == studentID){
					student[i].Score.Midterm = midterm;
					student[i].Score.Bonus = bonus;
					student[i].Score.Final = final;
					student[i].Score.Total = total;
				cout << "Do you want to edit this student like this: " << endl;
				cout << student[i].Name << "  " << student[i].Score.Midterm << "  " << student[i].Score.Bonus << "  " << student[i].Score.Final << "  " << student[i].Score.Total << endl;
				stringstream dd;
				string Choicea;
				int Choice;
				cout << "1.Yes   2.No  Your Choice: " ;
				cin >> Choicea;
				dd << Choicea;
				dd >> Choice;
				if(1 == Choice){
					insertDataStudentInCourse(filename, student, size);
					cout << "Changed successfully!" << endl;
					string key;
					cout << "Press any key to return: ";
					cin >> key;
					system("CLS");
					return jobFeature();
				}
				else if(2 == Choice)
					cout << "Ending Edit" << endl;
					
				else 
					cout << "Invalid Enter" << endl;
				string key;
				cout << "Press any key to return: ";
				cin >> key;
				system("CLS");
				return jobFeature();
			}
		}
	}
}

void spinputLecturerScoreboard(string LecturerID , string &filename, string &filename1, string &studentID, string &CourseID, string &Classname){
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
	int S1 = 0;
	int stt = 0;
	for (int i = 0; i < size; i++)
	if (Lecturer[i].ID == LecturerID)
	{
		cout << ++stt << ". " << Course[i].courseID << "-" << Course[i].courseName << endl;
		check = true;
	}

	string NOCheck;
	cout << "Enter Number of Order: ";
	cin >> NOCheck;
	int checking = checkChoice(NOCheck, stt);
	if (("0" == NOCheck) || (-1 == checking))
	{
		//Sai
		cout << "Invalid Enter!" << endl;
		return jobFeature();
	}
	int NO;
	stringstream ss;
	ss << NOCheck;
	ss >> NO;
	
	CourseID = Course[NO - 1].courseID;
	Classname = Course[NO - 1].className;
	filename = "fileCourse/" + semesterCurrent + "-" + Course[NO - 1].className + "-" + Course[NO - 1].courseID + "-Student.txt";
	ifstream fi2;
	userData* UserData; 
	courseData Course2;
	int size2;
	fi2.open(filename.c_str());
	takeDataUser(fi2, UserData, size2, 4);
	fi2.close();
	string NO1;
	if(check == true){
		spViewScoreboardList(CourseID, Classname);
		cout << "Enter Student Number of Order(0 to exit): ";
		cin >> NO1;
		int checking = checkChoice(NO1, size2);
	if (("0" == NO1) || (-1 == checking))
	{
		cout << "Invalid Enter!" << endl;
		return jobFeature();
	}
	int NO;
	stringstream ss;
	ss << NO1;
	ss >> NO;
		studentID = UserData[NO - 1].ID;
		for(int i = 0; i < size2; i++){
			if(i == NO - 1){
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


void spinputLecturer(string LecturerID , string &filename, string &filename1, string &studentID, string &CourseID, string &Classname){
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
	int S1 = 0;
	int stt = 0;
	for (int i = 0; i < size; i++)
	if (Lecturer[i].ID == LecturerID)
	{
		cout << ++stt << ". " << Course[i].courseID << "-" << Course[i].courseName << endl;
		check = true;
	}

	string NOCheck;
	cout << "Enter Number of Order: ";
	cin >> NOCheck;
	int checking = checkChoice(NOCheck, stt);
	if (("0" == NOCheck) || (-1 == checking))
	{
		//Sai
		cout << "Invalid Enter!" << endl;
		return jobFeature();
	}
	int NO;
	stringstream ss;
	ss << NOCheck;
	ss >> NO;
	
	CourseID = Course[NO - 1].courseID;
	Classname = Course[NO - 1].className;
	filename = "fileCourse/" + semesterCurrent + "-" + Course[NO - 1].className + "-" + Course[NO - 1].courseID + "-Student.txt";
	ifstream fi2;
	userData* UserData; 
	courseData Course2;
	int size2;
	fi2.open(filename.c_str());
	takeDataUser(fi2, UserData, size2, 4);
	fi2.close();
	string NO1;
	if(check == true){
		spviewStudentAttendanceList(filename);
		cout << "Enter Student Number of Order(0 to exit): ";
		cin >> NO1;
		int checking = checkChoice(NO1, size2);
	if (("0" == NO1) || (-1 == checking))
	{
		cout << "Invalid Enter!" << endl;
		return jobFeature();
	}
	int NO;
	stringstream ss;
	ss << NO1;
	ss >> NO;
		studentID = UserData[NO - 1].ID;
		for(int i = 0; i < size2; i++){
			if(i == NO - 1){
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
