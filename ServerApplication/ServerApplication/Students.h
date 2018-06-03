#pragma once
#include"Student.h"
class Students
{
public:
	Students();
	string AddStudent(string request);
	string UpdateStudent(string request);
	string DeleteStudent(string request);
	string GetAllStudents();
	~Students();
private:
	static int count;
	static list <Student> students;
	void DeSerialize(string str, Student & s);
	string Serialize(Student s);
	string Students::SerializeList();
};

