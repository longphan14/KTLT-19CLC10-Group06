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

int choiceScreen(int Number)
{
	string Choice;					
	cout << "Enter your choice (0 -> " << Number << ") :" ; cin >> Choice;
	return checkChoice(Choice, Number);
}
//*******************************//

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

