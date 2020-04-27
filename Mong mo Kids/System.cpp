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
