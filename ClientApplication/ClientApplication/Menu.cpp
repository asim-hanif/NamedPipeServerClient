#include "stdafx.h"
#include "Menu.h"
using namespace std;

Menu::Menu()
{
}

void Menu::ShowMenu()
{
	int option = 0;
	Students students;

	while (option != 5)
	{
		cout <<
			"                  ***************************************************************\n"
			"                  *                     Please select an option                  *\n"
			"                  *                     Press 1 to show all students             *\n"
			"                  *                     Press 2 to add student                   *\n"
			"                  *                     Press 3 to update student                *\n"
			"                  *                     Press 4 to delete student                *\n"
			"                  *                     Press 5 to exit                          *\n"
			"                  ****************************************************************\n\n";
		cin >> option;
		switch (option)
		{
		case 1:
			students.ShowAllStudents();
			break;
		case 2:
			students.AddStudent();
			break;
		case 3:
			students.UpdateStudent();
			break;
		case 4:
			students.DeleteStudent();
			break;

		}
	}
}
Menu::~Menu()
{
}
