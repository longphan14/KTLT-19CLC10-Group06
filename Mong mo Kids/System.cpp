#include "Header.h"

//User Interface support Function//
void clearScreen()
{
	system("CLS");
}

void warnScreen()
{
	cout << "Your choice isn't correct !! Please choose again" << endl;
}

int choiceScreen(int Number) // Hao : Giup viec nhap so de dang hon
{
	string Choice;					
	if (Number == 0)
	{												
		cout << "Enter your choice : ";
		cin >> Choice;	
	}
	else
	{
		cout << "Enter your choice (0 -> " << Number << ") :" ; 
		cin >> Choice;
	}
	return checkChoice(Choice, Number); // Return -1 : Choice > Number or Format of chocie != Number , Return Value which is less than Number.
}
//*******************************//

//Nhung ham ho tro cho viec code ^^//

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int checkChoice(string Choice, int Number)
{
	int length = Choice.length();
	int numberCheck = 0;
	for (int i = 0 ; i < length; i++)
		if ((Choice[i] >= '0') && (Choice[i] <= '9'))
			numberCheck += int(Choice[i]) - 48;
		else 
			return -1;		
	if (numberCheck <= Number)						
		return numberCheck;
	return -1;
}

void ignoreLine(ifstream &fi, int number) // Hao. Bo qua number dong khi doc du lieu trong file
{
	for (int i = 0; i < number; i++)
		fi.ignore(255, '\n');
}

void deleteSpace(string &str) // Hao. Xoa khoang trang du thua o khuc cuoi
{
	string s = "";
	int size = str.length() - 1;
	while (str[size] == ' ')
		size--;
	for (int i = size; i >= 0; i--)
		s = str[i] + s;
	str = s;
}

void takeDataUser(ifstream &fi, userData * &Data, int &size, int type) // Hao : LAy du lieu trong file fi dua vao Data 
{
	size = 0;			
	fi >> size;
	fi.ignore();
	if (size <= 50)
		Data = new userData[100];
	else
		Data = new userData[size * 2];
		
	int k = (type == 4) ? 2 : type;
	
	for (int i = 0; i < size; i++)
	{
		Data[i].Type = k;
		getline(fi, Data[i].ID);	
		getline(fi, Data[i].Password);
		getline(fi, Data[i].Name);
		fi >> Data[i].Gender;		
		fi.ignore();		
		if (3 == Data[i].Type)
		{								
			getline(fi, Data[i].Degree);
			fi.ignore();
		}
		else if (2 == Data[i].Type)
		{
			getline(fi,Data[i].DoB);			
			getline(fi, Data[i].className);	
			if (4 != type)		
			{
				fi >> Data[i].Status;
				fi.ignore();
				fi.ignore();
			}
			else
			{
				fi >> Data[i].Score.Midterm;
				fi >> Data[i].Score.Final;
				fi >> Data[i].Score.Bonus;
				fi >> Data[i].Score.Total;
				fi.ignore();					
				for (int j = 0; j < 10; j++)
				{
					string s;
					getline(fi, s);
					int n = s.length();
					if (s[n - 2] == '-')
						Data[i].Attendance[j] = -1;
					else
						Data[i].Attendance[j] = 1;
				}
				fi >> Data[i].Status;	
				fi.ignore();
				fi.ignore();
			}
		}
		else
			fi.ignore();
	}
}

void insertDataUser(ofstream &fo, userData * &Data, int size) // HAo : Dua du lieu cua mang Data vao file fo
{
	fo << size << endl;
	for (int i = 0; i < size; i++)
	{
		fo << Data[i].ID << endl;			
		fo << Data[i].Password << endl;
		fo << Data[i].Name << endl;
		fo << Data[i].Gender << endl;
		if (Data[i].Type == 2)
		{
			fo << Data[i].DoB << endl;
			fo << Data[i].className << endl;
			fo << Data[i].Status << endl;
		}
		else if (3 == Data[i].Type)
			fo << Data[i].Degree << endl;
		fo << endl;
	}
}

void takeDataCourse(ifstream &fi, userData * &Lecturer, courseData * &Course, int &size)
{
	fi >> size;
	fi.ignore();
	if (size > 50)
	{
		Lecturer = new userData[size * 2];
		Course = new courseData[size * 2];
	}
	else
	{
		Lecturer = new userData[100];
		Course = new courseData[100];
	}
	
	for (int i = 0; i < size; i++)
	{
		Lecturer[i].Type = 3;
		getline(fi, Course[i].courseID);
		getline(fi, Course[i].courseName);
		getline(fi, Course[i].className);
		getline(fi, Lecturer[i].ID);
		getline(fi, Lecturer[i].Name);
		getline(fi, Lecturer[i].Degree);
		fi >> Lecturer[i].Gender;
		fi.ignore();
		getline(fi, Course[i].startDate);
		getline(fi, Course[i].endDate);
		fi >> Course[i].DoW;
		fi.ignore();
		getline(fi, Course[i].startTime);
		getline(fi, Course[i].endTime);
		getline(fi, Course[i].Room);
		fi.ignore();
	}
}

void insertDataCourse(ofstream &fo, userData * &Lecturer, courseData * &Course, int &size)
{
	fo << size << endl;
	for (int i = 0; i < size; i++)
	{
		fo << Course[i].courseID << endl;
		fo << Course[i].courseName << endl;
		fo << Course[i].className << endl;
		fo << Lecturer[i].ID << endl;
		fo << Lecturer[i].Name << endl;
		fo << Lecturer[i].Degree << endl;
		fo << Lecturer[i].Gender << endl;
		fo << Course[i].startDate << endl;
		fo << Course[i].endDate << endl;
		fo << Course[i].DoW << endl;
		fo << Course[i].startTime << endl;
		fo << Course[i].endTime << endl;
		fo << Course[i].Room << endl;
		fo << endl;
	}
}

void takeDataClass(ifstream &fi, string nameClass[], int &size)
{
	fi >> size;
	fi.ignore();
	for (int i = 0; i < size; i++)
		fi >> nameClass[i];	
}

void insertDataClass(ofstream &fo, string nameClass[], int size)
{
	fo << size << endl;
	for (int i = 0; i < size; i++)
		fo << nameClass[i] << endl;
}

void takeCurrentSemester(string &semesterCurrent) // Lay Hoc ki va nam hoc hien tai vao semesterCurrent VD: semesterCurrent = "2019-2020-HK2"
{
	ifstream fi;
	semesterCurrent = "";
	fi.open("fileCourse/Semester.txt");
	if (!fi.is_open())
		cout << "Khong mo duoc file" << endl;
	else
	{
		int n;
		fi >> n;
		string Semester;
		string Scholatics;
		for (int i = 0; i < n; i++)
		{
			fi >> Semester >> Scholatics;
			fi.ignore();
		}
		semesterCurrent = Semester + "-" + Scholatics;
		fi.close();	
	}					 		
}

bool isLeapYear(int year)
{
	if (0 == year % 100)	
	{
		if (year % 400 == 0)
			return true;
		return false;
	}
	else
	{
		if (0 == year % 4)
			return true;
		return false;
	}
}

void writeAttendanceToFile(ofstream &fo, int Attendance[], string startDate, string startTime, string endTime) // viet Bang diem danh vao tung sinh vien
{
	int dateOfMonth[20];
	int Day = 0, Month = 0, Year = 0;
	int i = 0;
	while (startDate[i] != ' ')									
		Year = Year * 10 + int(startDate[i++]) - 48;
	i++;
	
	while (startDate[i] != ' ')
		Month = Month * 10 + int(startDate[i++]) - 48;

	i++;	
	int n = startDate.length();
	
	while (i != n)
		Day = Day * 10 + int(startDate[i++]) - 48; 
													
	
	for (int i = 1; i <= 12; i++)
	{
		switch(i)
		{
			case 1: case 3: case 5: case 7: case 8 : case 10: case 12:
			{
				dateOfMonth[i] = 31;
				break;
			}
			case 4: case 6: case 9: case 11:
			{
				dateOfMonth[i] = 30;
				break;
			}
			default:
			{
				if (isLeapYear(Year))
					dateOfMonth[i] = 29;
				else
					dateOfMonth[i] = 28;
				break;
			}
		}
	}
	
	for (int i = 0 ; i < 10; i++)
	{
		fo << Year << " ";
		if (Month < 10)
			fo << "0";
		fo << Month << " ";
		if (Day < 10)
			fo << "0";
		fo << Day << " " << startTime << " " << endTime << " " << Attendance[i] << endl;
		Day = Day + 7;										
		if (Day > dateOfMonth[Month])
		{
			Day = Day % dateOfMonth[Month];
			Month++;
			if (Month > 12)
			{
				Year++;
				Month = 1;
			}
		}	
	}
}


void insertDataStudentInCourse(string fileName, userData *Data, int size) //Dua du lieu Data vao fileName . fileName o day la file chua du lieu sinh vien trong mot khoa hoc
{
	string fileNameCourse = "fileCourse/";
	int i = 0, dem = 0;
	while (fileName[i++] != '/');
	while (dem != 3)
	{
		fileNameCourse += fileName[i];
		if (fileName[i++] == '-')
			dem++;
	}			
	fileNameCourse += "Schedule-";
	while (dem != 4)
	{
		if (fileName[i] == '-')
		{
			dem++;
			i++;
			break;
		}
		fileNameCourse += fileName[i++];	
	}		
	
	string courseID = "";
	while (dem != 5)
	{
		if (fileName[i] == '-')
			break;
		courseID += fileName[i++];		
	}
	
	fileNameCourse += ".txt";
	
	int sizeCourse;
	userData * Lecturer;
	courseData * Course;
	
	ifstream fi;
	fi.open(fileNameCourse.c_str());
	if (!fi.is_open())
		cout << "don't open" << endl;
	else
		takeDataCourse(fi, Lecturer, Course, sizeCourse);
	fi.close();
	
						
	string startDate = "", startTime = "", endTime = "" ;

	for (int i = 0; i < sizeCourse; i++)
	if (courseID == Course[i].courseID)
	{
			startDate = Course[i].startDate;
			startTime = Course[i].startTime;
		 	endTime = Course[i].endTime;
			break;
	}
	
		
	ofstream fo;
	fo.open(fileName.c_str());
	fo << size << endl;
	for (int i = 0; i < size; i++)
	{
		fo << Data[i].ID << endl;
		fo << Data[i].Password << endl;
		fo << Data[i].Name << endl;
		fo << Data[i].Gender << endl;
		fo << Data[i].DoB << endl;
		fo << Data[i].className << endl;
		fo << Data[i].Score.Midterm << endl;
		fo << Data[i].Score.Final << endl;
		fo << Data[i].Score.Bonus << endl;
		fo << Data[i].Score.Total << endl;			
		writeAttendanceToFile(fo, Data[i].Attendance, startDate, startTime, endTime);	
		fo << Data[i].Status << endl;	
		fo << endl;
	}
	fo.close();
}

//*********************************************************//

//*********************Cac ham dung chung ****************//

bool check(ifstream &fi, string Username, string Password, accountData &Data, int number) // Hao . Chuc nang: Lay du lieu va Kiem tra tung tai khoan
{
	int n;
	fi >> n;
	fi.ignore(255, '\n');
	accountData dataCheck;
	for (int i = 0; i < n; i++)
	{
		getline(fi, dataCheck.ID); deleteSpace(dataCheck.ID);									
		getline(fi, dataCheck.Password); deleteSpace(dataCheck.Password);						
		getline(fi, dataCheck.Name); deleteSpace(dataCheck.Name);
		fi >> dataCheck.Gender;
		if (5 == number)
		{
			ignoreLine(fi, 3);
			fi >> dataCheck.Status;												
			ignoreLine(fi, 2);
		}
		else
		{								
			ignoreLine(fi, number);
			dataCheck.Status = 1;
		}
		if ((dataCheck.ID == Username) && (dataCheck.Password == Password))
		{
			if (dataCheck.Status == 1)
			{			
				Data = dataCheck;
				return true;
			}
		}
	}
	return false;
}

int checkPassword(string Username, string Password, accountData &Data) // Hao .Chuc nang : Kiem tra tai khoan .
{
		string nameFolder = "fileUser/";
	string nameFile = "";
	ifstream fi;
	bool kt;
	
	nameFile = nameFolder + "Staff.txt";
	fi.open(nameFile.c_str());
	kt = check(fi, Username, Password, Data, 2);
	if (kt)
		return 1;
	fi.close();
	
	nameFile = nameFolder + "Lecturer.txt";
	fi.open(nameFile.c_str());
	kt = check(fi, Username, Password, Data, 3);
	if (kt)
		return 3;
	fi.close();
	
	nameFile = nameFolder + "Student.txt";
	fi.open(nameFile.c_str());
	kt = check(fi, Username, Password, Data, 5);
	if (kt)
		return 2;
	fi.close();
	
	return -1;
}

void changePassword(string Username, string Password, int type) // Hao : Ham thay doi password
{
	
	ifstream fi;
	if (1 == type)
		fi.open("fileUser/Staff.txt");
	else if (2 == type)
		fi.open("fileUser/Student.txt");
	else if (3 == type)
		fi.open("fileUser/Lecturer.txt");
	if (!fi.is_open())
		cout << "Khong mo duoc file" << endl;
	else
	{
		userData * Data;
		int size, i = 0;				
		takeDataUser(fi, Data, size, type);
		for (i = 0; i < size; i++)
			if (Data[i].ID == Username)
				break;
		string currentPassword = "";
		while (currentPassword != Password)
		{				
			cout << "Enter your current Password : " ; 
			cin >> currentPassword;
			if (currentPassword != Password)
			{
				system("CLS");
				cout << "Your enter password isn't correct !!" << endl;
				cout << "0. Return       1. Continue" << endl;
				int numberChoice = -1;
				while (numberChoice == -1)
					numberChoice = choiceScreen(1);
				system("CLS"); 
				if (numberChoice == 0)
				{
					switch(type)
					{
						case 1:
						{
							staffUI();
							break;		
						}
						case 2:
						{
							studentUI();
							break;
						}
						case 3:
						{
							lecturerUI();
						}
					}
				}
			}
		}
		
		string newPassword1 = "a", newPassword2 = "b";
		while (newPassword1 != newPassword2)
		{
			cout << "Enter new password       : " ; cin >> newPassword1;
			cout << "Enter new password again : " ; cin >> newPassword2;
			if (newPassword1 != newPassword2)
			{
				system("CLS");
				cout << "Two new password you've entered isn't the same !! Try again" << endl;		
			}
		}
		Data[i].Password = newPassword1;
		ofstream fo;
		if (1 == type)
			fo.open("fileUser/Staff.txt");
		else if (2 == type)
			fo.open("fileUser/Student.txt");
		else if (3 == type)
			fo.open("fileUser/Lecturer.txt");
		insertDataUser(fo, Data, size);
		
		cout << "Your password is changed successfully !!!" << endl;
		system("CLS");
		switch(type)
		{
			case 1:
				{
					staffUI();
					break;		
				}
			case 2:
				{
					studentUI();
					break;
				}
			case 3:
				{
					lecturerUI();
					break;
				}
		}
		fi.close();	
	}	
}
//*******************************************************//	

