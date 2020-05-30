#include "Student.h"

//Ham support
bool viewSchedules_checkStudent(string courseID, string className, string IDStudent)//Hao: Check SV co nam trong du lieu hay khong 
{
	//Lay ten file
	string currentSemester = "";
	takeCurrentSemester(currentSemester);
	string fileName = "fileCourse/" + currentSemester + "-" + className + "-" + courseID + "-Student.txt";
	//Lay du lieu tu file
	userData * Student;
	int n;			
	ifstream fi;				
	fi.open(fileName.c_str());
	takeDataUser(fi, Student, n, 4);
	fi.close();
	
	//Check SV
	for (int i = 0; i < n; i++)
		if (IDStudent == Student[i].ID)
			return true;
	
	return false;
}

void viewSchedules_findCourse(string IDStudent, courseData studentCourse[], string lecturerName[], int &ncStudent) // Tim tat ca mon hoc hien co
{
	//Lay hoc ki hien tai 
	string currentSemester = "";
	takeCurrentSemester(currentSemester);
	//Lay du lieu tat ca mon hoc
	courseData * Course;
	userData * Lecturer;	
	int nCourse = 0;
	string fileName = "fileCourse/" + currentSemester + "-Schedule.txt";
	ifstream fi;
	fi.open(fileName.c_str());						
	takeDataCourse(fi, Lecturer, Course, nCourse);
	fi.close();
	//Duyet tat ca mon hoc 
	for (int i = 0; i < nCourse; i++)
		if (viewSchedules_checkStudent(Course[i].courseID, Course[i].className, IDStudent))
		{						
			lecturerName[ncStudent] = Lecturer[i].Name;							
			studentCourse[ncStudent++] = Course[i];
		}
}					

void viewSchedules_printSpace(int number)		
{
	for (int i = 0; i < number; i++)
		cout << " ";
}
void viewSchedules_print(int Thu, int stt) // HAo : Danh dau check cho mon hoc
{
	if (-1 == stt)
		cout << " ";
	else
		cout << stt;
	
	int number = 0;						
	switch(Thu)
	{
		case 2: case 6:
		{
			number = 6;
			break;   
		}
		case 3:
		{
			number = 7;
			break;
		}
		case 4: case 5:
		{
			number = 8;
			break;
		}
	}
	viewSchedules_printSpace(number);
}		

//HAm chinh					

void viewSchedules(string ID) //Hao: Hien ra thoi khoa bieu cho hoc sinh
{
	//Lay danh sach cac mon hoc ma sinh vien dang co
	courseData studentCourse[20];
	string Lecturer[20];										
	int nCourse = 0;
	viewSchedules_findCourse(ID, studentCourse, Lecturer, nCourse);
	//HIen ra danh sach mon hoc de sinh vien chon
	cout <<"The course which you enroll" << endl;
	for (int i = 0; i < nCourse; i++)
	{									
		cout << i + 1 << ". " << studentCourse[i].courseName << endl;
		cout << ">> Lecturer: " << Lecturer[i] << endl;
		cout << "**********************************" << endl;
	}						
	//Notes
	cout << "Time 1 : 7 30 -> 9 30" << endl;
	cout << "Time 2 : 9 30 -> 11 30" << endl;
	cout << "Time 3 : 13 30 -> 15 30" << endl;
	cout << "Time 4 : 15 30 -> 17 30" << endl;
	cout << "Number is numerical order of course above" << endl;
	cout << "**********************************" << endl;							
	//Hien ra tohi khoa bieu
	cout << "        Monday Tuesday Wednsday Thursday Friday Saturday" << endl;
	cout << "Time 1  ";
	for (int DoW = 2; DoW <= 7; DoW++)
	{
		bool dd = false;
		for (int stt = 0; stt < nCourse; stt++)
		if (studentCourse[stt].startTime == "7 30")
		{
			if (studentCourse[stt].DoW[0] == char(DoW + 48))
			{				
				viewSchedules_print(DoW, stt + 1);
				dd = true;
				break;
			}
		}
		if (!dd)
			viewSchedules_print(DoW, -1);
	}
	cout << endl;
	cout << "Time 2  ";
	for (int DoW = 2; DoW <= 7; DoW++)
	{
		bool dd = false;
		for (int stt = 0; stt < nCourse; stt++)
		if ((studentCourse[stt].startTime == "9 30") || (studentCourse[stt].endTime == "11 30"))
		{
			if (studentCourse[stt].DoW[0] == char(DoW + 48))
			{				
				viewSchedules_print(DoW, stt + 1);
				dd = true;
				break;
			}
		}
		if (!dd)
			viewSchedules_print(DoW, -1);
	}
	cout << endl;
	cout << "Time 3  ";
	for (int DoW = 2; DoW <= 7; DoW++)
	{
		bool dd = false;
		for (int stt = 0; stt < nCourse; stt++)
		if(studentCourse[stt].startTime == "13 30")
		{
			if (studentCourse[stt].DoW[0] == char(DoW + 48))
			{				
				viewSchedules_print(DoW, stt + 1);
				dd = true;
				break;
			}
		}
		if (!dd)
			viewSchedules_print(DoW, -1);
	}
	cout << endl;
	cout << "Time 4  ";
	for (int DoW = 2; DoW <= 7; DoW++)
	{
		bool dd = false;
		for (int stt = 0; stt < nCourse; stt++)
		if ((studentCourse[stt].startTime == "15 30") || (studentCourse[stt].endTime == "17 30"))
		{
			if (studentCourse[stt].DoW[0] == char(DoW + 48))
			{				
				viewSchedules_print(DoW, stt + 1);
				dd = true;
				break;
			}
		}
		if (!dd)
			viewSchedules_print(DoW, -1);
	}
	cout << endl;
	cout << "Press any key to return" << endl;
	string key;
	cin >> key;
	system("CLS");
	return studentShowMenu();
}
