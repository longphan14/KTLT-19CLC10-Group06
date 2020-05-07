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

//**********************************************//

//Tinh Nang cua User STAFF//

void importCourse() {
	fstream fi;
	string file;
	int size;
	cout << "Nhap duong truyen file: ";
	cin >> file;
	fi.open(file);
	if(fi.fail()){
		cout << "Fail to open this file!";
	}
	else {
		cout << "Open success!" << endl;
		size = strlen(file);
		for (int i = size; i > size - 5; i--){
			if(file[i] = "v" && file[i-1] = "s" && file[i-2] = "c"){
				cout << "This is csv file!" << endl;
			}
			else 
				cout << "This is not csv file!" << endl;
		}
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
	pauseScreen();
	editFeatureStu();	
}
//************************//
