#include "stdafx.h"
#include "Students.h"
using namespace std;

int Students::count = 0;
list <Student> Students::students;

Students::Students()
{
	
}
string Students::AddStudent(string request)
{
	Student s;
	DeSerialize(request, s);
	s.Id = ++count;
	students.push_back(s);
	return (to_string(s.Id));
}

string Students::UpdateStudent(string request)
{
	Student s;
	DeSerialize(request, s);
	list <Student> ::iterator it;
	for (it = students.begin(); it != students.end(); ++it)
	{
		if (it->Id == s.Id)
		{
			it->Name = s.Name;
			it->Address = s.Address;
			it->Email = s.Email;
			break;
		}
	}
	return "";
}

string Students::DeleteStudent(string request)
{
	Student s;
	DeSerialize(request, s);
	list <Student> ::iterator it;
	for (it = students.begin(); it != students.end(); ++it)
	{
		if (it->Id == s.Id)
		{
			students.erase(it);
			break;
		}
	}
	return "";
}

string Students::GetAllStudents() 
{	
	return SerializeList();
}

#pragma region Helper functions

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

string Students::SerializeList() 
{
	list<string> listStr;
	list <Student> ::iterator it;
	for (it = students.begin(); it != students.end(); ++it)
		listStr.push_back(Serialize(*it));
	json j_list(listStr);
	return j_list.dump(1);
}

#pragma endregion
Students::~Students()
{
}
