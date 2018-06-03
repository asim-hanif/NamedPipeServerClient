#include "stdafx.h"
#include "ServerPIpe.h"
#include "Route.h"


ServerPIpe::ServerPIpe()
{
	
}

void ServerPIpe::Listen()
{
	// The main loop creates an instance of the named pipe and 
	// then waits for a client to connect to it. When the client 
	// connects, a thread is created to handle communications 
	// with that client, and this loop is free to wait for the
	// next client connect request. It is an infinite loop.
	
	DWORD  dwThreadId = 0;
	HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;
	LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");
	int BuffSize = 1024;

	bool fConnected;
	for (;;)
	{
		_tprintf(TEXT("\nPipe Server: Main thread awaiting client connection on %s\n"), lpszPipename);
		hPipe = CreateNamedPipe(
			lpszPipename,             // pipe name 
			PIPE_ACCESS_DUPLEX,       // read/write access 
			PIPE_TYPE_MESSAGE |       // message type pipe 
			PIPE_READMODE_MESSAGE |   // message-read mode 
			PIPE_WAIT,                // blocking mode 
			PIPE_UNLIMITED_INSTANCES, // max. instances  
			BuffSize,                  // output buffer size 
			BuffSize,                  // input buffer size 
			0,                        // client time-out 
			NULL);                    // default security attribute 

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			return;
		}

		// Wait for the client to connect; if it succeeds, 
		// the function returns a nonzero value. If the function
		// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 

		fConnected = ConnectNamedPipe(hPipe, NULL) ?
			TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (fConnected)
		{
			printf("Client connected, creating a processing thread.\n");

			// Create a thread for this client. 
			hThread = CreateThread(
				NULL,              // no security attribute 
				0,                 // default stack size 
				InstanceThread,    // thread proc
				(LPVOID)hPipe,    // thread parameter 
				0,                 // not suspended 
				&dwThreadId);      // returns thread ID 

			if (hThread == NULL)
			{
				return;
			}
			else CloseHandle(hThread);
		}
		else
			// The client could not connect, so close the pipe. 
			CloseHandle(hPipe);
	}
}

DWORD WINAPI ServerPIpe::InstanceThread(LPVOID lpvParam)
// This routine is a thread processing function to read from and reply to a client
// via the open pipe connection passed from the main loop. Note this allows
// the main loop to continue executing, potentially creating more threads of
// of this procedure to run concurrently, depending on the number of incoming
// client connections.
{
	if (lpvParam == NULL)
	{
		return (DWORD)-1;
	}

	HANDLE hPipe = (HANDLE)lpvParam;
	Route route;
	
	string request, response, actionName;
	actionName = GetActionName(hPipe);
	ReadFromPipe(request, GetBuffSize(hPipe), hPipe);
	response = route.MapRoute(actionName, request);
	if (SendBuffSize(response.length(), hPipe))
		WriteToPipe(response, hPipe);

	// Flush the pipe to allow the client to read the pipe's contents 
	// before disconnecting. Then disconnect the pipe, and close the 
	// handle to this pipe instance. 

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}

int ServerPIpe::GetBuffSize(HANDLE hPipe)
{
	string buffSize;
	return ReadFromPipe(buffSize, 10, hPipe) ? stoi(buffSize) : 0;
}

bool ServerPIpe::SendBuffSize(int buffSize, HANDLE hPipe)
{
	return WriteToPipe(to_string(buffSize), hPipe);
}

string ServerPIpe::GetActionName(HANDLE hPipe)
{
	string actionName;
	return ReadFromPipe(actionName, 50, hPipe) ? actionName : "";
}

bool ServerPIpe::WriteToPipe(string response , HANDLE hPipe)
{
	DWORD cbToWrite = 0;
	cbToWrite = (response.length() + 1) * sizeof(char);
	// Write the reply to the pipe. 
	BOOL fSuccess = WriteFile(
		hPipe,        // handle to pipe 
		response.c_str(),     // buffer to write from 
		cbToWrite, // number of bytes to write 
		NULL,   // number of bytes written 
		NULL);        // not overlapped I/O 

	if (!fSuccess)
	{
		return false;		
	}
}

bool ServerPIpe::ReadFromPipe(string & request, int buffSize, HANDLE hPipe)
{
	char * chBuf = new char[buffSize];
	bool fSuccess = ReadFile(
		hPipe,        // handle to pipe 
		chBuf,		// buffer to receive data 
		buffSize * sizeof(TCHAR), // size of buffer 
		NULL, // number of bytes read 
		NULL);        // not overlapped I/O 

	if (!fSuccess)
	{
		return false;
	}	
	request.assign(chBuf, buffSize);
	return true;
}

ServerPIpe::~ServerPIpe()
{
}