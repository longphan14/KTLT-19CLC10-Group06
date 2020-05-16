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
	//Dua ve dung dang yyyy mm dd
	string newDate = "";
	string year = "", month = "", day = "";
	int i = 0;
	while ((Date[i] <= '9') && (Date[i] >= '0'))
		year += Date[i++];
	
	i++;
	while ((Date[i] <= '9') && (Date[i] >= '0'))
		month += Date[i++];
	
	if (month.length() == 1)
		month = '0' + month;
		
	i++	;
	while ((Date[i] <= '9') && (Date[i] >= '0'))
		day += Date[i++];
	
	if (day.length() == 1)
		day = '0' + day;
	
	Date = year + ' ' + month + ' ' + day ;
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
void addCourse();
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
	userData student, studenttemp;
	string coursename, classname;
	cout << "Enter student id: ";
	cin >> student.ID;
	ifstream fi;
	ofstream fo3;
	fi.open("fileUser/Student.txt");
	takeDataUser(fi,studentinfo, size, 2);
	for(int i = 0; i < size; i++){
		if(studentinfo[i].ID == student.ID){
			cout << studentinfo[i].ID << " - " << studentinfo[i].Name << endl;
			classname = studentinfo[i].className;
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
		fi1.close();
		for (int i = 0; i < size1; i++)
		{
			cout << "Course ID: " << Course[i].courseID << endl;
			cout << "Course Name: " << Course[i].courseName << endl;
			cout << "Lecturer Name: " << Lecturer[i].Name << endl;
			cout << "Room: " << Course[i].Room << endl;
			cout << endl;
		}	

	cout << "Enter course name: ";
	cin >> coursename;
	for (int i = 0; i < size1; i++){
		if(coursename == Course[i].courseID){
			check2 = true;
			
		}
	}

		if(check2 == true){
			string semesterCurrent3;
			takeCurrentSemester(semesterCurrent3);
			string fileName3;
			fileName3 = "fileClass/" + semesterCurrent3 + "-" + classname + "-" + coursename + "-" + "Student.txt";
			fo3.open(fileName3.c_str());
			fo3 << studenttemp.ID << endl;			
			fo3 << studenttemp.Name << endl;
			fo3 << studenttemp.Gender << endl;
			if (studenttemp.Type == 2)
			{
				fo3 << studenttemp.DoB << endl;
				fo3 << studenttemp.className << endl;
				fo3 << studenttemp.Status << endl;
			}
				cout << "Student has " << coursename << " in his profile!" << endl;
			}
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


//************************//
