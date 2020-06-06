#include "Header.h"
#include "Staff.h"
#include "Student.h"
#include "Lecturer.h"
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
			string Username, Password, P;
			char p;
			accountData Data;
			cout << "ACCOUNT" << endl;
			cout << "Username : "; cin >> Username;
			cout << "Password : ";
			p=_getch();
			while(p != 13){
				if(p == 8){
					Password.resize(P.length() - 1);
					cout << P;
					Password.resize(Password.length() - 1);
				}
				else{
					P = P + "*";
					cout << P;
					Password.push_back(p); 
				}
				p = _getch();
				system("CLS");
				cout << "ACCOUNT" << endl;
				cout << "Username : " << Username << endl;
				cout << "Enter Password: ";
			}
			cout << endl << Password << endl;
			clearScreen();
			int kt = checkPassword(Username, Password, Data);
			dataAccess = Data;
			switch(kt)
			{
				case 1:
				{
					staffUI();
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
			importStudent();
			break;
		}
		case 2:
		{
			addStudent();
			break;
		}
		case 3:
		{
			editStudent();
			break;
		}
		case 4:
		{
			removeStudent();
			break;
		}
		case 5:
		{
			changeClass();
			break;
		}
		case 6:
		{
			removeStudentinCourse();
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
	cout << "7. View scoreboard list of a course" << endl;
	int numberChoice = choiceScreen(7);
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
			viewListStudentinClass();
			break;
		}
		case 2:
		{
			viewListClassused(); // dung sua ten ham nay nha lop du chu ca mo
			break;
		}
		case 3:
		{
			searchViewScoreboardList();
			break;
		}
		case 4:
		{
			viewAttendanceList();
			break;
		}
		case 5:
		{
			searchViewAttendanceList();
			break;
		}
		case 6:
		{
			viewListStudentinCourse(1);
			break;
		}
		case 7:{
			ViewScoreboardList();
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
			exportScoreboadrdList();
			break;
		}
		case 2:
		{
			exportAttendanceList();
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
			addCourse();
			break;
		}
		case 3:
		{
			editCourse();
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
			viewListCourse(1);
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
	cout << "3. View Information" << endl;
	int numberChoice = choiceScreen(3);
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
		case 3:
		{
			viewInfor(dataAccess.ID, 1);
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
	cout << "Hello ";
	cout << dataAccess.Name << endl;
	cout << "0. Logout" << endl;
	cout << "1. Show Menu" << endl;
	cout << "2. Change Password" << endl;
	cout << "3. View Information" << endl;
	int numberChoice = choiceScreen(3);
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
			studentShowMenu();
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			viewInfor(dataAccess.ID, 2);
			break;
		}
		default:
		{
			warnScreen();
			studentUI();
			break;
		}
	}
}

void studentShowMenu()
{
	cout << "Show Menu: " << endl;
	cout << "0. Return " << endl;
	cout << "1. Check-in" << endl;
	cout << "2. View check-in result" << endl;
	cout << "3. View schedules" << endl;
	cout << "4. View scores of a course" << endl;
	cout << "5. View Information" << endl;
	int numberChoice = choiceScreen(5);
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			studentUI();
			break;
		}
		case 1:
		{
			check_in(dataAccess.ID);
			break;
		}
		case 2:
		{
			viewCheckIn(dataAccess.ID);
			break;
		}	
		case 3:
		{
			viewSchedules(dataAccess.ID);
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
		default:
		{
			warnScreen();
			studentShowMenu();
			break;	
		}
	} 
}
//********************************//

//******LECTURER USER INTERFACE***//
void lecturerUI()
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
	cout << "3. View Information" << endl;
	int numberChoice = choiceScreen(3);
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
			lecturerShowMenu();
			break;
		}
		case 2:
		{
			changePassword(dataAccess.ID, dataAccess.Password, 1);
			break;
		}
		case 3:
		{
			viewInfor(dataAccess.ID, 3);
			break;
		}
		default:
		{
			warnScreen();
			lecturerUI();
			break;
		}
	}
}

void lecturerShowMenu()
{
	cout << "Show Menu: " << endl;
	cout << "0. Return " << endl;
	cout << "1. View feature" << endl;
	cout << "2. Job" << endl;
	int numberChoice = choiceScreen(2);
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			lecturerUI();
			break;
		}
		case 1:
		{
			viewFeatureOfLecturer();
			break;
		}
		case 2:
		{
			jobFeature();
			break;
		}	
		default:
		{
			warnScreen();
			lecturerShowMenu();
			break;	
		}
	} 
}

void viewFeatureOfLecturer()
{
	cout << "View features :" << endl;
	cout << "0. Return" << endl;
	cout << "1. View list of course" << endl;
	cout << "2. View list student of a course" << endl;
	cout << "3. View attendance list" << endl;
	cout << "4. View a scoreboard" << endl;
	int numberChoice = choiceScreen(4);
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			lecturerShowMenu();
			break;
		}
		case 1:
		{
			viewListCourse(2);
			break;
		}
		case 2:
		{
			viewListStudentinCourse(2);
			break;
		}
		case 3:
		{
			viewAttendanceListOfLecturer(dataAccess.ID);
			break;
		}
		case 4:
		{
			viewScoreboardListOfLecturer(dataAccess.ID);
			break;
		}
		default:
		{
			warnScreen();
			viewFeatureOfLecturer();
			break;
		}
	}
}

void jobFeature()
{
	cout << "Feature support to your job :" << endl;
	cout << "0. Return" << endl;
	cout << "1. Edit an attendance" << endl;
	cout << "2. Import scoreboard" << endl;
	cout << "3. Edit Score of a student" << endl;
	int numberChoice = choiceScreen(3);
	clearScreen();
	switch (numberChoice)
	{
		case 0:
		{
			lecturerShowMenu();
			break;
		}
		case 1:
		{
			editAttendance(dataAccess.ID);
			break;
		}
		case 2:
		{
			ImportScoreBoard(dataAccess.ID);
			break;
		}
		case 3:
		{
			editScoreboard(dataAccess.ID);
			break;
		}
		default:
		{
			warnScreen();
			jobFeature();
			break;
		}
	}
}
