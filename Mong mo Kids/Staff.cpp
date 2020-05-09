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

void editStudentInFile(string className, string courseName, string ID, userData Data) // Duyet tung phan tu cuar file student in course
{
	string semesterCurrent;
	takeCurrentSemester(semesterCurrent);
	string fileName;
	fileName = "fileClass/" + semesterCurrent + "-" + className + "-" + courseName + "-" + "Student.txt";
	
	userData * Student;
	int size;
	cout << fileName << endl;
								
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


//**********************************************//

//Tinh Nang cua User STAFF//

void importCourse() {
	ifstream fi;
	ofstream fo;
	string file, fileout;
	int size;
	
	std::cout << "Nhap duong truyen file: ";
	std::cin >> file;
	size = file.length();
	int i = size;
	if(file[i - 1] == 'v' && file[i - 2] == 's' && file[i - 3] == 'c')
		cout << "This is csv file!" << endl;
	else
		cout << "This is not csv file!" << endl;
		
		
	fi.open(file.c_str());
	fileout = "fileCourse/2019-2020-HK2-CS162-19CLC10-Students.txt";
	fo.open(fileout.c_str());
	if(fi.is_open()){
		cout << "Filein is Open!" << endl;
	}
	else{
		cout << "Filein is not Open" << endl;
	}
	if(fo.is_open()){
		cout << "Fileout is Open!" << endl;
		insertCourse(fi, fo);
	}
	else{
		cout << "Fileout is not Open" << endl;
	}
	
	fi.close();
	fo.close();
	cout << endl;
	editFeatureCourse();
}

void insertCourse(ifstream &filein, ofstream &fileout){
	userData info[100];
	string firstline;
	if(filein.is_open() && fileout.is_open()){
		getline(filein, firstline);
		int i = 0;
		while(!filein.eof()){
			getline(filein, info[i].NO , ',');
			getline(filein, info[i].ID, ',');
			getline(filein, info[i].Name, ',');
			getline(filein, info[i].DoB, ',');
			getline(filein, info[i].className,',');
			i++;
		}
		for(int k = 0; k <= i;k++){
			fileout << info[k].NO << " ";
			fileout << info[k].ID << " ";
			fileout << info[k].Name << " ";
			fileout << info[k].DoB <<" ";
			fileout << info[k].className <<" ";
		}
		cout << endl;
		cout << "Transfer Sussces" << endl;
	}
	else{
		cout << "Cannot processing file!" << endl;
	}
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

void editStudent()
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
	
	cout << ">>" << Student[NOofStudent].Name << endl;
	cout << ">>" << Student[NOofStudent].DoB << endl;
	cout << "Are you sure to edit this student ?" << endl;
	cout << "0.No                1.Yes" << endl;
	numberChoice = choiceScreen(1);
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
	//Edit thong tin sinh vien
	string Name, DoB, ID;
	int Gender;											
	cin.ignore();
	cout << "Enter new ID : " ; getline(cin, ID);
	cout << "Enter new Name : "; getline(cin, Name);
	cout << "Enter new DoB : "; getline(cin, DoB);
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
//************************//
