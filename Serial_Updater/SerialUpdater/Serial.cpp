#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "serial.h"
#include <assert.h>
#include <sstream>

using namespace std;

#pragma warning (disable:4996)
char temp_cmd[50];

//----------------------------------------------------------------
CSyncSerialComm::CSyncSerialComm(const char *pszPortName) : m_hSerialComm(INVALID_HANDLE_VALUE)
{
	assert(pszPortName);

	m_pszPortName = new char[strlen(pszPortName)];
	strcpy(m_pszPortName, pszPortName);
}

CSyncSerialComm::~CSyncSerialComm()
{
	Close();
}

HRESULT CSyncSerialComm::Open()
{
	HRESULT hResult;

	m_hSerialComm = CreateFile(m_pszPortName,GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (m_hSerialComm == INVALID_HANDLE_VALUE)
	{
		unsigned long error = ::GetLastError();
		hResult = E_FAIL;
	}
	else
		hResult = S_OK;

	return hResult;
}

HRESULT CSyncSerialComm::Close()
{
	if (m_hSerialComm != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hSerialComm);
		m_hSerialComm = INVALID_HANDLE_VALUE;
	}

	return S_OK;
}

HRESULT CSyncSerialComm::ConfigPort(DWORD dwBaudRate, DWORD dwTimeOut)
{
	if (!SetupComm(m_hSerialComm, 1024, 1024))
		return E_FAIL;

	DCB dcbConfig;

	if (GetCommState(m_hSerialComm, &dcbConfig)) 
	{
		dcbConfig.BaudRate = dwBaudRate;
		dcbConfig.ByteSize = 8;
		dcbConfig.Parity = NOPARITY;
		dcbConfig.StopBits = ONESTOPBIT;
		dcbConfig.fBinary = TRUE;
		dcbConfig.fParity = TRUE;
	}

	else
		return E_FAIL;

	if (!SetCommState(m_hSerialComm, &dcbConfig))
		return E_FAIL;

	COMMTIMEOUTS commTimeout;

	if (GetCommTimeouts(m_hSerialComm, &commTimeout))
	{
		commTimeout.ReadIntervalTimeout = dwTimeOut;
		commTimeout.ReadTotalTimeoutConstant = dwTimeOut;
		commTimeout.ReadTotalTimeoutMultiplier = 0;
		commTimeout.WriteTotalTimeoutConstant = dwTimeOut;
		commTimeout.WriteTotalTimeoutMultiplier = 0;
	}

	else
		return E_FAIL;

	if (SetCommTimeouts(m_hSerialComm, &commTimeout))
		return S_OK;

	else
		return E_FAIL;
}

HRESULT CSyncSerialComm::Read(char *ppszBuf, DWORD &dwSize, DWORD max_size)
{
	HRESULT hResult = S_OK;
	DWORD csz=0;
	std::stringbuf sb;
	DWORD dwEventMask;

	ZeroMemory(ppszBuf, max_size);

	if (!SetCommMask(m_hSerialComm, EV_RXCHAR))
		return E_FAIL;

	if (WaitCommEvent(m_hSerialComm, &dwEventMask, NULL)) 
	{
		char szBuf;
		DWORD dwIncommingReadSize;

		do
		{
			if (ReadFile(m_hSerialComm, &szBuf, 1, &dwIncommingReadSize, NULL) != 0)
			{
				if (dwIncommingReadSize > 0)
				{
					ppszBuf[csz] = szBuf;
					csz++;
				}
			}

			else
			{
				unsigned long error = ::GetLastError();
				hResult = E_FAIL;
				break;
			}

		} while (dwIncommingReadSize > 0);

		dwSize = csz;
		return hResult;
	}

	else
		return E_FAIL;
}

HRESULT CSyncSerialComm::Write(const char *pszBuf, DWORD dwSize)
{
	HRESULT hResult = S_OK;
	unsigned long dwNumberOfBytesWritten;

	assert(pszBuf);
	unsigned long dwNumberOfBytesSent = 0;
	while (dwNumberOfBytesSent < dwSize)
	{
		if (WriteFile(m_hSerialComm, &pszBuf[dwNumberOfBytesSent], 1, &dwNumberOfBytesWritten, NULL) != 0)
		{
			if (dwNumberOfBytesWritten > 0)
				++dwNumberOfBytesSent;
			else
			{
				unsigned long error = ::GetLastError();
				hResult = E_FAIL;
				break;
			}
		}
		else
		{
			unsigned long error = ::GetLastError();
			hResult = E_FAIL;
			break;
		}
	}
	return hResult;
}

HRESULT CSyncSerialComm::Flush(DWORD dwFlag)
{
	if (PurgeComm(m_hSerialComm, dwFlag))
		return S_OK;
	else
		return E_FAIL;
}