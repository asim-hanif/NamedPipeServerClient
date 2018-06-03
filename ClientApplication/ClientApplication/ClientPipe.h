#pragma once
class ClientPipe
{
private:
	HANDLE hPipe;
	BOOL   fSuccess;
	DWORD  cbRead, cbToWrite, cbWritten, dwMode;
	LPTSTR lpszPipename;

	bool WriteToPipe(string request);
	bool ReadFromPipe(string & response, int buffSize);
	int GetBuffSize();
	bool SendBuffSize(int buffSize);
	bool SendActionName(string actionName);
	bool ChangeToReadMode();
	bool Connect();
public:
	ClientPipe();
	bool SendRequest(string request, string & response, string actionName);
	~ClientPipe();
};

