#include "Lecturer.h"
float stof(string number)
{
	stringstream ss;
	ss << number;
	float so;
	ss >> so;
	return so;
}

void takeScoreCSVData(ifstream& fi, userData*& Data, int& size)
{
	Data = new userData[1000];
	string Midterm, Final, Bonus, Total;
	int i = 0;
	fi.ignore(1000, '\n');

	while (!fi.eof())
	{
		Data[i].Name = "";
		getline(fi, Data[i].Name, ',');
		if (Data[i].Name.length() == 0)
			break;
		getline(fi, Midterm, ',');
		if (Midterm == "x")
			Data[i].Score.Midterm = -1;
		else 
			Data[i].Score.Midterm = stof(Midterm);
			
		getline(fi, Bonus, ',');
		if (Bonus == "x")
			Data[i].Score.Bonus = -1;
		else
			Data[i].Score.Bonus = stof(Bonus);

		getline(fi, Final, ',');
		if (Final == "x")
			Data[i].Score.Final = -1;
		else
			Data[i].Score.Final = stof(Final);

		getline(fi, Total,'\n');
		if (Total == "x")
			Data[i].Score.Total = -1;
		else
			Data[i].Score.Total = stof(Total);

		size++;
		i++;
	}
}

void editAttendance(string LecturerID){
	
	
	string filename, studentID, CourseID, filename1, Classname;
	
	spinputLecturer(LecturerID, filename, filename1, studentID, CourseID, Classname);
	if(filename == ""){
		return jobFeature();
	}

	while(true){
		string week2;
		userData *student;
		int size = 0;
		ifstream fi;
		fi.open(filename.c_str());
		takeDataUser(fi, student, size, 4);
		fi.close();
	
		
		spviewAttendanceList(filename1, CourseID);
		stringstream week1;
		int week;
		cout << "Week to edit: ";
		cin >> week2;
		week1 << week2;
		week1 >> week;
		if(week == 0 || week > size){
			cout << "Invalid Enter!" << endl;
			return jobFeature();
		}
		for(int i = 0; i < size; i++){
			if(student[i].ID == studentID){
				stringstream choice2;
				string choice1;
				int choice;
				cout << "Enter edit(1: appearance, 2: not appearance, 3: not available): ";
				cin >> choice1;
				choice2 << choice1;
				choice2 >> choice;
				if(choice == 0 || choice > 3){
					cout << "Invalid Enter!" << endl;
					return jobFeature();
				}
				else if(choice == 1)
					student[i].Attendance[week - 1] = 1;
				else if(choice == -1)
					student[i].Attendance[week - 1] = 0;
				else
					student[i].Attendance[week - 1] = -1;
				insertDataStudentInCourse(filename, student, size);
				cout << "Changed successfully!" << endl;
				string key;
				cout << "Press any key to return: ";
				cin >> key;
				system("CLS");
				return jobFeature();
			}
		}
	}
}


void viewAttendanceListOfLecturer(string ID){
	int size = 0;
	string currentSemester;
	string LecturerChoice[100];
	userData* Lecturer;
	courseData* Course;
	takeCurrentSemester(currentSemester);
	ifstream fi;
	ifstream fi2;
	string filename ="fileCourse/" + currentSemester + "-Schedule.txt";
	fi.open(filename.c_str());
	takeDataCourse(fi, Lecturer, Course, size);
	int number = 0;	
	courseData courseLecturer[50];		
	for (int i = 0; i < size; i++){
		if (ID == Lecturer[i].ID){
			cout << "Classes Instructed: " << endl;
			cout << number << ". "<< Course[i].courseID << " - " <<  Course[i].courseName << endl;
			courseLecturer[number++] = Course[i];
		}	
	}
	if (number == 0){
		cout << "This lecturer does not instruct any class!!" << endl;
		cout << "Press any keys to return!" << endl;
		string key;
		cin >> key;
		system("CLS");
		viewFeatureOfLecturer();
	}
	cout << "Please choose class to view attendance list!" << endl;
	int numberChoice = choiceScreen(number - 1);
	string filename2 = "fileCourse/" + currentSemester + "-" + courseLecturer[numberChoice].className+ "-" + courseLecturer[numberChoice].courseID +"-Student.txt";
	if (numberChoice == -1){
		cout << "Wrong Class!" << endl;
	}
	else
	{
		spviewStudentAttendanceList(filename2);	
	}
	cout << "Press any keys to return!!" << endl;
	string key;
	cin >> key;
	system("CLS");
	viewFeatureOfLecturer();
}


void editScoreboard(string LecturerID){
	string filename, studentID, CourseID, filename1, Classname;
	spinputLecturerScoreboard(LecturerID, filename, filename1, studentID, CourseID, Classname);
	if(filename == ""){
		return jobFeature();
	}

	while(true){
		userData *student;
		int size = 0;
		ifstream fi;
		fi.open(filename.c_str());
		takeDataUser(fi, student, size, 4);
		fi.close();
		stringstream ss1, ss2, ss3, ss4;
		string midterm1, bonus1, final1, total1;
		int midterm, bonus, final, total;
		cout << "Midterm: " ;
		cin >> midterm1;
		ss1 << midterm1;
		ss1 >> midterm;
		cout << "Bonus: " ;
		cin >> bonus1;
		ss2 << bonus1;
		ss2 >> bonus;
		cout << "Final: ";
		cin >> final1;
		ss3 << final1;
		ss3 >> final;
		cout << "Total: ";
		cin >> total1;
		ss4 << total1;
		ss4 >> total;
		for(int i = 0; i < size; i++){
			if(student[i].ID == studentID){
					student[i].Score.Midterm = midterm;
					student[i].Score.Bonus = bonus;
					student[i].Score.Final = final;
					student[i].Score.Total = total;
				cout << "Do you want to edit this student like this: " << endl;
				cout << student[i].Name << "  " << student[i].Score.Midterm << "  " << student[i].Score.Bonus << "  " << student[i].Score.Final << "  " << student[i].Score.Total << endl;
				stringstream dd;
				string Choicea;
				int Choice;
				cout << "1.Yes   2.No  Your Choice: " ;
				cin >> Choicea;
				dd << Choicea;
				dd >> Choice;
				if(1 == Choice){
					insertDataStudentInCourse(filename, student, size);
					cout << "Changed successfully!" << endl;
					string key;
					cout << "Press any key to return: ";
					cin >> key;
					system("CLS");
					return jobFeature();
				}
				else if(2 == Choice)
					cout << "Ending Edit" << endl;
					
				else 
					cout << "Invalid Enter" << endl;
				string key;
				cout << "Press any key to return: ";
				cin >> key;
				system("CLS");
				return jobFeature();
			}
		}
	}
}

void spinputLecturerScoreboard(string LecturerID , string &filename, string &filename1, string &studentID, string &CourseID, string &Classname){
	ifstream fi1, fi;
	string semesterCurrent;
	userData* Lecturer;
	courseData* Course;
	int size = 0;
	int S = 0;
	bool check = false;
	takeCurrentSemester(semesterCurrent);
	filename1 = "fileCourse/" + semesterCurrent + "-Schedule.txt";
	fi1.open(filename1.c_str());
	takeDataCourse(fi1, Lecturer, Course, size);
	fi1.close();
	int S1 = 0;
	int stt = 0;
	for (int i = 0; i < size; i++)
	if (Lecturer[i].ID == LecturerID)
	{
		cout << ++stt << ". " << Course[i].courseID << "-" << Course[i].courseName << endl;
		check = true;
	}

	string NOCheck;
	cout << "Enter Number of Order: ";
	cin >> NOCheck;
	int checking = checkChoice(NOCheck, stt);
	if (("0" == NOCheck) || (-1 == checking))
	{
		//Sai
		cout << "Invalid Enter!" << endl;
		return jobFeature();
	}
	int NO;
	stringstream ss;
	ss << NOCheck;
	ss >> NO;
	
	CourseID = Course[NO - 1].courseID;
	Classname = Course[NO - 1].className;
	filename = "fileCourse/" + semesterCurrent + "-" + Course[NO - 1].className + "-" + Course[NO - 1].courseID + "-Student.txt";
	ifstream fi2;
	userData* UserData; 
	courseData Course2;
	int size2;
	fi2.open(filename.c_str());
	takeDataUser(fi2, UserData, size2, 4);
	fi2.close();
	string NO1;
	if(check == true){
		spViewScoreboardList(CourseID, Classname);
		cout << "Enter Student Number of Order(0 to exit): ";
		cin >> NO1;
		int checking = checkChoice(NO1, size2);
	if (("0" == NO1) || (-1 == checking))
	{
		cout << "Invalid Enter!" << endl;
		return jobFeature();
	}
	int NO;
	stringstream ss;
	ss << NO1;
	ss >> NO;
		studentID = UserData[NO - 1].ID;
		for(int i = 0; i < size2; i++){
			if(i == NO - 1){
				while(true){
				cout << "Do you want to edit this student: " << endl;
				cout << "0.No     1. Yes" << endl;
				int numberChoice = choiceScreen(1);
				if(numberChoice == -1){
					cout << "Error Enter!" << endl;
				}
				else if(numberChoice == 0){
					filename = "";
					return;
					}
				else{
					return;
				}
				}
			}
		}
	}
	else{
		cout << "Don't have any course!";
	}
}


void spinputLecturer(string LecturerID , string &filename, string &filename1, string &studentID, string &CourseID, string &Classname){
	ifstream fi1, fi;
	string semesterCurrent;
	userData* Lecturer;
	courseData* Course;
	int size = 0;
	int S = 0;
	bool check = false;
	takeCurrentSemester(semesterCurrent);
	filename1 = "fileCourse/" + semesterCurrent + "-Schedule.txt";
	fi1.open(filename1.c_str());
	takeDataCourse(fi1, Lecturer, Course, size);
	fi1.close();
	int S1 = 0;
	int stt = 0;
	for (int i = 0; i < size; i++)
	if (Lecturer[i].ID == LecturerID)
	{
		cout << ++stt << ". " << Course[i].courseID << "-" << Course[i].courseName << endl;
		check = true;
	}

	string NOCheck;
	cout << "Enter Number of Order: ";
	cin >> NOCheck;
	int checking = checkChoice(NOCheck, stt);
	if (("0" == NOCheck) || (-1 == checking))
	{
		//Sai
		cout << "Invalid Enter!" << endl;
		return jobFeature();
	}
	int NO;
	stringstream ss;
	ss << NOCheck;
	ss >> NO;
	
	CourseID = Course[NO - 1].courseID;
	Classname = Course[NO - 1].className;
	filename = "fileCourse/" + semesterCurrent + "-" + Course[NO - 1].className + "-" + Course[NO - 1].courseID + "-Student.txt";
	ifstream fi2;
	userData* UserData; 
	courseData Course2;
	int size2;
	fi2.open(filename.c_str());
	takeDataUser(fi2, UserData, size2, 4);
	fi2.close();
	string NO1;
	if(check == true){
		spviewStudentAttendanceList(filename);
		cout << "Enter Student Number of Order(0 to exit): ";
		cin >> NO1;
		int checking = checkChoice(NO1, size2);
	if (("0" == NO1) || (-1 == checking))
	{
		cout << "Invalid Enter!" << endl;
		return jobFeature();
	}
	int NO;
	stringstream ss;
	ss << NO1;
	ss >> NO;
		studentID = UserData[NO - 1].ID;
		for(int i = 0; i < size2; i++){
			if(i == NO - 1){
				while(true){
				cout << "Do you want to edit this student: " << endl;
				cout << "0.No     1. Yes" << endl;
				int numberChoice = choiceScreen(1);
				if(numberChoice == -1){
					cout << "Error Enter!" << endl;
				}
				else if(numberChoice == 0){
					filename = "";
					return;
					}
				else{
					return;
				}
				}
			}
		}
	}
	else{
		cout << "Don't have any course!";
	}
}

void ImportScoreBoard()
{
	cout << endl;
	cout << "\t=== IMPORT STUDENT SCORE BOARD ===" << endl;
	cout << endl;
	userData* Selected;
	int csvsize2 = 0;
	int size = 0;
	userData* Data2;
	string filename;
	//view class
	viewListClass();
	//check class
	int sizeofclass;
	string nameClass[100];
	string Class = "fileClass/Class_Mau.txt";
	ifstream file(Class.c_str());

	if (!file.is_open())
	{
		cout << "-> ERROR: File Open 1" << endl;
		cout << "-> Please check your program again!" << endl;
	}
	else
	{
		takeDataClass(file, nameClass, sizeofclass);
		file.close();
	}

	//enter class
	string classroom;
	string classchoice;
	int choice;
	while (true)
	{
		cout << "* Enter the number of the class which you chose: ";
		cin >> classchoice;

		stringstream zz(classchoice);
		if ((zz >> choice).fail() || choice > sizeofclass || choice <= 0)
			cout << "-> Please try again" << endl;
		else
			break;
	}
	cout << endl;

	for (int i = 0; i < sizeofclass; i++)
	{
		if (choice == i + 1)
			classroom = nameClass[i];
	}
	//enter semester
	string semester;
	takeCurrentSemester(semester);
	//view course id
	cout << endl;
	courseData* Course;
	Course = new courseData[10000];
	int sizecourse;

	while (true)
	{
		cout << "===List of " << classroom << "'s course===" << endl;
		string name = "fileCourse/" + semester + "-Schedule-" + classroom + ".txt";
		ifstream coursefile(name.c_str());
		if (!coursefile.is_open())
		{
			cout << "-> Course File does not exist" << endl;
			cout << "-> Please check your information again" << endl;

			while (true)
			{
				cout << "* Enter your choice of class: ";
				cin >> classchoice;

				stringstream zz(classchoice);
				if ((zz >> choice).fail() || choice > sizeofclass || choice <= 0)
					cout << "-> Please try again" << endl;
				else
					break;
			}
			cout << endl;

			for (int i = 0; i < sizeofclass; i++)
			{
				if (choice == i + 1)
					classroom = nameClass[i];
			}
		}
		else
		{
			coursefile >> sizecourse;
			coursefile.ignore();
			for (int i = 0; i < sizecourse; i++)
			{
				getline(coursefile, Course[i].courseID);
				cout << "\t" << i+1 << ". Course ID: " << Course[i].courseID << endl;
				getline(coursefile, Course[i].courseName);
				cout << "\tCourse Name : " << Course[i].courseName << endl;
				for (int j = 0; j < 12; j++)
					coursefile.ignore(1000, '\n');
			}
			break;
		}
	}
	//enter course name
	string coursename, courseid;
	string coursechoice;
	int coursenum;
	while (true)
	{
		cout << "* Enter your choice (1 -> 2): ";
		cin >> coursechoice;

		stringstream aa(coursechoice);
		if ((aa >> coursenum).fail())
		{
			cout << "-> Unavailable course" << endl;
			cout << "-> Please enter again" << endl;
		}
		else
		{
			if (coursenum > sizecourse)
			{
				cout << "-> Unavailable course" << endl;
				cout << "-> Please enter again" << endl;
			}
			else
			{
				coursename = Course[coursenum - 1].courseName;
				courseid = Course[coursenum - 1].courseID;
				break;
			}
		}
	}
	// take score data
	int csvsize;
	string fileName = "fileCourse/" + semester + "-" + classroom + "-" + courseid + "-Student.txt";
	ifstream scorefile(fileName.c_str());

	while (true)
	{
		ifstream scorefile(fileName.c_str());
		if (!scorefile.is_open())
		{
			cout << "-> Score file isn't available" << endl;
			cout << "-> Please check your Course ID or Class again" << endl;

			//view course id
			cout << endl;
			courseData* Course;
			Course = new courseData[10000];
			int sizecourse;

			while (true)
			{
				cout << "===List of " << classroom << "'s course===" << endl;
				string name = "fileCourse/" + semester + "-Schedule-" + classroom + ".txt";
				ifstream coursefile(name.c_str());
				if (!coursefile.is_open())
				{
					cout << "-> Course File does not exist" << endl;
					cout << "-> Please check your information again" << endl;

					while (true)
					{
						cout << "* Enter your choice of class: ";
						cin >> classchoice;

						stringstream zz(classchoice);
						if ((zz >> choice).fail() || choice > sizeofclass || choice <= 0)
							cout << "-> Please try again" << endl;
						else
							break;
					}
					cout << endl;

					for (int i = 0; i < sizeofclass; i++)
					{
						if (choice == i + 1)
							classroom = nameClass[i];
					}
				}
				else
				{
					coursefile >> sizecourse;
					coursefile.ignore();
					for (int i = 0; i < sizecourse; i++)
					{
						getline(coursefile, Course[i].courseID);
						cout << "\t" <<i + 1 << ". Course ID: " << Course[i].courseID << endl;
						getline(coursefile, Course[i].courseName);
						cout << "\tCourse Name : " << Course[i].courseName << endl;
						for (int j = 0; j < 12; j++)
							coursefile.ignore(1000, '\n');
					}
					break;
				}
			}
			//enter course id
			string courseid;
			string coursechoice;
			int cource;

			while (true)
			{
				cout << "* Enter your choice of course (1 -> 2): ";
				cin >> coursechoice;

				stringstream ss(coursechoice);
				if ((ss >> cource).fail() || cource > sizecourse || cource <= 0)
					cout << "-> Please try again" << endl;
				else
				{
					if (cource == 1)
					{
						courseid = Course[0].courseID;
						break;
					}
					else if (cource == 2)
					{
						courseid = Course[1].courseID;
						break;
					}
					else
						cout << "-> Please try again" << endl;
				}
			}

			cout << endl;
			for (int i = 0; i < sizeofclass; i++)
			{
				if (choice == i + 1)
					classroom = nameClass[i];
			}
			fileName = "fileCourse/" + semester + "-" + classroom + "-" + courseid + "-Student.txt";
		}
		else
		{
			takeDataUser(scorefile, Data2, csvsize,4);
			break;
		}
	}
	scorefile.close();

	//create csv score file
	cout << endl;
	cout << "\t*** HERE IS THE INSTRUCTION OF IMPORTING STUDENT'S SCORE ***" << endl;
	cout << "-> All you have to do is to give the " + classroom + "'s " + coursename + " course  a location where you want to store it so you can open the file to edit the score" << endl;
	cout << endl;
	cout << UNDERLINE << "Step 1: " << CLOSEUNDERLINE << "Enter the location of the CSV Score File";
	cout << endl;
	string filelocation;
	string filename2;
	string filecsv;
	cout << "* Enter where you want to open the csv Score File (for example: C:/file/): ";
	cin >> filelocation;
	cout << "* Enter the score CSV file name (for example: 19APCS1-CS1002): ";
	cin >> filename2;

	filecsv = filelocation + filename2 + ".csv";
	ofstream studentcourse(filecsv.c_str());
	while (true)
	{
		ofstream studentcourse(filecsv.c_str());
		if (!studentcourse.is_open())
		{
			cout << endl;
			cout << "--> Can't open file!!!!" << endl;
			cout << "-> Please check your information again" << endl;

			cout << "* Enter where you want to open the csv Score File (for example: C:/file/): ";
			cin >> filelocation;
			cout << "* Enter the score CSV file name (for example: 19APCS1-CS1002): ";
			cin >> filename;
			cout << endl;
			filecsv = filelocation + filename2 + ".csv";
		}
		else
		{
			studentcourse << "Name,Midterm,Bonus,Final,Total\n";
			for (int i = 0; i < csvsize; i++)
			{
				string midterm = tostring(Data2[i].Score.Midterm);
				if (Data2[i].Score.Midterm == -1)
					midterm = "x";
				string bonus = tostring(Data2[i].Score.Bonus);
				if (Data2[i].Score.Bonus == -1)
					bonus = "x";
				string final = tostring(Data2[i].Score.Final);
				if (Data2[i].Score.Final == -1)
					final = "x";
				string total = tostring(Data2[i].Score.Total);
				if (Data2[i].Score.Total == -1)
					total = "x";

				studentcourse << Data2[i].Name << "," << midterm << "," << bonus << "," << final << "," << total << "\n";
			}
			break;
		}
	}
	studentcourse.close();
	scorefile.close();
	//take score
	cout << endl;
	cout << UNDERLINE << "Step 2: " << CLOSEUNDERLINE << "edit the score" << endl;
	cout << endl;
	cout << "\t!!! Please Open the CSV Score file to edit the score !!!" << endl;
	cout << "-> After edting, you have to save the edited file by replacing the old one with the edited one, so you don't have to create a new file after editing" << endl;

	while (true)
	{
		cout << endl;
		cout << "Adress: " << UNDERLINE << filecsv << CLOSEUNDERLINE << endl;
		cout << "**Have you fixed the CSV Score file yet ?" << endl;
		cout << "\t1. Yes" << endl;
		cout << "\t2. No" << endl;
		cout << "* Enter your choice (1 -> 2): ";
		string yesno;
		cin >> yesno;
		stringstream aa(yesno);
		int yesnochoice;
		if ((aa >> yesnochoice).fail() || yesnochoice > 2)
		{
			cout << "-> Your input is unvailable" << endl;
			cout << "-> Please enter again" << endl;
		}
		else if (yesnochoice == 1)
		{
			ifstream scorecsv1(filecsv.c_str());
			if (!scorecsv1.is_open())
			{
				cout << "Cant open file" << endl;
			}
			else
			{
				takeScoreCSVData(scorecsv1, Selected, csvsize2);
				scorecsv1.close();
				break;
			}
		}
		else
		{
			cout << endl;
			cout << "\t!!! Please Open the CSV Score file to edit the score !!!" << endl;
			cout << "-> After edting, you have to save the edited file by replacing the old one with the edited one, so you don't have to create a new file after editing" << endl;
		}
	}
	//slected data
	for (int i = 0; i < csvsize2; i++)
	{
		for (int j = 0; j < csvsize2; j++)
		{
			if (Selected[i].Name == Data2[j].Name)
			{
				Data2[j].Score.Midterm = Selected[i].Score.Midterm;
				Data2[j].Score.Bonus = Selected[i].Score.Bonus;
				Data2[j].Score.Final = Selected[i].Score.Final;
				Data2[j].Score.Total = Selected[i].Score.Total;
			}
		}
	}

	//create file name
	string txtfilename = "fileCourse/" + semester + "-" + classroom + "-" + courseid + "-Student.txt";
	insertDataStudentInCourse(txtfilename, Data2, csvsize2);
	cout << endl;
	cout << UNDERLINE << "IMPORT SUCCESSFULLY" << CLOSEUNDERLINE << endl;
}
