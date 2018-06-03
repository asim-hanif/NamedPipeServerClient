#pragma once
class ServerPIpe
{
private:
	static DWORD WINAPI InstanceThread(LPVOID);
	static int GetBuffSize(HANDLE hPipe);
	static bool SendBuffSize(int buffSize, HANDLE hPipe);
	static bool WriteToPipe(string request, HANDLE hPipe);
	static bool ReadFromPipe(string & response, int buffSize, HANDLE hPipe);
	static string GetActionName(HANDLE hPipe);
public:
	ServerPIpe();
	static void Listen();
	~ServerPIpe();
};

