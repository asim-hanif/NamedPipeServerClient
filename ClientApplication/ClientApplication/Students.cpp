#include "stdafx.h"
#include "Students.h"
using namespace std;

Students::Students()
{
}

void Students::AddStudent()
{
	Student s = InputStudentInfo();
	cout << "\nSending Data to Server\n";
	string response;
	if (clientPipe.SendRequest(Serialize(s), response, "AddStudent"))
	{
		cout << "Data sent successfully\n";
		cout << "New Student Id is : " << response << "\n\n";

	}
	else
		cout << "Failed to send\n\n";
}
void Students::UpdateStudent()
{
	int id;
	cout << "Enter Id of student : ";
	cin >> id;
	Student s = InputStudentInfo();
	s.Id = id;
	cout << "\nSending Data to Server\n";
	string response;
	if (clientPipe.SendRequest(Serialize(s), response, "UpdateStudent"))
	{
		cout << "Data updated successfully\n";

	}
	else
		cout << "Failed to send\n\n";
}
void Students::DeleteStudent()
{
	Student s;
	cout << "Enter Id of student to delete : ";
	cin >> s.Id;
	
	string response;
	if (clientPipe.SendRequest(Serialize(s), response, "DeleteStudent"))
	{
		cout << "student deleted successfully\n";

	}
	else
		cout << "Failed to send\n\n";
}
void Students::ShowAllStudents() {
	// Get list from server
	string response;
	if (clientPipe.SendRequest("", response, "GetAllStudents"))
	{
		DeSerializeList(response);
		list <Student> ::iterator it;
		if (students.size() == 0)
			cout << "No record Found\n\n";
		else
		{
			cout << "       Following is the list of available students \n";
			for (it = students.begin(); it != students.end(); ++it)
				ShowStudentInfo(*it);
		}
	}
	else
		cout << "Failed to send request\n\n";
}

#pragma region Helper functions

Student Students::InputStudentInfo()
{
	Student student;
	cout << "Name : ";
	cin >> student.Name;
	cout << "Email : ";
	cin >> student.Email;
	cout << "Address : ";
	cin >> student.Address;
	return student;
}
void Students::ShowStudentInfo(Student student)
{
	cout << "Id : ";
	cout << student.Id << "\n";
	cout << "Name : ";
	cout << student.Name << "\n";
	cout << "Email : ";
	cout << student.Email << "\n";
	cout << "Address : ";
	cout << student.Address << "\n\n";
}


void Students::DeSerialize(string str, Student & s) {
	json j = json::parse(str);
	s.Id = j.at("Id").get<int>();
	s.Name = j.at("Name").get<string>();
	s.Email = j.at("Email").get<string>();
	s.Address = j.at("Address").get<string>();
}

string Students::Serialize(Student s) {
	json j;
	j["Id"] = s.Id;
	j["Name"] = s.Name;
	j["Email"] = s.Email;
	j["Address"] = s.Address;
	return j.dump();
}
void Students::DeSerializeList(string str)
{
	students.clear();
	list<string> listStr = json::parse(str);
	list <string> ::iterator it;
	for (it = listStr.begin(); it != listStr.end(); ++it)
	{
		Student s;
		DeSerialize(*it, s);
		students.push_back(s);
	}
}
#pragma endregion
Students::~Students()
{
}
