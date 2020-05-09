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
//************************//
