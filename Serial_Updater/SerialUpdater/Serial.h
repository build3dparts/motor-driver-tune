#pragma once

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define BAUD_RATE 262500

#define LEFT 'L'
#define RIGHT 'R'
#define AUTO 'A'
#define MANUAL 'M'

#define MOVE "dir:%s!"
#define STEP "stepping:%s!"
#define STEP_R "stepsrev:%s!"
#define STEP_S "stepssec:%s!"
#define PWM_FR "pwmfrequ:%s!"
#define PWM_FA "pwmfacto:%s!"

extern char temp_cmd[50];
#define SEND_CMD(cmd,param) {sprintf(temp_cmd,cmd,param);serial.Write(temp_cmd,strlen(temp_cmd));}

class CSyncSerialComm
{
	public:
		HRESULT Flush(DWORD dwFlag = PURGE_TXCLEAR | PURGE_RXCLEAR);
		HRESULT Write(const char *pszBuf, DWORD dwSize);
		HRESULT Read(char *ppszBuf, DWORD &dwSize,DWORD max_size);
		HRESULT ConfigPort(DWORD dwBaudRate = CBR_19200, DWORD dwTimeOutInSec = 5);
		HRESULT Close();
		HRESULT Open();

		CSyncSerialComm(const char *pszPortName);
		virtual ~CSyncSerialComm();

	private:
		char *m_pszPortName;
		HANDLE m_hSerialComm;
};

#define MAX_BUF_SZ 65536*2
