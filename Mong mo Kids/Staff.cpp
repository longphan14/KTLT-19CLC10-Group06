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

void takeCurrentSemester(string &semesterCurrent)
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
//**********************************************//

//Tinh Nang cua User STAFF//

Void importCourse() {
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

}
Void addCourse();
Void viewListCourse();

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
}
//************************//
