#include "Staff.h"

//Nhung Ham ho tro cho viec code Tinh nang STAFF//
void copyData(ifstream &fi, ofstream &fo) // copy data from fi to fo
{
	string s;
	int dem = 0;
	while (!fi.eof())
	{
		getline(fi, s);
		if (s == "")
		{
			dem ++;
			if (dem <= 1)
				fo << s << endl;
		}
		else
		{
			dem = 0;
			fo << s << endl;
		}
	}
}

void editStudentInFile(string className, string courseName, string ID, userData Data) //Hao: Duyet tung phan tu cuar file student in course
{
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	string fileName;
	fileName = "fileCourse/" + semesterCurrent + "-" + className + "-" + courseName + "-" + "Student.txt";
	
	userData * Student;
	int size;
								
	ifstream fi;
	fi.open(fileName.c_str());
	takeDataUser(fi, Student, size, 4);
	fi.close();					
	
	for (int i = 0; i < size; i++)
	if (Student[i].ID == ID)
	{
		Student[i].ID = Data.ID;
		Student[i].Name = Data.Name;
		Student[i].Gender = Data.Gender;
		Student[i].DoB = Data.DoB;
	}
	insertDataStudentInCourse(fileName, Student, size);
}

bool checkCSV(string fileName)
{
	int n = fileName.length();
	if (fileName[n - 1] != 'v')
		return false;
	if (fileName[n - 2] != 's')
		return false;
	if (fileName[n - 3] != 'c')
		return false;
	return true;
}

void addDataCourse(string fileName, userData Lecturer, courseData Course)
{

	//Dua du lieu Course vao file Schedule.txt
	courseData * courseList;
	userData * lecturerList;
	int size = 0;			
	// Lay list course tu file
	ifstream fi;
	fi.open(fileName.c_str());
	if (!fi.is_open())
	{
		ofstream fo;
		fo.open(fileName.c_str());
		fo << 0 << endl;
		fo.close();
	}
	takeDataCourse(fi, lecturerList, courseList, size);
	fi.close();										
	
	//Kiem tra xem co ton tai chua 
	
	bool check = true;				
	for (int i = 0; i < size; i++)
		if ((courseList[i].courseID == Course.courseID))
		{
			check = false;
			break;
		}
	
	//Dua du lieu vao file
	
	if (check)
	{	
		ofstream fo;
		fo.open(fileName.c_str());
		//Them du lieu vao phan tu cuoi cung cuar lecturerList va courseList
		lecturerList[size] = Lecturer;
		courseList[size] = Course;
		size++;																		 
		insertDataCourse(fo, lecturerList, courseList, size);		
		fo.close();				
	}
												
	//Xoa du lieu trong heap
	delete [] lecturerList;
	delete [] courseList; 
}

void addStudentForImportCourse(userData Lecturer, courseData Course)
{
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	userData * Student;
	int size = 0;											
	//LAy du lieu trong file (class)-student.txt
	string fileName;
	fileName = "fileClass/" + Course.className + "-Student.txt";
	ifstream fi;
	fi.open(fileName.c_str());
	takeDataUser(fi, Student, size, 2);					
	fi.close();				
	
	//Them bang diem va bang diem danh
	for (int i = 0; i < size; i++)
	{					
		Student[i].Score.Midterm = -1;
		Student[i].Score.Final = -1;
		Student[i].Score.Bonus = -1;
		Student[i].Score.Total = -1;
		for (int j = 0; j < 10; j++)
			Student[i].Attendance[j] = -1;
	}	
	
	//Dua du lieu vao file (hoc ki)-(mon hoc)-(class)-Student.txt
	fileName = "fileCourse/" + semesterCurrent + '-' + Course.className + '-' + Course.courseID + "-Student.txt";	
	insertDataStudentInCourse(fileName, Student, size);
}

void addDataForImportCourse(userData Lecturer, courseData Course) // Ham dua du lieu vao ho tro import course
{
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	//Dua du lieu Course vao file (Hoc ki)-Schedule.txt
	string fileName = "fileCourse/" + semesterCurrent + "-Schedule.txt"; 
	addDataCourse(fileName, Lecturer, Course);
	//Dua du lieu Course vao file (Hoc ki)-(Ten lop)-Schedule.txt
	
	//TAo file (hoc ki)-(Ten lop)-Schedule.txt
	fileName = "fileCourse/" + semesterCurrent + '-' + "Schedule-" + Course.className + ".txt";
	addDataCourse(fileName, Lecturer, Course);
	
	//Dua du lieu Lecturer vao file Lecturer.txt
	userData * lecturerList;
	int size = 0;
										
	fileName = "fileUser/Lecturer.txt";
	ifstream fi;
	fi.open(fileName.c_str());
	takeDataUser(fi, lecturerList, size, 3);
	fi.close();						
	
	//Kiem tra xem co ton tai Lecture trong list hay chua 
	bool check = true;
	for (int i = 0; i < size; i++)
		if (lecturerList[i].ID == Lecturer.ID)
		{
			check = false;
			break;
		}
	
	//Dua du lieu vao
	ofstream fo;
	if (check)
	{
		lecturerList[size++] = Lecturer;

		fo.open(fileName.c_str());
		insertDataUser(fo, lecturerList, size);
		fo.close();									
	}
	
	//Dua du lieu hoc sinhg vao file (hoc ki)-(ten lop)-(Ten mon hoc)-Student.txt
	addStudentForImportCourse(Lecturer, Course);
}

void formatDate(string &Date)
{
		//Format khi no sai
	bool check = false;
	int n = Date.length();
	for (int i = 0; i < n; i++)
		if ((Date[i] < '0') || (Date[i] > '9'))
		{
			if ((Date[i] != ' ') && (Date[i] != '-'))
			{
				check = true;
				break;
			}
		}

	//Dua ve dung dang yyyy mm dd
	string newDate = "";
	string year = "", month = "", day = "";
	int i = 0;
	while ((Date[i] <= '9') && (Date[i] >= '0'))
		year += Date[i++];
	if (year.length() > 2)
		check = true;
	i++;
	while ((Date[i] <= '9') && (Date[i] >= '0'))
		month += Date[i++];
		
	if (month.length() > 2)
		check = true;

	if (month.length() == 1)
		month = '0' + month;
		
	i++	;
	while ((Date[i] <= '9') && (Date[i] >= '0'))
		day += Date[i++];
	
	if (day.length() > 2)
		check = true;
		
	if (day.length() == 1)
		day = '0' + day;
	
	if (check)
	{
		Date = "2020 00 00";
		return;
	}
	Date = year + ' ' + month + ' ' + day ;
}

void showCourse(userData Lecturer, courseData Course) // hien ra danh sach mon hoc
{
	cout << "Information Course you add" << endl;
	cout << "Course ID :" << Course.courseID << endl;
	cout << "Course name :" << Course.courseName << endl;
	cout << "Class of course :" << Course.className << endl;
	cout << "Room :" << Course.Room << endl;
	cout << "Start date :" << Course.startDate << endl;
	cout << "End date :" << Course.endDate << endl;
	cout << "Start time :" << Course.startTime << endl;
	cout << "End time :" << Course.endTime << endl;
	cout << "Information Lecturer who teach this course" << endl;
	cout << "ID lecturer :" << Lecturer.ID << endl;
	cout << "Name of lecturer :" << Lecturer.Name << endl;
	cout << "Gender of Lecturer :";
	if (Lecturer.Gender == 0)
		cout << "Male";
	else
		cout << "Female";
	cout << endl;
	cout << "Degree of lecturer :" << Lecturer.Degree << endl;
}


//**********************************************//

//Tinh Nang cua User STAFF//

void importCourse() {
	//Giao dien dau vao
	cout << "Do you want to import course ?" << endl;
	cout << "0.No                 1.Yes" << endl;
	int numberChoice = choiceScreen(1);
	system("CLS");
	switch(numberChoice)
	{
		case 0:
		{
			editFeatureCourse();
			break;	
		}	
		case -1:
		{
			cout << "Your choice is wrong !! Choice again" << endl;
			importCourse();
			break;
		}
	}
	//Cho nguoi dung nhap file
	string fileName;
	cout << "Enter locate file csv you want import (Example c:\\download\\aaa.csv) :" ;
	cin >> fileName;
	
	ifstream fi;
	fi.open(fileName.c_str());
	system("CLS");	
	//Check xem file co dung yeu cau khong 
	if (!fi.is_open())
	{
		cout << "Don't find your file !! Try again" << endl;
		importCourse();
	}
	else
	{
		if (!checkCSV(fileName))
		{											
			cout << "Your file isn't CSV type !! Try again" << endl;
			importCourse();
		}
										
	}
	numberChoice = -1;				
	while (numberChoice == -1)
	{
		cout << "Are you sure to import course ? "  << endl;
		cout << "0.No                1.Yes" << endl;
		numberChoice = choiceScreen(1);
		switch(numberChoice)
		{
			case 0:
			{
				system("CLS");
				editFeatureCourse();
				break;	
			}	
			case -1:
			{
				system("CLS");
				cout << "Your choice is wrong !! Choice again" << endl;
				break;
			}
		}
	}
	//Lay du lieu
	userData Lecturer;
	courseData Course;
	
	fi.ignore(500, '\n');
	while (!fi.eof())
	{
		string No;
		getline(fi, No, ',');
		if ((No == "") || (No == " "))
			break;
		else if (No.length() >= 2)
		{
			if ((No[0] == ' ') && (No[1] == ' '))
				break;
		}
		getline(fi, Course.courseID, ',');
		
		getline(fi,Course.courseName, ',');
		
		getline(fi, Course.className, ',');
		
		getline(fi,Course.lecturerAccount, ',');
		Lecturer.ID = Course.lecturerAccount;
		Lecturer.Password = Lecturer.ID;
		
		getline(fi, Lecturer.Name, ',');
		
		getline(fi,Lecturer.Degree, ',');
		
		string Gender;
		getline(fi, Gender, ',');
		if ((Gender[0] == 'f') || (Gender[0] == 'F'))
			Lecturer.Gender = 1;
		else
			Lecturer.Gender = 0;
				
		getline(fi,Course.startDate, ',');
		formatDate(Course.startDate);
		
		getline(fi, Course.endDate, ',');
		formatDate(Course.endDate);	
		
		getline(fi,Course.DoW, ',');
		
		string sHour;					
		getline(fi, sHour, ',');
		
		string sMinute;
		getline(fi, sMinute, ',');
		
		string eHour;					
		getline(fi, eHour, ',');
		
		string eMinute;
		getline(fi, eMinute, ',');
		
		Course.startTime = sHour + ' ' + sMinute;
		Course.endTime = eHour + ' ' + eMinute;
		
		getline(fi, Course.Room, '\n');
		Lecturer.Type = 3;
		addDataForImportCourse(Lecturer, Course);	
	}				
	fi.close();		
	cout << "Import Successfully" << endl;	
	
	string key;
	cout << "Press any key to return :"; cin >> key;
	system("CLS");
	editFeatureCourse();

}
void addCourse()
{
	cout << "Do you want to import course ?" << endl;
	cout << "0.No                 1.Yes" << endl;
	int numberChoice = choiceScreen(1);
	system("CLS");
	switch(numberChoice)
	{
		case 0:
		{
			editFeatureCourse();
			break;	
		}	
		case -1:
		{
			cout << "Your choice is wrong !! Choice again" << endl;
			addCourse();
			break;
		}
	}
	cin.ignore();
	
	userData Lecturer;
	courseData Course;
	cout << "Enter course ID : "; getline(cin, Course.courseID);		
	cout << "Enter course name : "; getline(cin, Course.courseName);
	system("CLS");
	
	//Lay du lieu trong class de in ra 
	string nameClass[500];
	int size = 0;								
	ifstream fi("fileClass/Class.txt");
	takeDataClass(fi, nameClass, size);			
	fi.close();				
	
	numberChoice = -1;
	
	while (numberChoice == -1)
	{														
		cout << "*******LIST CLASS**********" << endl;
		for (int i = 0; i < size; i++)
			cout << i  << " " << nameClass[i] << endl;
		cout << "**************************" << endl;
		
		cout << "Choose one class in above list " << endl;
		numberChoice = choiceScreen(size - 1);
		if (numberChoice == -1)
		{																							
			system("CLS");																				
			cout << "Your class which you choose isn't exit !! please choose again " << endl;
		}
	}
	Course.className = nameClass[numberChoice];
	cin.ignore();												
	
	system("CLS");										
	cout << "Enter lecturer account : "; getline(cin, Course.lecturerAccount);
	Lecturer.ID = Course.lecturerAccount;
	Lecturer.Password = Lecturer.ID;
		
	cout << "Enter Lecturer name : "; getline(cin, Lecturer.Name);
		
	cout << "Enter lecturer degree : "; getline(cin, Lecturer.Degree);
	
	numberChoice = -1;	
	string Gender;
	while (numberChoice == -1)
	{													
		cout << "Enter gender of lecturer " << endl;
		cout << "0. Male     1. Female" << endl;
		numberChoice = choiceScreen(1);
		if (numberChoice == -1)
		{	
			system("CLS");																					
			cout << "Your gender which you choose isn't exit !! please choose again " << endl;
		}
	}
	Lecturer.Gender = numberChoice;
	
	system("CLS");
	cin.ignore();
	cout << "Enter start date of course(yyyy mm dd) : "; getline(cin, Course.startDate);
	formatDate(Course.startDate);
		
	cout << "enter end date of course(yyyy mm dd) : "; getline(cin, Course.endDate);
	formatDate(Course.endDate);	
	
	numberChoice = -1;
	while (numberChoice == -1)
	{												
		cout << "Enter day of week of course : " << endl;
		cout << "0. Monday" << endl << "1. Tuesday" << endl;
		cout << "2. Wednesday" << endl << "3. Thursday" << endl;
		cout << "4. Friday" << endl << "5. Saturday" << endl;
		numberChoice = choiceScreen(5);
		if (-1 == numberChoice)
		{
			system("CLS");																	
			cout << "Your day which you choose isn't exit !! please choose again " << endl;
		}
	}
	Course.DoW = char(numberChoice + 2 + 48);
	system("CLS");
	cin.ignore();
	string sHour;					
	cout << "Enter start hour of course : "; getline(cin, sHour);
		
	string sMinute;
	cout << "Enter start minute of course : "; getline(cin, sMinute);
		
	string eHour;					
	cout << "Enter end hour of course : "; getline(cin, eHour);
		
	string eMinute;
	cout << "Enter end minute of course : "; getline(cin, eMinute);
		
	Course.startTime = sHour + ' ' + sMinute;
	Course.endTime = eHour + ' ' + eMinute;
		
	cout << "Enter room of course : "; getline(cin, Course.Room);
	Lecturer.Type = 3;
	system("CLS");
	
	numberChoice = -1;
	while (numberChoice == -1)
	{				
		showCourse(Lecturer, Course);										
		cout << "Are you sure to add above information to data ?" << endl;
		cout << "0.No                 1.Yes" << endl;
		numberChoice = choiceScreen(1);
		switch (numberChoice)
		{
			case 0:
			{
				system("CLS");
				addCourse();
				break;
			}
			case -1:
			{
				system("CLS");
				cout << "Your choice is wrong !! Choice again " << endl;
				break;
			}
		}
	}
	addDataForImportCourse(Lecturer, Course);	
	string key;
	cout << "Import Successfully " << endl;
	cout << "Enter any key to return :";
	cin >> key;		
	system("CLS");
	editFeatureCourse();
}
void viewListCourse();

void updateSemester()
{
	ifstream fi;
	ofstream fo;
	
	fi.open("fileCourse/Semester.txt");
	fo.open("fileCourse/SemesterTmp.txt");
	int n;
	fi >> n;
	fi.ignore();
	fo << n + 1 << endl;
	copyData(fi, fo);
	fi.close();						
	fo.close();			
	
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
			
	//Phan xu li nam hoc
	int numberScholatics = 0;	// Nam hoc
	for (int i = 0; semesterCurrent[i] != '-'; i++)
		numberScholatics = numberScholatics * 10 + (semesterCurrent[i] - 48);
	//Phan xu li hoc ki
	n = semesterCurrent.length();					
	int numberSemester = (semesterCurrent[n - 1] - 48);
	numberSemester = (numberSemester + 1) % 3;
	if (numberSemester == 0)
		numberSemester = 3;
	if (numberSemester == 1)
		numberScholatics++;
	//Phan them file vao
	fi.open("fileCourse/SemesterTmp.txt");
	fo.open("fileCourse/Semester.txt");
	copyData(fi, fo);
	fo << numberScholatics << "-" << numberScholatics + 1 << endl;
	fo << "HK" << numberSemester << endl;
	fo << endl;
	fi.close();					
	fo.close();		
	int result = remove("fileCourse/SemesterTmp.txt");		
	cout << "Update Successfully" << endl;
	returnScreen(updateSemester, editFeatureCourse);	
	
}

void editStudent() // Hao : Chinh sua thong tin sinh vien
{
	string IDFound;											
	cout << "Do you want to edit student ?" << endl;
	cout << "0.No                 1.Yes" << endl;
	int numberChoice = choiceScreen(1);
	system("CLS");
	switch(numberChoice)
	{
		case 0:
		{
			editFeatureStu();
			break;	
		}	
		case -1:
		{
			cout << "Your choice is wrong !! Choice again" << endl;
			editStudent();
			break;
		}
	}				
	cout << "Press ID Student you want edit : "; cin >> IDFound;
	
	//Lay du lieu trong dataUser
	userData * Student;
	userData Data;
	int size = 0;
	ifstream fi;
	fi.open("fileUser/Student.txt");
	takeDataUser(fi, Student, size, 2);		
		cout << 1 << endl;	
	fi.close();						
	// Kiem tra ID
	int NOofStudent = -1; // Vi tri cua sinh vien can tim]
	for (int i = 0; i < size; i++)
	if (IDFound == Student[i].ID)
	{									
		NOofStudent = i;
		break;
	}	
	
	if (NOofStudent == -1)
	{
		system("CLS");
		cout << "Your student isn't exit !! Please try again" << endl;
		editStudent();
	}
	numberChoice = -1;
	while (numberChoice == -1)
	{
		cout << ">>" << Student[NOofStudent].Name << endl;
		cout << ">>" << Student[NOofStudent].DoB << endl;
		cout << "Are you sure to edit this student ?" << endl;
		cout << "0.No                1.Yes" << endl;
		numberChoice = choiceScreen(1);
		switch(numberChoice)
		{
			case 0:
			{
				system("CLS");
				editFeatureStu();
				break;	
			}	
			case -1:
			{
				system("CLS");
				cout << "Your choice is wrong !! Choice again" << endl;
				break;
			}
		}
	}								
	//Edit thong tin sinh vien
	system("CLS");
	cout << "Now you can change this student !!" << endl;
	string Name, DoB, ID;
	int Gender;											
	cin.ignore();
	cout << "Enter new ID : " ; getline(cin, ID);
	cout << "Enter new Name : "; getline(cin, Name);
	cout << "Enter new DoB (Year Month Day No hypen('-')) : "; getline(cin, DoB);
	cout << "Enter new Gender (0:Male, 1:Female) :" ; cin >> Gender;
	Student[NOofStudent].ID = ID; Data.ID = ID;
	Student[NOofStudent].Name = Name; Data.Name = Name;
	Student[NOofStudent].Gender = Gender; Data.Gender = Gender;
	Student[NOofStudent].DoB = DoB; Data.DoB = DoB;
	//Dua du lieu vao lai file
	ofstream fo;
	fo.open("fileUser/Student.txt");
	insertDataUser(fo, Student, size);
	fo.close();	
	
	string fileName ;
	fileName = "fileClass/" + Student[NOofStudent].className;			
	fileName += "-Student.txt";
	//Lay du lieu sinh vien trong file data User
	fi.open(fileName.c_str());
	takeDataUser(fi, Student, size, 2);
	fi.close();							
	
	for (int i = 0; i < size; i++)
	if (Student[i].ID == IDFound)
	{
		Student[i].ID = ID;
		Student[i].Name = Name;
		Student[i].DoB = DoB;
		Student[i].Gender = Gender;
	}
	//Dua du lieu vao file Data user
	fo.open(fileName.c_str());
	insertDataUser(fo, Student, size);
	fo.close();				
	
	//Lay du lieu sinh vien trong cac file mon hoc
	string semesterCurrent ;
	takeCurrentSemester(semesterCurrent);
	fileName = "fileCourse/" + semesterCurrent + "-Schedule.txt";	
	courseData * Course;
	userData * Lecturer;
	fi.open(fileName.c_str());
	takeDataCourse(fi, Lecturer, Course, size);
	fi.close();			
	
	for (int i = 0; i < size; i++)
		editStudentInFile(Course[i].className, Course[i].courseID, IDFound, Data);
	
	system("CLS");
	cout << "Your edit is successfully !! " << endl;
	cout << "Student whom you edit : " << endl;
	cout << "Name : " << Student[NOofStudent].Name << endl;
	cout << "ID   :" << Student[NOofStudent].ID << endl;
	cout << "DoB  :" << Student[NOofStudent].DoB << endl;
	returnScreen(editStudent, editFeatureStu);
}

void viewAllLecturer()
{
	cout << "List of all lecturers in school" << endl;
	userData * Lecturer;
	int size = 0;
	ifstream fi;
	fi.open("fileUser/Lecturer.txt");							
	takeDataUser(fi, Lecturer, size, 3);
	fi.close();					
	
	for (int i = 0; i < size; i++)
	{
		cout << "ID: " << Lecturer[i].ID << endl;
		cout << "Name : " << Lecturer[i].Name << endl;
		cout << "Degree : " << Lecturer[i].Degree << endl;
		cout << endl;	
	}				
	string key;
	cout << "Press any key to return :"; cin >> key;
	system("CLS");	
	viewFeatureCourse();		
}

void deleteSemester() //Hao: xoa mot hoc ki
{
	//Phan giao dien luc dau
	cout << "Do you want to remove semester ?" << endl;
	cout << "0.No                 1.Yes" << endl;
	int numberChoice = choiceScreen(1);
	system("CLS");
	switch(numberChoice)
	{
		case 0:
		{
			editFeatureCourse();
			break;	
		}	
		case -1:
		{
			warnScreen();
			deleteSemester();
			break;
		}
	}		
	//Phan nhap nam hoc va hoc ki
	ifstream fi;
	fi.open("fileCourse/Semester.txt");
	string semesterRemove, academicRemove;
	cout << "You have to enter data which is like in braces" << endl;
	cout << "Enter academic year you want to remove (Year - Year) :";
	cin >> academicRemove;
	cout << "Enter semester you want to remove (HK1, HK2, HK3):";
	cin >> semesterRemove;
	//Kiem tra xem co hoc ki nguoi dung vua nhap khong 
	
	string Semester, Academic;
	int size, NOofSemester = -1;
	fi >> size;
	for (int i = 0; i < size; i++)
	{
		fi >> Academic;
		fi >> Semester;
		fi.ignore();
		if ((Semester == semesterRemove) && (Academic == academicRemove))
		{
			NOofSemester = i;
			break;
		}
	}
	
	if (NOofSemester == -1)
	{
		system("CLS");
		cout << "Your semester isn't exit or Format in academic year is wrong !! Please try again." << endl;
		deleteSemester();
	}
	fi.close();
	//Xoa hoc ki
	fi.open("fileCourse/Semester.txt");
	ofstream fo;
	fo.open("fileCourse/Semester_tam.txt");
	fi >> size; 
	fo << size - 1 << endl;
	for (int i = 0; i < size; i++)
	{
		fi >> Academic;
		fi >> Semester;
		fi.ignore();
		if (i != NOofSemester)
		{
			fo << Academic << endl;
			fo << Semester << endl;
			fo << endl;
		}
	}
	fo.close();
	fi.close();
	remove("fileCourse/Semester.txt");
	rename("fileCourse/Semester_tam.txt","fileCourse/Semester.txt");
	cout << "Delte semester is succesfully" << endl;
	string key;
	cout << "Press any key to return :"; cin >> key;
	system("CLS");
	editFeatureCourse();
}

void viewSemester()
{
	ifstream fi;
	fi.open("fileCourse/Semester.txt");
	string Semester, Academic;
	cout << "All semester school go through " << endl;
	cout << "********************************" << endl;
	int size;
	fi >> size;
	for (int i = 0; i < size; i++)
	{
		fi >> Academic;
		fi >> Semester;
		fi.ignore();
		cout << "Academic :" << Academic << endl;
		cout << "Semester :" << Semester << endl;
		cout << endl;
	}
	cout << "********************************" << endl;
	fi.close();		
	string key;
	cout << "Press any key to return :"; cin >> key;
	system("CLS");	
	viewFeatureCourse();						
}

void removeFileCourse(string fileName, string IDRemove) //HAo : Ham dung de xoa du lieu trong fileName voi ID la remove
{
	userData * Lecturer;
	courseData * Course;
	int NOofCourse = -1, size;
	ifstream fi;
	fi.open(fileName.c_str());
	if (!fi.is_open())
		cout << "Khong tim duoc file " << endl;
	takeDataCourse(fi, Lecturer, Course, size);
	fi.close();						
	for (int i = 0; i < size; i++)
	{
		if (Course[i].courseID == IDRemove)
		{
			NOofCourse = i;
			break;
		}
	}		
		
	ofstream fo;
	fo.open(fileName.c_str());
	string fileNameCourse = fileName + '-' + Course[NOofCourse].className;
	size = size - 1;
	for (int i = 0; i < size; i++)
	if (i >= NOofCourse)
	{
		Course[i] = Course[i + 1];
		Lecturer[i] = Lecturer[i + 1];
	}
	insertDataCourse(fo, Lecturer, Course, size);
	fo.close();
	delete [] Lecturer;
	delete [] Course;		
}
void viewListCourse()
{
	cout << "List of all List Course in school" << endl;
	courseData* Course;
	userData* Lecturer;
	int size = 0;
	ifstream fi;
	string semesterCurrent ;
	takeCurrentSemester(semesterCurrent);
	string filename;
	filename = "fileCourse/" + semesterCurrent +"-Schedule.txt";
	fi.open(filename.c_str());
	if(fi.is_open()){
		cout << "Open!" << endl;
	}
	else
	cout << "Not Open" << endl;
	takeDataCourse(fi, Lecturer, Course, size);
	fi.close();
	for (int i = 0; i < size; i++)
	{
		cout << "Course ID: " << Course[i].courseID << endl;
		cout << "Course Name: " << Course[i].courseName << endl;
		cout << "Course ClassName: " << Course[i].className << endl;
		cout << "Lecturer ID: " << Lecturer[i].ID << endl;
		cout << "Lecturer Name: " << Lecturer[i].Name << endl;
		cout << "Lecturer Degree: " << Lecturer[i].Degree << endl;
		cout << "Lecturer Gender: " << Lecturer[i].Gender << endl;
		cout << "Start Date: " << Course[i].startDate << endl;
		cout << "End Data: " << Course[i].endDate << endl;
		cout << "Date of Week: " << Course[i].DoW << endl;
		cout << "Start Time: " << Course[i].startTime << endl;
		cout << "End Time: " << Course[i].endTime << endl;
		cout << "Room: " << Course[i].Room << endl;
		cout << endl;
	}				
		string key;
	cout << "Press any key to return :"; cin >> key;
	system("CLS");	
	viewFeatureCourse();	
}

void removeCourse()//Hao : Xoa mot mon hoc
{
	//Phan bat dau
	cout << "Do you want to remove course ?" << endl;
	cout << "0.NO              1. Yes" << endl;
	int numberChoice = choiceScreen(1);
	system("CLS");
	switch (numberChoice)
	{
		case 0:
		{
			editFeatureCourse();
			break;
		}
		case -1:
		{
			removeCourse();
			break;
		}
	}
	//Nguoi dung nhap
	string IDRemove;
	cout << "Enter your course ID :";
	cin >> IDRemove;
	//Kiem tra xem course ID co ton tai khong?
	userData * Lecturer;
	courseData * Course;
	int size, NOofCourse = - 1;
	string currentSemester;
	takeCurrentSemester(currentSemester);
	string fileName = "fileCourse/" + currentSemester + "-Schedule.txt";
	ifstream fi;
	fi.open(fileName.c_str());
	if (!fi.is_open())
		cout << "Khong tim duoc file " << endl;
	takeDataCourse(fi, Lecturer, Course, size);
	fi.close();						
	for (int i = 0; i < size; i++)
	{
		if (Course[i].courseID == IDRemove)
		{
			NOofCourse = i;
			break;
		}
	}						
	if (NOofCourse == -1)
	{
		system("CLS");												
		cout << "Your coure isn't exit !! Pleae try again" << endl;
		removeCourse();
	}		
	//Xoa Course
	numberChoice = -1;
	while (numberChoice == -1)
	{
		cout << ">> Course name :" << Course[NOofCourse].courseName << endl;
		cout << ">> Class :" << Course[NOofCourse].className << endl;
		cout << "Are you sure to remove above course" << endl;
		cout << "0.NO              1. Yes" << endl;
		numberChoice = choiceScreen(1);
		switch (numberChoice)
		{
			case 0:
			{
				system("CLS");
				editFeatureCourse();
				break;
			}
			case -1:
			{
				system("CLS");
				warnScreen();
				break;
			}
		}
	}
	string fileNameCourse = "fileCourse/" + currentSemester + '-' + "Schedule-" + Course[NOofCourse].className + ".txt";
	
	//Xoa du lieu tong file Schedule 
	removeFileCourse(fileName, IDRemove);
	
	// Xoa du lieu trong file Schedule-Lop hoc					
	removeFileCourse(fileNameCourse, IDRemove);				
		
	cout << "Your course is remove successfully!!" << endl;
	string key;
	cout << "Press any key to return :"; cin >> key;
	system("CLS");
	editFeatureCourse();
}

void addStudentToCourse(){
	userData *studentinfo;
	bool check = false;
	bool check2 = false;
	int size = 0;
	int size1 = 0;
	userData student, studenttemp;
	string classname, coursename, courseid;
	int courseNo;
	cout << "Enter student id: ";
	cin >> student.ID;
	ifstream fi;
	ofstream fo3;
	fi.open("fileUser/Student.txt");
	takeDataUser(fi,studentinfo, size, 2);
	for(int i = 0; i < size; i++){
		if(studentinfo[i].ID == student.ID){
			cout << studentinfo[i].ID << " - " << studentinfo[i].Name << endl;
			studenttemp = studentinfo[i];
			check = true;
	}
}
	if(check == true){
		cout << "Student exist!" << endl << endl;
		cout << "List of Course in school" << endl;
		courseData* Course;
		userData* Lecturer;
		int size1 = 0;
		ifstream fi1;
		string semesterCurrent;
		takeCurrentSemester(semesterCurrent);
		string filename;
		filename = "fileCourse/" + semesterCurrent +"-Schedule.txt";
		fi1.open(filename.c_str());
		takeDataCourse(fi1, Lecturer, Course, size1);
		int NO[size1 - 1];
		fi1.close();
		for (int i = 0; i < size1; i++)
		{
			NO[i + 1] = i + 1;
			cout << i + 1<<". " << "Course ID: " << Course[i].courseID << endl;
			cout << "Course Name: " << Course[i].courseName << endl;
			cout << "Lecturer Name: " << Lecturer[i].Name << endl;
			cout << "Room: " << Course[i].Room << endl;
			cout << endl;
		}	

	cout << "Enter course No: ";
	cin >> courseNo;
	for (int i = 0; i < size1; i++){
		if(courseNo == NO[i + 1]){
			classname = Course[i].className;
			courseid = Course[i].courseID;
			coursename = Course[i].courseName;
			check2 = true;
			
		}
	}

		if(check2 == true){
			string semesterCurrent3;
			takeCurrentSemester(semesterCurrent3);
			string fileName3;
			fileName3 = "fileCourse/" + semesterCurrent3 + "-" + classname + "-" + courseid + "-" + "Student.txt";
			
			userData * studentCourse;
			int size3 = 0;					
			ifstream fi3;
			fi3.open(fileName3.c_str());
			if (!fi3.is_open())
				fo3.open(fileName3.c_str());	
			takeDataUser(fi3, studentCourse, size3, 4);
			fi3.close();						
			cout << size3 << endl;
			studentCourse[size3].ID = studenttemp.ID;
			studentCourse[size3].Password = studenttemp.Password;
			studentCourse[size3].Name = studenttemp.Name;
			studentCourse[size3].Gender = studenttemp.Gender;
			studentCourse[size3].DoB =  studenttemp.DoB ;
			studentCourse[size3].className = studenttemp.className ;
			studenttemp.Score.Midterm = -1;
			studentCourse[size3].Score.Midterm = studenttemp.Score.Midterm;
			studenttemp.Score.Final = -1;								
			studentCourse[size3].Score.Final = studenttemp.Score.Final;
			studenttemp.Score.Bonus = -1;
			studentCourse[size3].Score.Bonus = studenttemp.Score.Bonus ;
			studenttemp.Score.Total = -1;
			studentCourse[size3].Score.Total = studenttemp.Score.Total;	

			for (int i = 0; i < 10; i++)
				studentCourse[size3].Attendance[i] = -1;
			size3 = size3 + 1;
			insertDataStudentInCourse(fileName3, studentCourse, size3);
			}
			fo3.close();
			
			
			cout << "Student has " << courseid << " " << coursename << " in his profile!" << endl;
			}
			
			
	if(check == false)
	cout << "Student is not exist!" << endl;
	

	string key;
	cout << "Press any key to return :"; 
	cin >> key;
	system("CLS");
	editFeatureStu();
}


void removeStudentInFile(string className, string courseName, string ID, userData Data) //Hao: Duyet tung phan tu cuar file student in course
{
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	string fileName;
	fileName = "fileCourse/" + semesterCurrent + "-" + className + "-" + courseName + "-" + "Student.txt";
	
	userData * Student;
	int size;
								
	ifstream fi;
	fi.open(fileName.c_str());
	takeDataUser(fi, Student, size, 4);
	fi.close();					
	
	for (int i = 0; i < size; i++)
	if (Student[i].ID == ID)
	{
		Student[i].Status = 0;
		break;
	}
	insertDataStudentInCourse(fileName, Student, size);
}

void removeStudent() // Hao : Chinh sua thong tin sinh vien
{
	string IDFound;											
	cout << "Do you want to remove student ?" << endl;
	cout << "0.No                 1.Yes" << endl;
	int numberChoice = choiceScreen(1);
	system("CLS");
	switch(numberChoice)
	{
		case 0:
		{
			editFeatureStu();
			break;	
		}	
		case -1:
		{
			cout << "Your choice is wrong !! Choice again" << endl;
			removeStudent();
			break;
		}
	}				
	cout << "Press ID Student you want edit : "; cin >> IDFound;
	
	//Lay du lieu trong dataUser
	userData * Student;
	userData Data;
	int size = 0;
	ifstream fi;
	fi.open("fileUser/Student.txt");
	takeDataUser(fi, Student, size, 2);		

	fi.close();						
	// Kiem tra ID
	int NOofStudent = -1; // Vi tri cua sinh vien can tim]
	for (int i = 0; i < size; i++)
	if (IDFound == Student[i].ID)
	{									
		NOofStudent = i;
		break;
	}	
	

	if ((NOofStudent == -1) || (Student[NOofStudent].Status == 0))
	{					
			system("CLS");
			cout << "Your student isn't exit !! Please try again" << endl;
			removeStudent();
	}
	
	numberChoice = -1;
	while (numberChoice == -1)
	{
		cout << ">>" << Student[NOofStudent].Name << endl;
		cout << ">>" << Student[NOofStudent].DoB << endl;
		cout << "Are you sure to remove this student ?" << endl;
		cout << "0.No                1.Yes" << endl;
		numberChoice = choiceScreen(1);
		switch(numberChoice)
		{
			case 0:
			{
				system("CLS");
				editFeatureStu();
				break;	
			}	
			case -1:
			{
				system("CLS");
				cout << "Your choice is wrong !! Choice again" << endl;
				break;
			}
		}
	}	
	
	//Remove student
	system("CLS");
	Student[NOofStudent].Status = 0;
	//Dua du lieu vao lai file
	ofstream fo;
	fo.open("fileUser/Student.txt");
	insertDataUser(fo, Student, size);
	fo.close();	
	
	string fileName ;
	fileName = "fileClass/" + Student[NOofStudent].className;			
	fileName += "-Student.txt";
	//Lay du lieu sinh vien trong file (nameClass)-Student.txt
	fi.open(fileName.c_str());
	takeDataUser(fi, Student, size, 2);
	fi.close();							
	
	for (int i = 0; i < size; i++)
	if (Student[i].ID == IDFound)
	{
		Student[i].Status = 0;
		break;
	}
	//Dua du lieu vao file Data (nameClass)-Student.txt
	fo.open(fileName.c_str());
	insertDataUser(fo, Student, size);
	fo.close();				
	
	//Lay du lieu sinh vien trong cac file mon hoc
	string semesterCurrent ;
	takeCurrentSemester(semesterCurrent);
	fileName = "fileCourse/" + semesterCurrent + "-Schedule.txt";	
	courseData * Course;
	userData * Lecturer;
	fi.open(fileName.c_str());
	takeDataCourse(fi, Lecturer, Course, size);
	fi.close();			
	
	for (int i = 0; i < size; i++)
		removeStudentInFile(Course[i].className, Course[i].courseID, IDFound, Data);
	
	string key;
	cout << "Your student is remove successfully" << endl;
	cout << "Press any key to return" << endl;
	cin >> key;
	system("CLS");
	editFeatureStu();
}

void viewListStudentinCourse(){
	userData *studentinfo;
	bool check = false;
	bool check2 = false;
	int size = 0;
	int size1 = 0;
	userData student, studenttemp;
	string classname, coursename, courseid;
	int courseNo;
		cout << "List of Course in school" << endl;
		courseData* Course;
		userData* Lecturer;
		ifstream fi1;
		string semesterCurrent;
		takeCurrentSemester(semesterCurrent);
		string filename;
		filename = "fileCourse/" + semesterCurrent +"-Schedule.txt";
		fi1.open(filename.c_str());
		takeDataCourse(fi1, Lecturer, Course, size1);
		int NO[size1 - 1];
		fi1.close();
		for (int i = 0; i < size1; i++)
		{
			NO[i + 1] = i + 1;
			cout << i + 1<<". " << "Course ID: " << Course[i].courseID << endl;
			cout << "Course Name: " << Course[i].courseName << endl;
			cout << "Lecturer Name: " << Lecturer[i].Name << endl;
			cout << "Room: " << Course[i].Room << endl;
			cout << endl;
		}	

	cout << "Enter course No: ";
	cin >> courseNo;
	for (int i = 0; i < size1; i++){
		if(courseNo == NO[i + 1]){
			classname = Course[i].className;
			courseid = Course[i].courseID;
			coursename = Course[i].courseName;
		}
	}
	string semesterCurrent2;
	takeCurrentSemester(semesterCurrent2);
	string fileName3;
	fileName3 = "fileCourse/" + semesterCurrent2 + "-" + classname + "-" + courseid + "-" + "Student.txt";
	ifstream fi2;	
	fi2.open(fileName3.c_str());
	userData* studentCourse;
	int size3 = 0;
	takeDataUser(fi2, studentCourse, size3, 4);
	cout << "The Numbers of student: " << size3 << endl;
	for(int i = 0; i < size3; i++){
		cout << endl;
			cout << studentCourse[i].ID << endl;
			cout << studentCourse[i].Name << endl;
			cout << studentCourse[i].Gender << endl;
			cout << studentCourse[i].DoB << endl;
			cout << studentCourse[i].className << endl;
//			cout << studenttemp.Score.Midterm = -1;
			cout << studentCourse[i].Score.Midterm << endl;
//			cout << studenttemp.Score.Final = -1;								
			cout << studentCourse[i].Score.Final << endl;
//			cout << studenttemp.Score.Bonus = -1;
			cout << studentCourse[i].Score.Bonus << endl;
//			cout << studenttemp.Score.Total = -1;
			cout << studentCourse[i].Score.Total << endl;	

	}
	
	
	fi2.close();
	
	string key;
	cout << "Press any key to return: ";
	cin >> key;
	system("CLS");
	viewFeatureStu();
}
void removeStudentinCourse(){
		userData *studentinfo;
	bool check = false;
	bool check2 = false;
	int size = 0;
	int size1 = 0;
	userData student, studenttemp;
	string classname, coursename, courseid;
	int courseNo;
		cout << "List of Course in school" << endl;
		courseData* Course;
		userData* Lecturer;
		ifstream fi1;
		string semesterCurrent;
		takeCurrentSemester(semesterCurrent);
		string filename;
		filename = "fileCourse/" + semesterCurrent +"-Schedule.txt";
		fi1.open(filename.c_str());
		takeDataCourse(fi1, Lecturer, Course, size1);
		int NO[size1 - 1];
		fi1.close();
		for (int i = 0; i < size1; i++)
		{
			NO[i + 1] = i + 1;
			cout << i + 1<<". " << "Course ID: " << Course[i].courseID << endl;
			cout << "Course Name: " << Course[i].courseName << endl;
			cout << "Lecturer Name: " << Lecturer[i].Name << endl;
			cout << "Room: " << Course[i].Room << endl;
			cout << endl;
		}	

	cout << "Enter course No: ";
	cin >> courseNo;
	for (int i = 0; i < size1; i++){
		if(courseNo == NO[i + 1]){
			classname = Course[i].className;
			courseid = Course[i].courseID;
			coursename = Course[i].courseName;
		}
	}
	string semesterCurrent2;
	takeCurrentSemester(semesterCurrent2);
	string fileName3;
	fileName3 = "fileCourse/" + semesterCurrent2 + "-" + classname + "-" + courseid + "-" + "Student.txt";
	ifstream fi2;	
	fi2.open(fileName3.c_str());
	userData* studentCourse;
	int size3 = 0;
	takeDataUser(fi2, studentCourse, size3, 4);
	cout << "The Numbers of student: " << size3 << endl;
	int NO1[size3 - 1];
	for(int i = 0; i < size3; i++){
		cout << endl;
			cout << "No" << i + 1 << "." << studentCourse[i].ID << endl;
			cout << studentCourse[i].Name << endl;
			cout << studentCourse[i].Gender << endl;
			cout << studentCourse[i].DoB << endl;
			cout << studentCourse[i].className << endl;
			cout << studentCourse[i].Score.Midterm << endl;								
			cout << studentCourse[i].Score.Final << endl;
			cout << studentCourse[i].Score.Bonus << endl;
			cout << studentCourse[i].Score.Total << endl;
	}
	int choice;
	cout << "Choose No to remove: ";
	cin >> choice;
	studentCourse[choice - 1].Status = 0;
	insertDataStudentInCourse(fileName3, studentCourse, size3);
	fi2.close();
	
	string key;
	cout << "Press any key to return: ";
	cin >> key;
	system("CLS");
	editFeatureStu();
}

void spviewStudentAttendanceList(string filename){
	ifstream fi;
	fi.open(filename.c_str());
	userData* studentdata;
	int size = 0;
	takeDataUser(fi, studentdata, size, 4);
	cout << "Student Name        ";
	for(int i = 0; i < 10; i++){
		cout << "Week " << i + 1 << " ";
	} 
	cout << endl;
	for(int i = 0; i < size; i++){
		cout << studentdata[i].Name;
		int length = studentdata[i].Name.length();
		for (int j = 0; j < 20 - length; j++)
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
		cout << endl;
	}
}

void searchViewAttendanceList(){
	string Courseid, Classname;
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	cout << "Enter Class name: ";
	cin >> Classname;
	cout << "Enter Course id: ";
	cin >> Courseid;
	string filename;
	filename = "fileCourse/" + semesterCurrent + "-" + Classname + "-" + Courseid + "-Student.txt";
	string filename1;
	filename1 = "fileCourse/" + semesterCurrent + "-Schedule-" + Classname + ".txt";
	
	
	spviewAttendanceList(filename1, Courseid);
	spviewStudentAttendanceList(filename);
	
	
	string key;
	cout << "Press any key to return: ";
	cin >> key;
	system("CLS");
	viewFeatureStu();
}


void viewAttendanceList(){
	ifstream fi;
	string filename;
	string semesterCurrent;
	userData * Lecturer;
	courseData * Course;
	int size = 0;
	string classname, coursename, courseid;
	
	
	takeCurrentSemester(semesterCurrent);
	filename = "fileCourse/" + semesterCurrent + "-Schedule.txt";
	fi.open(filename.c_str());
	takeDataCourse(fi, Lecturer, Course, size);
	int NO[size - 1];
	fi.close();
	for (int i = 0; i < size; i++)
	{
		NO[i + 1] = i + 1;
		cout << i + 1<<". " << "Course ID: " << Course[i].courseID << endl;
		cout << "Course Name: " << Course[i].courseName << endl;
		cout << "Lecturer Name: " << Lecturer[i].Name << endl;
		cout << endl;
	}	
	int courseNo;
	cout << "Enter course No: ";
	cin >> courseNo;
	for (int i = 0; i < size; i++){
		if(courseNo == NO[i + 1]){
			classname = Course[i].className;
			courseid = Course[i].courseID;
			coursename = Course[i].courseName;
		}
	}
	string filename1;
	filename1 = "fileCourse/" + semesterCurrent + "-" + classname + "-" + courseid + "-Student.txt";
	spviewAttendanceList(filename, courseid);
	spviewStudentAttendanceList(filename1);
	
	
	string key;
	cout << "Press any key to return: ";
	cin >> key;
	system("CLS");
	viewFeatureStu();
}
void spviewAttendanceList(string filename, string courseID){
	ifstream fi;
	int sizeCourse;
	userData * Lecturer;
	courseData * Course;
	string startDate = "", startTime = "", endTime = "" ;
	fi.open(filename.c_str());
	if(fi.is_open()){
		takeDataCourse(fi, Lecturer, Course, sizeCourse);					
	
		for (int i = 0; i < sizeCourse; i++)
		if (courseID == Course[i].courseID)
		{
				startDate = Course[i].startDate;
				startTime = Course[i].startTime;
			 	endTime = Course[i].endTime;
				break;
		}
	}
	else{
		cout << "Course does not exist!" << endl;
	}
	readAttendanceToFile(startDate, startTime, endTime);
	fi.close();
}

void spViewScoreboardList(string courseid, string classname){
	string filename;
	userData* studentinfo;
	int size = 0;
	
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	filename = "fileCourse/" + semesterCurrent + "-" + classname + "-" + courseid + "-Student.txt";
	ifstream fi;
	fi.open(filename.c_str());
	takeDataUser(fi, studentinfo, size, 4);
	fi.close();
	
	
	cout << "Name                ";
	cout << "Midterm ";
	cout << "Bonus ";
	cout << "Final ";
	cout << "Total ";
	cout << endl;
	for(int i = 0; i < size; i++){
		cout << studentinfo[i].Name;
		int length = studentinfo[i].Name.length();
		for (int j = 0; j < 20 - length; j++)
			cout << " ";
	
	cout << studentinfo[i].Score.Midterm << "      ";
	cout << studentinfo[i].Score.Bonus << "     ";
	cout << studentinfo[i].Score.Final << "     ";
	cout << studentinfo[i].Score.Total << endl;
}
}

void searchViewScoreboardList(){
	string courseid, classname;
	userData* Lecturer;
	courseData* CourseData;
	int size = 0;
	bool check = false;
	
	cout << "Enter Course ID: ";
	cin >> courseid;
	cout << "Enter Class(name): ";
	cin >> classname;
	
	string filename;
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	filename = "fileCourse/" + semesterCurrent + "-Schedule.txt";
	ifstream fi;
	fi.open(filename.c_str());
	takeDataCourse(fi, Lecturer, CourseData, size);
	fi.close();
	
	for(int i = 0; i < size; i++){
		if(courseid == CourseData[i].courseID && classname == CourseData[i].className)
			check = true;
	}
	
	if(check == false)
		cout << "Invalid Course ID or Class(name)!" << endl;
	else
		spViewScoreboardList(courseid, classname);
	
	
	cout << endl;
	string key;
	cout << "Press any key to return: ";
	cin >> key;
	system("CLS");
	viewFeatureStu();
}
void ViewScoreboardList(){
	string filename, filename1;
	userData* Lecturer;
	courseData* CourseData;
	int size, size1;
	string nameClass[1000];
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	filename = "fileCourse/" + semesterCurrent + "-Schedule.txt";
	ifstream fi;
	fi.open(filename.c_str());
	takeDataCourse(fi, Lecturer, CourseData, size);
	fi.close();
	filename1 = "fileClass/Class.txt";
	ifstream fi2;
	fi2.open(filename1.c_str());
	takeDataClass(fi2, nameClass, size1);
	fi2.close();
	cout << "List of Class: " << endl;
	for(int i = 0; i < size1; i++){
		cout << i+1 << "." << nameClass[i] << endl;
	}
	string nameclass;
	bool check = false;
	cout << "Enter Class to view (Name of Class)(Press 0 to exit): ";
	cin >> nameclass;
	
	if(nameclass == "0")
	{									
		system("CLS");
		viewFeatureStu();
	}
		
	for(int i = 0; i < size1; i++){
		if(nameclass == nameClass[i])
			check = true;
}
	if(check == false){
		cout << "Invalid enter!" << endl;
	}
	
	
	
	else{
	for(int i = 0; i < size; i++){
		cout << i+1 << "." << CourseData[i].courseID << "-" << CourseData[i].courseName << endl;
	}
	string Courseid;
	cout << "Enter Course ID: ";
	cin >> Courseid;
	bool check1 = false;
	for(int i = 0; i < size1; i++){
		if(Courseid == CourseData[i].courseID)
			check1 = true;
}
	if(check1 == false){
		cout << "Invalid enter!" << endl;
	}
	else{
		spViewScoreboardList(Courseid, nameclass);
	}
}
	cout << endl;
	string key;
	cout << "Press any key to return: ";
	cin >> key;
	system("CLS");
	viewFeatureStu();
}
//************************//
