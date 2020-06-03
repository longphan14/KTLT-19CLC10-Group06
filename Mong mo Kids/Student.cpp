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

void check_in_convertTime(string &timeReal, int timeConvert, int type)
{
	stringstream ss;
	ss << timeConvert;
	ss >> timeReal;
	if ((timeConvert < 10) && (1 == type))
		timeReal = '0' + timeReal;
}

void check_in_takeTime(string &dateNow, string &timeNow)
{
	time_t t = time(0);
	tm* now = localtime(&t);
	string year;
	//Lay date hien tai
	check_in_convertTime(year, now -> tm_year + 1900, 1);
	string month;
	check_in_convertTime(month, now -> tm_mon + 1, 1);
	string day;
	check_in_convertTime(day, now -> tm_mday, 1);
	dateNow = year + " " + month + " " + day;

	// Lay time hien tai
	string hour;
	check_in_convertTime(hour, now -> tm_hour, 2);
	string minute;
	check_in_convertTime(minute, now -> tm_min, 2);
	timeNow = hour + " " + minute;
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

void viewCheckIn(string StudentID){
	courseData studentCourse[30];
	string lecturerName[30];
	int size = 0;
	viewSchedules_findCourse(StudentID, studentCourse, lecturerName, size);
	for(int i = 0; i < size; i++){
		cout << i + 1 << "." << studentCourse[i].courseID << "-" << studentCourse[i].courseName << "   Lecturer Name: " << lecturerName[i] << endl;
	}
	string NO1;
	stringstream NOSS;
	int NO;
	cout << "Enter Number of Order: ";
	cin >> NO1;
	NOSS << NO1;
	NOSS >> NO;
	if(NO == 0 || NO > size || NO < 0){
		cout << "Invalid Enter!" << endl;
		return studentShowMenu();
	}
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	string filename;
	filename = "fileCourse/" + semesterCurrent + "-" + studentCourse[NO - 1].className + "-" + studentCourse[NO - 1].courseID + "-Student.txt";
	ifstream fi;
	fi.open(filename.c_str());
	userData* studentdata;
	int size1 = 0;
	takeDataUser(fi, studentdata, size1, 4);
	cout << "  Student Name                ";
	for(int i = 0; i < 10; i++){
		cout << "Week " << i + 1 << " ";
	} 
	cout << endl;
	for(int i = 0; i < size1; i++){
		if(studentdata[i].ID == StudentID){
		cout << studentdata[i].Name;
		int length = studentdata[i].Name.length();
		for (int j = 0; j < 30 - length; j++)
			cout << " ";
		for(int j = 0; j < 10; j++){
			if(studentdata[i].Attendance[j] == 0)
				cout << "X";
			else if(studentdata[i].Attendance[j] == 1)
				cout << "V";
			else if(studentdata[i].Attendance[j] == -1)
				cout << "O";
			for (int k = 0; k < 6; k++)
				cout << " ";
		}
		cout << studentdata[i].ID;
		cout << endl;
	}
	}
	cout << endl;
	cout << "Press any key to return" << endl;
	string key;
	cin >> key;
	system("CLS");
	return studentShowMenu();
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

void check_in_takeDateCourse(string fileName, string Date[])
{
	ifstream fi;
	fi.open(fileName.c_str());
	ignoreLine(fi, 11);
	string dateTmp;
	for (int i = 0; i < 10; i++)
	{
		getline(fi, dateTmp);
		int count = 0;
		int m = 0;				
		Date[i] = "";
		while (count != 3)
		{
			if (' '  == dateTmp[m])
				count++;
			if (count != 3)
				Date[i] += dateTmp[m];
			m++;
		}
	}
	fi.close();			
}

void check_in_support(courseData Course, string ID) // Danh dau check va ho tro cho ham check_in
{
	string currentSemester = "";
	takeCurrentSemester(currentSemester);
	
	//Lay du lieu trong file
	string fileName = "fileCourse/" + currentSemester + "-" + Course.className + "-" + Course.courseID + "-Student.txt";
	int nStudent = 0;
	userData * Student;
	ifstream fi;
	fi.open(fileName.c_str());
	takeDataUser(fi, Student, nStudent, 4);
	fi.close();
	//Take Date and time Now
	string dateNow, timeNow;
	check_in_takeTime(dateNow, timeNow);
	//Find ID
	int STT = -1;
	for (int i = 0; i < nStudent; i++)
	if (Student[i].ID == ID)
	{
		STT = i;
		break;
	}
	//Take time and date
	string Date[20];
	check_in_takeDateCourse(fileName, Date);

	//Check in
	for (int i = 0; i < 10; i++)
	if (dateNow == Date[i])
	{
		if ((timeNow >= Course.startTime) && (timeNow <= Course.endTime))
		{
			Student[STT].Attendance[i] = 1;
			cout << "Check in successfully" << endl;
			break;
		}
	}
	cout << "Check in is failed" << endl;
	//Dua lai du lieu vao trong
	insertDataStudentInCourse(fileName, Student, nStudent);
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

void check_in(string ID)//Hao : HAm diem danh cua hoc sinh
{
	//Lay danh sach mon hoc ma sinh vien tham gia
	int nCourse = 0;
	string Lecturer[20];
	courseData Course[20];
	viewSchedules_findCourse(ID, Course, Lecturer, nCourse);
	//Hien ra danh sach mon hoc cho nguoi dung chon
	int numberChoice = -1;
	while (-1 == numberChoice)
	{
		cout << "List course is enrolled by you :" << endl; 
		for (int i = 0; i < nCourse; i++)
		{
			cout << i + 1 << ". ";
			cout << "Course Name : " << Course[i].courseName << endl;
			cout << "Lecturer : " << Lecturer[i] << endl;
			cout << "Start time : " << Course[i].startTime << endl;
			cout << "End time : " << Course[i].endTime << endl;
			cout << "********************************" << endl;
		}
		cout << "0. Return" << endl;
		cout << "If you don't want check_in please press 0" << endl;
		cout << "Choose your choice to check_in" << endl;
		numberChoice = choiceScreen(nCourse);
		system("CLS");
		if (-1 == numberChoice)
			cout << "Your choice isn't wrong !! Please choose again " << endl;
		else if (0 == numberChoice)
			studentShowMenu();
	}
	//Bat dau diem danh
	cout << "Your course you choose is : " << endl;
	cout << ">>" << Course[numberChoice - 1].courseName << endl;
	check_in_support(Course[numberChoice - 1], ID);
	
	cout << "Press any key to return" << endl;
	string key;
	cin >> key;
	system("CLS");
	studentShowMenu();
}
