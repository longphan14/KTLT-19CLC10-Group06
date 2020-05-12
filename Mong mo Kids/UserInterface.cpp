#include "Header.h"
#include "Staff.h"
#include "Student.h"
accountData dataAccess;


// First User Interface and Login //
void Login() // Hao. Chuc nang: Dang nhap
{
	cout << "Do you want to sign in :" << endl;
	cout << "0. No              1. Yes" << endl;
	int numberChoice = choiceScreen(1);
	clearScreen();
	switch(numberChoice)
	{
		case 0:
		{
			firstUI();
			break;
		}
		case 1:
		{
			string Username, Password;
			accountData Data;
			cout << "ACCOUNT" << endl;
			cout << "Username : "; cin >> Username;
			cout << "Password : "; cin >> Password;
			clearScreen();
			int kt = checkPassword(Username, Password, Data);
			dataAccess = Data;
			kt = 1;
			switch(kt)
			{
				case 1:
				{
					staffUI();
				}
				case 2:
				{
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					cout << "Your username or password isn't correct , Please try again!!" << endl;
					Login();
					break;
				}
			}
			break;	
		}
		default:
		{
			warnScreen();
			Login();
			break;
		}
	}
}

void firstUI()
{
	string Choice;								
	int kt = -1;
	while (-1 == kt)
	{
		cout << "0. Exit" << endl << "1. Login" << endl;
		int numberChoice = choiceScreen(1);
		clearScreen();
		switch (numberChoice)
		{
			case 0:
			{
				exit(0);
				break;		
			}
			case 1:
			{
				Login();
				break;
			}
			default:
			{
				warnScreen();
				break;
			}	
		}
		kt = numberChoice;
	}
}

void returnScreen(void (*functionCurrent)(), void (*functionPrevious)())
{													
	cout << "Do you want to continue ?" << endl;
	cout << "0. No              1.Yes" << endl;
	int numberChoice = choiceScreen(1);
	clearScreen();
	switch(numberChoice)
	{
		case 0 :
		{
			(*functionPrevious)();
			break;
		}
		case 1:
		{
			(*functionCurrent)();
			break;
		}
		default:
		{
			cout << "Your choose isn't Wrong !! please try again" << endl;
			returnScreen(functionCurrent, functionPrevious);
			break;
		}
	}
}
// ******************************** //




//*********STAFF USERINTERFACE**** //

//+++++++++Feature Student++++++++ //
void editFeatureStu()
{
	cout << "Edit features of student : " << endl;
	cout << "0. Return" << endl;
	cout << "1. Import student" << endl;
	cout << "2. Add new student" << endl;
	cout << "3. Edit student" << endl;
	cout << "4. Remove student" << endl;
	cout << "5. Change class of student" << endl;
	cout << "6. Remove student from a course" << endl;
	cout << "7. Add student to a course" << endl;
	int numberChoice = choiceScreen(7);
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			studentFeatureUI();
			break;
		}
		case 1:
		{
	
			break;
		}
		case 2:
		{
			
			break;
		}
		case 3:
		{
			editStudent();
			break;
		}
		case 4:
		{
			break;
		}
		case 5:
		{
			break;
		}
		case 6:
		{
			break;
		}
		case 7:
		{
			addStudentToCourse();
			break;
		}
		default:
		{
			warnScreen();
			editFeatureStu();
			break;
		}
	}
}

void viewFeatureStu()
{
	cout << "View features of student :" << endl;
	cout << "0. Return" << endl;
	cout << "1. View list students of a class" << endl;
	cout << "2. View list of class" << endl;
	cout << "3. Search and view scoreboard list of a course" << endl;
	cout << "4. View attendance list of a course" << endl;
	cout << "5. Search and view attendance list of a course" << endl;
	cout << "6. View list of students in a course" << endl;
	int numberChoice = choiceScreen(6);
	clearScreen();
	switch(numberChoice)
	{
		case 0:
		{
			studentFeatureUI();
			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			break;
		}
		case 5:
		{
			break;
		}
		case 6:
		{
			break;
		}
		default:
		{
			warnScreen();
			viewFeatureStu();
			break;
		}
	}
}

void exportFeatureStu()
{
	cout << "Export file feature :" << endl;
	cout << "0. Return" << endl;
	cout << "1. Export a scoreboard" << endl;
	cout << "2. Export attendance list" << endl;
	int numberChoice = choiceScreen(2);
	clearScreen();
	switch(numberChoice)
	{
		case 0:
		{
			studentFeatureUI();		
			break;		
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			warnScreen();
			exportFeatureStu();
			break;
		}
	}
}

void studentFeatureUI()
{
	cout << "Student Features :" << endl;
	cout << "0. Return: " << endl;
	cout << "1. Edit feature" << endl;
	cout << "2. View feature" << endl;
	cout << "3. Export file feature" << endl;
	
	int numberChoice = choiceScreen(3);
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			showMenu();
			break;
		}
		case 1:
		{
			editFeatureStu();
			break;
		}
		case 2:
		{
			viewFeatureStu();
			break;
		}
		case 3:
		{
			exportFeatureStu();
			break;
		}
		default:
		{
			warnScreen();
			studentFeatureUI();
			break;
		}
	} 	
}
//+++++++++++++++++++++++++++++++ //

//+++++++++Feature Course+++++++ //
void editFeatureCourse()
{
	
	cout << "Edit features of course :" << endl;
	cout << "0. Return" << endl;
	cout << "1. Import course" << endl;
	cout << "2. Add new course" << endl;
	cout << "3. Edit course" << endl;
	cout << "4. Remove course" << endl;
	cout << "5. Update semester" << endl;
	cout << "6. Delete semester" << endl;
	int numberChoice = choiceScreen(6);	
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			courseFeatureUI();
			break;
		}
		case 1:
		{
			importCourse();
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			removeCourse();
			break;
		}
		case 5:
		{
			updateSemester();
			break;
		}
		case 6:
		{
			deleteSemester();
			break;
		}
		default:
		{
			warnScreen();
			editFeatureCourse();
			break;
		}
	}
}

void viewFeatureCourse()
{
	cout << "View features of course :" << endl;
	cout << "0. Return" << endl;
	cout << "1. View list of course" << endl;
	cout << "2. View all lecturers" << endl;
	cout << "3. View Semester" << endl;
	int numberChoice = choiceScreen(3);
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			courseFeatureUI();
			break;
		}
		case 1:
		{
			viewListCourse();
			break;
		}
		case 2:
		{
			viewAllLecturer();
			break;
		}
		case 3:
		{
			viewSemester();
			break;
		}
		default:
		{
			warnScreen();
			viewFeatureCourse();
			break;
		}
	}
}
void courseFeatureUI()
{
	cout << "Features of course :" << endl;
	cout << "0. Return" << endl;
	cout << "1. Edit feature" << endl;
	cout << "2. View feature" << endl;
	int numberChoice = choiceScreen(2);
	clearScreen();
	switch(numberChoice)
	{
		case 0:
		{
			showMenu();
			break;
		}
		case 1:
		{
			editFeatureCourse();
			break;
		}
		case 2:
		{	
			viewFeatureCourse();
			break;
		}
		default:
		{
			warnScreen();
			courseFeatureUI();
			break;
		}
	}			
}
//++++++++++++++++++++++++++++++ //
void showMenu()
{
	cout << "Show Menu: " << endl;
	cout << "0. Return " << endl;
	cout << "1. Student" << endl;
	cout << "2. Course" << endl;
	int numberChoice = choiceScreen(2);
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			staffUI();
			break;
		}
		case 1:
		{
			studentFeatureUI();
			break;
		}
		case 2:
		{
			courseFeatureUI();
			break;
		}	
		default:
		{
			warnScreen();
			showMenu();
			break;	
		}
	} 
}

void staffUI()
{
	cout << "Hello ";
	if (dataAccess.Gender == 0)
		cout << "Mr ";
	else
		cout << "Mrs ";
	cout << dataAccess.Name << endl;
	cout << "0. Logout" << endl;
	cout << "1. Show Menu" << endl;
	cout << "2. Change Password" << endl;
	int numberChoice = choiceScreen(2);
	clearScreen();
	switch(numberChoice)
	{
		case 0:
		{
			Login();
			break;
		}
		case 1:
		{
			showMenu();
			break;
		}
		case 2:
		{
			changePassword(dataAccess.ID, dataAccess.Password, 1);
			break;
		}
		default:
		{
			warnScreen();
			staffUI();
			break;
		}
	}
	
}
//******************************** //	

//******STUDENT USER INTERFACE*****//
void studentUI()
{
	
}
//********************************//

//******LECTURER USER INTERFACE***//
void lecturerUI()
{
	
}
//********************************//
