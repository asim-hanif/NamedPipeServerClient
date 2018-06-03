#pragma once
#include"Student.h"
#include "ClientPipe.h"
class Students
{
public:
	Students();
	void AddStudent();
	void UpdateStudent();
	void DeleteStudent();
	void ShowAllStudents();
	void ShowStudentInfo(Student student);
	~Students();
private:
	Student InputStudentInfo();
	list <Student> students;
	void DeSerialize(string str, Student & s);
	string Serialize(Student s);
	void DeSerializeList(string str);
	ClientPipe clientPipe;
};

