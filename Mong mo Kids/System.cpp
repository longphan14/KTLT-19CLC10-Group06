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
	cout << "Enter your choice (0 -> " << Number << ") :" ; cin >> Choice;
	return checkChoice(Choice, Number); // Return -1 : Choice > Number or Format of chocie != Number , Return Value which is less than Number.
}
//*******************************//

//Nhung ham ho tro cho viec code ^^//

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
		ignoreLine(fi, number);
		if ((dataCheck.ID == Username) && (dataCheck.Password == Password))
		{
			Data = dataCheck;
			return true;
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
		return 2;
	fi.close();
	
	nameFile = nameFolder + "Student.txt";
	fi.open(nameFile.c_str());
	kt = check(fi, Username, Password, Data, 5);
	if (kt)
		return 3;
	fi.close();
	
	return -1;
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
	for (int i = 0 ; i < max(size * 2, 100); i++)
		Data[i].Type = type;
	for (int i = 0; i < size; i++)
	{
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
			fi >> Data[i].Status;
			fi.ignore();
			fi.ignore();
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

//*********************************************************//

//*********************Cac ham dung chung ****************//

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
		cout << "Wait 5 second to return main UI" << endl;
		sleep(5);
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

