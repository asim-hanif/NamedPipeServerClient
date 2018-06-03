// ServerApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ServerPIpe.h"

int main() 
{
	ServerPIpe server;
	server.Listen();
	return 0;
}
