#pragma once
class Route
{
private:
	static bool IsActionNameEqualTo(string actionName, string str);
public:
	Route();
	static string MapRoute(string actionName, string Request);
	~Route();
};

