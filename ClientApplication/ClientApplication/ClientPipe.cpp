#include "stdafx.h"
#include "ClientPipe.h"


ClientPipe::ClientPipe()
{
	fSuccess = FALSE;
	cbRead, cbToWrite, cbWritten, dwMode;
	lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");
}

bool ClientPipe::Connect()
{
	while (1)
	{
		hPipe = CreateFile(
			lpszPipename,   // pipe name 
			GENERIC_READ |  // read and write access 
			GENERIC_WRITE,
			0,              // no sharing 
			NULL,           // default security attributes
			OPEN_EXISTING,  // opens existing pipe 
			0,              // default attributes 
			NULL);          // no template file 

							// Break if the pipe handle is valid. 

		if (hPipe != INVALID_HANDLE_VALUE)
			return true;

		// Exit if an error other than ERROR_PIPE_BUSY occurs. 

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			return false;
		}

		// All pipe instances are busy, so wait for 20 seconds. 

		if (!WaitNamedPipe(lpszPipename, 20000))
		{
			return false;
		}
	}
}

bool ClientPipe::ChangeToReadMode()
{
	dwMode = PIPE_READMODE_MESSAGE;
	fSuccess = SetNamedPipeHandleState(
		hPipe,    // pipe handle 
		&dwMode,  // new pipe mode 
		NULL,     // don't set maximum bytes 
		NULL);    // don't set maximum time 
	if (!fSuccess)
	{
		return false;
	}
	else
		return true;
}

bool ClientPipe::SendRequest(string request, string & response, string actionName)
{
	if (Connect() && ChangeToReadMode())
	{
		// first send buffer size and then send actual message
		if (SendActionName(actionName) && SendBuffSize(request.length()))
		{
			WriteToPipe(request);
			ReadFromPipe(response, GetBuffSize());
			CloseHandle(hPipe);
			return true;
		}
	}
	return false;
}

int  ClientPipe::GetBuffSize()
{
	string buffSize;
	return ReadFromPipe(buffSize, 10) ? stoi(buffSize) : 0;
}

bool ClientPipe::SendBuffSize(int buffSize)
{
	return WriteToPipe(to_string(buffSize));
}

bool ClientPipe::SendActionName(string actionName)
{
	return WriteToPipe(actionName);
}

bool ClientPipe::WriteToPipe(string request)
{
	cbToWrite = (request.length() + 1) * sizeof(char);

	fSuccess = WriteFile(
		hPipe,                  // pipe handle 
		request.c_str(),             // message 
		cbToWrite,              // message length 
		&cbWritten,             // bytes written 
		NULL);                  // not overlapped 

	if (!fSuccess)
	{
		return false;
	}
	return true;
}

bool ClientPipe::ReadFromPipe(string & response, int buffSize)
{
	char * chBuf = new char[buffSize];
	// Read from the pipe. 
	fSuccess = ReadFile(
		hPipe,    // pipe handle 
		chBuf,    // buffer to receive reply 
		buffSize * sizeof(char),  // size of buffer 
		&cbRead,  // number of bytes read 
		NULL);    // not overlapped 


	response.assign(chBuf, buffSize);

	if (!fSuccess)
	{
		return false;
	}
	return true;
}

ClientPipe::~ClientPipe()
{
}
