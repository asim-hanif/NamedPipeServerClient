#include "stdafx.h"
#include "Route.h"
#include "Students.h";


Route::Route()
{

}
string Route::MapRoute(string actionName, string request)
{
	if (IsActionNameEqualTo(actionName ,"AddStudent"))
	{
		Students s;
		return s.AddStudent(request);
	}
	else if (IsActionNameEqualTo(actionName, "UpdateStudent"))
	{
		Students s;
		return s.UpdateStudent(request);
	}
	else if (IsActionNameEqualTo(actionName, "DeleteStudent"))
	{
		Students s;
		return s.DeleteStudent(request);
	}
	else if (IsActionNameEqualTo(actionName, "GetAllStudents"))
	{
		Students s;
		return s.GetAllStudents();
	}
}

bool Route::IsActionNameEqualTo(string actionName , string str)
{
	return !actionName.compare(0, actionName.find('\0'), str);
}
Route::~Route()
{
}
